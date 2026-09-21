// Copyright (C) 2026 Garrin McGoldrick
// SPDX-License-Identifier: GPL-3.0-or-later

use std::array;
use std::f32::consts::PI;

const OFFSET_DB: f32 = 19.37125;
const HIGH_PASS_HZ: f32 = 111.0027;
const LOW_PASS_HZ: f32 = 10_998.76;
const CABINET_SHELF_HZ: f32 = 5_600.0;
const CABINET_SHELF_DB: f32 = -30.02781;

const PEAKS: [(f32, f32, f32); 10] = [
    (600.0, -25.00029, 29.93194),
    (640.0, 15.97118, 100.0074),
    (1_120.0, -15.07867, 49.99785),
    (1_180.0, 8.909575, 159.9996),
    (1_660.0, -3.531785, 790.1408),
    (3_050.0, -9.011323, 330.9512),
    (3_800.0, -5.999392, 749.9988),
    (7_200.0, -29.99869, 199.9953),
    (2_300.0, 3.0001, 750.0001),
    (4_900.0, -4.999868, 1_000.935),
];
const SCOOP: (f32, f32, f32) = (950.9019, -15.29571, 2_799.926);

/// The released Free cabinet: a fixed parametric cabinet response whose upper
/// range follows a 100 ms input envelope.
pub(crate) struct Cabinet {
    sample_rate: f32,
    brightness: f32,
    distance: f32,
    dynamic: f32,
    dynamic_level: f32,
    envelope: f32,
    envelope_pole: f32,
    high_pass: EvenOrderFilter<2>,
    low_pass: OddOrderSplit<1>,
    cabinet_shelf: OddOrderSplit<3>,
    cabinet_shelf_gain: f32,
    fixed_peaks: [Peak; 10],
    dynamic_peak: Peak,
    fixed_notch: Peak,
    low_shelf: OddOrderSplit<1>,
    brightness_peak: Peak,
    high_shelf: OddOrderSplit<1>,
    distance_peaks: [Peak; 2],
    output_gain: f32,
}

impl Cabinet {
    pub(crate) fn new(sample_rate: f32) -> Self {
        let sample_rate = valid_sample_rate(sample_rate);
        let mut cabinet = Self {
            sample_rate,
            brightness: 0.0,
            distance: 0.0,
            dynamic: 0.5,
            dynamic_level: 1.0,
            envelope: 0.0,
            envelope_pole: (-10.0 / sample_rate).exp(),
            high_pass: EvenOrderFilter::high_pass(
                sample_rate,
                HIGH_PASS_HZ,
                [1.847_759, 0.765_366_85],
            ),
            low_pass: OddOrderSplit::new(sample_rate, LOW_PASS_HZ, [1.0]),
            cabinet_shelf: OddOrderSplit::new(
                sample_rate,
                CABINET_SHELF_HZ,
                [1.801_937_7, 1.246_979_6, 0.445_041_87],
            ),
            cabinet_shelf_gain: db_to_gain(CABINET_SHELF_DB),
            fixed_peaks: array::from_fn(|_| Peak::default()),
            dynamic_peak: Peak::default(),
            fixed_notch: Peak::new(sample_rate, 100.0, -5.0, 200.0),
            low_shelf: OddOrderSplit::new(sample_rate, 1_100.0, [1.0]),
            brightness_peak: Peak::default(),
            high_shelf: OddOrderSplit::new(sample_rate, 6_500.0, [1.0]),
            distance_peaks: [Peak::default(), Peak::default()],
            output_gain: db_to_gain(OFFSET_DB),
        };

        for (peak, &(frequency, level, bandwidth)) in cabinet
            .fixed_peaks
            .iter_mut()
            .zip(PEAKS[..7].iter().chain(PEAKS[8..].iter()).chain([&SCOOP]))
        {
            peak.set(sample_rate, frequency, level, bandwidth);
        }
        cabinet.refresh_controls();
        cabinet
    }

    pub(crate) fn prepare(&mut self, sample_rate: f32) {
        let controls = (
            self.brightness,
            self.distance,
            self.dynamic,
            self.dynamic_level,
        );
        *self = Self::new(sample_rate);
        self.set_brightness(controls.0);
        self.set_distance(controls.1);
        self.set_dynamic(controls.2);
        self.set_dynamic_level(controls.3);
    }

