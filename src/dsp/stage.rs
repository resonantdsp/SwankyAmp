//! The tube stages: a triode with grid conduction and plate saturation, and a
//! push-pull tetrode power stage with crossover distortion and sag.
//!
//! Every fitted quantity is a `Fitted` control: a unit-space input in
//! roughly -1..1 plus the offset the fit settled on, mapped to real units.
//! Voicing controls move the unit-space input; fixed constants use zero.

use super::filters::{
    Charge, Divisor, OnePole, Smoother, charge_rate, soft_clip_down, soft_clip_up, tau_to_pole,
};

/// Maps a unit-space value in -1..1 onto real units, linearly or
/// logarithmically between `lo` and `hi`.
#[derive(Debug, Clone, Copy)]
pub enum Range {
    Linear(f32, f32),
    Log(f32, f32),
}

impl Range {
    #[inline]
    pub fn at(self, u: f32) -> f32 {
        let t = (u + 1.) / 2.;
        match self {
            Self::Linear(lo, hi) => lo + t * (hi - lo),
            Self::Log(lo, hi) => (lo.ln() + t * (hi.ln() - lo.ln())).exp(),
        }
    }
}

/// A fitted control: its range and the unit-space offset from the fit.
#[derive(Debug, Clone, Copy)]
pub struct Fitted {
    pub range: Range,
    pub offset: f32,
}

impl Fitted {
    pub const fn new(range: Range, offset: f32) -> Self {
        Self { range, offset }
    }
    #[inline]
    pub fn at(self, u: f32) -> f32 {
        self.range.at(u + self.offset)
    }
    #[inline]
    pub fn fixed(self) -> f32 {
        self.at(0.)
    }
}

/// Number of triode stages in the preamp.
pub const STAGES: usize = 5;

#[derive(Debug, Clone, Copy)]
pub(crate) enum PlateFilter {
    Released44k1,
    Fixed20k,
}

#[allow(clippy::excessive_precision)] // fitted values, kept verbatim
mod triode {
    use super::{Fitted, Range::*};
    pub const HP_FREQ: Fitted = Fitted::new(Log(0.1, 100.), 0.452_223_2);
    pub const TAU: Fitted = Fitted::new(Log(1e-6, 1e-3), -1.357_775_7);
    pub const RATIO: Fitted = Fitted::new(Log(0.1, 1e4), 1.208_987_9);
    pub const SMOOTH: Fitted = Fitted::new(Log(1e-5, 10.), 1.529_416_4);
    pub const LEVEL: Fitted = Fitted::new(Linear(-5., 5.), 0.335_753_1);
    pub const CAP: Fitted = Fitted::new(Log(0.1, 10.), 1.739_276_8);
    pub const GRID_CLIP: Fitted = Fitted::new(Linear(0., 5.), 0.407_827_53);
    pub const GRID_CORNER: Fitted = Fitted::new(Linear(0., 5.), 0.011_509_125);
    pub const BIAS: Fitted = Fitted::new(Linear(-100., 100.), 2.368_186_4);
    pub const BIAS_CORNER: Fitted = Fitted::new(Log(0.1, 1e3), 0.489_370_03);
    pub const SCALE: Fitted = Fitted::new(Log(0.1, 10.), 1.524_155_9);
    pub const PLATE_CLIP: Fitted = Fitted::new(Linear(-100., 100.), -1.075_611_2);
    pub const PLATE_CORNER: Fitted = Fitted::new(Log(0.01, 100.), -0.024_479_386);
    pub const DRIFT_LEVEL: Fitted = Fitted::new(Linear(-100., 100.), 0.101_869_44);
    pub const DRIFT_TAU: Fitted = Fitted::new(Log(1e-3, 1.), -1.088_059_9);
    pub const DRIFT_DEPTH: Fitted = Fitted::new(Log(0.1, 10.), -0.824_979_99);
    pub const COMP_LEVEL: Fitted = Fitted::new(Linear(-100., 100.), -1.019_789_2);
    pub const COMP_TAU: Fitted = Fitted::new(Log(1e-3, 1.), -1.100_163_6);
    pub const COMP_RATIO: Fitted = Fitted::new(Log(1., 10.), 3.138_569_8);
    pub const COMP_DEPTH: Fitted = Fitted::new(Log(0.1, 10.), -0.160_235_71);
    pub const COMP_CAP: Fitted = Fitted::new(Log(0.1, 10.), 2.536_884_4);
    pub const COMP_CORNER: Fitted = Fitted::new(Log(0.1, 100.), 0.015_071_488);
    pub const COMP_OFFSET: Fitted = Fitted::new(Linear(-100., 100.), 0.);

