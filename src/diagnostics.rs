//! The block the information panel copies for a support request. It says
//! what is running and where.

use crate::params::SwankyAmpParams;
use std::sync::atomic::{AtomicU32, Ordering};

/// The host rate in hertz and the frames in the latest block, shared from the
/// audio thread for a support report; zero until audio has run.
#[derive(Default)]
pub struct Audio {
    sample_rate: AtomicU32,
    block: AtomicU32,
}

impl Audio {
    pub fn record(&self, sample_rate: f32, frames: usize) {
        self.sample_rate
            .store(sample_rate.round() as u32, Ordering::Relaxed);
        self.block.store(frames as u32, Ordering::Relaxed);
    }

    fn running(&self) -> Option<(u32, u32)> {
        match (
            self.sample_rate.load(Ordering::Relaxed),
            self.block.load(Ordering::Relaxed),
        ) {
            (0, _) | (_, 0) => None,
            running => Some(running),
        }
    }
}

/// Product, version and commit, operating system, host and format, the audio
/// the host is running, the licence, the GPU, where the log is and the
/// warnings and errors it recorded lately, one fact per line.
pub fn report(params: &SwankyAmpParams) -> String {
    let audio = match params.audio.running() {
        Some((rate, block)) => format!("{rate} Hz, {block}-sample buffer"),
        None => "not running".into(),
    };
    format!(
        "{}\nOS: {} ({})\nHost: {}, {}\nAudio: {audio}\nLicence: free, GPL-3.0-or-later\n{}",
        heading(),
        os(),
        std::env::consts::ARCH,
        host(),
        FORMAT,
        crate::editor_log::summary(),
    )
}

/// The product, its version and, when the build knew it, its commit.
pub(crate) fn heading() -> String {
    format!("Swanky Amp Free {}", build())
}

/// Shown in native text in place of an editor that cannot draw, in one line.
pub(crate) fn graphics_failed(log: Option<&str>) -> String {
    match log {
        Some(log) => format!(
            "The editor cannot draw on this computer's graphics. Send the log at {log} to {SUPPORT_ADDRESS}."
        ),
        None => format!(
            "The editor cannot draw on this computer's graphics. Write to {SUPPORT_ADDRESS}."
        ),
    }
}
const SUPPORT_ADDRESS: &str = "support@resonantdsp.com";

/// The version and, when the build knew it, the short commit, since every
/// release candidate reports the version of the release it leads to.
fn build() -> String {
    match env!("SWANKY_AMP_COMMIT") {
        "" => env!("CARGO_PKG_VERSION").to_owned(),
        commit => format!("{} ({commit})", env!("CARGO_PKG_VERSION")),
    }
}

/// Each shipped binary is built for exactly one format, so the feature that
/// is on names it.
pub(crate) const FORMAT: &str = if cfg!(feature = "clap") {
    "CLAP"
} else if cfg!(feature = "vst3") {
    "VST3"
} else if cfg!(feature = "au") {
    "AU"
} else if cfg!(feature = "standalone") {
    "Standalone"
} else {
    "no plug-in format"
};

/// The application that loaded the plug-in, by the name its user knows it by:
/// on macOS the outermost app bundle, since the executable inside is often
/// named differently.
pub(crate) fn host() -> String {
    let Ok(path) = std::env::current_exe() else {
        return "unknown".into();
    };
    let bundle = path
        .ancestors()
        .filter(|p| p.extension().is_some_and(|e| e == "app"))
        .last();
    bundle
        .unwrap_or(&path)
        .file_stem()
        .map_or_else(|| "unknown".into(), |s| s.to_string_lossy().into_owned())
}

#[cfg(target_os = "macos")]
pub(crate) fn os() -> String {
    let version = std::fs::read_to_string("/System/Library/CoreServices/SystemVersion.plist")
        .ok()
        .and_then(|plist| {
            let after = plist.split("<key>ProductVersion</key>").nth(1)?;
            let value = after.split("<string>").nth(1)?.split("</string>").next()?;
            Some(value.trim().to_owned())
        });
    format!(
        "macOS {}",
        version.as_deref().unwrap_or("(version unknown)")
    )
}

#[cfg(windows)]
pub(crate) fn os() -> String {
    const KEY: &str = r"SOFTWARE\Microsoft\Windows NT\CurrentVersion";
    let build = windows::registry_string(KEY, "CurrentBuildNumber");
    // Windows 11 still names itself Windows 10 in the registry; its builds
    // start at 22000.
    let name = match build.as_deref().and_then(|b| b.parse::<u32>().ok()) {
        Some(number) if number >= 22000 => "Windows 11",
        Some(_) => "Windows 10",
        None => "Windows",
    };
    let release = windows::registry_string(KEY, "DisplayVersion")
        .map(|r| format!(" {r}"))
        .unwrap_or_default();
    match build {
        Some(build) => format!("{name}{release} (build {build})"),
        None => name.into(),
    }
}

#[cfg(windows)]
mod windows {
    use windows_sys::Win32::System::Registry::{HKEY_LOCAL_MACHINE, RRF_RT_REG_SZ, RegGetValueW};

    /// A string value under HKEY_LOCAL_MACHINE, or `None` when it is absent.
    pub fn registry_string(key: &str, value: &str) -> Option<String> {
        let wide = |s: &str| s.encode_utf16().chain([0]).collect::<Vec<u16>>();
        let (key, value) = (wide(key), wide(value));
        let mut buffer = [0u16; 128];
        let mut bytes = std::mem::size_of_val(&buffer) as u32;
        // SAFETY: both names are NUL-terminated and the buffer's size in
        // bytes is passed alongside it.
        let status = unsafe {
            RegGetValueW(
                HKEY_LOCAL_MACHINE,
                key.as_ptr(),
                value.as_ptr(),
                RRF_RT_REG_SZ,
                std::ptr::null_mut(),
                buffer.as_mut_ptr().cast(),
                &mut bytes,
            )
        };
        if status != 0 {
            return None;
        }
        let chars = (bytes as usize / 2).saturating_sub(1);
        Some(String::from_utf16_lossy(&buffer[..chars]))
    }
}

#[cfg(not(any(target_os = "macos", windows)))]
pub(crate) fn os() -> String {
    std::fs::read_to_string("/etc/os-release")
        .ok()
        .and_then(|release| {
            release.lines().find_map(|line| {
                line.strip_prefix("PRETTY_NAME=")
                    .map(|name| name.trim_matches('"').to_owned())
            })
        })
        .unwrap_or_else(|| std::env::consts::OS.into())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn the_report_gives_the_rate_and_buffer_audio_ran_at() {
        let params = SwankyAmpParams::default();
        assert!(report(&params).contains("Audio: not running"));
        let mut engine = crate::engine::Engine::new(&params);
        engine.reset(&params, 44_100., 512);
        let input = [0.; 128];
        let mut outputs = [[0.; 128]; 2];
        let inputs: [&[f32]; 2] = [&input, &input];
        let [left, right] = &mut outputs;
        let mut outputs: [&mut [f32]; 2] = [left, right];
        let mut buffer =
            truce::prelude::AudioBuffer::from_slices_checked(&inputs, &mut outputs, 128);
        engine.process(&params, &mut buffer);
        let report = report(&params);
        assert!(
            report.contains("Audio: 44100 Hz, 128-sample buffer"),
            "{report}"
        );
    }
}
