use crate::dsp::amp::AmpPath;
use crate::dsp::mapping::AmpControls;
use crate::params::SwankyAmpParams;
use truce::prelude::AudioBuffer;

const INITIAL_BLOCK: usize = 1024;

pub struct Engine {
    sample_rate: f32,
    controls: AmpControls,
    paths: [AmpPath; 2],
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
        Self {
            sample_rate,
            controls,
            paths: std::array::from_fn(|_| AmpPath::new(sample_rate, controls)),
            scratch: std::array::from_fn(|_| vec![0.; INITIAL_BLOCK]),
        }
    }

    pub fn reset(&mut self, params: &SwankyAmpParams, sample_rate: f64, max_block: usize) {
        self.sample_rate = sample_rate.clamp(8_000., 384_000.) as f32;
        self.controls = params.snapshot();
        for path in &mut self.paths {
            path.prepare(self.sample_rate, self.controls);
        }
        for scratch in &mut self.scratch {
            scratch.resize(max_block.max(1), 0.);
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
                self.paths[channel].process(&mut self.scratch[channel][..length]);
                buffer.output(channel)[start..start + length]
                    .copy_from_slice(&self.scratch[channel][..length]);
            }
            start += length;
        }
        for channel in channels..buffer.num_output_channels() {
            buffer.output(channel).fill(0.);
        }
    }
}
