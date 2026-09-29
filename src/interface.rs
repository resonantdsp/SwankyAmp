//! How large the interface is drawn. The size answers to this computer's
//! screens and eyes, not to a sound, so it is kept once per installation and
//! never in a preset or a host project.
use std::path::{Path, PathBuf};
use std::sync::atomic::{AtomicU16, Ordering};

/// The sizes offered, in percent of the 864 × 512 design. Quarter steps keep
/// every window a whole number of points, and they are the steps Windows
/// offers for display scaling, so a size here composes with the desktop's.
/// Three quarters fits a small laptop at a large desktop scaling; one and a
/// half fills a 1440-point-wide display about as Pro's largest size does.
pub const SIZES: [u16; 4] = [75, 100, 125, 150];
pub const DEFAULT: u16 = 100;
const FILE: &str = "Swanky Amp 2 interface.json";

#[derive(serde::Serialize, serde::Deserialize)]
struct Saved {
    size: u16,
}

/// Where this installation keeps its interface size: JUCE's user application
/// data folder, where Pro keeps its own beside the licence.
pub fn folder() -> Option<PathBuf> {
    if held().is_some() {
        return None;
    }
    #[cfg(target_os = "macos")]
    let root = crate::presets::home().map(|home| home.join("Library"));
    #[cfg(target_os = "windows")]
    let root = dirs::data_dir();
    #[cfg(not(any(target_os = "macos", target_os = "windows")))]
    let root = dirs::config_dir();
    root.map(|root| root.join("Resonant DSP"))
}

/// The size this installation last chose, or the default when it has chosen
/// none, when `folder` is nothing, or when what is saved is not on offer.
pub fn load(folder: Option<&Path>) -> u16 {
    if let Some(size) = held() {
        return size;
    }
    folder
        .and_then(|folder| std::fs::read_to_string(folder.join(FILE)).ok())
        .and_then(|body| serde_json::from_str::<Saved>(&body).ok())
        .map(|saved| saved.size)
        .filter(|size| SIZES.contains(size))
        .unwrap_or(DEFAULT)
}

/// Remember `size` for every later editor on this installation.
pub fn save(folder: &Path, size: u16) -> Result<(), String> {
    let body = serde_json::to_string(&Saved { size }).map_err(|e| e.to_string())?;
    std::fs::create_dir_all(folder)
        .and_then(|_| std::fs::write(folder.join(FILE), body))
        .map_err(|e| format!("The interface size could not be saved: {e}"))
}

/// The editor zoom a size asks for.
pub fn zoom(size: u16) -> f64 {
    f64::from(size) / 100.0
}

pub fn label(size: u16) -> String {
    format!("{size}%")
}

static HELD: AtomicU16 = AtomicU16::new(0);

/// Set by the capture command: a review capture draws at a stated size, never
/// at whatever this machine chose, and never records one.
pub fn hold(size: u16) {
    HELD.store(size, Ordering::Relaxed);
}

fn held() -> Option<u16> {
    Some(HELD.load(Ordering::Relaxed)).filter(|size| SIZES.contains(size))
}