    pub(crate) fn reset(&mut self) {
        self.envelope = 0.0;
        self.high_pass.reset();
        self.low_pass.reset();
        self.cabinet_shelf.reset();
        for peak in &mut self.fixed_peaks {
            peak.reset();
        }
        self.dynamic_peak.reset();
        self.fixed_notch.reset();
        self.low_shelf.reset();
        self.brightness_peak.reset();
        self.high_shelf.reset();
        for peak in &mut self.distance_peaks {
            peak.reset();
        }
    }

    /// Accepts the released sided mapping, -0.6..=0.6.
    pub(crate) fn set_brightness(&mut self, value: f32) {
        self.brightness = finite_or(value, 0.0).clamp(-0.6, 0.6);
        self.refresh_controls();
    }

    /// Accepts the released cabinet distance control, 0..=1.
    pub(crate) fn set_distance(&mut self, value: f32) {
        self.distance = finite_or(value, 0.0).clamp(0.0, 1.0);
        self.refresh_controls();
    }

    /// Accepts the released wrapper's mapped value, 0..=1.
    pub(crate) fn set_dynamic(&mut self, value: f32) {
        self.dynamic = finite_or(value, 0.5).clamp(0.0, 1.0);
    }

    /// Accepts the released wrapper's logarithmically mapped value, 0.5..=2.
    pub(crate) fn set_dynamic_level(&mut self, value: f32) {
        self.dynamic_level = finite_or(value, 1.0).clamp(0.5, 2.0);
    }

    pub(crate) fn process(&mut self, samples: &mut [f32]) {
        let detector_feed = 1.0 - self.envelope_pole;
        for sample in samples {
            let input = finite_or(*sample, 0.0);
            self.envelope =
                flush_denormal(self.envelope_pole * self.envelope + detector_feed * input.abs());
            let response = dynamic_response(self.envelope, self.dynamic_level);

            let mut value = self.high_pass.process(input);
            value = self.low_pass.process_low(value);
            let (low, high, scale) = self.cabinet_shelf.process_raw(value);
            value = scale * (low + self.cabinet_shelf_gain * high);

            for peak in &mut self.fixed_peaks[..7] {
                value = peak.process(value);
            }

            // Faust evaluates this level-dependent peak for every sample. Keeping
            // that baseline avoids block-size-dependent envelope quantisation.
            self.dynamic_peak.set(
                self.sample_rate,
                PEAKS[7].0 - 250.0 * self.dynamic * response,
                PEAKS[7].1 + 2.5 * self.dynamic * response,
                PEAKS[7].2 + 100.0 * self.dynamic * response,
            );
            value = self.dynamic_peak.process(value);

            for peak in &mut self.fixed_peaks[7..] {
                value = peak.process(value);
            }
            value = self.fixed_notch.process(value);

            let (low, high, scale) = self.low_shelf.process_raw(value);
            let low_gain = db_to_gain(1.5 * self.dynamic * response - 3.0 * self.brightness);
            value = scale * (high + low_gain * low);

            value = self.brightness_peak.process(value);

            let (low, high, scale) = self.high_shelf.process_raw(value);
            let high_gain = db_to_gain(-2.5 * self.dynamic * response);
            value = scale * (high_gain * high + low);

            for peak in &mut self.distance_peaks {
                value = peak.process(value);
            }

            let output = value * self.output_gain;
            *sample = if output.is_finite() { output } else { 0.0 };
        }
    }

    fn refresh_controls(&mut self) {
        self.brightness_peak
            .set(self.sample_rate, 6_000.0, 15.0 * self.brightness, 1_000.0);
        self.distance_peaks[0].set(self.sample_rate, 70.0, -10.0 * self.distance, 100.0);
        self.distance_peaks[1].set(self.sample_rate, 1_200.0, -17.0 * self.distance, 300.0);
        self.output_gain = db_to_gain(OFFSET_DB) * 10.0_f32.powf(0.1 * self.distance);
    }
}

#[derive(Clone, Copy, Default)]
struct BiquadState {
    delay_1: f32,
    delay_2: f32,
}