    /// Per-stage detuning in unit space, so cascaded stages never share one
    /// exact corner or bias. These are the released product's values.
    pub struct Detune {
        pub hp_freq: [f32; 5],
        pub tau: [f32; 5],
        pub grid_clip: [f32; 5],
        pub bias: [f32; 5],
        pub plate_clip: [f32; 5],
        pub drift_level: [f32; 5],
        pub drift_tau: [f32; 5],
        pub comp_level: [f32; 5],
    }
    pub const DETUNE: Detune = Detune {
        hp_freq: [
            -0.198_885_1,
            0.017_609_477,
            0.027_089_214,
            0.023_919_344,
            -0.189_397_19,
        ],
        tau: [
            -0.198_876_11,
            0.051_622_462,
            -0.132_369_74,
            -0.019_436_145,
            0.197_785_09,
        ],
        grid_clip: [
            -0.198_858_13,
            0.119_648_41,
            -0.051_287_651,
            -0.106_147_125,
            0.172_149_66,
        ],
        bias: [
            -0.198_849_13,
            0.153_661_4,
            0.189_253_4,
            -0.149_502_62,
            0.159_331_95,
        ],
        plate_clip: [
            -0.198_831_16,
            -0.178_312_64,
            -0.129_664_53,
            0.163_786_41,
            0.133_696_51,
        ],
        drift_level: [
            -0.198_822_16,
            -0.144_299_67,
            0.110_876_516,
            0.120_430_924,
            0.120_878_79,
        ],
        drift_tau: [
            -0.198_813_17,
            -0.110_286_68,
            -0.048_582_435,
            0.077_075_437,
            0.108_061_075,
        ],
        comp_level: [
            -0.198_804_17,
            -0.076_273_7,
            0.191_958_59,
            0.033_719_946,
            0.095_243_335,
        ],
    };
}

/// Unit-space voicing inputs to one triode stage.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct TriodeControls {
    pub hp_freq: f32,
    pub tau: f32,
    pub ratio: f32,
    pub level: f32,
    pub grid_clip: f32,
    pub bias: f32,
    pub comp_ratio: f32,
    pub comp_level: f32,
    pub comp_offset: f32,
    /// Gain applied before and removed after the stage, so later stages
    /// saturate less; the first stage always uses unity.
    pub overhead: f32,
    /// Wet share of this stage; the stage count fades the last stage in.
    pub mix: f32,
}

impl Default for TriodeControls {
    fn default() -> Self {
        Self {
            hp_freq: 0.,
            tau: 0.,
            ratio: 0.,
            level: 0.,
            grid_clip: 0.,
            bias: 0.,
            comp_ratio: 0.,
            comp_level: 0.,
            comp_offset: 0.,
            overhead: 1.,
            mix: 1.,
        }
    }
}

/// One triode gain stage with its own detuning.
#[derive(Debug, Clone)]
pub struct Triode {
    stage: usize,
    sample_rate: f32,
    controls: TriodeControls,
    unscale_inv: f32,
    overhead_inv: f32,
    grid_hp: OnePole,
    grid_level: f32,
    grid_rise: f32,
    grid_fall: f32,
    grid_cap: Divisor,
    grid_charge: Charge,
    grid_smooth: Smoother,
    grid_corner: Divisor,
    grid_clip: f32,
    scale: f32,
    bias_corner: Divisor,
    bias: f32,
    plate_corner: Divisor,
    plate_clip: f32,
    drift_level: f32,
    drift_smooth: Smoother,
    drift_depth: f32,
    comp_level: f32,
    comp_rise: f32,
    comp_fall: f32,
    comp_cap: Divisor,
    comp_charge: Charge,
    comp_depth: f32,
    comp_offset: f32,
    comp_corner: Divisor,
    plate_lp: OnePole,
    plate_filter: PlateFilter,
}

