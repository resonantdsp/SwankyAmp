//! Refits factory presets from the released octave-high tone mapping to the
//! standard one. The aim is that each preset sounds roughly as it did, not a
//! dB-exact replica: chasing exactness drives Low/Mid/High to their limits,
//! so the objective weighs broad spectral shape and the level into the power
//! stage together and the residuals are reported rather than forced to zero.

use serde::{Deserialize, Serialize};

use super::amp::{AmpControls, ClipKnee, CorrectedPath, SeamOutput, ToneMapping};
use super::mapping::AmpVoicing;
use super::tone_stack::ToneStack;
use crate::engine::doublings_for;

/// The host rate every refit measurement runs at, with Auto oversampling as
/// shipped.
pub const SAMPLE_RATE: u32 = 48_000;
const BLOCK: usize = 512;

/// Seed of the pluck's excitation noise. Changing it changes every result.
pub const PLUCK_SEED: u32 = 0x2450_7a11;
/// MIDI notes of the pluck, low E to high E across a guitar's range.
pub const PLUCK_NOTES: [u8; 8] = [40, 45, 50, 55, 59, 64, 71, 76];
const NOTE_SECONDS: f32 = 0.5;
const PLUCK_PEAK: f32 = 0.17;

const POINTS: usize = 48;
const LOW_HZ: f64 = 80.;
const HIGH_HZ: f64 = 8_000.;
const SUB_BANDS: usize = 4;
const OUTER_BANDS_PER_OCTAVE: f64 = 24.;

/// Cost in dB² of moving Low, Mid or High by a whole control range, so a
/// control moves only as far as the sound improvement pays for. Without it
/// the fit trades fractions of a dB for Mid near its maximum on most presets.
pub const RESTRAINT: f64 = 2.;
const FIT_STEPS: [f32; 3] = [0.25, 0.05, 0.01];
const FIT_SPAN: [i32; 3] = [4, 5, 5];
/// Leftover drive change below which Power Drive is left alone.
pub const DRIVE_DEADBAND_DB: f64 = 0.5;
/// The most Power Drive may move, in control units.
pub const POWER_DRIVE_LIMIT: f32 = 0.15;

/// A deterministic Karplus-Strong pluck, one decaying note per pitch in
/// `PLUCK_NOTES`, peaking near the level of the reference single-coil DI.
pub fn pluck(sample_rate: u32) -> Vec<f32> {
    let mut state = PLUCK_SEED;
    let mut noise = move || {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        state as f32 / u32::MAX as f32 * 2. - 1.
    };
    let note_frames = (NOTE_SECONDS * sample_rate as f32) as usize;
    let mut output = Vec::with_capacity(note_frames * PLUCK_NOTES.len());
    for note in PLUCK_NOTES {
        let frequency = 440. * 2_f32.powf((f32::from(note) - 69.) / 12.);
        let period = (sample_rate as f32 / frequency).round() as usize;
        // A one-pole low-pass on the burst stands in for pick and pickup.
        let mut previous = 0.;
        let mut line: Vec<f32> = (0..period)
            .map(|_| {
                previous = 0.5 * noise() + 0.5 * previous;
                previous
            })
            .collect();
        let start = output.len();
        for frame in 0..note_frames {
            let index = frame % period;
            let next = line[(index + 1) % period];
            let sample = line[index];
            line[index] = 0.996 * 0.5 * (sample + next);
            output.push(sample);
        }
        let peak = output[start..]
            .iter()
            .fold(0_f32, |peak, x| peak.max(x.abs()));
        for sample in &mut output[start..] {
            *sample *= PLUCK_PEAK / peak;
        }
    }
    output
}

fn fft(real: &mut [f64], imaginary: &mut [f64]) {
    let size = real.len();
    let mut target = 0;
    for index in 1..size {
        let mut bit = size >> 1;
        while target & bit != 0 {
            target ^= bit;
            bit >>= 1;
        }
        target |= bit;
        if index < target {
            real.swap(index, target);
            imaginary.swap(index, target);
        }
    }
    let mut length = 2;
    while length <= size {
        let angle = -std::f64::consts::TAU / length as f64;
        for start in (0..size).step_by(length) {
            for offset in 0..length / 2 {
                let (sin, cos) = (angle * offset as f64).sin_cos();
                let (a, b) = (start + offset, start + offset + length / 2);
                let (re, im) = (
                    real[b] * cos - imaginary[b] * sin,
                    real[b] * sin + imaginary[b] * cos,
                );
                real[b] = real[a] - re;
                imaginary[b] = imaginary[a] - im;
                real[a] += re;
                imaginary[a] += im;
            }
        }
        length <<= 1;
    }
}

