// Copyright (C) 2026 Garrin McGoldrick
// SPDX-License-Identifier: GPL-3.0-or-later

use std::array;
use std::f64::consts::PI;

use super::cabinet_data::MATCHED;

#[cfg(feature = "tools")]
pub mod fit;

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

/// The cabinet was voiced at this rate; its response there is the reference
/// every other host rate is matched to.
const REFERENCE_RATE: f32 = 48_000.;
const MAX_SAMPLE_RATE: f32 = 384_000.;
/// Bilinear designs stay below Nyquist, where their tangent turns negative
/// and the section unstable.
const MAX_DESIGN_FRACTION: f32 = 0.49;

/// The released Free cabinet: a fixed parametric cabinet response whose upper
/// range follows a 100 ms input envelope.
///
/// The sections run in double precision: in single precision the
/// low-frequency sections' round-off is audible hiss that follows the note
/// and grows with the sample rate.
pub(crate) struct Cabinet {
    sample_rate: f32,
    brightness: f32,
    distance: f32,
    dynamic: f32,
    dynamic_level: f32,
    envelope: f32,
    envelope_pole: f32,
    high_pass: [Biquad; 2],
    low_pass: Split<1>,
    cabinet_shelf: Split<3>,
    cabinet_shelf_gain: f64,
    /// At a tabled rate other than the reference, replaces the low-pass and
    /// the cabinet shelf, whose bilinear designs match the reference only at
    /// their corners.
    matched: Option<[Biquad; MATCHED_SECTIONS]>,
    /// The released path keeps the bilinear design at every rate.
    follows_reference: bool,
    fixed_peaks: [Biquad; 10],
    dynamic_peak: Biquad,
    fixed_notch: Biquad,
    low_shelf: Split<1>,
    brightness_peak: Biquad,
    high_shelf: Split<1>,
    distance_peaks: [Biquad; 2],
    output_gain: f64,
}

impl Cabinet {
    /// The shipping cabinet: at the rates `just fit-cabinet` tables it plays
    /// the reference rate's response; at any other rate, the bilinear design.
    pub(crate) fn new(sample_rate: f32) -> Self {
        let mut cabinet = Self::designed(valid_sample_rate(sample_rate));
        cabinet.follows_reference = true;
        cabinet.matched = MATCHED
            .iter()
            .find(|(rate, _)| *rate == cabinet.sample_rate)
            .map(|(_, sections)| sections.map(Biquad::new));
        cabinet
    }

    /// Keeps the released bilinear design at every rate, as 1.4.0 did, for
    /// the path that is checked against 1.4.0's renders.
    pub(crate) fn use_released_design(&mut self) {
        self.follows_reference = false;
        self.matched = None;
    }