impl Triode {
    /// `unscale` removes the stage's nominal gain so stages cascade at a
    /// constant level; it is the preamp's calibrated stage gain.
    pub fn new(stage: usize, unscale: f32, sample_rate: f32, plate_filter: PlateFilter) -> Self {
        let mut triode = Self {
            stage,
            sample_rate,
            controls: TriodeControls::default(),
            unscale_inv: 1. / unscale,
            overhead_inv: 1.,
            grid_hp: OnePole::default(),
            grid_level: 0.,
            grid_rise: 0.,
            grid_fall: 0.,
            grid_cap: Divisor::default(),
            grid_charge: Charge::default(),
            grid_smooth: Smoother::default(),
            grid_corner: Divisor::default(),
            grid_clip: 0.,
            scale: 1.,
            bias_corner: Divisor::default(),
            bias: 0.,
            plate_corner: Divisor::default(),
            plate_clip: 0.,
            drift_level: 0.,
            drift_smooth: Smoother::default(),
            drift_depth: 0.,
            comp_level: 0.,
            comp_rise: 0.,
            comp_fall: 0.,
            comp_cap: Divisor::default(),
            comp_charge: Charge::default(),
            comp_depth: 0.,
            comp_offset: 0.,
            comp_corner: Divisor::default(),
            plate_lp: OnePole::default(),
            plate_filter,
        };
        triode.configure(TriodeControls::default());
        triode
    }

    pub fn prepare(&mut self, sample_rate: f32) {
        self.sample_rate = sample_rate;
        self.configure(self.controls);
        self.reset();
    }

    pub fn reset(&mut self) {
        self.grid_hp.reset();
        self.grid_charge.reset();
        self.grid_smooth.reset();
        self.drift_smooth.reset();
        self.comp_charge.reset();
        self.plate_lp.reset();
    }

    pub fn settle(&mut self, x: f32) -> f32 {
        let c = &self.controls;
        let a = x * self.overhead_inv;
        let h = self.grid_hp.settle(a);
        let excess = (h - self.grid_level).max(0.);
        let charge =
            self.grid_charge
                .settle_capped(excess, self.grid_rise, self.grid_fall, self.grid_cap);
        let g = h - self.grid_smooth.settle(charge);
        let g = soft_clip_up(g, self.grid_corner, self.grid_clip);
        let p = soft_clip_down(g * self.scale, self.bias_corner, self.bias);
        let p = soft_clip_down(-p, self.plate_corner, self.plate_clip);
        let drift = self
            .drift_smooth
            .settle(p.max(self.drift_level) - self.drift_level);
        let p = p - drift * self.drift_depth;
        let excess = p.max(self.comp_level) - self.comp_level;
        let ceiling =
            self.comp_charge
                .settle_capped(excess, self.comp_rise, self.comp_fall, self.comp_cap)
                * self.comp_depth
                + self.comp_offset;
        let p = soft_clip_up(p, self.comp_corner, ceiling);
        let p = -self.plate_lp.settle(p);
        c.mix * (p * c.overhead * self.unscale_inv) + (1. - c.mix) * x
    }

    #[inline]
    pub fn controls(&self) -> TriodeControls {
        self.controls
    }