impl BiquadState {
    fn process(&mut self, input: f32, coefficients: BiquadCoefficients) -> f32 {
        let state = flush_denormal(
            input
                - coefficients.scale
                    * (coefficients.a2 * self.delay_2 + coefficients.a1 * self.delay_1),
        );
        let output = coefficients.scale
            * ((coefficients.b0 * state + coefficients.b1 * self.delay_1)
                + coefficients.b2 * self.delay_2);
        self.delay_2 = self.delay_1;
        self.delay_1 = state;
        output
    }

    fn process_raw(&mut self, input: f32, coefficients: BiquadCoefficients) -> f32 {
        let state = flush_denormal(
            input
                - coefficients.scale
                    * (coefficients.a2 * self.delay_2 + coefficients.a1 * self.delay_1),
        );
        let output = (coefficients.b0 * state + coefficients.b1 * self.delay_1)
            + coefficients.b2 * self.delay_2;
        self.delay_2 = self.delay_1;
        self.delay_1 = state;
        output
    }

    fn reset(&mut self) {
        *self = Self::default();
    }
}

#[derive(Clone, Copy, Default)]
struct BiquadCoefficients {
    b0: f32,
    b1: f32,
    b2: f32,
    a1: f32,
    a2: f32,
    scale: f32,
}

impl BiquadCoefficients {
    fn low_pass(sample_rate: f32, frequency: f32, damping: f32) -> Self {
        let tangent = (PI * frequency / sample_rate).tan();
        let inverse = 1.0 / tangent;
        let inverse_squared = 1.0 / (tangent * tangent);
        Self {
            b0: 1.0,
            b1: 2.0,
            b2: 1.0,
            a1: 2.0 * (1.0 - inverse_squared),
            a2: ((inverse - damping) / tangent) + 1.0,
            scale: 1.0 / (((inverse + damping) / tangent) + 1.0),
        }
    }

    fn high_pass(sample_rate: f32, frequency: f32, damping: f32) -> Self {
        let tangent = (PI * frequency / sample_rate).tan();
        let inverse = 1.0 / tangent;
        let inverse_squared = 1.0 / (tangent * tangent);
        Self {
            b0: inverse_squared,
            b1: -2.0 / (tangent * tangent),
            b2: inverse_squared,
            a1: 2.0 * (1.0 - inverse_squared),
            a2: ((inverse - damping) / tangent) + 1.0,
            scale: 1.0 / (((inverse + damping) / tangent) + 1.0),
        }
    }
}

#[derive(Default)]
struct Peak {
    state: BiquadState,
    coefficients: PeakCoefficients,
}

impl Peak {
    fn new(sample_rate: f32, frequency: f32, level: f32, bandwidth: f32) -> Self {
        let mut peak = Self::default();
        peak.set(sample_rate, frequency, level, bandwidth);
        peak
    }

    fn set(&mut self, sample_rate: f32, frequency: f32, level: f32, bandwidth: f32) {
        self.coefficients = PeakCoefficients::new(
            sample_rate,
            frequency.clamp(1.0, sample_rate * 0.49),
            level,
            bandwidth.max(f32::MIN_POSITIVE),
        );
    }

    fn process(&mut self, input: f32) -> f32 {
        let coefficients = self.coefficients;
        let state = flush_denormal(
            input
                - (self.state.delay_2 * coefficients.a2 + coefficients.middle * self.state.delay_1)
                    / coefficients.denominator,
        );
        let output = ((coefficients.middle * self.state.delay_1 + state * coefficients.b0)
            + self.state.delay_2 * coefficients.b2)
            / coefficients.denominator;
        self.state.delay_2 = self.state.delay_1;
        self.state.delay_1 = state;
        output
    }

    fn reset(&mut self) {
        self.state.reset();
    }
}

#[derive(Clone, Copy, Default)]
struct PeakCoefficients {
    b0: f32,
    b2: f32,
    middle: f32,
    a2: f32,
    denominator: f32,
}

impl PeakCoefficients {
    fn new(sample_rate: f32, frequency: f32, level: f32, bandwidth: f32) -> Self {
        let angle = PI * frequency / sample_rate;
        let tangent = angle.tan();
        let inverse = 1.0 / tangent;
        let sine = (2.0 * angle).sin();
        let unscaled = (PI / sample_rate) * (bandwidth / sine);
        let scaled = (PI / sample_rate) * ((bandwidth * db_to_gain(level.abs())) / sine);
        let (denominator_bandwidth, numerator_bandwidth) = if level > 0.0 {
            (unscaled, scaled)
        } else {
            (scaled, unscaled)
        };
        Self {
            b0: inverse * (inverse + numerator_bandwidth) + 1.0,
            b2: inverse * (inverse - numerator_bandwidth) + 1.0,
            middle: 2.0 * (1.0 - 1.0 / (tangent * tangent)),
            a2: inverse * (inverse - denominator_bandwidth) + 1.0,
            denominator: inverse * (inverse + denominator_bandwidth) + 1.0,
        }
    }
}

