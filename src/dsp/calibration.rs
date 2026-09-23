//! Measures the shipping path's level compensation.
//!
//! The first stage keeps the released structure against the released 1.4.0
//! path on the single-coil DI: the preamp table normalises the last active
//! triode's output against Drive, the tone-stack scale normalises the stack's
//! gain at the factory defaults, and the power table normalises the power
//! amp's output against Power Drive. Each is transferred to the shipping path
//! by the RMS ratio of the released seam to the shipping seam, so the power
//! stage is driven as 1.4.0 drove it.
//!
//! The second stage holds loudness. 1.4.0 lost level as Drive and Power
//! Drive rose, by amounts that depend on the material: on a plucked note
//! heavy compression flattens the attack, so RMS falls further than on a
//! played DI. Loudness is ITU-R BS.1770-4 gated integrated loudness, averaged
//! in LUFS over the single-coil DI and the refit pluck, and the target is the
//! factory defaults' loudness from the first stage, so Init keeps its level.
//! In order, each with the values found so far in place: the power table is
//! rescaled point by point to the target, then an output gain against Drive,
//! then one against Grit, all applied after the cabinet so they change level
//! and nothing else. Stages stays uncompensated, as released. Every render
//! starts from a settled amplifier with the other controls at their
//! defaults.

use super::amp::{
    AmpControls, AmpPath, ClipKnee, CorrectedPath, GRIT_COMPRESSION_LIMIT, LevelTables, SeamOutput,
    TABLE_POINTS, ToneMapping, interpolate,
};
use super::mapping::{AmpVoicing, drive_setting, power_drive_setting};
use crate::engine::doublings_for;

/// The host rate every calibration render runs at, with Auto oversampling.
pub const SAMPLE_RATE: u32 = 44_100;
const BLOCK: usize = 512;

/// RMS levels at the seams around the level compensation for one render.
#[derive(Debug, Clone, Copy)]
struct Levels {
    last_triode: f64,
    tone_stack: f64,
    power_amp: f64,
    output: f64,
}

fn rms(samples: &[f32]) -> f64 {
    let sum: f64 = samples
        .iter()
        .map(|sample| f64::from(*sample) * f64::from(*sample))
        .sum();
    (sum / samples.len() as f64).sqrt()
}

fn db(ratio: f64) -> f64 {
    20. * ratio.log10()
}

fn levels(seams: &SeamOutput) -> Levels {
    let last_triode = seams
        .triodes
        .iter()
        .rev()
        .find(|samples| !samples.is_empty())
        .expect("at least one triode is active");
    Levels {
        last_triode: rms(last_triode),
        tone_stack: rms(&seams.tone_stack),
        power_amp: rms(&seams.power_amp),
        output: rms(&seams.raw_output),
    }
}

/// The released path, which `just model-check` holds to the frozen 1.4.0
/// renders.
fn released(controls: AmpControls, clip: &[f32]) -> Levels {
    let mut path = AmpPath::new_legacy(SAMPLE_RATE as f32, controls);
    let mut seams = SeamOutput::with_capacity(clip.len());
    let mut audio = clip.to_vec();
    for block in audio.chunks_mut(BLOCK) {
        path.process_with_seams(block, &mut seams);
    }
    levels(&seams)
}

fn shipping(controls: AmpControls, clip: &[f32], tables: LevelTables) -> Levels {
    let doublings = doublings_for(0, f64::from(SAMPLE_RATE));
    let mut path = CorrectedPath::new(
        SAMPLE_RATE as f32,
        BLOCK,
        controls,
        doublings,
        ToneMapping::Standard,
        ClipKnee::UnitSlope,
        tables,
    );
    let mut seams = SeamOutput::with_capacity(clip.len() << doublings);
    let mut audio = clip.to_vec();
    for block in audio.chunks_mut(BLOCK) {
        path.process_with_seams(block, &mut seams);
    }
    levels(&seams)
}

/// The level into the power stage: the tone-stack seam with its gain
/// compensation and the preamp table applied.
fn power_input(levels: Levels, controls: AmpControls, tables: &LevelTables) -> f64 {
    let drive = AmpVoicing::from_controls(controls).preamp_drive;
    levels.tone_stack * f64::from(tables.tone_stack * interpolate(drive, &tables.preamp))
}