    pub fn configure(&mut self, controls: TriodeControls) {
        use triode::*;
        let i = self.stage;
        let sr = self.sample_rate;
        self.controls = controls;
        self.overhead_inv = 1. / controls.overhead;
        let tau = TAU.at(controls.tau + DETUNE.tau[i]);
        self.grid_hp
            .set_highpass(HP_FREQ.at(controls.hp_freq + DETUNE.hp_freq[i]), sr);
        self.grid_level = LEVEL.at(controls.level);
        self.grid_rise = charge_rate(tau, sr);
        self.grid_fall = charge_rate(tau * RATIO.at(controls.ratio), sr);
        self.grid_cap = Divisor::new(CAP.fixed());
        self.grid_smooth
            .set_pole(1. - charge_rate(tau * SMOOTH.fixed(), sr));
        self.grid_corner = Divisor::new(GRID_CORNER.fixed());
        self.grid_clip = GRID_CLIP.at(controls.grid_clip + DETUNE.grid_clip[i]);

        self.scale = SCALE.fixed();
        self.bias_corner = Divisor::new(BIAS_CORNER.fixed());
        self.bias = -BIAS.at(controls.bias + DETUNE.bias[i]);
        self.plate_corner = Divisor::new(PLATE_CORNER.fixed());
        self.plate_clip = PLATE_CLIP.at(DETUNE.plate_clip[i]);
        self.drift_level = DRIFT_LEVEL.at(DETUNE.drift_level[i]);
        self.drift_smooth
            .set_pole(tau_to_pole(DRIFT_TAU.at(DETUNE.drift_tau[i]), sr));
        self.drift_depth = DRIFT_DEPTH.fixed();
        let comp_tau = COMP_TAU.fixed();
        self.comp_level = COMP_LEVEL.at(controls.comp_level + DETUNE.comp_level[i]);
        self.comp_rise = charge_rate(comp_tau, sr);
        self.comp_fall = charge_rate(comp_tau * COMP_RATIO.at(controls.comp_ratio), sr);
        self.comp_cap = Divisor::new(COMP_CAP.fixed());
        self.comp_depth = COMP_DEPTH.fixed();
        self.comp_offset = COMP_OFFSET.at(controls.comp_offset);
        self.comp_corner = Divisor::new(COMP_CORNER.fixed());
        match self.plate_filter {
            PlateFilter::Released44k1 => {
                self.plate_lp
                    .set_digital(0.863_271_24, 0.863_271_24, 0.726_542_53);
            }
            PlateFilter::Fixed20k => {
                self.plate_lp.set_lowpass(20_000., sr);
            }
        }
    }

    #[inline]
    pub fn process(&mut self, x: f32) -> f32 {
        let c = &self.controls;
        let a = x * self.overhead_inv;
        let h = self.grid_hp.process(a);
        let excess = (h - self.grid_level).max(0.);
        let charge =
            self.grid_charge
                .step_capped(excess, self.grid_rise, self.grid_fall, self.grid_cap);
        let g = h - self.grid_smooth.process(charge);
        let g = soft_clip_up(g, self.grid_corner, self.grid_clip);
        let p = soft_clip_down(g * self.scale, self.bias_corner, self.bias);
        let p = soft_clip_down(-p, self.plate_corner, self.plate_clip);
        let drift = self
            .drift_smooth
            .process(p.max(self.drift_level) - self.drift_level);
        let p = p - drift * self.drift_depth;
        let excess = p.max(self.comp_level) - self.comp_level;
        let ceiling =
            self.comp_charge
                .step_capped(excess, self.comp_rise, self.comp_fall, self.comp_cap)
                * self.comp_depth
                + self.comp_offset;
        let p = soft_clip_up(p, self.comp_corner, ceiling);
        let p = -self.plate_lp.process(p);
        c.mix * (p * c.overhead * self.unscale_inv) + (1. - c.mix) * x
    }
}

#[allow(clippy::excessive_precision)] // fitted values, kept verbatim
mod tetrode {
    use super::{Fitted, Range::*};
    pub const GRID_HP_FREQ: Fitted = Fitted::new(Log(0.1, 100.), -7.134_431);
    pub const GRID_OFFSET1: Fitted = Fitted::new(Linear(0., 500.), 0.047_838_75);
    pub const GRID_OFFSET2: Fitted = Fitted::new(Linear(0., 500.), -2.047_840_2);
    pub const GRID_TAUS: Fitted = Fitted::new(Log(1e-4, 1.), -4.923_804e-5);
    pub const GRID_LEVEL: Fitted = Fitted::new(Linear(-100., 100.), 0.424_825_08);
    pub const GRID_TAU: Fitted = Fitted::new(Log(1e-4, 1.), -0.619_324_13);
    pub const GRID_RATIO: Fitted = Fitted::new(Log(0.01, 100.), 0.631_697_6);
    pub const GRID_CAP: Fitted = Fitted::new(Log(0.1, 10.), 2.465_974_4);