struct EvenOrderFilter<const SECTIONS: usize> {
    states: [BiquadState; SECTIONS],
    coefficients: [BiquadCoefficients; SECTIONS],
}

impl<const SECTIONS: usize> EvenOrderFilter<SECTIONS> {
    fn high_pass(sample_rate: f32, frequency: f32, damping: [f32; SECTIONS]) -> Self {
        Self {
            states: [BiquadState::default(); SECTIONS],
            coefficients: damping
                .map(|value| BiquadCoefficients::high_pass(sample_rate, frequency, value)),
        }
    }

    fn process(&mut self, mut input: f32) -> f32 {
        for (state, &coefficients) in self.states.iter_mut().zip(&self.coefficients) {
            input = state.process(input, coefficients);
        }
        input
    }

    fn reset(&mut self) {
        self.states.fill(BiquadState::default());
    }
}

struct FirstOrderSplit {
    inverse: f32,
    input_delay: f32,
    low_delay: f32,
    high_delay: f32,
}

impl FirstOrderSplit {
    fn new(sample_rate: f32, frequency: f32) -> Self {
        Self {
            inverse: 1.0 / (PI * frequency / sample_rate).tan(),
            input_delay: 0.0,
            low_delay: 0.0,
            high_delay: 0.0,
        }
    }

    fn process(&mut self, input: f32) -> (f32, f32) {
        let denominator = self.inverse + 1.0;
        let scale = 1.0 / denominator;
        let feedback = 1.0 - self.inverse;
        let low = flush_denormal(-scale * (feedback * self.low_delay - (input + self.input_delay)));
        let high = flush_denormal(
            -(self.inverse * scale) * self.input_delay
                - scale * (feedback * self.high_delay - self.inverse * input),
        );
        self.input_delay = input;
        self.low_delay = low;
        self.high_delay = high;
        (low, high)
    }

    fn reset(&mut self) {
        self.input_delay = 0.0;
        self.low_delay = 0.0;
        self.high_delay = 0.0;
    }
}

struct OddOrderSplit<const SECTIONS: usize> {
    first_order: FirstOrderSplit,
    low_states: [BiquadState; SECTIONS],
    high_states: [BiquadState; SECTIONS],
    low_coefficients: [BiquadCoefficients; SECTIONS],
    high_coefficients: [BiquadCoefficients; SECTIONS],
}

impl<const SECTIONS: usize> OddOrderSplit<SECTIONS> {
    fn new(sample_rate: f32, frequency: f32, damping: [f32; SECTIONS]) -> Self {
        Self {
            first_order: FirstOrderSplit::new(sample_rate, frequency),
            low_states: [BiquadState::default(); SECTIONS],
            high_states: [BiquadState::default(); SECTIONS],
            low_coefficients: damping
                .map(|value| BiquadCoefficients::low_pass(sample_rate, frequency, value)),
            high_coefficients: damping
                .map(|value| BiquadCoefficients::high_pass(sample_rate, frequency, value)),
        }
    }

    fn process(&mut self, input: f32) -> (f32, f32) {
        let (low, high, scale) = self.process_raw(input);
        (scale * low, scale * high)
    }

    fn process_raw(&mut self, input: f32) -> (f32, f32, f32) {
        let (mut low, mut high) = self.first_order.process(input);
        for (state, &coefficients) in self.low_states[..SECTIONS - 1]
            .iter_mut()
            .zip(&self.low_coefficients[..SECTIONS - 1])
        {
            low = state.process(low, coefficients);
        }
        for (state, &coefficients) in self.high_states[..SECTIONS - 1]
            .iter_mut()
            .zip(&self.high_coefficients[..SECTIONS - 1])
        {
            high = state.process(high, coefficients);
        }
        let low_coefficients = self.low_coefficients[SECTIONS - 1];
        let high_coefficients = self.high_coefficients[SECTIONS - 1];
        debug_assert_eq!(low_coefficients.scale, high_coefficients.scale);
        low = self.low_states[SECTIONS - 1].process_raw(low, low_coefficients);
        high = self.high_states[SECTIONS - 1].process_raw(high, high_coefficients);
        (low, high, low_coefficients.scale)
    }

