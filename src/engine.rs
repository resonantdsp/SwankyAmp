use crate::dsp::amp::{AmpChannel, AmpControls, MAX_OVERSAMPLING};
use crate::dsp::mapping::AmpVoicing;
use crate::meters;
use crate::params::SwankyAmpParams;
use truce::prelude::AudioBuffer;

const INITIAL_BLOCK: usize = 1024;
const AUTO_TARGET_RATE: f64 = 88_200.;
const MAX_INTERNAL_RATE: f64 = 192_000. * 1.01;
/// A meter level falls to 1/e of itself in this time.
const METER_RELEASE_SECONDS: f64 = 0.3;

pub(crate) fn doublings_cap(sample_rate: f64) -> usize {
    (0..=MAX_OVERSAMPLING)
        .rev()
        .find(|doublings| sample_rate * (1 << doublings) as f64 <= MAX_INTERNAL_RATE)
        .unwrap_or(0)
}

pub fn doublings_for(choice: usize, sample_rate: f64) -> usize {
    let cap = doublings_cap(sample_rate);
    match choice {
        0 => (0..=cap)
            .find(|doublings| sample_rate * (1 << doublings) as f64 >= AUTO_TARGET_RATE)
            .unwrap_or(cap),
        fixed => fixed.saturating_sub(1).min(cap),
    }
}

pub struct Engine {
    sample_rate: f32,
    controls: AmpControls,
    oversampling_choice: usize,
    doublings: usize,
    requested_doublings: usize,
    paths: [AmpChannel; 2],
    scratch: [Vec<f32>; 2],
    levels: [f32; 4],
    block_peaks: [f32; 4],
}

impl Default for Engine {
    fn default() -> Self {
        Self::new(&SwankyAmpParams::default())
    }
}

impl Engine {
    pub fn new(params: &SwankyAmpParams) -> Self {
        let sample_rate = 44_100.;
        let controls = params.snapshot();
        let oversampling_choice = params.oversampling_choice();
        let doublings = doublings_for(oversampling_choice, sample_rate);
        Self {
            sample_rate: sample_rate as f32,
            controls,
            oversampling_choice,
            doublings,
            requested_doublings: doublings,
            paths: std::array::from_fn(|_| {
                AmpChannel::new(sample_rate as f32, INITIAL_BLOCK, controls, doublings)
            }),
            scratch: std::array::from_fn(|_| vec![0.; INITIAL_BLOCK]),
            levels: [0.; 4],
            block_peaks: [0.; 4],
        }
    }

    pub fn reset(&mut self, params: &SwankyAmpParams, sample_rate: f64, max_block: usize) {
        self.sample_rate = sample_rate.clamp(8_000., 384_000.) as f32;
        self.controls = params.snapshot();
        self.oversampling_choice = params.oversampling_choice();
        self.doublings = doublings_for(self.oversampling_choice, f64::from(self.sample_rate));
        self.requested_doublings = self.doublings;
        params.resolved_oversampling.publish(self.doublings);
        for path in &mut self.paths {
            path.prepare(self.sample_rate, max_block, self.controls, self.doublings);
        }
        for scratch in &mut self.scratch {
            scratch.resize(max_block.max(1), 0.);
        }
        self.levels = [0.; 4];
    }

    pub fn reset_realtime(&mut self, params: &SwankyAmpParams) {
        self.controls = params.snapshot();
        self.oversampling_choice = params.oversampling_choice();
        self.requested_doublings =
            doublings_for(self.oversampling_choice, f64::from(self.sample_rate));
        for path in &mut self.paths {
            path.reset_realtime(self.controls);
        }
        for scratch in &mut self.scratch {
            scratch.fill(0.);
        }
        self.levels = [0.; 4];
    }

