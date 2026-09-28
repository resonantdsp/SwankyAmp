//! Streams in a device's own sample format, rendered and captured in
//! `f32`. ASIO interfaces commonly take 32-bit integers, and cpal's ASIO
//! backend builds streams only in the driver's format.

use cpal::traits::DeviceTrait;
use cpal::{FromSample, SampleFormat, SizedSample};

/// The largest sample below full scale. Integer formats map +1.0 one step
/// past their largest value, which 24-bit samples wrap instead of clip.
const BELOW_FULL_SCALE: f32 = 1.0 - f32::EPSILON / 2.0;

/// `sample` in a device format, clipped to full scale.
fn to_device<T: FromSample<f32>>(sample: f32) -> T {
    T::from_sample_(sample.clamp(-1.0, BELOW_FULL_SCALE))
}

/// Build an output stream in `format`, rendered in `f32` by `render`.
/// Formats other than `f32` render into a buffer allocated here for
/// `capacity` samples and convert.
pub(crate) fn build_output(
    device: &cpal::Device,
    config: cpal::StreamConfig,
    format: SampleFormat,
    capacity: usize,
    mut render: impl FnMut(&mut [f32]) + Send + 'static,
    on_error: impl FnMut(cpal::Error) + Send + 'static,
) -> Result<cpal::Stream, String> {
    let built = match format {
        SampleFormat::F32 => device.build_output_stream(
            config,
            move |data: &mut [f32], _: &cpal::OutputCallbackInfo| render(data),
            on_error,
            None,
        ),
        SampleFormat::I16 => {
            build_converted_output::<i16>(device, config, capacity, render, on_error)
        }
        SampleFormat::I24 => {
            build_converted_output::<cpal::I24>(device, config, capacity, render, on_error)
        }
        SampleFormat::I32 => {
            build_converted_output::<i32>(device, config, capacity, render, on_error)
        }
        format => {
            return Err(format!(
                "audio output format {format:?} is not supported \
                 (truce standalone handles f32, i16, i24 and i32)"
            ));
        }
    };
    built.map_err(|e| format!("could not build output stream: {e}"))
}

fn build_converted_output<T>(
    device: &cpal::Device,
    config: cpal::StreamConfig,
    capacity: usize,
    mut render: impl FnMut(&mut [f32]) + Send + 'static,
    on_error: impl FnMut(cpal::Error) + Send + 'static,
) -> Result<cpal::Stream, cpal::Error>
where
    T: SizedSample + FromSample<f32>,
{
    let mut rendered: Vec<f32> = Vec::with_capacity(capacity);
    device.build_output_stream(
        config,
        move |data: &mut [T], _: &cpal::OutputCallbackInfo| {
            rendered.clear();
            rendered.resize(data.len(), 0.0);
            render(&mut rendered);
            for (out, &sample) in data.iter_mut().zip(&rendered) {
                *out = to_device(sample);
            }
        },
        on_error,
        None,
    )
}

/// Build an input stream in `format`, handing what it captures to
/// `capture` in `f32`. Formats other than `f32` convert through a buffer
/// allocated here for `capacity` samples.
pub(crate) fn build_input(
    device: &cpal::Device,
    config: cpal::StreamConfig,
    format: SampleFormat,
    capacity: usize,
    mut capture: impl FnMut(&[f32]) + Send + 'static,
    on_error: impl FnMut(cpal::Error) + Send + 'static,
) -> Result<cpal::Stream, String> {
    let built = match format {
        SampleFormat::F32 => device.build_input_stream(
            config,
            move |data: &[f32], _: &cpal::InputCallbackInfo| capture(data),
            on_error,
            None,
        ),
        SampleFormat::I16 => {
            build_converted_input::<i16>(device, config, capacity, capture, on_error)
        }
        SampleFormat::I24 => {
            build_converted_input::<cpal::I24>(device, config, capacity, capture, on_error)
        }
        SampleFormat::I32 => {
            build_converted_input::<i32>(device, config, capacity, capture, on_error)
        }
        format => return Err(format!("audio input format {format:?} is not supported")),
    };
    built.map_err(|e| format!("could not build input stream: {e}"))
}

fn build_converted_input<T>(
    device: &cpal::Device,
    config: cpal::StreamConfig,
    capacity: usize,
    mut capture: impl FnMut(&[f32]) + Send + 'static,
    on_error: impl FnMut(cpal::Error) + Send + 'static,
) -> Result<cpal::Stream, cpal::Error>
where
    T: SizedSample,
    f32: FromSample<T>,
{
    let mut captured: Vec<f32> = Vec::with_capacity(capacity);
    device.build_input_stream(
        config,
        move |data: &[T], _: &cpal::InputCallbackInfo| {
            captured.clear();
            captured.extend(data.iter().map(|&sample| f32::from_sample_(sample)));
            capture(&captured);
        },
        on_error,
        None,
    )
}

#[cfg(test)]
mod tests {
    use super::to_device;

    const I24_MAX: i32 = (1 << 23) - 1;
    const I24_MIN: i32 = -(1 << 23);

    #[test]
    fn full_scale_reaches_the_extreme_24_bit_samples_without_wrapping() {
        assert_eq!(to_device::<cpal::I24>(1.0).inner(), I24_MAX);
        assert_eq!(to_device::<cpal::I24>(-1.0).inner(), I24_MIN);
        assert_eq!(
            to_device::<cpal::I24>(1.5).inner(),
            I24_MAX,
            "over full scale clips"
        );
    }
}
