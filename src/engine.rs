use crate::dsp::amp::{AmpChannel, AmpControls, MAX_OVERSAMPLING};
use crate::params::SwankyAmpParams;
use truce::prelude::AudioBuffer;

const INITIAL_BLOCK: usize = 1024;
const AUTO_TARGET_RATE: f64 = 88_200.;
const MAX_INTERNAL_RATE: f64 = 192_000. * 1.01;

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
                AmpChannel::new(sample_rate as f32, INITIAL_BLOCK, controls)
            }),
            scratch: std::array::from_fn(|_| vec![0.; INITIAL_BLOCK]),
        }
    }

    pub fn reset(&mut self, params: &SwankyAmpParams, sample_rate: f64, max_block: usize) {
        self.sample_rate = sample_rate.clamp(8_000., 384_000.) as f32;
        self.controls = params.snapshot();
        self.oversampling_choice = params.oversampling_choice();
        self.doublings = doublings_for(self.oversampling_choice, f64::from(self.sample_rate));
        self.requested_doublings = self.doublings;
        for path in &mut self.paths {
            path.prepare(self.sample_rate, max_block, self.controls);
        }
        for scratch in &mut self.scratch {
            scratch.resize(max_block.max(1), 0.);
        }
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
    }

    pub fn process(&mut self, params: &SwankyAmpParams, buffer: &mut AudioBuffer) {
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

        let mut start = 0;
        while start < frames {
            let length = (frames - start).min(capacity);
            for channel in 0..channels {
                self.scratch[channel][..length]
                    .copy_from_slice(&buffer.input(channel)[start..start + length]);
                self.paths[channel].process(&mut self.scratch[channel][..length], self.doublings);
                buffer.output(channel)[start..start + length]
                    .copy_from_slice(&self.scratch[channel][..length]);
            }
            start += length;
        }
        for channel in channels..buffer.num_output_channels() {
            buffer.output(channel).fill(0.);
        }
    }

    pub fn latency(&self) -> u32 {
        u32::try_from(self.paths[0].latency(self.requested_doublings)).unwrap_or(u32::MAX)
    }
}