    fn designed(sample_rate: f32) -> Self {
        let mut cabinet = Self {
            sample_rate,
            brightness: 0.0,
            distance: 0.0,
            dynamic: 0.5,
            dynamic_level: 1.0,
            envelope: 0.0,
            envelope_pole: (-10.0 / sample_rate).exp(),
            high_pass: [1.847_759, 0.765_366_85]
                .map(|damping| Biquad::new(high_pass(sample_rate, HIGH_PASS_HZ, damping))),
            low_pass: Split::new(sample_rate, LOW_PASS_HZ, [1.0]),
            cabinet_shelf: Split::new(
                sample_rate,
                CABINET_SHELF_HZ,
                [1.801_937_7, 1.246_979_6, 0.445_041_87],
            ),
            cabinet_shelf_gain: f64::from(db_to_gain(CABINET_SHELF_DB)),
            matched: None,
            follows_reference: false,
            fixed_peaks: array::from_fn(|_| Biquad::default()),
            dynamic_peak: Biquad::default(),
            fixed_notch: Biquad::new(peak(sample_rate, 100.0, -5.0, 200.0)),
            low_shelf: Split::new(sample_rate, 1_100.0, [1.0]),
            brightness_peak: Biquad::default(),
            high_shelf: Split::new(sample_rate, 6_500.0, [1.0]),
            distance_peaks: [Biquad::default(), Biquad::default()],
            output_gain: f64::from(db_to_gain(OFFSET_DB)),
        };

        for (section, &(frequency, level, bandwidth)) in cabinet
            .fixed_peaks
            .iter_mut()
            .zip(PEAKS[..7].iter().chain(PEAKS[8..].iter()).chain([&SCOOP]))
        {
            section.coefficients = peak(sample_rate, frequency, level, bandwidth);
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
        let follows_reference = self.follows_reference;
        *self = Self::new(sample_rate);
        if !follows_reference {
            self.use_released_design();
        }
        self.set_brightness(controls.0);
        self.set_distance(controls.1);
        self.set_dynamic(controls.2);
        self.set_dynamic_level(controls.3);
    }

    pub(crate) fn reset(&mut self) {
        self.envelope = 0.0;
        reset_all(&mut self.high_pass);
        self.low_pass.reset();
        self.cabinet_shelf.reset();
        if let Some(matched) = &mut self.matched {
            reset_all(matched);
        }
        reset_all(&mut self.fixed_peaks);
        self.dynamic_peak.reset();
        self.fixed_notch.reset();
        self.low_shelf.reset();
        self.brightness_peak.reset();
        self.high_shelf.reset();
        reset_all(&mut self.distance_peaks);
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

            let mut value = process_all(&mut self.high_pass, f64::from(input));
            if let Some(matched) = &mut self.matched {
                value = process_all(matched, value);
            } else {
                value = self.low_pass.process(value).0;
                let (low, high) = self.cabinet_shelf.process(value);
                value = low + self.cabinet_shelf_gain * high;
            }

            value = process_all(&mut self.fixed_peaks[..7], value);

            // Faust evaluates this level-dependent peak for every sample. Keeping
            // that baseline avoids block-size-dependent envelope quantisation.
            self.dynamic_peak.coefficients = peak(
                self.sample_rate,
                PEAKS[7].0 - 250.0 * self.dynamic * response,
                PEAKS[7].1 + 2.5 * self.dynamic * response,
                PEAKS[7].2 + 100.0 * self.dynamic * response,
            );
            value = self.dynamic_peak.process(value);

            value = process_all(&mut self.fixed_peaks[7..], value);
            value = self.fixed_notch.process(value);

            let (low, high) = self.low_shelf.process(value);
            let low_gain = db_to_gain(1.5 * self.dynamic * response - 3.0 * self.brightness);
            value = high + f64::from(low_gain) * low;

            value = self.brightness_peak.process(value);

            let (low, high) = self.high_shelf.process(value);
            let high_gain = db_to_gain(-2.5 * self.dynamic * response);
            value = f64::from(high_gain) * high + low;

            value = process_all(&mut self.distance_peaks, value);

            let output = (value * self.output_gain) as f32;
            *sample = if output.is_finite() { output } else { 0.0 };
        }
    }

    fn refresh_controls(&mut self) {
        self.brightness_peak.coefficients =
            peak(self.sample_rate, 6_000.0, 15.0 * self.brightness, 1_000.0);
        self.distance_peaks[0].coefficients =
            peak(self.sample_rate, 70.0, -10.0 * self.distance, 100.0);
        self.distance_peaks[1].coefficients =
            peak(self.sample_rate, 1_200.0, -17.0 * self.distance, 300.0);
        self.output_gain = f64::from(db_to_gain(OFFSET_DB) * 10.0_f32.powf(0.1 * self.distance));
    }
}

/// Biquad coefficients `[b0, b1, b2, a1, a2]`, normalised so that `a0` is 1.
type Section = [f64; 5];

/// A section in transposed direct form II, whose round-off stays low with
/// poles close to `z = 1`.
#[derive(Clone, Copy, Default)]
struct Biquad {
    coefficients: Section,
    state: [f64; 2],
}

impl Biquad {
    fn new(coefficients: Section) -> Self {
        Self {
            coefficients,
            state: [0.; 2],
        }
    }

    fn process(&mut self, input: f64) -> f64 {
        let [b0, b1, b2, a1, a2] = self.coefficients;
        let output = b0 * input + self.state[0];
        self.state[0] = flush_denormal_wide(b1 * input - a1 * output + self.state[1]);
        self.state[1] = flush_denormal_wide(b2 * input - a2 * output);
        output
    }

    fn reset(&mut self) {
        self.state = [0.; 2];
    }
}

fn process_all(sections: &mut [Biquad], mut value: f64) -> f64 {
    for section in sections {
        value = section.process(value);
    }
    value
}

fn reset_all(sections: &mut [Biquad]) {
    sections.iter_mut().for_each(Biquad::reset);
}

fn low_pass(sample_rate: f32, frequency: f32, damping: f32) -> Section {
    bilinear(
        design_tangent(sample_rate, frequency),
        [0., 0., 1.],
        [1., f64::from(damping), 1.],
    )
}

fn high_pass(sample_rate: f32, frequency: f32, damping: f32) -> Section {
    bilinear(
        design_tangent(sample_rate, frequency),
        [1., 0., 0.],
        [1., f64::from(damping), 1.],
    )
}

