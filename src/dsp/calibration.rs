//! Measures the shipping path's level compensation on the guitar recordings in
//! `verification/reference/input`, played as recorded at Input 0.
//!
//! The first stage makes real playing drive the power stage as 1.4.0 did. With
//! the tone controls at their defaults, the level into the power stage is
//! measured on the released path and the shipping path at every Drive table
//! point for each tone stack. The corrected stack passes a guitar a different
//! amount than the released one, differently for each stack and a little by
//! Drive, so the tone-stack scale takes the mean gap and the preamp table each
//! Drive point's departure from it. One scale serving three stacks leaves each
//! off by up to half their spread. The corrected Fender stack also passes more
//! of a humbucker's upper mids than 1.4.0's did, so its two pickups land either
//! side of the average; one gain cannot serve both. The power table then
//! normalises the power amp's output against Power Drive, transferred by the
//! ratio of the released to the shipping seam.
//!
//! The second stage holds loudness, which 1.4.0 let change as Drive and Power
//! Drive rose. Loudness is ITU-R BS.1770-4 gated integrated loudness, averaged
//! in LUFS over the two recordings, and the target is the factory defaults'
//! loudness from the first stage, so Init keeps its level. In order, each with
//! the values found so far in place: the power table is rescaled point by
//! point to the target, then an output gain against Drive, then one against
//! Grit, all applied after the cabinet so they change level and nothing else.
//! Stages stays uncompensated, as released. Every render starts from a settled
//! amplifier with the other controls at their defaults.

use super::amp::{
    AmpControls, AmpPath, ClipKnee, CorrectedPath, GRIT_COMPRESSION_LIMIT, LevelTables, SeamOutput,
    TABLE_POINTS, TONE_STACKS, ToneMapping,
};
use super::mapping::{AmpVoicing, drive_setting, power_drive_setting};
use crate::engine::doublings_for;

/// The host rate every calibration render runs at, with Auto oversampling.
pub const SAMPLE_RATE: u32 = 44_100;
const BLOCK: usize = 512;

/// Seam levels in dB of RMS, averaged over the recordings.
#[derive(Debug, Clone, Copy)]
struct Levels {
    power_input: f64,
    power_amp: f64,
    output: f64,
}

fn rms_db(samples: &[f32]) -> f64 {
    let sum: f64 = samples
        .iter()
        .map(|sample| f64::from(*sample) * f64::from(*sample))
        .sum();
    10. * (sum / samples.len() as f64).log10()
}

fn seam_levels(seams: &SeamOutput) -> Levels {
    Levels {
        power_input: rms_db(&seams.power_input),
        power_amp: rms_db(&seams.power_amp),
        output: rms_db(&seams.raw_output),
    }
}

fn averaged(each: impl Iterator<Item = Levels>) -> Levels {
    let each: Vec<Levels> = each.collect();
    let mean =
        |select: fn(&Levels) -> f64| each.iter().map(select).sum::<f64>() / each.len() as f64;
    Levels {
        power_input: mean(|levels| levels.power_input),
        power_amp: mean(|levels| levels.power_amp),
        output: mean(|levels| levels.output),
    }
}

/// The released path, which `just model-check` holds to the frozen 1.4.0
/// renders.
fn released(controls: AmpControls, clips: &Clips) -> Levels {
    averaged(clips.each().map(|clip| {
        let mut path = AmpPath::new_legacy(SAMPLE_RATE as f32, controls);
        let mut seams = SeamOutput::with_capacity(clip.len());
        let mut audio = clip.to_vec();
        for block in audio.chunks_mut(BLOCK) {
            path.process_with_seams(block, &mut seams);
        }
        seam_levels(&seams)
    }))
}

fn shipping_path(controls: AmpControls, tables: LevelTables) -> CorrectedPath {
    CorrectedPath::new(
        SAMPLE_RATE as f32,
        BLOCK,
        controls,
        doublings_for(0, f64::from(SAMPLE_RATE)),
        ToneMapping::Standard,
        ClipKnee::UnitSlope,
        tables,
    )
}

fn shipping(controls: AmpControls, clips: &Clips, tables: LevelTables) -> Levels {
    averaged(clips.each().map(|clip| {
        let mut path = shipping_path(controls, tables);
        let mut seams = SeamOutput::with_capacity(clip.len() * path.factor());
        let mut audio = clip.to_vec();
        for block in audio.chunks_mut(BLOCK) {
            path.process_with_seams(block, &mut seams);
        }
        seam_levels(&seams)
    }))
}