/// Welch power spectrum with Hann windows at half overlap; scaling is
/// arbitrary but shared, since only differences between renders are used.
fn power_spectrum(samples: &[f32], size: usize) -> Vec<f64> {
    let window: Vec<f64> = (0..size)
        .map(|index| 0.5 - 0.5 * (std::f64::consts::TAU * index as f64 / size as f64).cos())
        .collect();
    let mut power = vec![0.; size / 2 + 1];
    let mut start = 0;
    while start + size <= samples.len() {
        let mut real: Vec<f64> = samples[start..start + size]
            .iter()
            .zip(&window)
            .map(|(sample, weight)| f64::from(*sample) * weight)
            .collect();
        let mut imaginary = vec![0.; size];
        fft(&mut real, &mut imaginary);
        for (bin, value) in power.iter_mut().enumerate() {
            *value += real[bin] * real[bin] + imaginary[bin] * imaginary[bin];
        }
        start += size / 2;
    }
    power
}

/// The analysis frequencies: `POINTS` log-spaced from 80 Hz to 8 kHz.
fn points() -> [f64; POINTS] {
    std::array::from_fn(|index| {
        LOW_HZ * (HIGH_HZ / LOW_HZ).powf(index as f64 / (POINTS - 1) as f64)
    })
}

#[derive(Debug, Clone, Copy)]
struct Band {
    low: f64,
    high: f64,
    point: Option<usize>,
}

impl Band {
    fn centre(self) -> f64 {
        (self.low.max(1.) * self.high).sqrt()
    }
}

/// Bands covering DC to Nyquist: each analysis point owns `SUB_BANDS` equal
/// log slices of its own band, and the rest counts only toward level.
fn bands(nyquist: f64) -> Vec<Band> {
    let ratio = (HIGH_HZ / LOW_HZ).powf(1. / (POINTS - 1) as f64);
    let lowest = LOW_HZ / ratio.sqrt();
    let highest = HIGH_HZ * ratio.sqrt();
    let outer = 2_f64.powf(1. / OUTER_BANDS_PER_OCTAVE);
    let mut bands = vec![Band {
        low: 0.,
        high: 20.,
        point: None,
    }];
    let mut edge = 20.;
    while edge * outer < lowest {
        bands.push(Band {
            low: edge,
            high: edge * outer,
            point: None,
        });
        edge *= outer;
    }
    bands.push(Band {
        low: edge,
        high: lowest,
        point: None,
    });
    for (index, point) in points().into_iter().enumerate() {
        for slice in 0..SUB_BANDS {
            let step = ratio.powf(1. / SUB_BANDS as f64);
            let low = point / ratio.sqrt() * step.powi(slice as i32);
            bands.push(Band {
                low,
                high: low * step,
                point: Some(index),
            });
        }
    }
    let mut edge = highest;
    while edge < nyquist {
        let high = (edge * outer).min(nyquist + 1.);
        bands.push(Band {
            low: edge,
            high,
            point: None,
        });
        edge = high;
    }
    bands
}

/// Power per band of one render, and its measurement grid.
#[derive(Debug, Clone)]
struct Banded {
    bands: Vec<Band>,
    energy: Vec<f64>,
}

impl Banded {
    fn measure(samples: &[f32], sample_rate: f64) -> Self {
        let size = (sample_rate / 3.).max(1.) as usize;
        let size = size.next_power_of_two();
        let power = power_spectrum(samples, size);
        let bin_hz = sample_rate / size as f64;
        let bands = bands(sample_rate / 2.);
        let mut energy = vec![0.; bands.len()];
        let mut band = 0;
        for (bin, value) in power.iter().enumerate() {
            let frequency = bin as f64 * bin_hz;
            while band + 1 < bands.len() && frequency >= bands[band].high {
                band += 1;
            }
            energy[band] += value;
        }
        Self { bands, energy }
    }

    fn with_energy(&self, energy: Vec<f64>) -> Self {
        Self {
            bands: self.bands.clone(),
            energy,
        }
    }

    fn profile(&self) -> Profile {
        let mut shape = [0.; POINTS];
        for (band, energy) in self.bands.iter().zip(&self.energy) {
            if let Some(point) = band.point {
                shape[point] += energy;
            }
        }
        let shape = shape.map(|energy| 10. * energy.max(1e-30).log10());
        let mean = shape.iter().sum::<f64>() / POINTS as f64;
        Profile {
            shape: shape.map(|level| level - mean),
            level: 10. * self.energy.iter().sum::<f64>().max(1e-30).log10(),
        }
    }
}

/// A render's spectral shape (band dB about their mean) and total level.
#[derive(Debug, Clone, Copy)]
struct Profile {
    shape: [f64; POINTS],
    level: f64,
}

