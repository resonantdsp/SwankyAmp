use super::stage::{Range, STAGES, TetrodeControls, TriodeControls};
use super::tone_stack::ToneControls;

#[inline]
pub(crate) fn sided(value: f32, low: f32, high: f32) -> f32 {
    if value >= 0. {
        value * high
    } else {
        -value * low
    }
}

#[inline]
fn range(value: f32, low: f32, high: f32) -> f32 {
    (value + 1.) * 0.5 * (high - low) + low
}

#[inline]
fn map(value: f32, x1: f32, x2: f32, y1: f32, y2: f32) -> f32 {
    let unit = (value.clamp(x1.min(x2), x1.max(x2)) - x1) / (x2 - x1);
    unit * (y2 - y1) + y1
}

#[inline]
fn dense(value: f32, centre: f32, scale: f32) -> f32 {
    let shaped = ((value - centre) * scale).sinh();
    let low = ((-1. - centre) * scale).sinh();
    let high = ((1. - centre) * scale).sinh();
    (shaped - low) / (high - low) * 2. - 1.
}

/// Inverse of `dense`: the control setting whose shaped value is `shaped`.
#[inline]
fn undense(shaped: f32, centre: f32, scale: f32) -> f32 {
    let low = ((-1. - centre) * scale).sinh();
    let high = ((1. - centre) * scale).sinh();
    ((shaped + 1.) * 0.5 * (high - low) + low).asinh() / scale + centre
}

/// Centre and scale of Drive's and Power Drive's control shaping.
const DRIVE_SHAPE: (f32, f32) = (0.5, 1.);
const POWER_DRIVE_SHAPE: (f32, f32) = (-0.2, 1.);

/// The Drive setting whose shaped value, the level tables' axis, is `shaped`.
pub(crate) fn drive_setting(shaped: f32) -> f32 {
    undense(shaped, DRIVE_SHAPE.0, DRIVE_SHAPE.1)
}

/// The Power Drive setting whose shaped value is `shaped`.
pub(crate) fn power_drive_setting(shaped: f32) -> f32 {
    undense(shaped, POWER_DRIVE_SHAPE.0, POWER_DRIVE_SHAPE.1)
}

const PREAMP_DRIVE: Range = Range::Log(0.1, 2e3);
const PREAMP_OVERHEAD: Range = Range::Log(0.1, 10.);
const POWER_DRIVE: Range = Range::Log(30., 3e4);

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct AmpControls {
    pub input: f32,
    pub output: f32,
    pub low: f32,
    pub mid: f32,
    pub high: f32,
    pub presence: f32,
    pub tone_stack: f32,
    pub stages: f32,
    pub overhead: f32,
    pub low_cut: f32,
    pub cabinet_on: bool,
    pub cabinet_brightness: f32,
    pub cabinet_distance: f32,
    pub cabinet_dynamic: f32,
    pub preamp_drive: f32,
    pub preamp_tight: f32,
    pub preamp_grit: f32,
    pub power_drive: f32,
    pub power_tight: f32,
    pub power_sag: f32,
    pub power_sag_ratio: f32,
}

