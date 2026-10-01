//! One line about the input that the player has to see, such as why it is
//! off at launch and what turns it on.
//!
//! A windowed app has no console, so the line goes to a sink the plugin
//! author supplies through [`crate::Defaults`], which shows it in the
//! plugin's own interface. Without a sink it is only printed. Lines are
//! posted from the UI and worker threads, never from an audio callback.

use std::sync::{Mutex, OnceLock};

/// Receives the line to show, or `None` once nothing needs saying.
pub type Sink = fn(Option<&str>);

static SINK: OnceLock<Sink> = OnceLock::new();
static INPUT: Mutex<Option<String>> = Mutex::new(None);

pub(crate) fn set_sink(sink: Sink) {
    let _ = SINK.set(sink);
}

/// Why the input is off, or `None` once it is on.
pub(crate) fn input(line: Option<String>) {
    let Ok(mut shown) = INPUT.lock() else {
        return;
    };
    if let Some(line) = &line {
        eprintln!("{line}");
    }
    if let Some(sink) = SINK.get() {
        sink(line.as_deref());
    }
    *shown = line;
}

/// Whether a line about the input is showing.
pub(crate) fn input_showing() -> bool {
    INPUT.lock().is_ok_and(|shown| shown.is_some())
}

/// The input toggle as the player finds it: the Settings menu item and its
/// shortcut, or on Linux, which has no menu, the shortcut alone.
pub(crate) const MIC_INPUT: &str = if cfg!(target_os = "macos") {
    "turn on Mic Input (Cmd+I)"
} else if cfg!(target_os = "linux") {
    "press Ctrl+I"
} else {
    "turn on Mic Input (Ctrl+I)"
};

/// How the player chooses an input device: the Settings menu, or on Linux
/// the launch flag.
pub(crate) const CHOOSE_INPUT: &str = if cfg!(target_os = "linux") {
    "relaunch with --input <device>"
} else {
    "choose it in Settings › Input Device"
};
