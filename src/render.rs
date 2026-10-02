//! Offline rendering through the plug-in itself, for listening examples and
//! sound checks without a host.
use crate::Plugin;
use crate::presets::{self, Library};
use std::path::Path;
use truce::core::{
    AudioBuffer, AudioConfig, EventList, PluginExport, PluginRuntime, ProcessContext,
};
use truce::prelude::Params;

const BLOCK: usize = 256;

/// Renders a WAV's first channel through a preset at the file's own sample
/// rate, as the plug-in plays a mono track on a stereo output, and writes a
/// stereo 32-bit float WAV of the same length. The preset is a library key
/// (`init`, `factory:<name>`, `user:<file>`); overrides are (id, plain value)
/// pairs applied after it. Returns the frame count and the latency the
/// plug-in reports to a host, which the file is not shifted by.
pub fn render_file(
    preset: &str,
    input: &Path,
    output: &Path,
    overrides: &[(u32, f64)],
) -> Result<(usize, u32), String> {
    let (sample_rate, mono) = read_first_channel(input)?;
    let mut plugin = Plugin::create();
    plugin.init();
    let library = Library::default();
    presets::apply_offline(&library, preset, plugin.params()).map_err(|error| {
        let keys: Vec<_> = library.list().entries.into_iter().map(|e| e.key).collect();
        format!("{error}; available presets: {}", keys.join(", "))
    })?;
    for (id, value) in overrides {
        plugin.params().set_plain(*id, *value);
    }
    plugin.reset(&AudioConfig::new(f64::from(sample_rate), BLOCK));

    let mut left = vec![0.; mono.len()];
    let mut right = vec![0.; mono.len()];
    let transport = Default::default();
    let input_events = EventList::with_capacity(0);
    let mut output_events = EventList::with_capacity(0);
    for start in (0..mono.len()).step_by(BLOCK) {
        let end = (start + BLOCK).min(mono.len());
        let inputs = [&mono[start..end]];
        let mut outputs: [&mut [f32]; 2] = [&mut left[start..end], &mut right[start..end]];
        let mut buffer = AudioBuffer::from_slices_checked(&inputs, &mut outputs, end - start);
        let mut context = ProcessContext::new(
            &transport,
            f64::from(sample_rate),
            end - start,
            &mut output_events,
        );
        plugin.process(&mut buffer, &input_events, &mut context);
    }
    write_stereo(output, sample_rate, &left, &right)?;
    Ok((mono.len(), plugin.latency()))
}

fn read_first_channel(path: &Path) -> Result<(u32, Vec<f32>), String> {
    let mut reader =
        hound::WavReader::open(path).map_err(|error| format!("{}: {error}", path.display()))?;
    let spec = reader.spec();
    let channels = usize::from(spec.channels.max(1));
    let samples: Vec<f32> = match spec.sample_format {
        hound::SampleFormat::Float => reader.samples::<f32>().collect::<Result<_, _>>(),
        hound::SampleFormat::Int => {
            let scale = 1. / (1_i64 << (spec.bits_per_sample - 1)) as f32;
            reader
                .samples::<i32>()
                .map(|sample| sample.map(|value| value as f32 * scale))
                .collect()
        }
    }
    .map_err(|error| format!("{}: {error}", path.display()))?;
    Ok((
        spec.sample_rate,
        samples.into_iter().step_by(channels).collect(),
    ))
}

fn write_stereo(path: &Path, sample_rate: u32, left: &[f32], right: &[f32]) -> Result<(), String> {
    let spec = hound::WavSpec {
        channels: 2,
        sample_rate,
        bits_per_sample: 32,
        sample_format: hound::SampleFormat::Float,
    };
    let mut writer = hound::WavWriter::create(path, spec).map_err(|error| error.to_string())?;
    for (l, r) in left.iter().zip(right) {
        writer.write_sample(*l).map_err(|error| error.to_string())?;
        writer.write_sample(*r).map_err(|error| error.to_string())?;
    }
    writer.finalize().map_err(|error| error.to_string())
}
