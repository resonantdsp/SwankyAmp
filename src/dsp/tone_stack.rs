use super::filters::Biquad;

#[derive(Debug, Clone, Copy, PartialEq, Default)]
pub(crate) struct ToneControls {
    pub bass: f32,
    pub mids: f32,
    pub treble: f32,
    pub presence: f32,
    pub model: f32,
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

    fn settle(&mut self, input: f32) -> f32 {
        self.treble_gain * self.treble.settle(input)
            + self.mid_low_gain * self.mid_low.settle(input)
    }
}

#[derive(Debug, Clone)]
pub(crate) struct ToneStack {
    sample_rate: f32,
    controls: ToneControls,
    fender: Stack,
    marshall: Stack,
    ac30: Stack,
    ac30_mids: Biquad,
    presence: Biquad,
    weights: [f32; 3],
}

impl ToneStack {
    pub(crate) fn new(sample_rate: f32) -> Self {
        let mut stack = Self {
            sample_rate,
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
        // The 1.4.0 Faust graph used SR rather than 2*SR here. RD-245 replaces
        // this octave-high mapping after the released baseline is proved.
        let c = f64::from(self.sample_rate);
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
            let (b, a) = discretise(
                [0., treble * c1 * r1 * r1, 0.],
                [r1 + ri, ((r1 + ri) * r2 + ri * r1) * c1, 0.],
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
            let (b, a) = discretise(
                [0., treble * c1 * r1 * r1, 0.],
                [r1 + ri, ((r1 + ri) * r2 + ri * r1) * c1, 0.],
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
            let (b, a) = discretise(
                [r2, ((r2 + treble * r1) * r3 + r1 * r2) * c1, 0.],
                [
                    r2 + r1 + ri,
                    ((r2 + r1 + ri) * r3 + r1 * (r2 + ri)) * c1,
                    0.,
                ],
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

    pub(crate) fn settle(&mut self, input: f32) -> f32 {
        let fender = self.fender.settle(input);
        let marshall = self.marshall.settle(input);
        let ac30 = self.ac30_mids.settle(self.ac30.settle(input));
        let [fender_weight, marshall_weight, ac30_weight] = self.weights;
        self.presence
            .settle(fender_weight * fender + marshall_weight * marshall + ac30_weight * ac30)
    }
}