impl Profile {
    fn against(&self, reference: &Profile) -> Residual {
        let squared = self
            .shape
            .iter()
            .zip(&reference.shape)
            .map(|(value, target)| (value - target).powi(2))
            .sum::<f64>()
            / POINTS as f64;
        Residual {
            shape_db: squared.sqrt(),
            level_db: self.level - reference.level,
        }
    }
}

/// RMS difference of spectral shape in dB and signed level difference in dB.
#[derive(Debug, Clone, Copy, PartialEq, Serialize, Deserialize)]
pub struct Residual {
    pub shape_db: f64,
    pub level_db: f64,
}

impl Residual {
    fn error(self) -> f64 {
        self.shape_db.powi(2) + self.level_db.powi(2)
    }
}

/// The four controls the refit may move.
#[derive(Debug, Clone, Copy, PartialEq, Serialize, Deserialize)]
pub struct ToneSettings {
    pub low: f32,
    pub mid: f32,
    pub high: f32,
    pub power_drive: f32,
}

impl ToneSettings {
    fn of(controls: AmpControls) -> Self {
        Self {
            low: controls.low,
            mid: controls.mid,
            high: controls.high,
            power_drive: controls.power_drive,
        }
    }
}

/// One preset's fit and its before/after measurements, each against the
/// preset rendered with the released mapping.
#[derive(Debug, Clone, PartialEq, Serialize, Deserialize)]
pub struct PresetRefit {
    pub name: String,
    pub original: ToneSettings,
    pub refit: ToneSettings,
    /// The corrected mapping with the original controls.
    pub unrefit: Measurement,
    pub refitted: Measurement,
    pub limits: Vec<String>,
}

/// Residuals at the tone-stack seam and the output, plus the drive change
/// into the power stage (seam level with Power Drive's gain change).
#[derive(Debug, Clone, Copy, PartialEq, Serialize, Deserialize)]
pub struct Measurement {
    pub tone_stack: Residual,
    pub drive_db: f64,
    pub output: Residual,
}

struct Render {
    tone_stack: Banded,
    output: Banded,
}

fn render(controls: AmpControls, tone_mapping: ToneMapping, input: &[f32]) -> Render {
    let doublings = doublings_for(0, f64::from(SAMPLE_RATE));
    let mut path = CorrectedPath::new(
        SAMPLE_RATE as f32,
        BLOCK,
        controls,
        doublings,
        tone_mapping,
        ClipKnee::UnitSlope,
    );
    let mut seams = SeamOutput::with_capacity(input.len() << doublings);
    let mut output = input.to_vec();
    for block in output.chunks_mut(BLOCK) {
        path.process_with_seams(block, &mut seams);
    }
    let internal = f64::from(SAMPLE_RATE) * path.factor() as f64;
    Render {
        tone_stack: Banded::measure(&seams.tone_stack, internal),
        output: Banded::measure(&output, f64::from(SAMPLE_RATE)),
    }
}

fn power_gain_db(controls: AmpControls) -> f64 {
    20. * f64::from(AmpVoicing::from_controls(controls).power_gain).log10()
}

/// Predicts the tone-stack seam for other settings from the reference render:
/// the stack is linear and nothing before it depends on its controls.
struct Predictor {
    reference: Banded,
    reference_gain: Vec<f64>,
    internal_rate: f32,
}

impl Predictor {
    fn new(reference: Banded, controls: AmpControls, internal_rate: f32) -> Self {
        let reference_gain = Self::gain(
            &reference.bands,
            controls,
            ToneMapping::Released,
            internal_rate,
        );
        Self {
            reference,
            reference_gain,
            internal_rate,
        }
    }

    fn gain(
        bands: &[Band],
        controls: AmpControls,
        tone_mapping: ToneMapping,
        internal_rate: f32,
    ) -> Vec<f64> {
        let mut stack = ToneStack::new(internal_rate, tone_mapping);
        stack.configure(AmpVoicing::from_controls(controls).tone);
        bands
            .iter()
            .map(|band| stack.response(band.centre()).norm_squared())
            .collect()
    }

    fn predict(&self, controls: AmpControls) -> Banded {
        let gain = Self::gain(
            &self.reference.bands,
            controls,
            ToneMapping::Standard,
            self.internal_rate,
        );
        let energy = self
            .reference
            .energy
            .iter()
            .zip(gain.iter().zip(&self.reference_gain))
            .map(|(energy, (new, old))| energy * new / old.max(1e-300))
            .collect();
        self.reference.with_energy(energy)
    }
}

fn grid(centre: f32, step: f32, span: i32) -> Vec<f32> {
    let hundredths = (centre * 100.).round() as i32;
    let step = (step * 100.).round() as i32;
    let mut values: Vec<f32> = (-span..=span)
        .map(|offset| (hundredths + offset * step).clamp(-100, 100) as f32 / 100.)
        .collect();
    values.dedup();
    values
}