fn shipping_output(controls: AmpControls, clip: &[f32], tables: LevelTables) -> Vec<f32> {
    let mut path = shipping_path(controls, tables);
    let mut audio = clip.to_vec();
    for block in audio.chunks_mut(BLOCK) {
        path.process(block);
    }
    audio
}

/// The two recordings at `SAMPLE_RATE`, as recorded: the humbucker plays
/// about 8.7 dB hotter, and that difference is part of what is measured.
pub struct Clips {
    pub single_coil: Vec<f32>,
    pub humbucker: Vec<f32>,
}

impl Clips {
    pub fn new(single_coil_wav: &[u8], humbucker_wav: &[u8]) -> Result<Self, String> {
        Ok(Self {
            single_coil: clip(single_coil_wav)?,
            humbucker: clip(humbucker_wav)?,
        })
    }

    fn each(&self) -> impl Iterator<Item = &[f32]> {
        [self.single_coil.as_slice(), self.humbucker.as_slice()].into_iter()
    }
}

/// Loudness on each recording and their mean, in LUFS.
#[derive(Debug, Clone, Copy)]
pub struct Loudness {
    pub single_coil: f64,
    pub humbucker: f64,
}

impl Loudness {
    pub fn blend(self) -> f64 {
        (self.single_coil + self.humbucker) / 2.
    }
}

/// The shipping path's loudness with `tables` in place.
pub fn loudness(controls: AmpControls, clips: &Clips, tables: LevelTables) -> Loudness {
    Loudness {
        single_coil: integrated_loudness(&shipping_output(controls, &clips.single_coil, tables)),
        humbucker: integrated_loudness(&shipping_output(controls, &clips.humbucker, tables)),
    }
}

fn biquad(samples: &[f64], b: [f64; 3], a: [f64; 3]) -> Vec<f64> {
    let (mut x1, mut x2, mut y1, mut y2) = (0., 0., 0., 0.);
    samples
        .iter()
        .map(|&x| {
            let y = (b[0] * x + b[1] * x1 + b[2] * x2 - a[1] * y1 - a[2] * y2) / a[0];
            (x2, x1, y2, y1) = (x1, x, y1, y);
            y
        })
        .collect()
}

/// ITU-R BS.1770-4 integrated loudness of a mono signal at `SAMPLE_RATE`, in
/// LUFS: K-weighting, 400 ms blocks at 75 % overlap, the -70 LUFS absolute
/// gate and the -10 LU relative gate.
pub fn integrated_loudness(samples: &[f32]) -> f64 {
    let rate = f64::from(SAMPLE_RATE);
    let input: Vec<f64> = samples.iter().map(|&x| f64::from(x)).collect();
    // The standard's two stages, designed for any rate as in its annex.
    let (gain_db, q, fc) = (
        3.999_843_853_973_347,
        0.707_175_236_955_419_3,
        1_681.974_450_955_532,
    );
    let a = 10_f64.powf(gain_db / 40.);
    let w = std::f64::consts::TAU * fc / rate;
    let (cos, alpha) = (w.cos(), w.sin() / (2. * q));
    let root = 2. * a.sqrt() * alpha;
    let shelf = biquad(
        &input,
        [
            a * ((a + 1.) + (a - 1.) * cos + root),
            -2. * a * ((a - 1.) + (a + 1.) * cos),
            a * ((a + 1.) + (a - 1.) * cos - root),
        ],
        [
            (a + 1.) - (a - 1.) * cos + root,
            2. * ((a - 1.) - (a + 1.) * cos),
            (a + 1.) - (a - 1.) * cos - root,
        ],
    );
    let (q, fc) = (0.500_327_037_325_395_3, 38.135_470_876_139_82);
    let w = std::f64::consts::TAU * fc / rate;
    let (cos, alpha) = (w.cos(), w.sin() / (2. * q));
    let weighted = biquad(
        &shelf,
        [(1. + cos) / 2., -(1. + cos), (1. + cos) / 2.],
        [1. + alpha, -2. * cos, 1. - alpha],
    );
    let size = (0.4 * rate) as usize;
    let hop = size / 4;
    let blocks: Vec<f64> = (0..=weighted.len().saturating_sub(size) / hop)
        .map(|block| {
            let window = &weighted[block * hop..block * hop + size];
            window.iter().map(|x| x * x).sum::<f64>() / size as f64
        })
        .collect();
    let level = |power: f64| -0.691 + 10. * power.log10();
    let mean = |powers: &[f64]| powers.iter().sum::<f64>() / powers.len() as f64;
    let audible: Vec<f64> = blocks.into_iter().filter(|&p| level(p) > -70.).collect();
    if audible.is_empty() {
        return f64::NEG_INFINITY;
    }
    let relative = level(mean(&audible)) - 10.;
    let gated: Vec<f64> = audible
        .into_iter()
        .filter(|&p| level(p) > relative)
        .collect();
    level(mean(&gated))
}

