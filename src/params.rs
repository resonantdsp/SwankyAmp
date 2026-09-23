use crate::dsp::mapping::AmpControls;
use std::sync::atomic::{AtomicU32, Ordering};
use truce::prelude::*;
use truce_params::FloatParamReadF32;

#[derive(Params)]
pub struct SwankyAmpParams {
    #[param(id = 0, name = "Input", range = "linear(-1, 1)", default = 0.0)]
    pub input: FloatParam,
    #[param(id = 1, name = "Output", range = "linear(-1, 1)", default = 0.0)]
    pub output: FloatParam,
    #[param(id = 2, name = "Low", range = "linear(-1, 1)", default = 0.0)]
    pub low: FloatParam,
    #[param(id = 3, name = "Mid", range = "linear(-1, 1)", default = 0.0)]
    pub mid: FloatParam,
    #[param(id = 4, name = "High", range = "linear(-1, 1)", default = 0.0)]
    pub high: FloatParam,
    #[param(id = 5, name = "Presence", range = "linear(-1, 1)", default = 0.0)]
    pub presence: FloatParam,
    #[param(id = 6, name = "Tone Stack", range = "linear(0, 2)", default = 0.0)]
    pub tone_stack: FloatParam,
    #[param(id = 7, name = "Stages", range = "linear(1, 5)", default = 3.0)]
    pub stages: FloatParam,
    #[param(id = 8, name = "Overhead", range = "linear(-1, 1)", default = 0.0)]
    pub overhead: FloatParam,
    #[param(id = 9, name = "Low Cut", range = "linear(-1, 1)", default = 0.0)]
    pub low_cut: FloatParam,
    #[param(id = 10, name = "Cabinet Enabled", default = true)]
    pub cabinet_on: BoolParam,
    #[param(
        id = 11,
        name = "Cabinet Bright",
        range = "linear(-1, 1)",
        default = 0.0
    )]
    pub cabinet_brightness: FloatParam,
    #[param(
        id = 12,
        name = "Cabinet Distance",
        range = "linear(0, 1)",
        default = 0.5
    )]
    pub cabinet_distance: FloatParam,
    #[param(id = 13, name = "Cabinet Dynamic", range = "linear(-1, 1)", default = -0.3)]
    pub cabinet_dynamic: FloatParam,
    #[param(id = 14, name = "Preamp Drive", range = "linear(-1, 1)", default = -0.4)]
    pub preamp_drive: FloatParam,
    #[param(id = 15, name = "Preamp Tight", range = "linear(-1, 1)", default = 0.0)]
    pub preamp_tight: FloatParam,
    #[param(id = 16, name = "Preamp Grit", range = "linear(-1, 1)", default = 0.0)]
    pub preamp_grit: FloatParam,
    #[param(id = 17, name = "Power Drive", range = "linear(-1, 1)", default = -0.2)]
    pub power_drive: FloatParam,
    #[param(id = 18, name = "Power Tight", range = "linear(-1, 1)", default = 0.0)]
    pub power_tight: FloatParam,
    #[param(id = 19, name = "Power Sag", range = "linear(-1, 1)", default = -0.6)]
    pub power_sag: FloatParam,
    #[param(
        id = 20,
        name = "Power Sag Ratio",
        range = "linear(-1, 1)",
        default = 0.0,
        flags = "hidden"
    )]
    pub power_sag_ratio: FloatParam,
    /// 0 is Auto; 1, 2 and 3 request 1x, 2x and 4x processing.
    #[param(id = 21, name = "Oversampling", range = "discrete(0, 3)", default = 0)]
    pub oversampling: IntParam,
    /// What the engine settled on, which under Auto depends on the host rate
    /// and so is known only once audio has been prepared. Session state for
    /// the editor, never host state.
    #[skip]
    pub resolved_oversampling: ResolvedOversampling,
}

/// Doublings of the host rate the engine is running, shared from the audio
/// thread to the editor.
pub struct ResolvedOversampling(AtomicU32);

const UNRESOLVED: u32 = u32::MAX;

impl Default for ResolvedOversampling {
    fn default() -> Self {
        Self(AtomicU32::new(UNRESOLVED))
    }
}

impl ResolvedOversampling {
    pub fn publish(&self, doublings: usize) {
        self.0.store(
            u32::try_from(doublings).unwrap_or(UNRESOLVED),
            Ordering::Relaxed,
        );
    }

    pub fn get(&self) -> Option<usize> {
        match self.0.load(Ordering::Relaxed) {
            UNRESOLVED => None,
            doublings => Some(doublings as usize),
        }
    }
}

fn plain(param: &FloatParam) -> f32 {
    FloatParamReadF32::value(param)
}

impl SwankyAmpParams {
    pub fn oversampling_choice(&self) -> usize {
        self.oversampling.value_usize()
    }

    pub fn snapshot(&self) -> AmpControls {
        AmpControls {
            input: plain(&self.input),
            output: plain(&self.output),
            low: plain(&self.low),
            mid: plain(&self.mid),
            high: plain(&self.high),
            presence: plain(&self.presence),
            tone_stack: plain(&self.tone_stack),
            stages: plain(&self.stages),
            overhead: plain(&self.overhead),
            low_cut: plain(&self.low_cut),
            cabinet_on: self.cabinet_on.value(),
            cabinet_brightness: plain(&self.cabinet_brightness),
            cabinet_distance: plain(&self.cabinet_distance),
            cabinet_dynamic: plain(&self.cabinet_dynamic),
            preamp_drive: plain(&self.preamp_drive),
            preamp_tight: plain(&self.preamp_tight),
            preamp_grit: plain(&self.preamp_grit),
            power_drive: plain(&self.power_drive),
            power_tight: plain(&self.power_tight),
            power_sag: plain(&self.power_sag),
            power_sag_ratio: plain(&self.power_sag_ratio),
        }
    }
}
