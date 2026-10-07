//! Voices presets made on 1.4.0's octave-high tone stack for the corrected
//! one. `voice` voices the factory bank at the output on the guitar
//! recordings; it renders the whole amplifier for every candidate, so it
//! runs offline. Imported 1.x presets take a fixed correction derived from
//! how this voicing moved the factory bank (`presets::convert_1x`).

use super::amp::{AmpControls, CorrectedPath, SeamOutput, ToneMapping};
use super::mapping::AmpVoicing;
use super::tone_stack::ToneStack;
use crate::engine::doublings_for;

const BLOCK: usize = 512;

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

fn power_gain_db(controls: AmpControls) -> f64 {
    20. * f64::from(AmpVoicing::from_controls(controls).power_gain).log10()
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
const GRID_STEP: f32 = 0.1;
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
    pub current_comparison: Comparison,
    pub voiced_comparison: Comparison,
    /// The feed with Power Drive off the grid, restoring it exactly for the
    /// voiced tone, minus 1.4.0's.
    pub exact_feed_db: [f64; 2],
    /// Voiced output band levels minus 1.4.0's at the strikes, averaged
    /// over the recordings.
    pub strike_bands_db: [f64; BANDS],
}

/// Band centres of `Voiced::strike_bands_db`, in Hz.
pub fn band_centres() -> [f64; BANDS] {
    std::array::from_fn(band_centre)
}

struct Trial {
    voicing: Voicing,
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
    Voiced {
        original,
        current,
        voiced: best.voicing,
        current_comparison: compare(&current_heard),
        voiced_comparison: compare(&voiced),
        exact_feed_db: std::array::from_fn(|index| exact[index].feed_db - reference[index].feed_db),
        strike_bands_db: std::array::from_fn(|band| {
            (0..2)
                .map(|index| voiced[index].strike[band] - reference[index].strike[band])
                .sum::<f64>()
                / 2.
        }),
    }
}
