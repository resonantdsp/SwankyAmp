//! Measures the shipping path's level compensation against the released
//! 1.4.0 path on the single-coil calibration clip.
//!
//! As released, the preamp table normalises the last active triode's output
//! against Drive, the tone-stack scale normalises the stack's gain at the
//! factory defaults, and the power table normalises the power amp's output
//! against Power Drive; the cabinet keeps its own fixed scale. Oversampling,
//! the unit-slope knee and the standard tone-stack mapping change the level
//! reaching each of them, so each is transferred to the shipping path by the
//! RMS ratio of the released seam to the shipping seam: every table point
//! lands on the released level, so Drive and Power Drive move loudness as
//! 1.4.0 did. In order, each with the values found so far in place: the
//! Drive sweep at the last active triode, the tone-stack scale anchoring the
//! power stage input at the factory defaults, then the Power Drive sweep at
//! the power amp. Every render starts from a settled amplifier with the other
//! controls at their defaults. Grit and Stages stay uncompensated, as
//! released.

use super::amp::{
    AmpControls, AmpPath, ClipKnee, CorrectedPath, LevelTables, SeamOutput, TABLE_POINTS,
    ToneMapping, interpolate,
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
    pub anchor: Anchor,
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

/// Measures the compensation on `clip`, which must be at `SAMPLE_RATE`.
pub fn measure(clip: &[f32]) -> Calibration {
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

    Calibration {
        tables,
        drive,
        tone_stack,
        power: power_points,
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
    let step = f64::from(rate) / f64::from(SAMPLE_RATE);
    let frames = (source.len() as f64 / step).round() as usize;
    Ok((0..frames)
        .map(|frame| {
            let position = frame as f64 * step;
            let lower = position as usize;
            let upper = (lower + 1).min(source.len() - 1);
            let fraction = (position - lower as f64) as f32;
            source[lower] + fraction * (source[upper] - source[lower])
        })
        .collect())
}

#[cfg(test)]
mod tests {
    use super::*;

    /// How far the committed compensation may leave the factory defaults
    /// from the released level. Power Drive's default sits between table
    /// points, so this bounds the interpolation error.
    const ANCHOR_TOLERANCE_DB: f64 = 0.1;

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
