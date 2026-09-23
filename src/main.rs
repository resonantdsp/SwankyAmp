use std::path::PathBuf;
use swanky_amp::{Plugin, artwork, layout};
use truce::core::{
    AudioBuffer, AudioConfig, EventList, PluginExport, PluginRuntime, ProcessContext,
};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let arguments: Vec<_> = std::env::args().skip(1).collect();
    if arguments.first().map(String::as_str) == Some("export-layout") {
        let destination = PathBuf::from(
            arguments
                .get(1)
                .map(String::as_str)
                .unwrap_or("assets/layout"),
        );
        let path = layout::export(&destination)?;
        let manifest = layout::manifest();
        println!("{} {}", path.display(), manifest.physical_sha256);
    } else if arguments.first().map(String::as_str) == Some("capture") {
        let destination = PathBuf::from(
            arguments
                .get(1)
                .map(String::as_str)
                .unwrap_or("verification/interface"),
        );
        let live = arguments.get(2).map(String::as_str) == Some("live");
        std::fs::create_dir_all(&destination)?;
        for scale in [1.0, 2.0] {
            let (pixels, width, height) = if live {
                truce::core::screenshot::render_pixels_for_at_scale(&mut playing(), scale)
            } else {
                truce::core::screenshot::render_with_state_at_scale::<Plugin>(None, scale)
            };
            let suffix = scale as u32;
            let path = destination.join(format!("amp-{suffix}x.png"));
            truce::core::screenshot::save_png(&path, &pixels, width, height);
            println!("{} {width}x{height}", path.display());
        }
    } else if arguments.first().map(String::as_str) == Some("pack-artwork") {
        let layers = PathBuf::from(
            arguments
                .get(1)
                .ok_or("pack-artwork <layers directory> <package>")?,
        );
        let package = PathBuf::from(
            arguments
                .get(2)
                .ok_or("pack-artwork <layers directory> <package>")?,
        );
        let header = artwork::pack(&layers, &package)?;
        println!(
            "{} {} layers {}",
            package.display(),
            header.layers.len(),
            header.physical_sha256
        );
    } else if arguments.first().map(String::as_str) == Some("unpack-artwork") {
        let package = PathBuf::from(
            arguments
                .get(1)
                .ok_or("unpack-artwork <package> <directory>")?,
        );
        let destination = PathBuf::from(
            arguments
                .get(2)
                .ok_or("unpack-artwork <package> <directory>")?,
        );
        let header = artwork::unpack(&package, &destination)?;
        println!(
            "{} {} layers {}",
            destination.display(),
            header.layers.len(),
            header.physical_sha256
        );
    } else if arguments.first().map(String::as_str) == Some("validate-assets") {
        let package = PathBuf::from(
            arguments
                .get(1)
                .map(String::as_str)
                .unwrap_or("assets/artwork.pack"),
        );
        let layers = PathBuf::from(
            arguments
                .get(2)
                .map(String::as_str)
                .unwrap_or("assets/artwork"),
        );
        let header = artwork::validate_assets(&package, &layers)?;
        println!(
            "{} {} layers {}",
            package.display(),
            header.layers.len(),
            header.physical_sha256
        );
    } else if arguments.first().map(String::as_str) == Some("refresh-artwork") {
        let layers = PathBuf::from(
            arguments
                .get(1)
                .ok_or("refresh-artwork <layers directory>")?,
        );
        artwork::refresh_receipt(&layers)?;
        println!("{}", layers.join("receipt.json").display());
    } else {
        truce_standalone::run::<Plugin>();
    }
    Ok(())
}

/// An instance that has just played a deterministic stereo note, so a
/// capture shows lit meters: the left channel louder than the right, cut
/// off mid-note so the meters hold their attack.
fn playing() -> Plugin {
    const SAMPLE_RATE: f64 = 48_000.;
    const BLOCK: usize = 256;
    let mut plugin = Plugin::create();
    plugin.init();
    plugin.reset(&AudioConfig::new(SAMPLE_RATE, BLOCK));
    let note = |amplitude: f32| -> Vec<f32> {
        (0..BLOCK * 40)
            .map(|frame| {
                let phase = std::f32::consts::TAU * 110.0 * frame as f32 / SAMPLE_RATE as f32;
                amplitude * phase.sin()
            })
            .collect()
    };
    let inputs = [note(0.4), note(0.2)];
    let transport = Default::default();
    let input_events = EventList::with_capacity(0);
    let mut output_events = EventList::with_capacity(0);
    for start in (0..inputs[0].len()).step_by(BLOCK) {
        let input_refs: Vec<&[f32]> = inputs
            .iter()
            .map(|channel| &channel[start..start + BLOCK])
            .collect();
        let mut outputs = [vec![0.0; BLOCK], vec![0.0; BLOCK]];
        let mut output_refs: Vec<&mut [f32]> = outputs.iter_mut().map(Vec::as_mut_slice).collect();
        let mut buffer = AudioBuffer::from_slices_checked(&input_refs, &mut output_refs, BLOCK);
        let mut context = ProcessContext::new(&transport, SAMPLE_RATE, BLOCK, &mut output_events);
        plugin.process(&mut buffer, &input_events, &mut context);
    }
    plugin
}