/// The released peaking section: its centre is prewarped and its bandwidth
/// scaled by `1 / sin(2 angle)`.
fn peak(sample_rate: f32, frequency: f32, level: f32, bandwidth: f32) -> Section {
    let sample_rate = f64::from(sample_rate);
    let frequency = f64::from(frequency).clamp(1.0, sample_rate * 0.49);
    let bandwidth = f64::from(bandwidth.max(f32::MIN_POSITIVE));
    let angle = PI * frequency / sample_rate;
    let tangent = angle.tan();
    let inverse = 1.0 / tangent;
    let sine = (2.0 * angle).sin();
    let unscaled = (PI / sample_rate) * (bandwidth / sine);
    let scaled = unscaled * f64::from(db_to_gain(level.abs()));
    let (denominator_bandwidth, numerator_bandwidth) = if level > 0.0 {
        (unscaled, scaled)
    } else {
        (scaled, unscaled)
    };
    let middle = 2.0 * (1.0 - inverse * inverse);
    let normalise = 1.0 / (inverse * (inverse + denominator_bandwidth) + 1.0);
    [
        (inverse * (inverse + numerator_bandwidth) + 1.0) * normalise,
        middle * normalise,
        (inverse * (inverse - numerator_bandwidth) + 1.0) * normalise,
        middle * normalise,
        (inverse * (inverse - denominator_bandwidth) + 1.0) * normalise,
    ]
}

/// An odd-order Butterworth crossover: complementary low and high outputs
/// that a shelf weights and sums.
struct Split<const SECTIONS: usize> {
    first_low: Biquad,
    first_high: Biquad,
    low: [Biquad; SECTIONS],
    high: [Biquad; SECTIONS],
}

impl<const SECTIONS: usize> Split<SECTIONS> {
    fn new(sample_rate: f32, frequency: f32, damping: [f32; SECTIONS]) -> Self {
        let tangent = design_tangent(sample_rate, frequency);
        Self {
            first_low: Biquad::new(bilinear(tangent, [0., 0., 1.], [0., 1., 1.])),
            first_high: Biquad::new(bilinear(tangent, [0., 1., 0.], [0., 1., 1.])),
            low: damping.map(|value| Biquad::new(low_pass(sample_rate, frequency, value))),
            high: damping.map(|value| Biquad::new(high_pass(sample_rate, frequency, value))),
        }
    }

    fn process(&mut self, input: f64) -> (f64, f64) {
        let low = process_all(&mut self.low, self.first_low.process(input));
        let high = process_all(&mut self.high, self.first_high.process(input));
        (low, high)
    }

    fn reset(&mut self) {
        self.first_low.reset();
        self.first_high.reset();
        reset_all(&mut self.low);
        reset_all(&mut self.high);
    }
}

/// The sections that replace the low-pass and the cabinet shelf at a tabled
/// rate.
const MATCHED_SECTIONS: usize = 6;

/// Maps a section given in the prewarped analogue variable, as `[W², W, 1]`
/// coefficients, to the digital domain; a section without `W²` in its
/// denominator is first order.
fn bilinear(tangent: f64, numerator: [f64; 3], denominator: [f64; 3]) -> Section {
    let first_order = denominator[0] == 0.;
    let map = |[squared, linear, constant]: [f64; 3]| {
        if first_order {
            [linear / tangent + constant, constant - linear / tangent, 0.]
        } else {
            let squared = squared / (tangent * tangent);
            let linear = linear / tangent;
            [
                squared + linear + constant,
                2. * (constant - squared),
                squared - linear + constant,
            ]
        }
    };
    let [b0, b1, b2] = map(numerator);
    let [a0, a1, a2] = map(denominator);
    [b0 / a0, b1 / a0, b2 / a0, a1 / a0, a2 / a0]
}

fn design_tangent(sample_rate: f32, frequency: f32) -> f64 {
    let frequency = frequency.min(MAX_DESIGN_FRACTION * sample_rate);
    (PI * f64::from(frequency) / f64::from(sample_rate)).tan()
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
    finite_or(sample_rate, REFERENCE_RATE).clamp(1.0, MAX_SAMPLE_RATE)
}

fn flush_denormal(value: f32) -> f32 {
    if value.abs() < f32::MIN_POSITIVE {
        0.0
    } else {
        value
    }
}