    fn process_low(&mut self, input: f32) -> f32 {
        self.process(input).0
    }

    fn reset(&mut self) {
        self.first_order.reset();
        self.low_states.fill(BiquadState::default());
        self.high_states.fill(BiquadState::default());
    }
}

fn dynamic_response(envelope: f32, level: f32) -> f32 {
    let normalized = 0.588_235_3 * (((envelope - 0.05 * level) / (0.45 * level)) - 0.5);
    let first = normalized.clamp(-1.0, 1.0);
    let second = first * (first.abs() - 2.0);
    second * (second.abs() - 2.0) + 1.0
}

fn db_to_gain(decibels: f32) -> f32 {
    10.0_f32.powf(0.05 * decibels)
}

fn finite_or(value: f32, fallback: f32) -> f32 {
    if value.is_finite() { value } else { fallback }
}

fn valid_sample_rate(sample_rate: f32) -> f32 {
    finite_or(sample_rate, 48_000.0).clamp(1.0, 192_000.0)
}

fn flush_denormal(value: f32) -> f32 {
    if value.abs() < f32::MIN_POSITIVE {
        0.0
    } else {
        value
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn controls_change_observable_frequency_and_level_response() {
        let sine = |frequency: f32| {
            (0..8_192)
                .map(|index| (2.0 * PI * frequency * index as f32 / 48_000.0).sin() * 0.01)
                .collect::<Vec<_>>()
        };
        let render_rms = |mut cabinet: Cabinet, mut signal: Vec<f32>| {
            cabinet.process(&mut signal);
            (signal[4_096..]
                .iter()
                .map(|sample| sample * sample)
                .sum::<f32>()
                / 4_096.0)
                .sqrt()
        };

        let dark = {
            let mut cabinet = Cabinet::new(48_000.0);
            cabinet.set_dynamic(0.0);
            cabinet.set_brightness(-0.6);
            render_rms(cabinet, sine(6_000.0))
        };
        let bright = {
            let mut cabinet = Cabinet::new(48_000.0);
            cabinet.set_dynamic(0.0);
            cabinet.set_brightness(0.6);
            render_rms(cabinet, sine(6_000.0))
        };
        assert!(
            bright > dark * 4.0,
            "brightness did not lift 6 kHz: {bright} vs {dark}"
        );

        let near = {
            let mut cabinet = Cabinet::new(48_000.0);
            cabinet.set_dynamic(0.0);
            cabinet.set_distance(0.0);
            render_rms(cabinet, sine(1_200.0))
        };
        let far = {
            let mut cabinet = Cabinet::new(48_000.0);
            cabinet.set_dynamic(0.0);
            cabinet.set_distance(1.0);
            render_rms(cabinet, sine(1_200.0))
        };
        assert!(
            near > far * 2.0,
            "distance did not attenuate 1.2 kHz: {near} vs {far}"
        );
    }

    #[test]
    fn sustained_level_moves_the_dynamic_high_frequency_response() {
        let mut quiet = Cabinet::new(48_000.0);
        let mut loud = Cabinet::new(48_000.0);
        quiet.set_dynamic(1.0);
        loud.set_dynamic(1.0);
        quiet.set_dynamic_level(1.0);
        loud.set_dynamic_level(1.0);

        let render = |cabinet: &mut Cabinet, amplitude: f32| {
            let mut samples = (0..12_000)
                .map(|index| amplitude * (2.0 * PI * 10_000.0 * index as f32 / 48_000.0).sin())
                .collect::<Vec<_>>();
            cabinet.process(&mut samples);
            let tail = &samples[8_000..];
            (tail.iter().map(|sample| sample * sample).sum::<f32>() / tail.len() as f32).sqrt()
                / amplitude
        };

        let quiet_gain = render(&mut quiet, 0.01);
        let loud_gain = render(&mut loud, 0.8);
        assert!(
            (quiet_gain - loud_gain).abs() > quiet_gain * 0.08,
            "dynamic response did not follow signal level: {quiet_gain} vs {loud_gain}"
        );
    }
}
