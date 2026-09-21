use std::f64::consts::PI;

const TAPS: usize = 63;
const KAISER_BETA: f64 = 9.;

fn bessel_i0(x: f64) -> f64 {
    let mut sum = 1.;
    let mut term = 1.;
    for k in 1..40 {
        term *= (x / (2. * k as f64)).powi(2);
        sum += term;
        if term < 1e-14 * sum {
            break;
        }
    }
    sum
}

fn halfband() -> (f32, Vec<f32>) {
    let midpoint = (TAPS / 2) as i64;
    let odd: Vec<f32> = (1..=midpoint)
        .step_by(2)
        .map(|offset| {
            let offset = offset as f64;
            let sinc = (PI * offset / 2.).sin() / (PI * offset);
            let window = bessel_i0(KAISER_BETA * (1. - (offset / midpoint as f64).powi(2)).sqrt())
                / bessel_i0(KAISER_BETA);
            (sinc * window) as f32
        })
        .collect();
    (0.5, odd)
}

#[inline]
fn dot(taps: &[f32], window: &[f32]) -> f32 {
    let mut parts = [0f32; 8];
    let mut tap_chunks = taps.chunks_exact(8);
    let mut window_chunks = window.chunks_exact(8);
    for (tap_chunk, window_chunk) in tap_chunks.by_ref().zip(window_chunks.by_ref()) {
        for index in 0..8 {
            parts[index] += tap_chunk[index] * window_chunk[index];
        }
    }
    let tail: f32 = tap_chunks
        .remainder()
        .iter()
        .zip(window_chunks.remainder())
        .map(|(tap, sample)| tap * sample)
        .sum();
    parts.iter().sum::<f32>() + tail
}

#[derive(Debug, Clone)]
struct Stage {
    centre: f32,
    taps: Vec<f32>,
    up_history: Vec<f32>,
    up_position: usize,
    down_even: Vec<f32>,
    down_odd: Vec<f32>,
    down_position: usize,
}

impl Stage {
    fn new() -> Self {
        let (centre, odd) = halfband();
        let taps: Vec<f32> = odd.iter().rev().chain(odd.iter()).copied().collect();
        let length = taps.len();
        Self {
            centre,
            taps,
            up_history: vec![0.; 2 * length],
            up_position: 0,
            down_even: vec![0.; 2 * length],
            down_odd: vec![0.; 2 * length],
            down_position: 0,
        }
    }

    #[inline]
    fn up(&mut self, sample: f32) -> [f32; 2] {
        let length = self.taps.len();
        self.up_history[self.up_position] = sample;
        self.up_history[self.up_position + length] = sample;
        let centre_at = self.up_position + length / 2;
        let even = 2. * self.centre * self.up_history[centre_at];
        let odd = dot(
            &self.taps,
            &self.up_history[self.up_position + 1..][..length],
        );
        self.up_position = if self.up_position + 1 == length {
            0
        } else {
            self.up_position + 1
        };
        [even, 2. * odd]
    }

    #[inline]
    fn down(&mut self, pair: [f32; 2]) -> f32 {
        let length = self.taps.len();
        // This window ends at the previous odd sample. It must be read before
        // the ring slot holding its oldest sample is replaced by this pair.
        let odd = dot(&self.taps, &self.down_odd[self.down_position..][..length]);
        self.down_even[self.down_position] = pair[0];
        self.down_even[self.down_position + length] = pair[0];
        self.down_odd[self.down_position] = pair[1];
        self.down_odd[self.down_position + length] = pair[1];
        let centre_at = self.down_position + length / 2;
        // Selecting the even decimation phase makes every supported cascade's
        // round-trip delay an integer number of host samples.
        let output = self.centre * self.down_even[centre_at] + odd;
        self.down_position = if self.down_position + 1 == length {
            0
        } else {
            self.down_position + 1
        };
        output
    }

    fn reset(&mut self) {
        self.up_history.fill(0.);
        self.up_position = 0;
        self.down_even.fill(0.);
        self.down_odd.fill(0.);
        self.down_position = 0;
    }
}

#[derive(Debug, Clone)]
pub(crate) struct Oversampler {
    stages: Vec<Stage>,
    scratch: Vec<f32>,
}

impl Oversampler {
    pub(crate) fn new(stages: usize, max_block: usize) -> Self {
        Self {
            stages: (0..stages).map(|_| Stage::new()).collect(),
            scratch: vec![0.; max_block.max(1) << stages],
        }
    }

    pub(crate) fn factor(&self) -> usize {
        1 << self.stages.len()
    }

    pub(crate) fn latency(&self) -> usize {
        (TAPS + 1) * (self.factor() - 1) / self.factor()
    }

    pub(crate) fn up(&mut self, input: &[f32], output: &mut [f32]) {
        let mut length = input.len();
        output[..length].copy_from_slice(input);
        for stage in &mut self.stages {
            for (index, &sample) in output[..length].iter().enumerate() {
                let [even, odd] = stage.up(sample);
                self.scratch[2 * index] = even;
                self.scratch[2 * index + 1] = odd;
            }
            output[..2 * length].copy_from_slice(&self.scratch[..2 * length]);
            length *= 2;
        }
    }

    pub(crate) fn down(&mut self, input: &[f32], output: &mut [f32]) {
        let mut length = input.len();
        self.scratch[..length].copy_from_slice(input);
        for stage in self.stages.iter_mut().rev() {
            for index in 0..length / 2 {
                self.scratch[index] =
                    stage.down([self.scratch[2 * index], self.scratch[2 * index + 1]]);
            }
            length /= 2;
        }
        output.copy_from_slice(&self.scratch[..length]);
    }

    pub(crate) fn reset(&mut self) {
        for stage in &mut self.stages {
            stage.reset();
        }
        self.scratch.fill(0.);
    }
}
