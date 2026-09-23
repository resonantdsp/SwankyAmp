use super::amp::{AmpChannel, AmpControls};
use super::oversample::Oversampler;

pub struct OversamplingImpulse {
    pub factor: usize,
    pub reported_latency: usize,
    pub peak_sample: usize,
    pub peak_value: f32,
    pub symmetry_max_error: f32,
    pub dc_gain: f32,
}

pub struct ResetEquilibrium {
    pub max_error: f32,
    pub rms_error: f32,
    pub stale_max_error: f32,
}

pub fn reset_equilibrium(
    sample_rate: f32,
    controls: AmpControls,
    doublings: usize,
) -> ResetEquilibrium {
    const BLOCK: usize = 64;
    const PROBE_FRAMES: usize = 512;
    const DRIVE_FRAMES: usize = 8_192;

    fn process(channel: &mut AmpChannel, samples: &mut [f32], doublings: usize) {
        for block in samples.chunks_mut(BLOCK) {
            channel.process(block, doublings);
        }
    }

    let mut channel = AmpChannel::new(sample_rate, BLOCK, controls, doublings);
    let probe: Vec<f32> = (0..PROBE_FRAMES)
        .map(|frame| {
            let x = frame as f32;
            0.18 * (x * 0.071).sin() + 0.07 * (x * 0.193).cos()
        })
        .collect();
    let mut fresh = probe.clone();
    process(&mut channel, &mut fresh, doublings);

    let mut drive: Vec<f32> = (0..DRIVE_FRAMES)
        .map(|frame| {
            let x = frame as f32;
            0.65 * (x * 0.071).sin() + 0.25 * (x * 0.193).cos()
        })
        .collect();
    process(&mut channel, &mut drive, doublings);
    let mut stale = probe.clone();
    process(&mut channel, &mut stale, doublings);

    channel.reset_realtime(controls);
    let mut reset = probe;
    process(&mut channel, &mut reset, doublings);

    let max_error = reset
        .iter()
        .zip(&fresh)
        .map(|(actual, expected)| (actual - expected).abs())
        .fold(0., f32::max);
    let rms_error = (reset
        .iter()
        .zip(&fresh)
        .map(|(actual, expected)| (actual - expected).powi(2))
        .sum::<f32>()
        / reset.len() as f32)
        .sqrt();
    let stale_max_error = stale
        .iter()
        .zip(&fresh)
        .map(|(actual, expected)| (actual - expected).abs())
        .fold(0., f32::max);
    ResetEquilibrium {
        max_error,
        rms_error,
        stale_max_error,
    }
}

pub fn oversampling_impulse(doublings: usize) -> OversamplingImpulse {
    assert!((1..=2).contains(&doublings));
    let frames = 256;
    let mut oversampler = Oversampler::new(doublings, frames);
    let mut input = vec![0.; frames];
    input[0] = 1.;
    let mut high = vec![0.; frames << doublings];
    let mut output = vec![0.; frames];
    oversampler.up(&input, &mut high);
    oversampler.down(&high, &mut output);
    let (peak_sample, peak_value) = output
        .iter()
        .copied()
        .enumerate()
        .max_by(|(_, left), (_, right)| left.abs().total_cmp(&right.abs()))
        .unwrap();
    let radius = peak_sample.min(output.len() - peak_sample - 1);
    let symmetry_max_error = (1..=radius)
        .map(|offset| (output[peak_sample - offset] - output[peak_sample + offset]).abs())
        .fold(0., f32::max);
    OversamplingImpulse {
        factor: oversampler.factor(),
        reported_latency: oversampler.latency(),
        peak_sample,
        peak_value,
        symmetry_max_error,
        dc_gain: output.iter().sum(),
    }
}