fn shipping_output(controls: AmpControls, clip: &[f32], tables: LevelTables) -> Vec<f32> {
    let doublings = doublings_for(0, f64::from(SAMPLE_RATE));
    let mut path = CorrectedPath::new(
        SAMPLE_RATE as f32,
        BLOCK,
        controls,
        doublings,
        ToneMapping::Standard,
        ClipKnee::UnitSlope,
        tables,
    );
    let mut audio = clip.to_vec();
    for block in audio.chunks_mut(BLOCK) {
        path.process(block);
    }
    audio
}

/// The two calibration inputs at `SAMPLE_RATE`: a played single-coil DI and
/// the refit's synthetic pluck, whose attacks the amplifier compresses harder.
pub struct Clips {
    pub di: Vec<f32>,
    pub pluck: Vec<f32>,
}

impl Clips {
    pub fn new(di_wav: &[u8]) -> Result<Self, String> {
        Ok(Self {
            di: clip(di_wav)?,
            pluck: resample(
                &super::refit::pluck(super::refit::SAMPLE_RATE),
                super::refit::SAMPLE_RATE,
            ),
        })
    }
}

/// Loudness on each clip and their mean, in LUFS.
#[derive(Debug, Clone, Copy)]
pub struct Loudness {
    pub di: f64,
    pub pluck: f64,
}

impl Loudness {
    pub fn blend(self) -> f64 {
        (self.di + self.pluck) / 2.
    }
}