    pub const SCALE: Fitted = Fitted::new(Log(0.01, 100.), 0.335_413);
    pub const DRIFT_LEVEL: Fitted = Fitted::new(Linear(-100., 100.), 1.145_707_5);
    pub const DRIFT_TAU: Fitted = Fitted::new(Log(1e-3, 1.), -0.244_901_6);
    pub const DRIFT_DEPTH: Fitted = Fitted::new(Log(0.1, 10.), 0.172_565_2);
    pub const DRIFT2_LEVEL: Fitted = Fitted::new(Linear(-50., 50.), 0.568_794_2);
    pub const DRIFT2_DEPTH: Fitted = Fitted::new(Log(0.1, 10.), 0.038_203_074);
    pub const CLIP: Fitted = Fitted::new(Linear(10., 50.), 0.512_660_5);
    pub const CLIP_CORNER: Fitted = Fitted::new(Log(0.1, 100.), 1.071_060_9);
    pub const COMP_TAU: Fitted = Fitted::new(Log(1e-3, 1.), -1.314_453_7);
    pub const COMP_DEPTH: Fitted = Fitted::new(Log(0.1, 10.), -0.541_347_1);
    pub const CROSS_CORNER: Fitted = Fitted::new(Log(0.1, 100.), 0.597_576_9);
    pub const HP_FREQ: Fitted = Fitted::new(Log(10., 100.), -2.867_792_2);
    pub const LP_FREQ: Fitted = Fitted::new(Log(5e3, 15e3), 0.480_499_13);
    pub const SAG_TOGGLE: Fitted = Fitted::new(Linear(0., 1.), 0.);
    pub const SAG_DEPTH: Fitted = Fitted::new(Log(0.01, 0.1), 0.);
    pub const SAG_TAU: Fitted = Fitted::new(Log(0.01, 0.5), 0.);
    pub const SAG_RATIO: Fitted = Fitted::new(Log(1., 10.), 0.);
    pub const SAG_ONSET: Fitted = Fitted::new(Log(0.01, 1.), 0.);
}

/// Unit-space voicing inputs to the push-pull power stage.
#[derive(Debug, Clone, Copy, PartialEq, Default)]
pub struct TetrodeControls {
    pub hp_freq: f32,
    pub tau: f32,
    pub ratio: f32,
    pub comp_depth: f32,
    pub sag_toggle: f32,
    pub sag_depth: f32,
    pub sag_tau: f32,
    pub sag_ratio: f32,
    pub sag_onset: f32,
    /// The released wrapper feeds the mapped power-drive value here.
    pub sag_factor: f32,
}

/// Constants shared by both halves of the push-pull pair.
#[derive(Debug, Clone, Copy, Default)]
struct SideVoicing {
    drift_level: f32,
    drift_depth: f32,
    clip: Divisor,
    clip_corner: Divisor,
    comp_depth: f32,
    cross_corner: Divisor,
}

/// One side of the push-pull pair: bias drift, an envelope-limited clip and
/// a softened crossover edge.
#[derive(Debug, Clone, Copy, Default)]
struct Side {
    drift: Smoother,
    comp: Smoother,
}

impl Side {
    #[inline]
    fn process(&mut self, v: f32, p: &SideVoicing) -> f32 {
        let drift = self.drift.process(v.max(p.drift_level) - p.drift_level);
        let v = v - drift * p.drift_depth;
        let load = self.comp.process((v * p.clip.inv()).abs().min(1.));
        let ceiling = p.clip.value() / (1. + load * p.comp_depth);
        let v = soft_clip_up(v, p.clip_corner, ceiling);
        soft_clip_down(v, p.cross_corner, 0.)
    }
    fn reset(&mut self) {
        self.drift.reset();
        self.comp.reset();
    }

