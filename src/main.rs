use std::path::PathBuf;
use swanky_amp::{Plugin, artwork, interface, layout, presets};
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
        let fixture = arguments.get(2).map(String::as_str);
        let preset = match fixture {
            Some("preset") => Some(arguments.get(3).ok_or("capture <dir> preset <name>")?),
            Some("menu") => {
                swanky_amp::ui::capture_menu(
                    arguments
                        .get(3)
                        .ok_or("capture <dir> menu <preset name>")?
                        .clone(),
                );
                None
            }
            Some("information") => {
                swanky_amp::ui::capture_information(arguments.get(3).cloned());
                None
            }
            Some("audio") => {
                let state = arguments.get(3).map_or("", String::as_str);
                swanky_amp::ui::capture_audio(audio_fixture(state).ok_or(
                    "capture <dir> audio <choose|missing-input|missing-output|built-in|interface|did-not-open|asio|fell-back>",
                )?);
                swanky_amp::ui::capture_information(None);
                None
            }
            _ => None,
        };
        std::fs::create_dir_all(&destination)?;
        // Every interface size at a standard and a Retina display scale; the
        // 100 % files keep their plain names.
        for size in interface::SIZES {
            interface::hold(size);
            for scale in [1.0, 2.0] {
                let (pixels, width, height) = if fixture == Some("live") {
                    truce::core::screenshot::render_pixels_for_at_scale(&mut playing(), scale)
                } else if let Some(name) = preset {
                    let mut plugin = Plugin::create();
                    plugin.init();
                    presets::apply_offline(
                        &presets::Library::with_user_root(None),
                        &format!("factory:{name}"),
                        plugin.params(),
                    )?;
                    truce::core::screenshot::render_pixels_for_at_scale(&mut plugin, scale)
                } else {
                    truce::core::screenshot::render_with_state_at_scale::<Plugin>(None, scale)
                };
                let suffix = scale as u32;
                let name = if size == interface::DEFAULT {
                    format!("amp-{suffix}x.png")
                } else {
                    format!("amp-{size}-{suffix}x.png")
                };
                let path = destination.join(name);
                truce::core::screenshot::save_png(&path, &pixels, width, height);
                println!("{} {width}x{height}", path.display());
            }
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
        // An amplifier with its input off makes no sound, so the standalone
        // opens listening, but only on an input the player chose: the system
        // default is often a built-in microphone beside the speakers. The
        // editor's panel opens to say why when it starts with the input off.
        truce_standalone::run_with::<Plugin>(truce_standalone::Defaults {
            input_enabled: Some(true),
            input_needs_choice: true,
            ..Default::default()
        });
    }
    Ok(())
}

/// The standalone's audio choices a capture shows, by name, with the names
/// macOS and Windows give real devices.
fn audio_fixture(state: &str) -> Option<truce_standalone::setup::Setup> {
    use truce_standalone::audio::ChannelRoute;
    use truce_standalone::setup::{InputNeed, OutputNeed, Setup};
    let mac = Setup {
        takes_input: true,
        inputs: vec![
            "MacBook Air Microphone".to_owned(),
            "UMC202HD 192k".to_owned(),
        ],
        outputs: vec![
            "MacBook Air Speakers".to_owned(),
            "UMC202HD 192k".to_owned(),
        ],
        output: Some("MacBook Air Speakers".to_owned()),
        ..Setup::default()
    };
    Some(match state {
        "choose" => Setup {
            input_need: Some(InputNeed::Choose),
            ..mac
        },
        "missing-input" => Setup {
            inputs: vec!["MacBook Air Microphone".to_owned()],
            input_need: Some(InputNeed::NotConnected("UMC202HD 192k".to_owned())),
            ..mac
        },
        "missing-output" => Setup {
            input: Some("MacBook Air Microphone".to_owned()),
            built_in_microphone: true,
            output_need: Some(OutputNeed::NotConnected("Studio Monitors".to_owned())),
            ..mac
        },
        "built-in" => Setup {
            input: Some("MacBook Air Microphone".to_owned()),
            built_in_microphone: true,
            ..mac
        },
        "interface" => Setup {
            input: Some("UMC202HD 192k".to_owned()),
            output: Some("UMC202HD 192k".to_owned()),
            input_channels: Some((2, ChannelRoute::Mono { base: 0 })),
            ..mac
        },
        "did-not-open" => Setup {
            input_need: Some(InputNeed::DidNotOpen("UMC202HD 192k".to_owned())),
            ..mac
        },
        "asio" => Setup {
            one_interface: true,
            inputs: vec!["UMC ASIO Driver".to_owned(), "ASIO4ALL v2".to_owned()],
            outputs: vec!["UMC ASIO Driver".to_owned(), "ASIO4ALL v2".to_owned()],
            input: Some("UMC ASIO Driver".to_owned()),
            output: Some("UMC ASIO Driver".to_owned()),
            input_channels: Some((2, ChannelRoute::Mono { base: 0 })),
            ..mac
        },
        "fell-back" => Setup {
            inputs: vec!["Microphone Array (Realtek(R) Audio)".to_owned()],
            outputs: vec!["Speakers (Realtek(R) Audio)".to_owned()],
            output: Some("Speakers (Realtek(R) Audio)".to_owned()),
            input_need: Some(InputNeed::FellBack("UMC ASIO Driver".to_owned())),
            ..mac
        },
        _ => return None,
    })
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
