use std::f32::consts::PI;

const MAX_FREQUENCY_RATIO: f32 = 0.45;

fn clamp_frequency(frequency: f32, sample_rate: f32) -> f32 {
    frequency.clamp(1e-3, sample_rate * MAX_FREQUENCY_RATIO)
}

#[derive(Debug, Clone, Copy, Default)]
pub(crate) struct OnePole {
    b0: f32,
    b1: f32,
    a1: f32,
    x1: f32,
    y1: f32,
}

impl OnePole {
    pub(crate) fn set_lowpass(&mut self, frequency: f32, sample_rate: f32) {
        self.set_analogue(0., 1., 1., frequency, sample_rate);
    }

    pub(crate) fn set_highpass(&mut self, frequency: f32, sample_rate: f32) {
        self.set_analogue(1., 0., 1., frequency, sample_rate);
    }

    pub(crate) fn set_digital(&mut self, b0: f32, b1: f32, a1: f32) {
        self.b0 = b0;
        self.b1 = b1;
        self.a1 = a1;
    }

    fn set_analogue(&mut self, b1: f32, b0: f32, a0: f32, frequency: f32, sample_rate: f32) {
        let frequency = clamp_frequency(frequency, sample_rate);
        let c = 1. / (PI * frequency / sample_rate).tan();
        let divisor = a0 + c;
        self.b0 = (b0 + b1 * c) / divisor;
        self.b1 = (b0 - b1 * c) / divisor;
        self.a1 = (a0 - c) / divisor;
    }

    #[inline]
    pub(crate) fn process(&mut self, input: f32) -> f32 {
        let output = self.b0 * input + self.b1 * self.x1 - self.a1 * self.y1;
        self.x1 = input;
        self.y1 = output;
        output
    }

    pub(crate) fn reset(&mut self) {
        self.x1 = 0.;
        self.y1 = 0.;
    }

    pub(crate) fn settle(&mut self, input: f32) -> f32 {
        let output = (self.b0 + self.b1) * input / (1. + self.a1);
        self.x1 = input;
        self.y1 = output;
        output
    }
}

#[derive(Debug, Clone, Copy, Default)]
pub(crate) struct Biquad {
    b0: f32,
    b1: f32,
    b2: f32,
    a1: f32,
    a2: f32,
    s1: f32,
    s2: f32,
}

impl Biquad {
    pub(crate) fn set_analogue(
        &mut self,
        b: [f32; 3],
        a1: f32,
        a0: f32,
        frequency: f32,
        sample_rate: f32,
    ) {
        let frequency = clamp_frequency(frequency, sample_rate);
        let c = 1. / (PI * frequency / sample_rate).tan();
        let c_squared = c * c;
        let [b2, b1, b0] = b;
        let divisor = a0 + a1 * c + c_squared;
        self.b0 = (b0 + b1 * c + b2 * c_squared) / divisor;
        self.b1 = 2. * (b0 - b2 * c_squared) / divisor;
        self.b2 = (b0 - b1 * c + b2 * c_squared) / divisor;
        self.a1 = 2. * (a0 - c_squared) / divisor;
        self.a2 = (a0 - a1 * c + c_squared) / divisor;
    }

    pub(crate) fn set_digital(&mut self, b: [f32; 3], a: [f32; 2]) {
        [self.b0, self.b1, self.b2] = b;
        [self.a1, self.a2] = a;
    }

    pub(crate) fn set_peak(
        &mut self,
        level_db: f32,
        frequency: f32,
        bandwidth: f32,
        sample_rate: f32,
    ) {
        let frequency = clamp_frequency(frequency, sample_rate);
        let omega = 2. * PI * frequency;
        let period = 1. / sample_rate;
        let warped_bandwidth = bandwidth * period / (omega * period).sin();
        let denominator = PI * warped_bandwidth;
        let numerator = db_to_gain(level_db.abs()) * denominator;
        let (b1, a1) = if level_db > 0. {
            (numerator, denominator)
        } else {
            (denominator, numerator)
        };
        self.set_analogue([1., b1, 1.], a1, 1., frequency, sample_rate);
    }

    #[inline]
    pub(crate) fn process(&mut self, input: f32) -> f32 {
        let output = self.b0 * input + self.s1;
        self.s1 = self.b1 * input - self.a1 * output + self.s2;
        self.s2 = self.b2 * input - self.a2 * output;
        output
    }

    pub(crate) fn reset(&mut self) {
        self.s1 = 0.;
        self.s2 = 0.;
    }

