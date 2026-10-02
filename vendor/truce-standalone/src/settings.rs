//! Audio choices the standalone remembers on this machine: the input and
//! output devices picked from the Settings menu, the input channels, the
//! buffer size, and on Windows the audio driver and the ASIO interface.
//!
//! Launch flags and their environment variables override the saved values
//! for that launch and are never written back, so a one-off `--buffer 32`
//! does not become the default. Offline renders ignore the saved values.

use std::path::{Path, PathBuf};
use std::sync::{Arc, Mutex};

/// Buffer sizes the Settings menu offers, in frames.
pub const BUFFER_SIZES: [u32; 6] = [32, 64, 128, 256, 512, 1024];

/// The buffer size when neither a flag nor a saved choice names one: low
/// enough to play an instrument through, and within what interfaces accept.
pub const DEFAULT_BUFFER_SIZE: u32 = 128;

/// The audio driver the standalone plays through. Windows offers two:
/// ASIO, an audio interface's own low-latency driver, and WASAPI shared
/// mode, which every device supports at the cost of about 10 ms each way.
/// Elsewhere the system has one driver and the choice has no effect.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum AudioDriver {
    Asio,
    Wasapi,
}

impl AudioDriver {
    /// Read the name a flag, the environment or the settings file uses.
    #[must_use]
    pub fn parse(name: &str) -> Option<Self> {
        match name.trim().to_ascii_lowercase().as_str() {
            "asio" => Some(Self::Asio),
            "wasapi" => Some(Self::Wasapi),
            _ => None,
        }
    }

    /// The name [`Self::parse`] reads.
    #[must_use]
    pub fn name(self) -> &'static str {
        match self {
            Self::Asio => "asio",
            Self::Wasapi => "wasapi",
        }
    }
}

/// The saved choices. `None` means nothing was chosen, so the launch falls
/// back to the system default device or [`DEFAULT_BUFFER_SIZE`].
#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub struct Settings {
    pub input_device: Option<String>,
    pub output_device: Option<String>,
    pub buffer_size: Option<u32>,
    pub driver: Option<AudioDriver>,
    /// The interface chosen while on ASIO, one device for input and output.
    /// It is kept apart from the WASAPI devices so that switching driver
    /// returns to the device last used with each.
    pub asio_device: Option<String>,
    /// The input channels chosen from the menu, as `--input-channels`
    /// reads them.
    pub input_channels: Option<String>,
}

const INPUT_DEVICE: &str = "input_device";
const OUTPUT_DEVICE: &str = "output_device";
const BUFFER_SIZE: &str = "buffer_size";
const DRIVER: &str = "driver";
const ASIO_DEVICE: &str = "asio_device";
const INPUT_CHANNELS: &str = "input_channels";

impl Settings {
    /// Read the settings at `path`. A missing or unreadable file, and any
    /// line this version does not understand, leave those choices unset:
    /// losing a preference must never stop the standalone from starting.
    #[must_use]
    pub fn load(path: &Path) -> Self {
        let mut settings = Self::default();
        let Ok(text) = std::fs::read_to_string(path) else {
            return settings;
        };
        for line in text.lines() {
            let Some((key, value)) = line.split_once('=') else {
                continue;
            };
            let name = Some(value.to_owned()).filter(|v| !v.is_empty());
            match key.trim() {
                INPUT_DEVICE => settings.input_device = name,
                OUTPUT_DEVICE => settings.output_device = name,
                BUFFER_SIZE => settings.buffer_size = value.trim().parse().ok().filter(|&n| n > 0),
                DRIVER => settings.driver = AudioDriver::parse(value),
                ASIO_DEVICE => settings.asio_device = name,
                INPUT_CHANNELS => settings.input_channels = name,
                _ => {}
            }
        }
        settings
    }

    /// Write the settings to `path`, creating its directory.
    ///
    /// # Errors
    ///
    /// Returns the I/O error when the directory or the file cannot be
    /// written.
    pub fn save(&self, path: &Path) -> std::io::Result<()> {
        let mut text = String::new();
        let lines = [
            (INPUT_DEVICE, self.input_device.clone()),
            (OUTPUT_DEVICE, self.output_device.clone()),
            (BUFFER_SIZE, self.buffer_size.map(|n| n.to_string())),
            (DRIVER, self.driver.map(|d| d.name().to_owned())),
            (ASIO_DEVICE, self.asio_device.clone()),
            (INPUT_CHANNELS, self.input_channels.clone()),
        ];
        for (key, value) in lines {
            if let Some(value) = value {
                text.push_str(key);
                text.push('=');
                text.push_str(&value);
                text.push('\n');
            }
        }
        if let Some(dir) = path.parent() {
            std::fs::create_dir_all(dir)?;
        }
        // Written beside the file and renamed over it, so a crash mid-write
        // leaves the previous choices whole.
        let partial = path.with_extension("partial");
        std::fs::write(&partial, text)?;
        std::fs::rename(&partial, path)
    }
}

/// The buffer size a launch asks the device for: the launch flag, else the
/// saved choice, else [`DEFAULT_BUFFER_SIZE`].
#[must_use]
pub fn launch_buffer_size(flag: Option<u32>, saved: Option<u32>) -> u32 {
    flag.filter(|&n| n > 0)
        .or(saved.filter(|&n| n > 0))
        .unwrap_or(DEFAULT_BUFFER_SIZE)
}