/// The shipping path's loudness with `tables` in place.
pub fn loudness(controls: AmpControls, clips: &Clips, tables: LevelTables) -> Loudness {
    Loudness {
        di: integrated_loudness(&shipping_output(controls, &clips.di, tables)),
        pluck: integrated_loudness(&shipping_output(controls, &clips.pluck, tables)),
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

/// Seam levels at one table point, in dB of RMS.
#[derive(Debug, Clone, Copy)]
pub struct Point {
    pub released_db: f64,
    pub shipping_db: f64,
}

/// Shipping minus released level at the factory defaults, in dB, with the
/// measured compensation in place. The cabinet-on output also carries the
/// cabinet's response to the default tone controls, which the standard
/// mapping voices differently; no level compensation is fitted to it because
/// the refitted factory presets already sit at the released stack's shape.
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
    /// Last active triode over the Drive sweep.
    pub drive: [Point; TABLE_POINTS],
    /// Power stage input at the factory defaults before the tone-stack
    /// compensation is measured.
    pub tone_stack: Point,
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

/// Measures `controls_at(index)` at every table point in parallel.
fn sweep(
    clips: &Clips,
    tables: LevelTables,
    controls_at: impl Fn(usize) -> AmpControls + Sync,
) -> [Loudness; TABLE_POINTS] {
    std::thread::scope(|scope| {
        let handles: Vec<_> = (0..TABLE_POINTS)
            .map(|index| {
                let controls = controls_at(index);
                scope.spawn(move || loudness(controls, clips, tables))
            })
            .collect();
        let measured: Vec<Loudness> = handles
            .into_iter()
            .map(|handle| handle.join().expect("calibration render panicked"))
            .collect();
        std::array::from_fn(|index| measured[index])
    })
}

/// The gain that brings `measured` to `target`.
fn to_target(target: Loudness, measured: Loudness) -> f64 {
    10_f64.powf((target.blend() - measured.blend()) / 20.)
}

fn gain(point: Point) -> f64 {
    10_f64.powf((point.released_db - point.shipping_db) / 20.)
}

fn point(released: f64, shipping: f64) -> Point {
    Point {
        released_db: db(released),
        shipping_db: db(shipping),
    }
}

/// Transfers each released table point to the shipping path by the ratio of
/// the two paths' seam levels there.
fn transfer(
    released_table: &[f32; TABLE_POINTS],
    mut measure: impl FnMut(usize) -> (f64, f64),
) -> ([f32; TABLE_POINTS], [Point; TABLE_POINTS]) {
    let points: [Point; TABLE_POINTS] = std::array::from_fn(|index| {
        let (released, shipping) = measure(index);
        point(released, shipping)
    });
    let table = std::array::from_fn(|index| {
        (f64::from(released_table[index]) * gain(points[index])) as f32
    });
    (table, points)
}

/// Measures the compensation on `clips`.
pub fn measure(clips: &Clips) -> Calibration {
    let clip = &clips.di;
    let defaults = AmpControls::default();
    let mut tables = LevelTables::RELEASED;
    let (preamp, drive) = transfer(&tables.preamp, |index| {
        let controls = AmpControls {
            preamp_drive: drive_setting(table_point(index)),
            ..defaults
        };
        (
            released(controls, clip).last_triode,
            shipping(controls, clip, tables).last_triode,
        )
    });
    tables.preamp = preamp;

    let tone_stack = point(
        power_input(released(defaults, clip), defaults, &LevelTables::RELEASED),
        power_input(shipping(defaults, clip, tables), defaults, &tables),
    );
    tables.tone_stack = (f64::from(tables.tone_stack) * gain(tone_stack)) as f32;

    let (power, power_points) = transfer(&tables.power, |index| {
        let controls = AmpControls {
            power_drive: power_drive_setting(table_point(index)),
            ..defaults
        };
        (
            released(controls, clip).power_amp,
            shipping(controls, clip, tables).power_amp,
        )
    });
    tables.power = power;
    tables.grit_compression = GRIT_COMPRESSION_LIMIT;

    let target = loudness(defaults, clips, tables);
    let power_loudness = sweep(clips, tables, |index| AmpControls {
        power_drive: power_drive_setting(table_point(index)),
        ..defaults
    });
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
        drive,
        tone_stack,
        power: power_points,
        power_transfer: power,
        target,
        power_loudness,
        drive_loudness,
        grit_loudness,
        anchor: anchor(clip, tables),
    }
}

/// How far the shipping path with `tables` lands from the released level at
/// the factory defaults.
pub fn anchor(clip: &[f32], tables: LevelTables) -> Anchor {
    let defaults = AmpControls::default();
    let reference = released(defaults, clip);
    let actual = shipping(defaults, clip, tables);
    let cabinet_off = AmpControls {
        cabinet_on: false,
        ..defaults
    };
    Anchor {
        power_input_db: db(power_input(actual, defaults, &tables)
            / power_input(reference, defaults, &LevelTables::RELEASED)),
        power_amp_db: db(actual.power_amp / reference.power_amp),
        output_db: db(actual.output / reference.output),
        output_cabinet_off_db: db(
            shipping(cabinet_off, clip, tables).output / released(cabinet_off, clip).output
        ),
    }
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

    /// How far the committed compensation may leave the factory defaults
    /// from the released level. Power Drive's default sits between table
    /// points, so this bounds the interpolation error.
    const ANCHOR_TOLERANCE_DB: f64 = 0.1;

    /// Drive, Power Drive and Grit change the sound, not the volume: their
    /// extremes keep the defaults' loudness averaged over the two clips.
    #[test]
    fn drive_power_drive_and_grit_extremes_keep_the_default_loudness() {
        const TOLERANCE_DB: f64 = 1.;
        let clips = Clips::new(include_bytes!(
            "../../verification/reference/input/single-coil.wav"
        ))
        .expect("calibration clip reads");
        let defaults = AmpControls::default();
        let target = loudness(defaults, &clips, LevelTables::CALIBRATED).blend();
        for extreme in [-1., 1.] {
            for (control, controls) in [
                (
                    "Drive",
                    AmpControls {
                        preamp_drive: extreme,
                        ..defaults
                    },
                ),
                (
                    "Power Drive",
                    AmpControls {
                        power_drive: extreme,
                        ..defaults
                    },
                ),
                (
                    "Grit",
                    AmpControls {
                        preamp_grit: extreme,
                        ..defaults
                    },
                ),
            ] {
                let change = loudness(controls, &clips, LevelTables::CALIBRATED).blend() - target;
                assert!(
                    change.abs() <= TOLERANCE_DB,
                    "{control} at {extreme:+} moves loudness {change:+.2} dB \
                     (tolerance {TOLERANCE_DB} dB)"
                );
            }
        }
    }

    #[test]
    fn factory_defaults_land_on_the_released_level() {
        let clip = clip(include_bytes!(
            "../../verification/reference/input/single-coil.wav"
        ))
        .expect("calibration clip reads");
        let anchor = anchor(&clip, LevelTables::CALIBRATED);
        for (seam, residual) in [
            ("power stage input", anchor.power_input_db),
            ("output with the cabinet off", anchor.output_cabinet_off_db),
        ] {
            assert!(
                residual.abs() <= ANCHOR_TOLERANCE_DB,
                "{seam} is {residual:+.3} dB from 1.4.0 at the defaults \
                 (tolerance {ANCHOR_TOLERANCE_DB} dB); run `just calibrate`"
            );
        }
    }
}