    fn settle(&mut self, v: f32, p: &SideVoicing) -> f32 {
        let drift = self.drift.settle(v.max(p.drift_level) - p.drift_level);
        let v = v - drift * p.drift_depth;
        let load = self.comp.settle((v * p.clip.inv()).abs().min(1.));
        let ceiling = p.clip.value() / (1. + load * p.comp_depth);
        let v = soft_clip_up(v, p.clip_corner, ceiling);
        soft_clip_down(v, p.cross_corner, 0.)
    }
}

/// Push-pull tetrode power stage.
#[derive(Debug, Clone)]
pub struct Tetrode {
    sample_rate: f32,
    controls: TetrodeControls,
    grid_offset1: f32,
    grid_offset2: f32,
    grid_hp: OnePole,
    grid_smooth: Smoother,
    grid_level: f32,
    grid_rise: f32,
    grid_fall: f32,
    grid_cap: Divisor,
    grid_charge: Charge,
    scale: f32,
    clip: Divisor,
    side: SideVoicing,
    positive: Side,
    negative: Side,
    sag_onset: f32,
    sag_factor_inv: f32,
    sag_rise: f32,
    sag_fall: f32,
    sag_charge: Charge,
    sag_gain: f32,
    sag_makeup: f32,
    band_hp: OnePole,
    band_lp: OnePole,
    drift2_level: f32,
    drift2_depth: f32,
    drift2_smooth: Smoother,
}

impl Tetrode {
    pub fn new(sample_rate: f32) -> Self {
        let mut tetrode = Self {
            sample_rate,
            controls: TetrodeControls::default(),
            grid_offset1: 0.,
            grid_offset2: 0.,
            grid_hp: OnePole::default(),
            grid_smooth: Smoother::default(),
            grid_level: 0.,
            grid_rise: 0.,
            grid_fall: 0.,
            grid_cap: Divisor::default(),
            grid_charge: Charge::default(),
            scale: 1.,
            clip: Divisor::default(),
            side: SideVoicing::default(),
            positive: Side::default(),
            negative: Side::default(),
            sag_onset: 0.,
            sag_factor_inv: 1.,
            sag_rise: 0.,
            sag_fall: 0.,
            sag_charge: Charge::default(),
            sag_gain: 0.,
            sag_makeup: 1.,
            band_hp: OnePole::default(),
            band_lp: OnePole::default(),
            drift2_level: 0.,
            drift2_depth: 0.,
            drift2_smooth: Smoother::default(),
        };
        tetrode.configure(TetrodeControls::default());
        tetrode
    }

    pub fn prepare(&mut self, sample_rate: f32) {
        self.sample_rate = sample_rate;
        self.configure(self.controls);
        self.reset();
    }

    pub fn reset(&mut self) {
        self.grid_hp.reset();
        self.grid_smooth.reset();
        self.grid_charge.reset();
        self.positive.reset();
        self.negative.reset();
        self.sag_charge.reset();
        self.band_hp.reset();
        self.band_lp.reset();
        self.drift2_smooth.reset();
    }

    pub fn settle(&mut self, x: f32) -> f32 {
        let g = self.grid_hp.settle(x - self.grid_offset1) - self.grid_offset2;
        let g = g - self.grid_smooth.settle(g);
        let excess = (g - self.grid_level).max(0.);
        let g = g - self.grid_charge.settle_capped(
            excess,
            self.grid_rise,
            self.grid_fall,
            self.grid_cap,
        );
        let v = g * self.scale;
        let side = &self.side;
        let pushed = self.positive.settle(v, side) - self.negative.settle(-v, side);
        let draw = (v * self.clip.inv()).abs();
        let demand = (self.sag_onset * draw.min(1.) + draw.max(1.)) * self.sag_factor_inv;
        let sag = self.sag_charge.settle(demand, self.sag_rise, self.sag_fall);
        let y = pushed / (1. + sag * self.sag_gain) * self.sag_makeup;
        let y = self.band_lp.settle(self.band_hp.settle(y));
        let drift = self
            .drift2_smooth
            .settle(y.abs().max(self.drift2_level) - self.drift2_level);
        y + drift * self.drift2_depth
    }