fn flush_denormal_wide(value: f64) -> f64 {
    if value.abs() < f64::MIN_POSITIVE {
        0.0
    } else {
        value
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::f32::consts::PI;

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

    fn resting(sample_rate: f32) -> Cabinet {
        let mut cabinet = Cabinet::new(sample_rate);
        cabinet.set_dynamic(0.0);
        cabinet
    }

    /// The gain in dB for a sine, measured after the cabinet settles.
    fn sine_gain_db(cabinet: &mut Cabinet, sample_rate: f32, frequency: f32) -> f32 {
        cabinet.reset();
        let settle = (0.05 * sample_rate) as usize;
        let window = (0.02 * sample_rate) as usize;
        let phase = |index: usize| 2.0 * PI * ((frequency * index as f32 / sample_rate) % 1.0);
        let mut samples: Vec<f32> = (0..settle + window)
            .map(|index| 0.01 * phase(index).sin())
            .collect();
        cabinet.process(&mut samples);
        let (sine, cosine) = samples[settle..].iter().enumerate().fold(
            (0.0, 0.0),
            |(sine, cosine), (offset, &sample)| {
                let angle = phase(settle + offset);
                (sine + sample * angle.sin(), cosine + sample * angle.cos())
            },
        );
        let amplitude = 2.0 * (sine * sine + cosine * cosine).sqrt() / window as f32;
        20.0 * (amplitude / 0.01).log10()
    }

    #[test]
    fn other_host_rates_play_the_reference_response() {
        let mut reference = resting(REFERENCE_RATE);
        for sample_rate in [44_100.0, 96_000.0, 384_000.0] {
            let mut cabinet = resting(sample_rate);
            for frequency in [200.0, 8_000.0, 14_000.0] {
                let expected = sine_gain_db(&mut reference, REFERENCE_RATE, frequency);
                let gain = sine_gain_db(&mut cabinet, sample_rate, frequency);
                assert!(
                    (gain - expected).abs() < 0.3,
                    "{frequency} Hz at {sample_rate} Hz: {gain:.2} dB against {expected:.2} dB at the reference rate"
                );
            }
        }
    }

    #[test]
    fn low_host_rates_keep_the_midrange() {
        let reference = sine_gain_db(&mut resting(REFERENCE_RATE), REFERENCE_RATE, 1_000.0);
        for sample_rate in [8_000.0, 11_025.0, 16_000.0] {
            let gain = sine_gain_db(&mut resting(sample_rate), sample_rate, 1_000.0);
            assert!(
                (gain - reference).abs() < 1.5,
                "1 kHz at {sample_rate} Hz: {gain:.2} dB against {reference:.2} dB at the reference rate"
            );
        }
    }

    #[test]
    fn falls_silent_after_its_input_stops() {
        for sample_rate in [22_050.0, 96_000.0] {
            let mut cabinet = resting(sample_rate);
            let burst = (0.05 * sample_rate) as usize;
            let mut samples: Vec<f32> = (0..(1.05 * sample_rate) as usize)
                .map(|index| {
                    if index < burst {
                        // A full-band burst that reaches Nyquist.
                        if index % 2 == 0 { 0.5 } else { -0.3 }
                    } else {
                        0.0
                    }
                })
                .collect();
            cabinet.process(&mut samples);
            let tail = samples[(0.55 * sample_rate) as usize..]
                .iter()
                .fold(0.0_f32, |peak, sample| peak.max(sample.abs()));
            assert!(
                tail < 1e-6,
                "at {sample_rate} Hz the cabinet still plays {tail:e} half a second after its input stopped"
            );
        }
    }

    #[test]
    fn a_low_note_at_a_high_rate_carries_no_round_off_hiss() {
        let sample_rate = 192_000.0;
        let mut cabinet = resting(sample_rate);
        cabinet.set_distance(0.5);
        let angle = |index: usize| 2.0 * std::f64::consts::PI * 110.0 * index as f64 / 192_000.0;
        let mut samples: Vec<f32> = (0..57_600)
            .map(|index| (0.1 * angle(index).sin()) as f32)
            .collect();
        cabinet.process(&mut samples);
        // Least-squares fit of the settled tone; what it leaves is the hiss.
        let tail = 38_400;
        let (mut ss, mut sc, mut cc, mut ys, mut yc) = (0.0, 0.0, 0.0, 0.0, 0.0);
        for (index, &sample) in samples.iter().enumerate().skip(tail) {
            let (sine, cosine) = angle(index).sin_cos();
            let sample = f64::from(sample);
            (ss, sc, cc) = (ss + sine * sine, sc + sine * cosine, cc + cosine * cosine);
            (ys, yc) = (ys + sample * sine, yc + sample * cosine);
        }
        let determinant = ss * cc - sc * sc;
        let (a, b) = (
            (ys * cc - yc * sc) / determinant,
            (yc * ss - ys * sc) / determinant,
        );
        let (mut tone, mut residue) = (0.0, 0.0);
        for (index, &sample) in samples.iter().enumerate().skip(tail) {
            let (sine, cosine) = angle(index).sin_cos();
            let fitted = a * sine + b * cosine;
            tone += fitted * fitted;
            residue += (f64::from(sample) - fitted).powi(2);
        }
        let residue_db = 10.0 * (residue / tone).log10();
        assert!(
            residue_db < -100.0,
            "residue {residue_db:.1} dB under a 110 Hz tone at 192 kHz"
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
