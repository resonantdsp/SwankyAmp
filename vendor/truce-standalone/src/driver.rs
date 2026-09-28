//! The audio driver the standalone is running on, and the cpal host that
//! serves it.
//!
//! On Windows the standalone runs on ASIO when an ASIO driver is installed
//! and the build has the `asio` feature, and otherwise on WASAPI shared
//! mode, which is cpal's default host. Elsewhere the default host is the
//! only driver. The choice is one per process because ASIO itself is: a
//! process loads one ASIO driver at a time.

use std::sync::atomic::{AtomicBool, Ordering};

use crate::settings::AudioDriver;

static ON_ASIO: AtomicBool = AtomicBool::new(false);

/// The driver the streams run on now.
#[must_use]
pub fn active() -> AudioDriver {
    if ON_ASIO.load(Ordering::Relaxed) {
        AudioDriver::Asio
    } else {
        AudioDriver::Wasapi
    }
}

pub(crate) fn set_active(driver: AudioDriver) {
    ON_ASIO.store(
        asio_built() && driver == AudioDriver::Asio,
        Ordering::Relaxed,
    );
}

pub(crate) fn on_asio() -> bool {
    active() == AudioDriver::Asio
}

/// Whether this build can run on ASIO at all.
#[must_use]
pub fn asio_built() -> bool {
    cfg!(all(windows, feature = "asio"))
}

/// Whether an ASIO driver is installed that this build could run on.
#[must_use]
pub fn asio_installed() -> bool {
    !asio_drivers().is_empty()
}

/// The cpal host for the active driver.
pub(crate) fn host() -> cpal::Host {
    #[cfg(all(windows, feature = "asio"))]
    if on_asio() && let Ok(host) = cpal::host_from_id(cpal::HostId::Asio) {
        return host;
    }
    cpal::default_host()
}

/// The ASIO drivers installed on this machine, from the SDK's driver list,
/// which names them as cpal does and loads none of them.
pub(crate) fn asio_drivers() -> Vec<String> {
    #[cfg(all(windows, feature = "asio"))]
    {
        asio_sys::Asio::new().driver_names()
    }
    #[cfg(not(all(windows, feature = "asio")))]
    {
        Vec::new()
    }
}

/// Drivers that wrap the Windows audio stack or stand in for many devices.
/// They come with other software as often as they are chosen, so a launch
/// with no saved interface tries an interface's own driver first.
const GENERIC_ASIO_DRIVERS: [&str; 7] = [
    "asio4all",
    "fl studio asio",
    "generic low latency",
    "realtek",
    "flexasio",
    "asio2wasapi",
    "voicemeeter",
];

/// Whether `name` is one of the generic drivers, which are tried after an
/// interface's own.
pub(crate) fn is_generic(name: &str) -> bool {
    let name = name.to_lowercase();
    GENERIC_ASIO_DRIVERS
        .iter()
        .any(|generic| name.contains(generic))
}
