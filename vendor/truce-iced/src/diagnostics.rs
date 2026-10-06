//! What the editor reports about itself, for a plug-in's support log.
//!
//! The editor reports through `log` and installs no sink of its own. Its
//! warnings, errors and the panics it catches arrive at their own levels;
//! its open and close stages, each with the time it took, a device loss and
//! its rebuild arrive at `Info` under [`LIFECYCLE`]. None of these is raised
//! per frame or from the audio thread, so a plug-in can write them all to a
//! file.

use std::sync::{Mutex, PoisonError};
use std::time::Instant;

/// The target of the editor's open, close and device-loss records.
pub const LIFECYCLE: &str = "truce_iced::lifecycle";

static GPU: Mutex<Option<String>> = Mutex::new(None);

/// The graphics adapter the editor last drew with, its backend and driver,
/// or `None` before any editor has chosen one in this process.
pub fn gpu() -> Option<String> {
    GPU.lock().unwrap_or_else(PoisonError::into_inner).clone()
}

/// Record the adapter an editor chose, `since` the request for it began.
#[cfg(not(target_os = "ios"))]
pub(crate) fn note_adapter(info: &iced_wgpu::wgpu::AdapterInfo, since: Instant) -> Instant {
    let driver = [info.driver.as_str(), info.driver_info.as_str()]
        .into_iter()
        .filter(|part| !part.is_empty())
        .collect::<Vec<_>>()
        .join(" ");
    let mut adapter = format!("{} ({:?}, {:?})", info.name, info.backend, info.device_type);
    if !driver.is_empty() {
        adapter = format!("{adapter}, driver {driver}");
    }
    let now = Instant::now();
    log::info!(
        target: LIFECYCLE,
        "adapter {} ms: {adapter}",
        now.duration_since(since).as_millis()
    );
    *GPU.lock().unwrap_or_else(PoisonError::into_inner) = Some(adapter);
    now
}

/// Record that `name` finished, `since` it began, and return the moment it
/// did, which is where the next stage begins.
#[cfg(not(target_os = "ios"))]
pub(crate) fn stage(name: &str, since: Instant) -> Instant {
    let now = Instant::now();
    log::info!(target: LIFECYCLE, "{name} {} ms", now.duration_since(since).as_millis());
    now
}