fn table_point(index: usize) -> f32 {
    -1. + 2. * index as f32 / (TABLE_POINTS - 1) as f32
}

/// Seam levels at one measured point, in dB of RMS.
#[derive(Debug, Clone, Copy)]
pub struct Point {
    pub released_db: f64,
    pub shipping_db: f64,
}

impl Point {
    fn gap_db(self) -> f64 {
        self.released_db - self.shipping_db
    }
}

/// Shipping minus released level at the factory defaults, in dB, with the
/// measured compensation in place.
#[derive(Debug, Clone, Copy)]
pub struct Anchor {
    pub power_input_db: f64,
    pub power_amp_db: f64,
    pub output_db: f64,
    pub output_cabinet_off_db: f64,
}

#[derive(Debug, Clone)]
pub struct Calibration {
    pub tables: LevelTables,
    /// Power stage input per tone stack over the Drive sweep, before the
    /// compensation is measured.
    pub feed: [[Point; TABLE_POINTS]; TONE_STACKS],
    /// Power amp seam over the Power Drive sweep.
    pub power: [Point; TABLE_POINTS],
    /// The power table the first stage transferred, before loudness.
    pub power_transfer: [f32; TABLE_POINTS],
    /// The factory defaults' loudness the second stage holds.
    pub target: Loudness,
    /// Loudness at each table point before that table's gain is applied.
    pub power_loudness: [Loudness; TABLE_POINTS],
    pub drive_loudness: [Loudness; TABLE_POINTS],
    pub grit_loudness: [Loudness; TABLE_POINTS],
    pub anchor: Anchor,
}

/// Runs `job` over `inputs` on every available core, keeping order.
fn parallel<T: Sync, R: Send>(inputs: &[T], job: impl Fn(&T) -> R + Sync) -> Vec<R> {
    let workers = std::thread::available_parallelism().map_or(4, usize::from);
    let next = std::sync::atomic::AtomicUsize::new(0);
    let results = std::sync::Mutex::new(Vec::with_capacity(inputs.len()));
    std::thread::scope(|scope| {
        for _ in 0..workers.min(inputs.len()) {
            scope.spawn(|| {
                loop {
                    let index = next.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                    let Some(input) = inputs.get(index) else {
                        break;
                    };
                    let result = job(input);
                    results
                        .lock()
                        .expect("no job panicked")
                        .push((index, result));
                }
            });
        }
    });
    let mut results = results.into_inner().expect("no job panicked");
    results.sort_by_key(|(index, _)| *index);
    results.into_iter().map(|(_, result)| result).collect()
}

/// Loudness at every table point of the control `controls_at` sets.
fn sweep(
    clips: &Clips,
    tables: LevelTables,
    controls_at: impl Fn(usize) -> AmpControls + Sync,
) -> [Loudness; TABLE_POINTS] {
    let indices: Vec<usize> = (0..TABLE_POINTS).collect();
    let measured = parallel(&indices, |&index| {
        loudness(controls_at(index), clips, tables)
    });
    std::array::from_fn(|index| measured[index])
}

/// The gain that brings `measured` to `target`.
fn to_target(target: Loudness, measured: Loudness) -> f64 {
    10_f64.powf((target.blend() - measured.blend()) / 20.)
}

fn gain(gap_db: f64) -> f64 {
    10_f64.powf(gap_db / 20.)
}

fn mean(values: impl Iterator<Item = f64>) -> f64 {
    let values: Vec<f64> = values.collect();
    values.iter().sum::<f64>() / values.len() as f64
}

