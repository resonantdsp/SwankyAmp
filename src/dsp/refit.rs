//! Converts presets made on 1.4.0's octave-high tone stack to the corrected
//! one. `voice` voices the factory bank at the output on the guitar
//! recordings; it renders the whole amplifier for every candidate, so it
//! runs offline. `fit` converts imported 1.x user presets inside the plugin:
//! it fits the tone-stack seam on a synthetic pluck, which is fast enough to
//! run there but judges the stack rather than the output, so imported presets
//! can sound boxier than their originals.

use super::amp::{AmpControls, ClipKnee, CorrectedPath, LevelTables, SeamOutput, ToneMapping};
use super::mapping::AmpVoicing;
use super::tone_stack::ToneStack;
use crate::engine::doublings_for;

/// The host rate every refit measurement runs at, with Auto oversampling as
/// shipped.
pub const SAMPLE_RATE: u32 = 48_000;
const BLOCK: usize = 512;

/// Seed of the pluck's excitation noise. Changing it changes every result.
const PLUCK_SEED: u32 = 0x2450_7a11;
/// MIDI notes of the pluck, low E to high E across a guitar's range.
const PLUCK_NOTES: [u8; 8] = [40, 45, 50, 55, 59, 64, 71, 76];
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
const RESTRAINT: f64 = 2.;
const FIT_STEPS: [f32; 3] = [0.25, 0.05, 0.01];
const FIT_SPAN: [i32; 3] = [4, 5, 5];
/// Leftover drive change below which Power Drive is left alone.
const DRIVE_DEADBAND_DB: f64 = 0.5;
/// The most Power Drive may move, in control units.
const POWER_DRIVE_LIMIT: f32 = 0.15;

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
#[derive(Debug, Clone, Copy)]
struct Residual {
    shape_db: f64,
    level_db: f64,
}

impl Residual {
    fn error(self) -> f64 {
        self.shape_db.powi(2) + self.level_db.powi(2)
    }
}

