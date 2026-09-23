use super::filters::{Biquad, Complex};

#[derive(Debug, Clone, Copy, PartialEq, Default)]
pub(crate) struct ToneControls {
    pub bass: f32,
    pub mids: f32,
    pub treble: f32,
    pub presence: f32,
    pub model: f32,
}

/// How the tone circuits' analogue transfer functions become digital filters.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ToneMapping {
    /// The 1.4.0 Faust constant `c = SR`, which voices every feature an
    /// octave above the circuit. Kept for the legacy path that the model gate
    /// compares with the frozen released renders.
    Released,
    /// The standard bilinear constant `c = 2·SR`, placing features where the
    /// circuit has them. The shipping path uses it with refitted presets.
    Standard,
}

impl ToneMapping {
    fn bilinear_constant(self, sample_rate: f32) -> f64 {
        match self {
            Self::Released => f64::from(sample_rate),
            Self::Standard => 2. * f64::from(sample_rate),
        }
    }

    /// The treble sections are first order. The released mapping keeps the
    /// 1.4.0 second-order form, Nyquist pole included, so the legacy path
    /// stays bit-identical to the frozen renders.
    fn first_order(self, b: [f64; 2], a: [f64; 2], c: f64) -> ([f32; 3], [f32; 2]) {
        match self {
            Self::Released => discretise([b[0], b[1], 0.], [a[0], a[1], 0.], c),
            Self::Standard => discretise_first_order(b, a, c),
        }
    }
}

fn discretise(b: [f64; 3], a: [f64; 3], c: f64) -> ([f32; 3], [f32; 2]) {
    let [b0, b1, b2] = b;
    let [a0, a1, a2] = a;
    let normal = 1. / (a0 + a1 * c + a2 * c * c);
    (
        [
            (normal * (b0 + b1 * c + b2 * c * c)) as f32,
            (normal * (2. * b0 - 2. * b2 * c * c)) as f32,
            (normal * (b0 - b1 * c + b2 * c * c)) as f32,
        ],
        [
            (normal * (2. * a0 - 2. * a2 * c * c)) as f32,
            (normal * (a0 - a1 * c + a2 * c * c)) as f32,
        ],
    )
}

/// Discretises a first-order section `(b0 + b1·s) / (a0 + a1·s)`.
///
/// Released 1.4.0 passed these through the second-order `discretise` with
/// `a2 = b2 = 0`, which multiplies numerator and denominator by `1 + z⁻¹`: a
/// pole on the unit circle at Nyquist, cancelled only in exact arithmetic.
/// Rounded to f32 that pole can land a few parts in 10⁹ outside the circle
/// (the Marshall treble at 88.2 kHz, the Fender treble at 176.4 kHz), so
/// rounding noise at Nyquist grows until it swamps the signal after hours of
/// play. The true first-order section has no such pole.
fn discretise_first_order(b: [f64; 2], a: [f64; 2], c: f64) -> ([f32; 3], [f32; 2]) {
    let [b0, b1] = b;
    let [a0, a1] = a;
    let normal = 1. / (a0 + a1 * c);
    (
        [
            (normal * (b0 + b1 * c)) as f32,
            (normal * (b0 - b1 * c)) as f32,
            0.,
        ],
        [(normal * (a0 - a1 * c)) as f32, 0.],
    )
}

fn knob(unit: f32) -> f64 {
    0.495 * f64::from(unit) + 0.505
}

fn tapered(unit: f32) -> f64 {
    let value = knob(unit);
    if value <= 0.5 {
        0.2 * value
    } else {
        1.6 * value - 0.7
    }
}

#[derive(Debug, Clone, Copy, Default)]
struct Stack {
    treble: Biquad,
    mid_low: Biquad,
    treble_gain: f32,
    mid_low_gain: f32,
}

impl Stack {
    fn process(&mut self, input: f32) -> f32 {
        self.treble_gain * self.treble.process(input)
            + self.mid_low_gain * self.mid_low.process(input)
    }

    fn reset(&mut self) {
        self.treble.reset();
        self.mid_low.reset();
    }

