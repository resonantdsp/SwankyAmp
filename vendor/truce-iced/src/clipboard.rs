//! The system clipboard the editor hands to iced's widgets.
//!
//! The published runtime hands them a null clipboard, so a plugin editor
//! cannot paste - which a product key field a player is meant to paste into
//! cannot do without. Text is the whole of what an editor needs; every other
//! flavour is left to the platform.

use iced_core::clipboard::Kind;

/// The system clipboard as a widget sees it.
pub struct Clipboard;

impl iced_core::Clipboard for Clipboard {
    fn read(&self, kind: Kind) -> Option<String> {
        read(kind)
    }
    fn write(&mut self, kind: Kind, contents: String) {
        write(kind, contents);
    }
}

/// What the clipboard holds as text, or nothing when it holds something else
/// or the platform has no clipboard to offer.
pub fn read(kind: Kind) -> Option<String> {
    system::read(kind)
}

/// Puts text on the clipboard. A platform that refuses is left alone: a failed
/// copy is not worth interrupting an editor over.
pub fn write(kind: Kind, contents: String) {
    system::write(kind, contents);
}

#[cfg(not(target_os = "ios"))]
mod system {
    use super::Kind;
    use std::cell::RefCell;

    pub fn read(kind: Kind) -> Option<String> {
        with(kind, |clipboard| clipboard.get_text().ok()).flatten()
    }

    pub fn write(kind: Kind, contents: String) {
        with(kind, |clipboard| {
            let _ = clipboard.set_text(contents);
        });
    }

    /// Runs `f` against this thread's connection, opening one on first use.
    ///
    /// The connection is per thread and kept open: X11 serves a paste from the
    /// process that owns the selection, so one opened and dropped per call
    /// would take the copied text with it. Only the window thread asks.
    ///
    /// `Kind::Primary` is X11's middle-click selection, which no plugin window
    /// owns; serving it from the standard clipboard would paste the wrong text,
    /// so it is served by nothing.
    fn with<T>(kind: Kind, f: impl FnOnce(&mut arboard::Clipboard) -> T) -> Option<T> {
        thread_local! {
            static CLIPBOARD: RefCell<Option<arboard::Clipboard>> = const { RefCell::new(None) };
        }
        if kind != Kind::Standard {
            return None;
        }
        CLIPBOARD.with(|cell| {
            let mut held = cell.borrow_mut();
            if held.is_none() {
                match arboard::Clipboard::new() {
                    Ok(opened) => *held = Some(opened),
                    Err(error) => {
                        log::warn!("no system clipboard: {error}");
                        return None;
                    }
                }
            }
            held.as_mut().map(f)
        })
    }
}

/// iOS has no desktop clipboard behind `arboard`; an editor there pastes
/// through the platform's own text input.
#[cfg(target_os = "ios")]
mod system {
    use super::Kind;
    pub fn read(_kind: Kind) -> Option<String> {
        None
    }
    pub fn write(_kind: Kind, _contents: String) {}
}