    pub(crate) fn settle(&mut self, input: f32) -> f32 {
        let output = (self.b0 + self.b1 + self.b2) * input / (1. + self.a1 + self.a2);
        self.s1 = output - self.b0 * input;
        self.s2 = self.b2 * input - self.a2 * output;
        output
    }
}

#[derive(Debug, Clone, Copy, Default)]
pub(crate) struct Smoother {
    pole: f32,
    value: f32,
}

impl Smoother {
    pub(crate) fn set_pole(&mut self, pole: f32) {
        self.pole = pole;
    }

    #[inline]
    pub(crate) fn process(&mut self, input: f32) -> f32 {
        self.value = (1. - self.pole) * input + self.pole * self.value;
        self.value
    }

    pub(crate) fn reset(&mut self) {
        self.value = 0.;
    }

    pub(crate) fn settle(&mut self, input: f32) -> f32 {
        self.value = input;
        input
    }
}

pub(crate) fn tau_to_pole(tau: f32, sample_rate: f32) -> f32 {
    if tau.abs() < f32::EPSILON {
        0.
    } else {
        (-1. / (tau * sample_rate)).exp()
    }
}

pub(crate) fn charge_rate(tau: f32, sample_rate: f32) -> f32 {
    1. / (tau * sample_rate + 1.)
}

#[derive(Debug, Clone, Copy)]
pub(crate) struct Divisor {
    value: f32,
    inverse: f32,
}

impl Divisor {
    pub(crate) fn new(value: f32) -> Self {
        Self {
            value,
            inverse: 1. / value,
        }
    }

    pub(crate) fn value(self) -> f32 {
        self.value
    }

    pub(crate) fn inverse(self) -> f32 {
        self.inverse
    }

    pub(crate) fn inv(self) -> f32 {
        self.inverse
    }
}

impl Default for Divisor {
    fn default() -> Self {
        Self::new(1.)
    }
}

#[derive(Debug, Clone, Copy, Default)]
pub(crate) struct Charge {
    value: f32,
}

impl Charge {
    #[inline]
    pub(crate) fn step(&mut self, signal: f32, rise: f32, fall: f32) -> f32 {
        let value = self.value;
        self.value = value + rise * (signal - value).max(0.) - fall * value;
        self.value
    }

    #[inline]
    pub(crate) fn step_capped(&mut self, signal: f32, rise: f32, fall: f32, cap: Divisor) -> f32 {
        let value = self.value;
        self.value = value
            + rise * (cap.value() - value).max(0.) * cap.inverse() * (signal - value).max(0.)
            - fall * value;
        self.value
    }

    pub(crate) fn reset(&mut self) {
        self.value = 0.;
    }

    pub(crate) fn settle(&mut self, signal: f32, rise: f32, fall: f32) -> f32 {
        self.value = if rise > 0. {
            rise * signal.max(0.) / (rise + fall)
        } else {
            0.
        };
        self.value
    }

    pub(crate) fn settle_capped(&mut self, signal: f32, rise: f32, fall: f32, cap: Divisor) -> f32 {
        let signal = signal.max(0.);
        if rise <= 0. || signal == 0. {
            self.value = 0.;
            return self.value;
        }
        let capacity = cap.value();
        let middle = rise * (capacity + signal) + fall * capacity;
        let discriminant = (middle * middle - 4. * rise * rise * capacity * signal).max(0.);
        self.value = 2. * rise * capacity * signal / (middle + discriminant.sqrt());
        self.value
    }
}

/// The released Faust model scaled its cubic clip input by 1/3.4.
#[inline]
fn saturate(value: f32) -> f32 {
    let first = (value / 3.4).clamp(-1., 1.);
    let second = (first.abs() - 2.) * first;
    (second.abs() - 2.) * second
}

#[inline]
pub(crate) fn soft_clip_up(input: f32, scale: Divisor, level: f32) -> f32 {
    let knee = level - scale.value();
    let delta = input - knee;
    delta.min(0.) + saturate(delta.max(0.) * scale.inverse()) * scale.value() + knee
}

#[inline]
pub(crate) fn soft_clip_down(input: f32, scale: Divisor, level: f32) -> f32 {
    let knee = level + scale.value();
    let delta = input - knee;
    saturate(delta.min(0.) * scale.inverse()) * scale.value() + delta.max(0.) + knee
}

pub(crate) fn db_to_gain(db: f32) -> f32 {
    10_f32.powf(db / 20.)
}