impl Default for AmpControls {
    fn default() -> Self {
        Self {
            input: 0.,
            output: 0.,
            low: 0.,
            mid: 0.,
            high: 0.,
            presence: 0.,
            tone_stack: 0.,
            stages: 3.,
            overhead: 0.,
            low_cut: 0.,
            cabinet_on: true,
            cabinet_brightness: 0.,
            cabinet_distance: 0.5,
            cabinet_dynamic: -0.3,
            preamp_drive: -0.4,
            preamp_tight: 0.,
            preamp_grit: 0.,
            power_drive: -0.2,
            power_tight: 0.,
            power_sag: -0.6,
            power_sag_ratio: 0.,
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub(crate) struct AmpVoicing {
    pub input_gain: f32,
    pub output_gain: f32,
    pub triodes: [TriodeControls; STAGES],
    pub preamp_gain: f32,
    pub preamp_drive: f32,
    pub preamp_grit: f32,
    pub tone: ToneControls,
    pub tetrode: TetrodeControls,
    pub power_gain: f32,
    pub power_drive: f32,
    pub cabinet_on: bool,
    pub cabinet_brightness: f32,
    pub cabinet_distance: f32,
    pub cabinet_dynamic: f32,
    pub cabinet_dynamic_level: f32,
}

impl AmpVoicing {
    pub(crate) fn from_controls(controls: AmpControls) -> Self {
        let preamp_drive = dense(controls.preamp_drive, DRIVE_SHAPE.0, DRIVE_SHAPE.1);
        let power_drive = dense(
            controls.power_drive,
            POWER_DRIVE_SHAPE.0,
            POWER_DRIVE_SHAPE.1,
        );
        let sag = dense(controls.power_sag, 0., 1.);
        let low_cut = dense(map(controls.low_cut, -1., 1., 0., 1.23), 0.5, 1.);
        let minimum_tight = map(preamp_drive, -0.5, 1., -1., 0.);
        let tight = range(controls.preamp_tight, minimum_tight, 1.);
        let active = controls.stages.clamp(1.1, STAGES as f32);
        let whole = active.floor();
        let overhead = PREAMP_OVERHEAD.at(controls.overhead);
        let grit = controls.preamp_grit;
        let triodes = std::array::from_fn(|stage| TriodeControls {
            hp_freq: sided(low_cut, -1., 0.75),
            tau: sided(-tight, -0.5, 0.1),
            ratio: sided(-tight, -1., 0.1),
            level: sided(-grit, -0.2, 3.),
            grid_clip: sided(-grit, -1., 4.),
            bias: sided(tight, -1., 0.5),
            comp_ratio: sided(tight, -1., 0.),
            comp_level: sided(grit, 0., 1.),
            comp_offset: sided(-grit, 0., 5.),
            overhead: if stage == 0 { 1. } else { overhead },
            mix: if (stage as f32) < whole {
                1.
            } else if (stage as f32) < active.ceil() {
                active - whole
            } else {
                0.
            },
        });
        let power_tight = controls.power_tight;
        let power_gain = POWER_DRIVE.at(power_drive);
        let tetrode = TetrodeControls {
            hp_freq: 0.,
            tau: sided(-power_tight, -1., 1.),
            ratio: sided(-power_tight, -1., 0.1),
            comp_depth: sided(-power_tight, -0.5, 0.),
            sag_depth: sag + map(power_drive, -1., 1., 1., -1.),
            sag_onset: sag,
            sag_factor: power_drive,
            sag_toggle: if sag < -0.99 { -1. } else { 1. },
            sag_tau: sided(-power_tight, -1., 1.),
            sag_ratio: controls.power_sag_ratio,
        };
        let output_boost = 10. + map(preamp_drive, 0., 1., 0., -3.);
        let dynamic_unit = map(controls.cabinet_dynamic, -1., 0., -1., 1.);

        Self {
            input_gain: super::filters::db_to_gain(range(controls.input, -35., 35.)),
            output_gain: super::filters::db_to_gain(
                range(controls.output, -35., 35.) + output_boost,
            ),
            triodes,
            preamp_gain: PREAMP_DRIVE.at(preamp_drive).max(0.5),
            preamp_drive,
            preamp_grit: controls.preamp_grit,
            tone: ToneControls {
                bass: controls.low,
                mids: controls.mid,
                treble: controls.high,
                presence: controls.presence,
                model: controls.tone_stack,
            },
            tetrode,
            power_gain,
            power_drive,
            cabinet_on: controls.cabinet_on,
            cabinet_brightness: sided(controls.cabinet_brightness, -0.6, 0.6),
            cabinet_distance: controls.cabinet_distance,
            cabinet_dynamic: range(dynamic_unit, 0., 1.),
            cabinet_dynamic_level: Range::Log(0.5, 2.).at(-controls.cabinet_dynamic),
        }
    }
}