fn fit_tone(predictor: &Predictor, target: &Profile, controls: AmpControls) -> AmpControls {
    let error = |candidate: AmpControls| {
        let moved = [
            candidate.low - controls.low,
            candidate.mid - controls.mid,
            candidate.high - controls.high,
        ]
        .map(|change| f64::from(change).powi(2))
        .iter()
        .sum::<f64>();
        predictor
            .predict(candidate)
            .profile()
            .against(target)
            .error()
            + RESTRAINT * moved
    };
    let mut best = AmpControls {
        low: 0.,
        mid: 0.,
        high: 0.,
        ..controls
    };
    let mut best_error = f64::INFINITY;
    for (step, span) in FIT_STEPS.into_iter().zip(FIT_SPAN) {
        let centre = best;
        for low in grid(centre.low, step, span) {
            for mid in grid(centre.mid, step, span) {
                for high in grid(centre.high, step, span) {
                    let candidate = AmpControls {
                        low,
                        mid,
                        high,
                        ..controls
                    };
                    let candidate_error = error(candidate);
                    if candidate_error < best_error {
                        best = candidate;
                        best_error = candidate_error;
                    }
                }
            }
        }
    }
    best
}

/// Moves Power Drive, within `POWER_DRIVE_LIMIT`, so its gain cancels the
/// tone stack's level change into the power stage. Names the bound that
/// stopped it short, if any.
fn fit_power_drive(controls: AmpControls, level_change_db: f64) -> (AmpControls, Option<String>) {
    if level_change_db.abs() <= DRIVE_DEADBAND_DB {
        return (controls, None);
    }
    let original = controls.power_drive;
    let target = power_gain_db(controls) - level_change_db;
    let mut low = (original - POWER_DRIVE_LIMIT).max(-1.);
    let mut high = (original + POWER_DRIVE_LIMIT).min(1.);
    let at = |power_drive: f32| {
        power_gain_db(AmpControls {
            power_drive,
            ..controls
        })
    };
    let bound = |value: f32| {
        Some(if value.abs() >= 1. {
            format!("Power Drive {value:+}")
        } else {
            "Power Drive change cap".to_owned()
        })
    };
    let (power_drive, limit) = if at(low) > target {
        (low, bound(low))
    } else if at(high) < target {
        (high, bound(high))
    } else {
        for _ in 0..40 {
            let middle = 0.5 * (low + high);
            if at(middle) < target {
                low = middle;
            } else {
                high = middle;
            }
        }
        (0.5 * (low + high), None)
    };
    let controls = AmpControls {
        power_drive: (power_drive * 1000.).round() / 1000.,
        ..controls
    };
    (controls, limit)
}

fn measure(
    reference: &Render,
    render: &Render,
    original: AmpControls,
    controls: AmpControls,
) -> Measurement {
    let reference_seam = reference.tone_stack.profile();
    let tone_stack = render.tone_stack.profile().against(&reference_seam);
    Measurement {
        tone_stack,
        drive_db: tone_stack.level_db + power_gain_db(controls) - power_gain_db(original),
        output: render.output.profile().against(&reference.output.profile()),
    }
}

fn limits(refit: ToneSettings, power_drive: Option<String>) -> Vec<String> {
    [("Low", refit.low), ("Mid", refit.mid), ("High", refit.high)]
        .into_iter()
        .filter(|(_, value)| value.abs() >= 1.)
        .map(|(name, value)| format!("{name} {value:+}"))
        .chain(power_drive)
        .collect()
}

/// Fits one preset and measures it before and after through the full amp.
pub fn refit(name: &str, controls: AmpControls, input: &[f32]) -> PresetRefit {
    let reference = render(controls, ToneMapping::Released, input);
    let unrefit = render(controls, ToneMapping::Standard, input);
    let internal_rate = SAMPLE_RATE as f32 * (1 << doublings_for(0, f64::from(SAMPLE_RATE))) as f32;
    let target = reference.tone_stack.profile();
    let predictor = Predictor::new(reference.tone_stack.clone(), controls, internal_rate);
    let toned = fit_tone(&predictor, &target, controls);
    let level_change = predictor.predict(toned).profile().against(&target).level_db;
    let (fitted, power_drive_limit) = fit_power_drive(toned, level_change);
    let refitted = render(fitted, ToneMapping::Standard, input);
    let original = ToneSettings::of(controls);
    let refit = ToneSettings::of(fitted);
    PresetRefit {
        name: name.to_owned(),
        original,
        refit,
        unrefit: measure(&reference, &unrefit, controls, controls),
        refitted: measure(&reference, &refitted, controls, fitted),
        limits: limits(refit, power_drive_limit),
    }
}