    fn response(&self, omega: f64) -> Complex {
        self.treble.response(omega) * f64::from(self.treble_gain)
            + self.mid_low.response(omega) * f64::from(self.mid_low_gain)
    }

    fn settle(&mut self, input: f32) -> f32 {
        self.treble_gain * self.treble.settle(input)
            + self.mid_low_gain * self.mid_low.settle(input)
    }
}

#[derive(Debug, Clone)]
pub(crate) struct ToneStack {
    sample_rate: f32,
    mapping: ToneMapping,
    controls: ToneControls,
    fender: Stack,
    marshall: Stack,
    ac30: Stack,
    ac30_mids: Biquad,
    presence: Biquad,
    weights: [f32; 3],
}

impl ToneStack {
    pub(crate) fn new(sample_rate: f32, mapping: ToneMapping) -> Self {
        let mut stack = Self {
            sample_rate,
            mapping,
            controls: ToneControls::default(),
            fender: Stack::default(),
            marshall: Stack::default(),
            ac30: Stack::default(),
            ac30_mids: Biquad::default(),
            presence: Biquad::default(),
            weights: [1., 0., 0.],
        };
        stack.configure(ToneControls::default());
        stack
    }

    pub(crate) fn prepare(&mut self, sample_rate: f32) {
        self.sample_rate = sample_rate;
        self.configure(self.controls);
        self.reset();
    }

    pub(crate) fn reset(&mut self) {
        self.fender.reset();
        self.marshall.reset();
        self.ac30.reset();
        self.ac30_mids.reset();
        self.presence.reset();
    }

