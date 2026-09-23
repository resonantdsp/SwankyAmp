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

    /// The steady-state complex gain at `omega` radians per sample, so offline
    /// tools can measure a configured filter without running audio through it.
    pub(crate) fn response(&self, omega: f64) -> Complex {
        let z1 = Complex::polar(-omega);
        let z2 = z1 * z1;
        let numerator =
            Complex::real(self.b0.into()) + z1 * f64::from(self.b1) + z2 * f64::from(self.b2);
        let denominator = Complex::real(1.) + z1 * f64::from(self.a1) + z2 * f64::from(self.a2);
        numerator / denominator
    }

    pub(crate) fn settle(&mut self, input: f32) -> f32 {
        let output = (self.b0 + self.b1 + self.b2) * input / (1. + self.a1 + self.a2);
        self.s1 = output - self.b0 * input;
        self.s2 = self.b2 * input - self.a2 * output;
        output
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Default)]
pub(crate) struct Complex {
    pub re: f64,
    pub im: f64,
}

impl Complex {
    pub(crate) fn real(re: f64) -> Self {
        Self { re, im: 0. }
    }

    pub(crate) fn polar(angle: f64) -> Self {
        Self {
            re: angle.cos(),
            im: angle.sin(),
        }
    }

    pub(crate) fn norm_squared(self) -> f64 {
        self.re * self.re + self.im * self.im
    }
}

impl std::ops::Add for Complex {
    type Output = Self;
    fn add(self, other: Self) -> Self {
        Self {
            re: self.re + other.re,
            im: self.im + other.im,
        }
    }
}

impl std::ops::Mul for Complex {
    type Output = Self;
    fn mul(self, other: Self) -> Self {
        Self {
            re: self.re * other.re - self.im * other.im,
            im: self.re * other.im + self.im * other.re,
        }
    }
}

impl std::ops::Mul<f64> for Complex {
    type Output = Self;
    fn mul(self, scale: f64) -> Self {
        Self {
            re: self.re * scale,
            im: self.im * scale,
        }
    }
}

impl std::ops::Div for Complex {
    type Output = Self;
    fn div(self, other: Self) -> Self {
        let scale = 1. / other.norm_squared();
        Self {
            re: (self.re * other.re + self.im * other.im) * scale,
            im: (self.im * other.re - self.re * other.im) * scale,
        }
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

/// The curve a soft clip follows between its knee and its ceiling.
///
/// The released Faust model scaled its cubic clip input by 1/3.4, so the
/// curve leaves the knee with slope 4/3.4 while the linear side arrives with
/// slope 1: every clip has a small corner. Scaling by 1/4 gives the cubic unit
/// slope at the knee, joining it smoothly, at the cost of slightly less gain
/// between the knee and the ceiling, which the triode stages make up.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ClipKnee {
    Released,
    UnitSlope,
}

impl ClipKnee {
    /// Input span, in corner units, over which the cubic reaches its ceiling.
    pub(crate) fn span(self) -> Divisor {
        match self {
            Self::Released => Divisor::new(3.4),
            Self::UnitSlope => Divisor::new(4.),
        }
    }
}

#[inline]
fn saturate(value: f32, span: Divisor) -> f32 {
    // Dividing, as the released model did, keeps its path bit-identical;
    // the unit span of 4 divides exactly.
    let first = (value / span.value()).clamp(-1., 1.);
    let second = (first.abs() - 2.) * first;
    (second.abs() - 2.) * second
}

#[inline]
pub(crate) fn soft_clip_up(input: f32, scale: Divisor, level: f32, span: Divisor) -> f32 {
    let knee = level - scale.value();
    let delta = input - knee;
    delta.min(0.) + saturate(delta.max(0.) * scale.inverse(), span) * scale.value() + knee
}

#[inline]
pub(crate) fn soft_clip_down(input: f32, scale: Divisor, level: f32, span: Divisor) -> f32 {
    let knee = level + scale.value();
    let delta = input - knee;
    saturate(delta.min(0.) * scale.inverse(), span) * scale.value() + delta.max(0.) + knee
}

pub(crate) fn db_to_gain(db: f32) -> f32 {
    10_f32.powf(db / 20.)
}

#[cfg(test)]
mod tests {
    use super::*;

    fn slopes_either_side_of_knee(span: Divisor) -> [(f32, f32); 2] {
        const STEP: f32 = 1e-3;
        let (scale, level) = (Divisor::new(0.5), 1.);
        let up = |x| soft_clip_up(x, scale, level, span);
        let down = |x| soft_clip_down(x, scale, -level, span);
        let (up_knee, down_knee) = (level - scale.value(), -level + scale.value());
        [
            (
                (up(up_knee) - up(up_knee - STEP)) / STEP,
                (up(up_knee + STEP) - up(up_knee)) / STEP,
            ),
            (
                (down(down_knee) - down(down_knee - STEP)) / STEP,
                (down(down_knee + STEP) - down(down_knee)) / STEP,
            ),
        ]
    }

    #[test]
    fn unit_slope_knee_has_no_corner() {
        for (below, above) in slopes_either_side_of_knee(ClipKnee::UnitSlope.span()) {
            assert!(
                (below - above).abs() < 0.01,
                "unit knee slope jumps from {below} to {above} at the knee"
            );
        }
        // The same probe resolves the released corner, so it can detect one.
        for (below, above) in slopes_either_side_of_knee(ClipKnee::Released.span()) {
            assert!(
                (below - above).abs() > 0.1,
                "probe did not resolve the released corner ({below} to {above})"
            );
        }
    }
}