/// The driver a launch opens: the launch flag, else the saved choice, else
/// ASIO when a driver for it is installed. ASIO without an installed driver
/// falls back to WASAPI. `asio_installed` is asked only when ASIO is wanted,
/// so choosing WASAPI never touches an ASIO driver.
#[must_use]
pub fn launch_driver(
    flag: Option<AudioDriver>,
    saved: Option<AudioDriver>,
    asio_installed: impl FnOnce() -> bool,
) -> AudioDriver {
    match flag.or(saved) {
        Some(AudioDriver::Wasapi) => AudioDriver::Wasapi,
        Some(AudioDriver::Asio) | None => {
            if asio_installed() {
                AudioDriver::Asio
            } else {
                AudioDriver::Wasapi
            }
        }
    }
}

/// Where a plugin's standalone keeps its settings: the machine-local
/// configuration directory (`~/Library/Application Support` on macOS,
/// `%LOCALAPPDATA%` on Windows, `$XDG_CONFIG_HOME` on Linux), under the
/// vendor and plugin names. Device names only mean something on the machine
/// that reported them, so the file never roams with a Windows profile.
#[must_use]
pub fn path_for(vendor: &str, plugin: &str) -> Option<PathBuf> {
    dirs::config_local_dir().map(|dir| {
        dir.join(truce_utils::safe_filename(vendor))
            .join(truce_utils::safe_filename(plugin))
            .join("standalone.cfg")
    })
}

/// The saved settings and the file they live in, shared by the audio
/// workers, which record a choice once the device has accepted it.
#[derive(Clone, Default)]
pub(crate) struct SettingsStore {
    path: Option<PathBuf>,
    saved: Arc<Mutex<Settings>>,
}

impl SettingsStore {
    pub(crate) fn open(path: Option<PathBuf>) -> Self {
        let saved = path.as_deref().map(Settings::load).unwrap_or_default();
        Self {
            path,
            saved: Arc::new(Mutex::new(saved)),
        }
    }

    pub(crate) fn saved(&self) -> Settings {
        self.saved.lock().map(|s| s.clone()).unwrap_or_default()
    }

    /// Apply `change` and write the file when it changed anything. A failed
    /// write is reported and otherwise ignored: the choice still holds for
    /// this session.
    pub(crate) fn update(&self, change: impl FnOnce(&mut Settings)) {
        let Ok(mut saved) = self.saved.lock() else {
            return;
        };
        let before = saved.clone();
        change(&mut saved);
        if *saved == before {
            return;
        }
        if let Some(path) = &self.path
            && let Err(e) = saved.save(path)
        {
            eprintln!("could not save audio settings to {}: {e}", path.display());
        }
    }
}

#[cfg(test)]
mod tests {
    use super::{AudioDriver, Settings, launch_buffer_size, launch_driver};

    fn scratch_file(name: &str) -> std::path::PathBuf {
        std::env::temp_dir()
            .join(format!("truce-standalone-settings-{}", std::process::id()))
            .join(name)
    }

    #[test]
    fn saved_choices_read_back_unchanged() {
        let path = scratch_file("round-trip.cfg");
        let saved = Settings {
            input_device: Some("IN 1-2 (BEHRINGER UMC 202HD 192k) = Line".to_owned()),
            output_device: Some("Haut-parleurs (Réalité)".to_owned()),
            buffer_size: Some(64),
            driver: Some(AudioDriver::Asio),
            asio_device: Some("UMC ASIO Driver".to_owned()),
            input_channels: Some("2".to_owned()),
        };
        saved.save(&path).expect("settings write");
        assert_eq!(Settings::load(&path), saved);

        let partly = Settings {
            input_device: None,
            output_device: Some("UMC202HD 192k".to_owned()),
            buffer_size: None,
            driver: Some(AudioDriver::Wasapi),
            asio_device: None,
            input_channels: None,
        };
        partly.save(&path).expect("settings write");
        assert_eq!(Settings::load(&path), partly);
        let _ = std::fs::remove_dir_all(path.parent().unwrap());
    }

    #[test]
    fn a_missing_file_chooses_nothing() {
        assert_eq!(
            Settings::load(&scratch_file("never-written.cfg")),
            Settings::default()
        );
    }

    #[test]
    fn launch_buffer_size_prefers_the_flag_then_the_saved_choice() {
        assert_eq!(launch_buffer_size(Some(32), Some(256)), 32);
        assert_eq!(launch_buffer_size(None, Some(256)), 256);
        assert_eq!(launch_buffer_size(None, None), 128);
    }

    #[test]
    fn launch_driver_prefers_the_flag_then_the_saved_choice_then_asio() {
        use AudioDriver::{Asio, Wasapi};
        let installed = || true;
        assert_eq!(launch_driver(Some(Wasapi), Some(Asio), installed), Wasapi);
        assert_eq!(launch_driver(Some(Asio), Some(Wasapi), installed), Asio);
        assert_eq!(launch_driver(None, Some(Wasapi), installed), Wasapi);
        assert_eq!(launch_driver(None, None, installed), Asio);
    }

    #[test]
    fn launch_driver_falls_back_to_wasapi_without_an_asio_driver() {
        use AudioDriver::{Asio, Wasapi};
        let missing = || false;
        assert_eq!(launch_driver(None, None, missing), Wasapi);
        assert_eq!(launch_driver(Some(Asio), None, missing), Wasapi);
        assert_eq!(launch_driver(None, Some(Asio), missing), Wasapi);
    }
}