    pub(crate) fn configure(&mut self, controls: ToneControls) {
        self.controls = controls;
        let c = self.mapping.bilinear_constant(self.sample_rate);
        let sample_rate = self.sample_rate;
        let treble = knob(controls.treble);
        let mids = knob(controls.mids);

        {
            let bass = knob(controls.bass);
            let bass_squared = bass * bass;
            let (c1, c2) = (100e-9, 47e-9);
            let (r1, r2, r3, ri) = (100e3, 250e3, 10e3, 38e3);
            let b2 = bass_squared * mids * c1 * c2 * r2 * r3;
            let b1 = (mids * c2 + mids * c1) * r3 + bass_squared * c1 * r2;
            let a2 = bass_squared * mids * c1 * c2 * r2 * r3
                + (bass_squared * c1 * c2 * r1 + bass_squared * ri * c1 * c2) * r2;
            let a1 = (mids * c2 + mids * c1) * r3
                + bass_squared * c1 * r2
                + (c2 + c1) * r1
                + ri * c2
                + ri * c1;
            let (b, a) = discretise([0., b1, b2], [1., a1, a2], c);
            self.fender.mid_low.set_digital(b, a);
            self.fender.mid_low_gain = 4.;
            let c1 = 250e-12;
            let (b, a) = self.mapping.first_order(
                [0., treble * c1 * r1 * r1],
                [r1 + ri, ((r1 + ri) * r2 + ri * r1) * c1],
                c,
            );
            self.fender.treble.set_digital(b, a);
            self.fender.treble_gain = 12.;
        }

        {
            let bass = tapered(controls.bass);
            let (c1, c2) = (22e-9, 22e-9);
            let (r1, r2, r3, ri) = (33e3, 1e6, 22e3, 0.);
            let b2 = ((mids * mids - mids) * r3 * r3 - bass * mids * r2 * r3) * c1 * c2;
            let b1 = (-mids * c2 - c1) * r3 - bass * c1 * r2;
            let a2 = ((mids * mids - mids) * r3 * r3
                + (-bass * mids * r2 + (mids - 1.) * r1 + (mids - 1.) * ri) * r3
                + (-bass * r1 - bass * ri) * r2)
                * c1
                * c2;
            let a1 = (-mids * c2 - c1) * r3 - bass * c1 * r2 + (-c2 - c1) * r1 - ri * c2 - ri * c1;
            let (b, a) = discretise([0., b1, b2], [-1., a1, a2], c);
            self.marshall.mid_low.set_digital(b, a);
            self.marshall.mid_low_gain = 1.4;
            let c1 = 470e-12;
            let (r1, r2) = (33e3, 220e3);
            let (b, a) = self.mapping.first_order(
                [0., treble * c1 * r1 * r1],
                [r1 + ri, ((r1 + ri) * r2 + ri * r1) * c1],
                c,
            );
            self.marshall.treble.set_digital(b, a);
            self.marshall.treble_gain = 6.;
        }

        {
            let bass = tapered(controls.bass);
            let bass_squared = bass * bass - bass;
            let (c1, c2) = (22e-9, 100e-9);
            let (r1, r2, r3, r4, r5, ri) = (100e3, 10e3, 250e3, 250e3, 150e3, 56e3);
            let b2 = bass_squared * c1 * c2 * r2 * r4 * r4 * r5;
            let b1 = (bass_squared * c2 * r4 * r4 + ((bass - 1.) * c1 - c2) * r2 * r4) * r5;
            let a2 = ((r2 + r1 + ri) * bass_squared * c1 * c2 * r4 * r4
                - (r1 + ri) * bass * c1 * c2 * r2 * r4)
                * r5
                + ((r2 + r1 + ri) * bass_squared * treble * c1 * c2 * r3
                    + (r1 + ri) * bass_squared * c1 * c2 * r2)
                    * r4
                    * r4
                - (r1 + ri) * bass * treble * c1 * c2 * r2 * r3 * r4;
            let a1 = (bass_squared * c2 * r4 * r4
                + (c1 * r2 + (c2 + c1) * r1 + ri * c2 + ri * c1) * (bass - 1.) * r4
                - r2 * c2 * r4
                + ((-c2 - c1) * r1 - ri * c2 - ri * c1) * r2)
                * r5
                + (treble * c2 * r3 + c1 * r2 + (c2 + c1) * r1 + ri * c2 + ri * c1)
                    * bass_squared
                    * r4
                    * r4
                + ((((bass - 1.) * treble * c1 - treble * c2) * r2
                    + ((bass - 1.) * treble * c2 + (bass - 1.) * treble * c1) * r1
                    + (bass - 1.) * ri * treble * c2
                    + (bass - 1.) * ri * treble * c1)
                    * r3
                    + ((-c2 - c1) * r1 - ri * c2 - ri * c1) * r2)
                    * r4
                + ((-treble * c2 - treble * c1) * r1 - ri * treble * c2 - ri * treble * c1)
                    * r2
                    * r3;
            let a0 = ((bass - 1.) * r4 - r2) * r5
                + bass_squared * r4 * r4
                + ((bass - 1.) * treble * r3 - r2) * r4
                - treble * r2 * r3;
            let (b, a) = discretise([0., b1, b2], [a0, a1, a2], c);
            self.ac30.mid_low.set_digital(b, a);
            self.ac30.mid_low_gain = 8.;
            let c1 = 560e-12;
            let ri = 48e3;
            let (b, a) = self.mapping.first_order(
                [r2, ((r2 + treble * r1) * r3 + r1 * r2) * c1],
                [r2 + r1 + ri, ((r2 + r1 + ri) * r3 + r1 * (r2 + ri)) * c1],
                c,
            );
            self.ac30.treble.set_digital(b, a);
            self.ac30.treble_gain = 1.5;
        }

        self.ac30_mids
            .set_peak(10. * controls.mids, 1e3, 2e3, sample_rate);
        self.presence
            .set_peak(10. * controls.presence, 4e3, 2e3, sample_rate);
        let selection = controls.model;
        self.weights = [
            1. - selection.clamp(0., 1.),
            1. - (selection - 1.).abs().clamp(0., 1.),
            selection.clamp(1., 2.) - 1.,
        ];
    }

    #[inline]
    pub(crate) fn process(&mut self, input: f32) -> f32 {
        let fender = self.fender.process(input);
        let marshall = self.marshall.process(input);
        let ac30 = self.ac30_mids.process(self.ac30.process(input));
        let [fender_weight, marshall_weight, ac30_weight] = self.weights;
        self.presence
            .process(fender_weight * fender + marshall_weight * marshall + ac30_weight * ac30)
    }