/// Measures the compensation on `clips`.
pub fn measure(clips: &Clips) -> Calibration {
    let defaults = AmpControls::default();
    let mut tables = LevelTables::RELEASED;

    let cells: Vec<AmpControls> = (0..TONE_STACKS)
        .flat_map(|stack| {
            (0..TABLE_POINTS).map(move |index| AmpControls {
                tone_stack: stack as f32,
                preamp_drive: drive_setting(table_point(index)),
                ..defaults
            })
        })
        .collect();
    let measured = parallel(&cells, |&controls| Point {
        released_db: released(controls, clips).power_input,
        shipping_db: shipping(controls, clips, tables).power_input,
    });
    let feed: [[Point; TABLE_POINTS]; TONE_STACKS] = std::array::from_fn(|stack| {
        std::array::from_fn(|index| measured[stack * TABLE_POINTS + index])
    });
    let overall = mean(feed.iter().flatten().map(|point| point.gap_db()));
    tables.tone_stack = (f64::from(tables.tone_stack) * gain(overall)) as f32;
    tables.preamp = std::array::from_fn(|index| {
        let drive_gap = mean(feed.iter().map(|row| row[index].gap_db())) - overall;
        (f64::from(tables.preamp[index]) * gain(drive_gap)) as f32
    });

    let indices: Vec<usize> = (0..TABLE_POINTS).collect();
    let power_controls = |index: usize| AmpControls {
        power_drive: power_drive_setting(table_point(index)),
        ..defaults
    };
    let power_points = parallel(&indices, |&index| Point {
        released_db: released(power_controls(index), clips).power_amp,
        shipping_db: shipping(power_controls(index), clips, tables).power_amp,
    });
    let power: [Point; TABLE_POINTS] = std::array::from_fn(|index| power_points[index]);
    tables.power = std::array::from_fn(|index| {
        (f64::from(tables.power[index]) * gain(power[index].gap_db())) as f32
    });
    let power_transfer = tables.power;
    tables.grit_compression = GRIT_COMPRESSION_LIMIT;

    let target = loudness(defaults, clips, tables);
    let power_loudness = sweep(clips, tables, power_controls);
    tables.power = std::array::from_fn(|index| {
        (f64::from(tables.power[index]) * to_target(target, power_loudness[index])) as f32
    });
    let drive_loudness = sweep(clips, tables, |index| AmpControls {
        preamp_drive: drive_setting(table_point(index)),
        ..defaults
    });
    tables.drive = std::array::from_fn(|index| to_target(target, drive_loudness[index]) as f32);
    // Loudness is not linear between table points, so the defaults can miss
    // the target they set by a few tenths of a dB. Scaling the two Drive
    // points either side of the default moves the default by exactly that
    // gain and keeps Init where it was.
    let miss = to_target(target, loudness(defaults, clips, tables)) as f32;
    let below = ((AmpVoicing::from_controls(defaults).preamp_drive + 1.) * 5.) as usize;
    tables.drive[below] *= miss;
    tables.drive[below + 1] *= miss;
    let grit_loudness = sweep(clips, tables, |index| AmpControls {
        preamp_grit: table_point(index),
        ..defaults
    });
    tables.grit = std::array::from_fn(|index| to_target(target, grit_loudness[index]) as f32);

    Calibration {
        tables,
        feed,
        power,
        power_transfer,
        target,
        power_loudness,
        drive_loudness,
        grit_loudness,
        anchor: anchor(clips, tables),
    }
}

/// How far the shipping path with `tables` lands from the released level at
/// the factory defaults.
pub fn anchor(clips: &Clips, tables: LevelTables) -> Anchor {
    let defaults = AmpControls::default();
    let reference = released(defaults, clips);
    let actual = shipping(defaults, clips, tables);
    let cabinet_off = AmpControls {
        cabinet_on: false,
        ..defaults
    };
    Anchor {
        power_input_db: actual.power_input - reference.power_input,
        power_amp_db: actual.power_amp - reference.power_amp,
        output_db: actual.output - reference.output,
        output_cabinet_off_db: shipping(cabinet_off, clips, tables).output
            - released(cabinet_off, clips).output,
    }
}

/// How far the shipping path feeds the power stage from 1.4.0 with
/// `controls`, in dB averaged over the recordings.
pub fn feed_gap_db(controls: AmpControls, clips: &Clips, tables: LevelTables) -> f64 {
    shipping(controls, clips, tables).power_input - released(controls, clips).power_input
}

/// Reads mono 24-bit PCM WAV and resamples it linearly to `SAMPLE_RATE`, as
/// the model comparison renders do.
pub fn clip(bytes: &[u8]) -> Result<Vec<f32>, String> {
    if bytes.get(0..4) != Some(b"RIFF") || bytes.get(8..12) != Some(b"WAVE") {
        return Err("clip is not a RIFF/WAVE file".into());
    }
    let chunk = |offset: usize| -> Option<(&[u8], &[u8])> {
        let id = bytes.get(offset..offset + 4)?;
        let size = u32::from_le_bytes(bytes.get(offset + 4..offset + 8)?.try_into().ok()?);
        Some((id, bytes.get(offset + 8..offset + 8 + size as usize)?))
    };
    let (mut offset, mut format, mut data) = (12, None, None);
    while let Some((id, body)) = chunk(offset) {
        if id == b"fmt " && body.len() >= 16 {
            let field = |at: usize| u16::from_le_bytes([body[at], body[at + 1]]);
            let rate = u32::from_le_bytes([body[4], body[5], body[6], body[7]]);
            format = Some((field(0), field(2), rate, field(14)));
        } else if id == b"data" {
            data = Some(body);
        }
        offset += 8 + body.len() + (body.len() & 1);
    }
    let (encoding, channels, rate, bits) = format.ok_or("clip has no format chunk")?;
    if (encoding, channels, bits) != (1, 1, 24) {
        return Err("clip must be mono 24-bit PCM".into());
    }
    let source: Vec<f32> = data
        .ok_or("clip has no data chunk")?
        .chunks_exact(3)
        .map(|sample| {
            (i32::from_le_bytes([0, sample[0], sample[1], sample[2]]) >> 8) as f32 / 8_388_608.
        })
        .collect();
    Ok(resample(&source, rate))
}

