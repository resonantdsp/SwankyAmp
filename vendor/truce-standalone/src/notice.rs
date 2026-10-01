//! One line about the devices that the player has to see: why the input is
//! off, or that the output stopped and what brings the sound back.
//!
//! A windowed app has no console, so the line goes to a sink the plugin
//! author supplies through [`crate::Defaults`], which shows it in the
//! plugin's own interface. Without a sink it is only printed. Lines are
//! posted from the UI and worker threads, never from an audio callback.

use std::sync::{Mutex, OnceLock};

/// Receives the line to show, or `None` once nothing needs saying.
pub type Sink = fn(Option<&str>);

static SINK: OnceLock<Sink> = OnceLock::new();
static LINES: Mutex<Lines> = Mutex::new(Lines {
    input: None,
    output: None,
});

struct Lines {
    input: Option<String>,
    output: Option<String>,
}

pub(crate) fn set_sink(sink: Sink) {
    let _ = SINK.set(sink);
}

/// Why the input is off, or `None` once it is on.
pub(crate) fn input(line: Option<String>) {
    post(|lines| lines.input = line);
}

/// That the output stopped and what brings the sound back, or `None` once
/// the player has chosen an output again.
pub(crate) fn output(line: Option<String>) {
    post(|lines| lines.output = line);
}

fn post(change: impl FnOnce(&mut Lines)) {
    let Ok(mut lines) = LINES.lock() else {
        return;
    };
    change(&mut lines);
    // A stopped output is the bigger surprise, and its line says what
    // became of the input too.
    let shown = lines.output.as_deref().or(lines.input.as_deref());
    if let Some(line) = shown {
        eprintln!("{line}");
    }
    if let Some(sink) = SINK.get() {
        sink(shown);
    }
}

/// Whether a line about the input is showing.
pub(crate) fn input_showing() -> bool {
    LINES.lock().is_ok_and(|lines| lines.input.is_some())
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

/// How the player chooses an output device: the Settings menu, or on Linux
/// the launch flag.
pub(crate) const CHOOSE_OUTPUT: &str = if cfg!(target_os = "linux") {
    "relaunch with --output <device>"
} else {
    "choose it in Settings › Output Device"
};

/// How the player chooses an input device: the Settings menu, or on Linux
/// the launch flag.
pub(crate) const CHOOSE_INPUT: &str = if cfg!(target_os = "linux") {
    "relaunch with --input <device>"
} else {
    "choose it in Settings › Input Device"
};