    /// The configured stack's steady-state complex gain at `frequency` Hz.
    pub(crate) fn response(&self, frequency: f64) -> Complex {
        let omega = std::f64::consts::TAU * frequency / f64::from(self.sample_rate);
        let [fender_weight, marshall_weight, ac30_weight] = self.weights.map(f64::from);
        let mixed = self.fender.response(omega) * fender_weight
            + self.marshall.response(omega) * marshall_weight
            + self.ac30_mids.response(omega) * self.ac30.response(omega) * ac30_weight;
        self.presence.response(omega) * mixed
    }

    pub(crate) fn settle(&mut self, input: f32) -> f32 {
        let fender = self.fender.settle(input);
        let marshall = self.marshall.settle(input);
        let ac30 = self.ac30_mids.settle(self.ac30.settle(input));
        let [fender_weight, marshall_weight, ac30_weight] = self.weights;
        self.presence
            .settle(fender_weight * fender + marshall_weight * marshall + ac30_weight * ac30)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Peak output in the last second of `seconds` of silence that follows
    /// one second of noise at the level the stack sees at high gain.
    fn tail_peak(sample_rate: f32, controls: ToneControls, seconds: f32) -> f32 {
        let mut stack = ToneStack::new(sample_rate, ToneMapping::Standard);
        stack.configure(controls);
        let mut state = 1_u32;
        for _ in 0..sample_rate as usize {
            state = state.wrapping_mul(1_664_525).wrapping_add(1_013_904_223);
            stack.process(10. * (state as f32 / u32::MAX as f32 * 2. - 1.));
        }
        let silence = (sample_rate * seconds) as usize;
        let last = silence - sample_rate as usize;
        (0..silence)
            .map(|_| stack.process(0.))
            .skip(last)
            .fold(0., |peak, sample| peak.max(sample.abs()))
    }

    #[test]
    fn stack_falls_silent_after_the_input_stops() {
        for sample_rate in [44_100., 88_200., 176_400.] {
            for model in [0., 1., 2.] {
                for knobs in [-1., 1.] {
                    let controls = ToneControls {
                        bass: knobs,
                        mids: knobs,
                        treble: knobs,
                        presence: knobs,
                        model,
                    };
                    let peak = tail_peak(sample_rate, controls, 3.);
                    assert!(
                        peak < 1e-9,
                        "{sample_rate} Hz, stack {model}, knobs {knobs}: output still {peak:e} \
                         two seconds after a signal at level 10 stopped"
                    );
                }
            }
        }
    }

    /// Frequency of the deepest cut between 100 Hz and 5 kHz, measured from
    /// the stack's impulse response.
    fn mid_notch(mapping: ToneMapping) -> f64 {
        const SAMPLE_RATE: f32 = 96_000.;
        let mut stack = ToneStack::new(SAMPLE_RATE, mapping);
        let impulse: Vec<f64> = (0..16_384)
            .map(|index| f64::from(stack.process(if index == 0 { 1. } else { 0. })))
            .collect();
        (0..=270)
            .map(|step| 100. * 2_f64.powf(f64::from(step) / 48.))
            .map(|frequency| {
                let omega = std::f64::consts::TAU * frequency / f64::from(SAMPLE_RATE);
                let (real, imaginary) = impulse.iter().enumerate().fold(
                    (0., 0.),
                    |(real, imaginary), (index, sample)| {
                        let (sin, cos) = (omega * index as f64).sin_cos();
                        (real + sample * cos, imaginary - sample * sin)
                    },
                );
                (frequency, real.hypot(imaginary))
            })
            .min_by(|left, right| left.1.total_cmp(&right.1))
            .map(|(frequency, _)| frequency)
            .unwrap()
    }

    #[test]
    fn standard_mapping_places_the_mid_cut_an_octave_below_the_released_one() {
        let released = mid_notch(ToneMapping::Released);
        let standard = mid_notch(ToneMapping::Standard);
        let octaves = (released / standard).log2();
        assert!(
            (octaves - 1.).abs() < 0.05,
            "mid cut moved {octaves:.3} octaves: released {released:.0} Hz, standard {standard:.0} Hz"
        );
    }
}