/// Linear interpolation from `rate` to `SAMPLE_RATE`.
fn resample(source: &[f32], rate: u32) -> Vec<f32> {
    let step = f64::from(rate) / f64::from(SAMPLE_RATE);
    let frames = (source.len() as f64 / step).round() as usize;
    (0..frames)
        .map(|frame| {
            let position = frame as f64 * step;
            let lower = position as usize;
            let upper = (lower + 1).min(source.len() - 1);
            let fraction = (position - lower as f64) as f32;
            source[lower] + fraction * (source[upper] - source[lower])
        })
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    fn recordings() -> Clips {
        Clips::new(
            include_bytes!("../../verification/reference/input/single-coil-plucks-strum-chord.wav"),
            include_bytes!("../../verification/reference/input/humbucker-plucks-strum-chord.wav"),
        )
        .expect("recordings read")
    }

    /// Drive, Power Drive and Grit change the sound, not the volume: their
    /// extremes keep the defaults' loudness averaged over the recordings.
    #[test]
    fn drive_power_drive_and_grit_extremes_keep_the_default_loudness() {
        const TOLERANCE_DB: f64 = 1.;
        let clips = recordings();
        let defaults = AmpControls::default();
        let cases: Vec<(&str, f32, AmpControls)> = [-1., 1.]
            .into_iter()
            .flat_map(|extreme| {
                [
                    (
                        "Drive",
                        extreme,
                        AmpControls {
                            preamp_drive: extreme,
                            ..defaults
                        },
                    ),
                    (
                        "Power Drive",
                        extreme,
                        AmpControls {
                            power_drive: extreme,
                            ..defaults
                        },
                    ),
                    (
                        "Grit",
                        extreme,
                        AmpControls {
                            preamp_grit: extreme,
                            ..defaults
                        },
                    ),
                ]
            })
            .chain([("Init", 0., defaults)])
            .collect();
        let measured = parallel(&cases, |(_, _, controls)| {
            loudness(*controls, &clips, LevelTables::CALIBRATED).blend()
        });
        let target = measured[cases.len() - 1];
        for ((control, extreme, _), level) in cases.iter().zip(&measured) {
            let change = level - target;
            assert!(
                change.abs() <= TOLERANCE_DB,
                "{control} at {extreme:+} moves loudness {change:+.2} dB \
                 (tolerance {TOLERANCE_DB} dB)"
            );
        }
    }

    /// With the tone controls at their defaults, real playing drives the
    /// power stage as 1.4.0 did on every tone stack, clean to full Drive.
    /// One tone-stack scale serves three stacks whose gaps to 1.4.0 lie
    /// within about 2 dB of each other, so each may sit up to half that
    /// spread from 1.4.0; the limit adds 0.5 dB for Drive's smaller part.
    #[test]
    fn default_tone_drives_the_power_stage_as_released() {
        const TOLERANCE_DB: f64 = 1. + 0.5;
        let clips = recordings();
        let cells: Vec<AmpControls> = [0., 1., 2.]
            .into_iter()
            .flat_map(|tone_stack| {
                [-1., AmpControls::default().preamp_drive, 1.].map(|preamp_drive| AmpControls {
                    tone_stack,
                    preamp_drive,
                    ..AmpControls::default()
                })
            })
            .collect();
        let gaps = parallel(&cells, |controls| {
            feed_gap_db(*controls, &clips, LevelTables::CALIBRATED)
        });
        for (controls, gap) in cells.iter().zip(gaps) {
            let (tone_stack, preamp_drive) = (controls.tone_stack, controls.preamp_drive);
            assert!(
                gap.abs() <= TOLERANCE_DB,
                "tone stack {tone_stack}, Drive {preamp_drive:+}: power stage fed \
                 {gap:+.2} dB from 1.4.0 (tolerance {TOLERANCE_DB} dB); run `just calibrate`"
            );
        }
    }
}