    pub fn configure(&mut self, controls: TetrodeControls) {
        use tetrode::*;
        let sr = self.sample_rate;
        self.controls = controls;
        self.grid_offset1 = GRID_OFFSET1.fixed();
        self.grid_offset2 = GRID_OFFSET2.fixed();
        self.grid_hp
            .set_highpass(GRID_HP_FREQ.at(controls.hp_freq), sr);
        self.grid_smooth
            .set_pole(tau_to_pole(GRID_TAUS.fixed(), sr));
        self.grid_level = GRID_LEVEL.fixed();
        let tau = GRID_TAU.at(controls.tau);
        self.grid_rise = charge_rate(tau, sr);
        self.grid_fall = charge_rate(tau * GRID_RATIO.at(controls.ratio), sr);
        self.grid_cap = Divisor::new(GRID_CAP.fixed());

        self.scale = SCALE.fixed();
        self.clip = Divisor::new(CLIP.fixed());
        let drift_pole = tau_to_pole(DRIFT_TAU.fixed(), sr);
        let comp_pole = tau_to_pole(COMP_TAU.fixed(), sr);
        self.side = SideVoicing {
            drift_level: DRIFT_LEVEL.fixed(),
            drift_depth: DRIFT_DEPTH.fixed(),
            clip: self.clip,
            clip_corner: Divisor::new(CLIP_CORNER.fixed()),
            comp_depth: COMP_DEPTH.at(controls.comp_depth),
            cross_corner: Divisor::new(CROSS_CORNER.fixed()),
        };
        for side in [&mut self.positive, &mut self.negative] {
            side.drift.set_pole(drift_pole);
            side.comp.set_pole(comp_pole);
        }
        let sag_tau = SAG_TAU.at(controls.sag_tau);
        let sag_amount = SAG_DEPTH.at(controls.sag_depth) * SAG_TOGGLE.at(controls.sag_toggle);
        self.sag_onset = SAG_ONSET.at(controls.sag_onset);
        self.sag_factor_inv = 1. / (1. + controls.sag_factor.max(0.));
        self.sag_rise = charge_rate(sag_tau, sr);
        self.sag_fall = charge_rate(sag_tau * SAG_RATIO.at(controls.sag_ratio), sr);
        self.sag_gain = sag_amount;
        self.sag_makeup = 1. + sag_amount;
        self.band_hp.set_highpass(HP_FREQ.fixed(), sr);
        self.band_lp.set_lowpass(LP_FREQ.fixed(), sr);
        self.drift2_level = DRIFT2_LEVEL.fixed();
        self.drift2_depth = DRIFT2_DEPTH.fixed();
        self.drift2_smooth.set_pole(drift_pole);
    }

    #[inline]
    pub fn process(&mut self, x: f32) -> f32 {
        let g = self.grid_hp.process(x - self.grid_offset1) - self.grid_offset2;
        let g = g - self.grid_smooth.process(g);
        let excess = (g - self.grid_level).max(0.);
        let g =
            g - self
                .grid_charge
                .step_capped(excess, self.grid_rise, self.grid_fall, self.grid_cap);
        let v = g * self.scale;
        let side = &self.side;
        let pushed = self.positive.process(v, side) - self.negative.process(-v, side);
        let draw = (v * self.clip.inv()).abs();
        let demand = (self.sag_onset * draw.min(1.) + draw.max(1.)) * self.sag_factor_inv;
        let sag = self.sag_charge.step(demand, self.sag_rise, self.sag_fall);
        let y = pushed / (1. + sag * self.sag_gain) * self.sag_makeup;
        let y = self.band_lp.process(self.band_hp.process(y));
        let drift = self
            .drift2_smooth
            .process(y.abs().max(self.drift2_level) - self.drift2_level);
        y + drift * self.drift2_depth
    }
}