/// The tone-stack seam of a render at `SAMPLE_RATE`.
fn render(controls: AmpControls, tone_mapping: ToneMapping, input: &[f32]) -> Banded {
    let doublings = doublings_for(0, f64::from(SAMPLE_RATE));
    let mut path = CorrectedPath::new(
        SAMPLE_RATE as f32,
        BLOCK,
        controls,
        doublings,
        tone_mapping,
        ClipKnee::UnitSlope,
        LevelTables::CALIBRATED,
    );
    let mut seams = SeamOutput::with_capacity(input.len() << doublings);
    let mut output = input.to_vec();
    for block in output.chunks_mut(BLOCK) {
        path.process_with_seams(block, &mut seams);
    }
    let internal = f64::from(SAMPLE_RATE) * path.factor() as f64;
    Banded::measure(&seams.tone_stack, internal)
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
/// tone stack's level change into the power stage.
fn fit_power_drive(controls: AmpControls, level_change_db: f64) -> AmpControls {
    if level_change_db.abs() <= DRIVE_DEADBAND_DB {
        return controls;
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
    let power_drive = if at(low) > target {
        low
    } else if at(high) < target {
        high
    } else {
        for _ in 0..40 {
            let middle = 0.5 * (low + high);
            if at(middle) < target {
                low = middle;
            } else {
                high = middle;
            }
        }
        0.5 * (low + high)
    };
    AmpControls {
        power_drive: (power_drive * 1000.).round() / 1000.,
        ..controls
    }
}

/// A 1.x preset converted for the corrected stack: Low, Mid, High and, where
/// the level into the power stage needs it, Power Drive move so the stack's
/// output on the pluck sounds roughly as it did; every other control is kept.
pub fn fit(controls: AmpControls, input: &[f32]) -> AmpControls {
    let tone_stack = render(controls, ToneMapping::Released, input);
    let internal_rate = SAMPLE_RATE as f32 * (1 << doublings_for(0, f64::from(SAMPLE_RATE))) as f32;
    let target = tone_stack.profile();
    let predictor = Predictor::new(tone_stack, controls, internal_rate);
    let toned = fit_tone(&predictor, &target, controls);
    let level_change = predictor.predict(toned).profile().against(&target).level_db;
    fit_power_drive(toned, level_change)
}

/// Sixth-octave bands from 80 Hz to 16 kHz, the range the factory voicing is
/// judged over. Bands this narrow keep a peak such as Presence's from
/// hiding in its neighbours.
const BANDS: usize = 47;
const BANDS_PER_OCTAVE: f64 = 6.;
/// The share of the recording's momentary-loudness blocks, loudest first,
/// whose balance the voicing matches: the strikes, where the ear judges a
/// tone, rather than the ring-out. They are picked on the recording itself,
/// where the player struck, because a driven preset's loudest blocks are its
/// sustained chord. Below 0.4 the single plucks drop out and only the strum
/// and the chord remain.
pub const STRIKE_FRACTION: f64 = 0.4;
/// The search keeps the tone controls within this, 1 to 9 on the panel, so a
/// preset leaves the player room either way.
pub const RAIL: f32 = 0.8;
/// Cost in dB² per dB² the power stage's feed misses 1.4.0's when Power
/// Drive runs out of range to restore it.
pub const FEED_COST: f64 = 0.5;
/// One step of the voicing grid in stored units: half a mark on the panel's
/// 0 to 10 scale. Finer settings are not a tone a player can tell apart.
pub const GRID_STEP: f32 = 0.1;
/// The least a step must lower the balance error, in dB, to be taken.
pub const RESOLUTION_DB: f64 = 0.1;

/// Band levels in dB about their mean, over `ranges` of the recording: the
/// tonal balance, not the level.
fn balance(samples: &[f32], sample_rate: f64, ranges: &[std::ops::Range<usize>]) -> [f64; BANDS] {
    let size = 16_384;
    let mut power = vec![0.; size / 2 + 1];
    for range in ranges {
        let part = &samples[range.start.min(samples.len())..range.end.min(samples.len())];
        for (total, value) in power.iter_mut().zip(power_spectrum(part, size)) {
            *total += value;
        }
    }
    let bin_hz = sample_rate / size as f64;
    let levels: [f64; BANDS] = std::array::from_fn(|band| {
        let centre = band_centre(band);
        let half = 2_f64.powf(0.5 / BANDS_PER_OCTAVE);
        let (low, high) = (centre / half, centre * half);
        let energy: f64 = power
            .iter()
            .enumerate()
            .filter(|(bin, _)| (low..high).contains(&(*bin as f64 * bin_hz)))
            .map(|(_, value)| value)
            .sum();
        10. * energy.max(1e-30).log10()
    });
    let mean = levels.iter().sum::<f64>() / BANDS as f64;
    levels.map(|level| level - mean)
}

fn band_centre(band: usize) -> f64 {
    80. * 2_f64.powf(band as f64 / BANDS_PER_OCTAVE)
}

/// The balance error in dB², from band differences averaged at the fourth
/// power: a narrow peak costs more than the same energy spread thin, where
/// a mean square would call a 2 dB peak cheap.
fn balance_error(balance: &[f64; BANDS], reference: &[f64; BANDS]) -> f64 {
    (balance
        .iter()
        .zip(reference)
        .map(|(value, target)| (value - target).powi(4))
        .sum::<f64>()
        / BANDS as f64)
        .sqrt()
}

fn level_db(samples: &[f32]) -> f64 {
    10. * (samples
        .iter()
        .map(|sample| f64::from(*sample).powi(2))
        .sum::<f64>()
        / samples.len() as f64)
        .log10()
}

/// Overlapping block ranges joined, so no stretch of the recording counts
/// twice.
fn merged(ranges: Vec<std::ops::Range<usize>>) -> Vec<std::ops::Range<usize>> {
    let mut joined: Vec<std::ops::Range<usize>> = Vec::new();
    for range in ranges {
        match joined.last_mut() {
            Some(last) if range.start <= last.end => last.end = last.end.max(range.end),
            _ => joined.push(range),
        }
    }
    joined
}

/// One recording through a path: its output balance over the whole
/// recording and at the strikes, the level it feeds the power stage and the
/// tone-stack seam's power spectrum.
struct Heard {
    whole: [f64; BANDS],
    strike: [f64; BANDS],
    feed_db: f64,
    seam: Vec<f64>,
    seam_rate: f64,
}

const SEAM_WINDOW: usize = 16_384;

fn hear(
    controls: AmpControls,
    legacy: bool,
    clip: &[f32],
    strikes: &[std::ops::Range<usize>],
) -> Heard {
    let rate = super::calibration::SAMPLE_RATE;
    let mut seams = SeamOutput::with_capacity(clip.len() * 2);
    let mut audio = clip.to_vec();
    let factor = if legacy {
        let mut path = super::amp::AmpPath::new_legacy(rate as f32, controls);
        for block in audio.chunks_mut(BLOCK) {
            path.process_with_seams(block, &mut seams);
        }
        1
    } else {
        let mut path = CorrectedPath::shipping(
            rate as f32,
            BLOCK,
            controls,
            doublings_for(0, f64::from(rate)),
        );
        for block in audio.chunks_mut(BLOCK) {
            path.process_with_seams(block, &mut seams);
        }
        path.factor()
    };
    Heard {
        whole: balance(
            &audio,
            f64::from(rate),
            std::slice::from_ref(&(0..audio.len())),
        ),
        strike: balance(&audio, f64::from(rate), strikes),
        feed_db: level_db(&seams.power_input),
        seam: if legacy {
            Vec::new()
        } else {
            power_spectrum(&seams.tone_stack, SEAM_WINDOW)
        },
        seam_rate: f64::from(rate) * factor as f64,
    }
}

/// The level change a tone setting makes at the tone-stack seam, predicted
/// from the seam at the original setting: the stack is linear and nothing
/// before it depends on its controls.
fn seam_change_db(heard: &Heard, original: AmpControls, candidate: AmpControls) -> f64 {
    let stack = |controls: AmpControls| {
        let mut stack = ToneStack::new(heard.seam_rate as f32, ToneMapping::Standard);
        stack.configure(AmpVoicing::from_controls(controls).tone);
        stack
    };
    let (before, after) = (stack(original), stack(candidate));
    let bin_hz = heard.seam_rate / SEAM_WINDOW as f64;
    let (mut old, mut new) = (0., 0.);
    for (bin, power) in heard.seam.iter().enumerate().skip(1) {
        let frequency = bin as f64 * bin_hz;
        let ratio = after.response(frequency).norm_squared()
            / before.response(frequency).norm_squared().max(1e-300);
        old += power;
        new += power * ratio;
    }
    10. * (new / old).log10()
}

/// A stored value's position on the voicing grid, in steps from -1.
fn grid_index(value: f32) -> f64 {
    f64::from((value + 1.) / GRID_STEP)
}

fn grid_value(index: i32) -> f32 {
    (f64::from(index) * f64::from(GRID_STEP) - 1.) as f32
}

/// The grid values either side of `value`, or the one it sits on.
fn neighbours(value: f32, lowest: i32, highest: i32) -> Vec<i32> {
    let index = grid_index(value);
    let mut indices = if (index - index.round()).abs() < 1e-3 {
        vec![index.round() as i32]
    } else {
        vec![index.floor() as i32, index.ceil() as i32]
    };
    for index in &mut indices {
        *index = (*index).clamp(lowest, highest);
    }
    indices.dedup();
    indices
}

/// Power Drive that brings the power stage's feed back by `change_db`: the
/// exact setting within the control's range, the grid value nearest it in
/// gain, and the dB the exact setting still misses by.
fn power_drive_for(controls: AmpControls, change_db: f64) -> (f32, f32, f64) {
    let target = power_gain_db(controls) + change_db;
    let at = |power_drive: f32| {
        power_gain_db(AmpControls {
            power_drive,
            ..controls
        })
    };
    let (mut low, mut high) = (-1_f32, 1_f32);
    for _ in 0..40 {
        let middle = 0.5 * (low + high);
        if at(middle) < target {
            low = middle;
        } else {
            high = middle;
        }
    }
    let exact = (0.5 * (low + high) * 1000.).round() / 1000.;
    let full = grid_index(1.) as i32;
    let on_grid = neighbours(exact, 0, full)
        .into_iter()
        .map(grid_value)
        .min_by(|a, b| (target - at(*a)).abs().total_cmp(&(target - at(*b)).abs()))
        .expect("a grid value is always near");
    (exact, on_grid, target - at(exact))
}

/// The four tone controls the voicing moves, plus Power Drive, which follows
/// them to keep the power stage's feed.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Voicing {
    pub low: f32,
    pub mid: f32,
    pub high: f32,
    pub presence: f32,
    pub power_drive: f32,
}

impl Voicing {
    pub fn of(controls: AmpControls) -> Self {
        Self {
            low: controls.low,
            mid: controls.mid,
            high: controls.high,
            presence: controls.presence,
            power_drive: controls.power_drive,
        }
    }

    pub fn apply(self, controls: AmpControls) -> AmpControls {
        AmpControls {
            low: self.low,
            mid: self.mid,
            high: self.high,
            presence: self.presence,
            power_drive: self.power_drive,
            ..controls
        }
    }

    fn tone(self) -> [f32; 4] {
        [self.low, self.mid, self.high, self.presence]
    }

    fn with_tone(self, tone: [f32; 4]) -> Self {
        Self {
            low: tone[0],
            mid: tone[1],
            high: tone[2],
            presence: tone[3],
            ..self
        }
    }
}

/// How a setting compares with 1.4.0 on each recording (single coil,
/// humbucker).
#[derive(Debug, Clone, Copy)]
pub struct Comparison {
    /// Band difference from 1.4.0's balance at the strikes, in dB, as the
    /// voicing weighs it.
    pub strike_db: [f64; 2],
    /// The same over the whole recording.
    pub whole_db: [f64; 2],
    /// The power stage's feed minus 1.4.0's, in dB.
    pub feed_db: [f64; 2],
}

/// A preset voiced for the corrected stack: its settings and how far each
/// is from 1.4.0 on the recordings.
#[derive(Debug, Clone)]
pub struct Voiced {
    pub original: Voicing,
    /// The bank being replaced, or the 1.4.0 settings without one.
    pub current: Voicing,
    pub voiced: Voicing,
    /// Power Drive that restores the feed exactly for the voiced tone,
    /// before it is put on the grid.
    pub exact_power_drive: f32,
    pub current_comparison: Comparison,
    pub voiced_comparison: Comparison,
    /// The feed with `exact_power_drive`, minus 1.4.0's.
    pub exact_feed_db: [f64; 2],
    /// Voiced output band levels minus 1.4.0's at the strikes and over the
    /// whole recording, averaged over the recordings.
    pub strike_bands_db: [f64; BANDS],
    pub whole_bands_db: [f64; BANDS],
    /// RMS difference in dB between the bank's band differences at the
    /// strikes and over the whole recording: how far the two pictures
    /// disagree.
    pub picture_gap_db: f64,
}

/// Band centres of `Voiced::strike_bands_db`, in Hz.
pub fn band_centres() -> [f64; BANDS] {
    std::array::from_fn(band_centre)
}

struct Trial {
    voicing: Voicing,
    exact_power_drive: f32,
    heard: [Heard; 2],
    cost: f64,
}

impl Trial {
    fn score(&self) -> f64 {
        self.cost.sqrt()
    }
}

/// Voices `controls`, a preset made on 1.4.0's octave-high stack, for the
/// corrected one on a grid of half panel marks. `current` is the voicing
/// already accepted by ear, the starting point; without it the 1.4.0
/// settings are. Low, Mid, High and Presence start on whichever
/// neighbouring grid values match 1.4.0's balance at the strikes best, then
/// move a step at a time while a step improves it by `RESOLUTION_DB`.
/// Power Drive follows every setting so the power stage is driven as 1.4.0
/// drove it.
pub fn voice(
    controls: AmpControls,
    current: Option<Voicing>,
    clips: &super::calibration::Clips,
) -> Voiced {
    let clips = [clips.single_coil.as_slice(), clips.humbucker.as_slice()];
    let strikes =
        clips.map(|clip| merged(super::calibration::loudest_blocks(clip, STRIKE_FRACTION)));
    let reference =
        std::array::from_fn::<_, 2, _>(|index| hear(controls, true, clips[index], &strikes[index]));
    let unvoiced = std::array::from_fn::<_, 2, _>(|index| {
        hear(controls, false, clips[index], &strikes[index])
    });
    let original = Voicing::of(controls);
    let current = current.unwrap_or(original);
    let heard = |voicing: Voicing| {
        std::array::from_fn::<_, 2, _>(|index| {
            hear(
                voicing.apply(controls),
                false,
                clips[index],
                &strikes[index],
            )
        })
    };
    let compare = |heard: &[Heard; 2]| {
        let each = |error: &dyn Fn(usize) -> f64| std::array::from_fn(error);
        Comparison {
            strike_db: each(&|index| {
                balance_error(&heard[index].strike, &reference[index].strike).sqrt()
            }),
            whole_db: each(&|index| {
                balance_error(&heard[index].whole, &reference[index].whole).sqrt()
            }),
            feed_db: each(&|index| heard[index].feed_db - reference[index].feed_db),
        }
    };
    let trial = |tone: [i32; 4]| {
        let tone = tone.map(grid_value);
        let candidate = original.with_tone(tone).apply(controls);
        let change = (0..2)
            .map(|index| {
                reference[index].feed_db
                    - unvoiced[index].feed_db
                    - seam_change_db(&unvoiced[index], controls, candidate)
            })
            .sum::<f64>()
            / 2.;
        let (exact_power_drive, power_drive, miss) = power_drive_for(candidate, change);
        // The tone is judged with the feed restored exactly, so the choice
        // between tones does not ride on where Power Drive's grid falls.
        let heard = heard(Voicing {
            power_drive: exact_power_drive,
            ..original.with_tone(tone)
        });
        let voicing = Voicing {
            power_drive,
            ..original.with_tone(tone)
        };
        let sound = (0..2)
            .map(|index| balance_error(&heard[index].strike, &reference[index].strike))
            .sum::<f64>()
            / 2.;
        Trial {
            voicing,
            exact_power_drive,
            heard,
            cost: sound + FEED_COST * miss.powi(2),
        }
    };
    let rail = grid_index(RAIL).round() as i32;
    let floor = grid_index(-RAIL).round() as i32;
    let starts: Vec<Vec<i32>> = current
        .tone()
        .iter()
        .map(|&value| neighbours(value, floor, rail))
        .collect();
    let mut rounded: Vec<([i32; 4], Trial)> = Vec::new();
    for &low in &starts[0] {
        for &mid in &starts[1] {
            for &high in &starts[2] {
                for &presence in &starts[3] {
                    let tone = [low, mid, high, presence];
                    rounded.push((tone, trial(tone)));
                }
            }
        }
    }
    // Among roundings the ear cannot tell apart, the one off the rails and
    // nearest 1.4.0's settings.
    let best_score = rounded
        .iter()
        .map(|(_, trial)| trial.score())
        .fold(f64::INFINITY, f64::min);
    let origin = original.tone().map(grid_index);
    let preference = |tone: &[i32; 4]| {
        let on_rails = tone
            .iter()
            .filter(|&&index| index == rail || index == floor)
            .count();
        let distance: f64 = tone
            .iter()
            .zip(origin)
            .map(|(&index, target)| (f64::from(index) - target).abs())
            .sum();
        (on_rails, distance)
    };
    let (mut tone, mut best) = rounded
        .into_iter()
        .filter(|(_, trial)| trial.score() <= best_score + RESOLUTION_DB)
        .min_by(|(a, _), (b, _)| {
            let (a, b) = (preference(a), preference(b));
            a.0.cmp(&b.0).then(a.1.total_cmp(&b.1))
        })
        .expect("at least one rounding");
    loop {
        let mut step: Option<([i32; 4], Trial)> = None;
        for control in 0..4 {
            for direction in [-1, 1] {
                let mut next = tone;
                next[control] += direction;
                if !(floor..=rail).contains(&next[control]) {
                    continue;
                }
                let candidate = trial(next);
                let bar = step
                    .as_ref()
                    .map_or(best.score() - RESOLUTION_DB, |(_, trial)| trial.score());
                if candidate.score() <= bar {
                    step = Some((next, candidate));
                }
            }
        }
        let Some((next, trial)) = step else {
            break;
        };
        tone = next;
        best = trial;
    }
    // A control left on a rail comes a step in where that is as good.
    for control in 0..4 {
        let inward = match tone[control] {
            index if index == rail => index - 1,
            index if index == floor => index + 1,
            _ => continue,
        };
        let mut next = tone;
        next[control] = inward;
        let candidate = trial(next);
        if candidate.score() <= best.score() + RESOLUTION_DB {
            tone = next;
            best = candidate;
        }
    }
    let exact = best.heard;
    let voiced = heard(best.voicing);
    let current_heard = heard(current);
    let bands = |pick: &dyn Fn(&Heard) -> &[f64; BANDS]| {
        std::array::from_fn(|band| {
            (0..2)
                .map(|index| pick(&voiced[index])[band] - pick(&reference[index])[band])
                .sum::<f64>()
                / 2.
        })
    };
    let picture_gap_db = ((0..2)
        .map(|index| {
            (0..BANDS)
                .map(|band| {
                    let strike = current_heard[index].strike[band] - reference[index].strike[band];
                    let whole = current_heard[index].whole[band] - reference[index].whole[band];
                    (strike - whole).powi(2)
                })
                .sum::<f64>()
                / BANDS as f64
        })
        .sum::<f64>()
        / 2.)
        .sqrt();
    Voiced {
        original,
        current,
        voiced: best.voicing,
        exact_power_drive: best.exact_power_drive,
        current_comparison: compare(&current_heard),
        voiced_comparison: compare(&voiced),
        exact_feed_db: std::array::from_fn(|index| exact[index].feed_db - reference[index].feed_db),
        strike_bands_db: bands(&|heard| &heard.strike),
        whole_bands_db: bands(&|heard| &heard.whole),
        picture_gap_db,
    }
}
