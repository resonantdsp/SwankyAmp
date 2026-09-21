use std::path::PathBuf;
use swanky_amp::{Plugin, artwork, layout};

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
        std::fs::create_dir_all(&destination)?;
        for scale in [1.0, 2.0] {
            let (pixels, width, height) =
                truce::core::screenshot::render_with_state_at_scale::<Plugin>(None, scale);
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