    pub fn process(&mut self, params: &SwankyAmpParams, buffer: &mut AudioBuffer) {
        params.audio.record(self.sample_rate, buffer.num_samples());
        let controls = params.snapshot();
        if controls != self.controls {
            for path in &mut self.paths {
                path.configure(controls);
            }
            self.controls = controls;
        }
        let oversampling_choice = params.oversampling_choice();
        if oversampling_choice != self.oversampling_choice {
            self.oversampling_choice = oversampling_choice;
            self.requested_doublings =
                doublings_for(oversampling_choice, f64::from(self.sample_rate));
        }

        let channels = buffer
            .channels()
            .min(buffer.num_output_channels())
            .min(self.paths.len());
        let frames = buffer.num_samples();
        let capacity = self.scratch[0].len();
        if frames == 0 || channels == 0 || capacity == 0 {
            return;
        }

        let input_gain = AmpVoicing::from_controls(controls).input_gain;
        self.begin();
        let mut start = 0;
        while start < frames {
            let length = (frames - start).min(capacity);
            for channel in 0..channels {
                let samples = &mut self.scratch[channel][..length];
                samples.copy_from_slice(&buffer.input(channel)[start..start + length]);
                // The soft clips hide poisoned filters from the output, so
                // one bad sample from upstream would otherwise leave the amp
                // silent until the next prepare with nothing to detect it by.
                zero_unplayable(samples);
                let input_peak = peak(samples);
                self.paths[channel].process(samples, self.doublings);
                self.observe_input(channel, input_peak * input_gain);
                self.observe_output(channel, peak(&self.scratch[channel][..length]));
                buffer.output(channel)[start..start + length]
                    .copy_from_slice(&self.scratch[channel][..length]);
            }
            // A mono input on a stereo output plays its one path on both sides.
            if channels == 1 {
                for channel in 1..buffer.num_output_channels() {
                    buffer.output(channel)[start..start + length]
                        .copy_from_slice(&self.scratch[0][..length]);
                }
            }
            start += length;
        }
        if channels > 1 {
            for channel in channels..buffer.num_output_channels() {
                buffer.output(channel).fill(0.);
            }
        }

        // A single path has no stereo field to place, so the meters show it
        // on both sides as the player hears it.
        if channels == 1 {
            self.block_peaks[1] = self.block_peaks[0];
            self.block_peaks[3] = self.block_peaks[2];
        }
        self.finish(frames);
    }

    fn begin(&mut self) {
        self.block_peaks = [0.; 4];
    }

    fn observe_input(&mut self, channel: usize, peak: f32) {
        self.block_peaks[channel] = self.block_peaks[channel].max(finite(peak));
    }

    fn observe_output(&mut self, channel: usize, peak: f32) {
        self.block_peaks[2 + channel] = self.block_peaks[2 + channel].max(finite(peak));
    }

    fn finish(&mut self, frames: usize) {
        let release =
            (-(frames as f64) / (f64::from(self.sample_rate) * METER_RELEASE_SECONDS)).exp() as f32;
        for ((level, peak), scale) in self
            .levels
            .iter_mut()
            .zip(self.block_peaks)
            .zip(meters::SCALES_DB)
        {
            // A meter too quiet to light a cell is already a still picture.
            // Reporting the remainder of its release would keep the editor
            // redrawing a meter that shows nothing.
            *level = peak.max(*level * release);
            if *level < meters::floor_amplitude(scale) {
                *level = 0.;
            }
        }
    }

    /// Peak amplitudes with the meters' release, input L/R after the Input
    /// control, then output L/R.
    pub fn meter_levels(&self) -> [f32; 4] {
        self.levels
    }

    pub fn latency(&self) -> u32 {
        u32::try_from(self.paths[0].latency(self.requested_doublings)).unwrap_or(u32::MAX)
    }
}

/// An overflowing peak would hold a meter full for good, since an infinite
/// level never releases.
fn finite(value: f32) -> f32 {
    if value.is_finite() { value } else { 0. }
}

/// No signal reaches 120 dB above full scale, while a sample near the largest
/// finite value overflows the amp's arithmetic and leaves its state stuck in a
/// way its output cannot show.
const MAX_INPUT: f32 = 1e6;

fn zero_unplayable(samples: &mut [f32]) {
    for sample in samples {
        if sample.is_nan() || sample.abs() > MAX_INPUT {
            *sample = 0.;
        }
    }
}

fn peak(samples: &[f32]) -> f32 {
    samples
        .iter()
        .copied()
        .filter(|sample| sample.is_finite())
        .map(f32::abs)
        .fold(0., f32::max)
}
