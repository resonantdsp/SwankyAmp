//! The product's log, for support: one small file shared by every format.
//!
//! It holds a header for each process that writes to it, the editor's
//! open and close stages with their durations, device losses and rebuilds,
//! and every warning and error from this crate, the editor framework and
//! wgpu, panics caught at the editor's catch points among them; everything
//! else is left out. Writing a line takes a lock and the file, so code logs
//! lifecycle events and warnings only, never per frame or per sample. The
//! home folder is written as `~`. A repeated line is counted rather than
//! rewritten, and past 1 MB the file becomes the previous one, so two are
//! kept.

use std::collections::VecDeque;
use std::io::Write as _;
use std::path::{Path, PathBuf};
use std::sync::{Mutex, OnceLock, PoisonError};

const PRODUCT: &str = "Swanky Amp 2";
const ROTATE_AT: u64 = 1024 * 1024;
const RECENT_LINES: usize = 50;
/// The warnings and errors a process may write, so a fault that alternates
/// two of them every frame cannot push the earlier history out of both files.
/// Lifecycle lines are not counted: they come a few per open and close.
const SESSION_ALARMS: u32 = 2000;

/// Where the log is written: in the account's Logs folder on macOS, beside
/// the shader cache under `%LOCALAPPDATA%` on Windows.
pub fn path() -> Option<PathBuf> {
    #[cfg(target_os = "macos")]
    let path = crate::presets::home().map(|home| {
        home.join("Library/Logs/Resonant DSP")
            .join(format!("{PRODUCT}.log"))
    });
    #[cfg(windows)]
    let path = local_folder().map(|folder| folder.join("Logs").join("editor.log"));
    #[cfg(not(any(target_os = "macos", windows)))]
    let path = std::env::var_os("XDG_STATE_HOME")
        .map(PathBuf::from)
        .or_else(|| crate::presets::home().map(|home| home.join(".local/state")))
        .map(|state| state.join("Resonant DSP").join(format!("{PRODUCT}.log")));
    path
}

/// The product's machine-local folder, `%LOCALAPPDATA%\Resonant DSP\Swanky
/// Amp 2`, for what belongs to this machine rather than the account.
#[cfg(windows)]
pub fn local_folder() -> Option<PathBuf> {
    std::env::var_os("LOCALAPPDATA")
        .map(|local| PathBuf::from(local).join("Resonant DSP").join(PRODUCT))
}

/// The log's path as a player can paste it into Finder or Explorer, with no
/// account name in it.
pub fn shown(path: &Path) -> String {
    #[cfg(windows)]
    if let Some(local) = std::env::var_os("LOCALAPPDATA")
        && let Ok(rest) = path.strip_prefix(&local)
    {
        return format!(r"%LOCALAPPDATA%\{}", rest.display());
    }
    hide_home(&path.display().to_string(), home().as_deref())
}

/// Start the log for this process; later calls do nothing. A process writes
/// its header with its first line, so one that only asks whether the plug-in
/// has an editor, as host scans do, leaves the file alone.
pub fn install() {
    static INSTALLED: std::sync::Once = std::sync::Once::new();
    INSTALLED.call_once(|| {
        if log::set_logger(LOG.get_or_init(|| Log::new(path(), home()))).is_ok() {
            log::set_max_level(log::LevelFilter::Info);
        }
    });
}

/// The adapter the editor draws with, the log's path, and the last warnings
/// and errors this process recorded, for the copied diagnostics.
pub fn summary() -> String {
    summary_of(LOG.get())
}

fn summary_of(log: Option<&Log>) -> String {
    let gpu = truce_iced::diagnostics::gpu().unwrap_or_else(|| "none (see the log)".into());
    let file = match log.and_then(|log| log.path.as_deref().map(|path| (log, path))) {
        Some((log, path)) if log.lock().written == Some(false) => {
            format!("{} (this host refused the write)", shown(path))
        }
        Some((_, path)) => shown(path),
        None => "none".into(),
    };
    let recent = log.map(Log::recent).unwrap_or_default();
    let recent = if recent.is_empty() {
        " none".into()
    } else {
        recent
            .iter()
            .map(|line| format!("\n  {line}"))
            .collect::<String>()
    };
    format!("GPU: {gpu}\nLog: {file}\nRecent warnings and errors:{recent}")
}

static LOG: OnceLock<Log> = OnceLock::new();

fn home() -> Option<String> {
    crate::presets::home().map(|home| home.display().to_string())
}

fn hide_home(text: &str, home: Option<&str>) -> String {
    match home {
        Some(home) if !home.is_empty() => text.replace(home, "~"),
        _ => text.to_owned(),
    }
}

struct Log {
    path: Option<PathBuf>,
    home: Option<String>,
    /// Which process and format wrote a line, since every format of the
    /// product, in any process, appends to the same file.
    tag: String,
    state: Mutex<State>,
}

#[derive(Default)]
struct State {
    last: String,
    repeats: u32,
    headed: bool,
    alarms: u32,
    /// Warnings and errors, each with how many more times it repeated.
    recent: VecDeque<(String, u32)>,
    /// Whether the last write reached the file.
    written: Option<bool>,
}

impl Log {
    fn new(path: Option<PathBuf>, home: Option<String>) -> Self {
        Self {
            path,
            home,
            tag: format!("{} {}", std::process::id(), crate::diagnostics::FORMAT),
            state: Mutex::default(),
        }
    }

    fn lock(&self) -> std::sync::MutexGuard<'_, State> {
        self.state.lock().unwrap_or_else(PoisonError::into_inner)
    }

    fn recent(&self) -> Vec<String> {
        self.lock()
            .recent
            .iter()
            .map(|(line, repeats)| match repeats {
                0 => line.clone(),
                n => format!("{line} (repeated {n} more times)"),
            })
            .collect()
    }

    fn write(&self, state: &mut State, entry: &str, alarm: bool) {
        if alarm {
            if state.alarms >= SESSION_ALARMS {
                return;
            }
            state.alarms += 1;
        }
        let stamp = timestamp();
        let mut text = String::new();
        if !state.headed {
            state.headed = true;
            text = format!(
                "{stamp} [{}] ==== {}, {} in {}, {} ({}), pid {}\n",
                self.tag,
                crate::diagnostics::heading(),
                crate::diagnostics::FORMAT,
                crate::diagnostics::host(),
                crate::diagnostics::os(),
                std::env::consts::ARCH,
                std::process::id(),
            );
        }
        text.push_str(&format!("{stamp} [{}] {entry}\n", self.tag));
        if alarm && state.alarms == SESSION_ALARMS {
            text.push_str("(warning limit reached; this process writes no more of them)\n");
        }
        if let Some(path) = &self.path {
            state.written = Some(append(path, &text));
        }
    }
}

impl log::Log for Log {
    fn enabled(&self, meta: &log::Metadata) -> bool {
        let target = meta.target();
        match meta.level() {
            log::Level::Info => target == truce_iced::diagnostics::LIFECYCLE,
            log::Level::Warn | log::Level::Error => {
                ["swanky_amp", "truce_iced", "baseview", "wgpu", "naga"]
                    .iter()
                    .any(|ours| target.starts_with(ours))
            }
            log::Level::Debug | log::Level::Trace => false,
        }
    }

    fn log(&self, record: &log::Record) {
        if !self.enabled(record.metadata()) {
            return;
        }
        let entry = hide_home(
            &format!(
                "{:<5} {}: {}",
                record.level(),
                record.target(),
                record.args()
            ),
            self.home.as_deref(),
        );
        let alarm = record.level() <= log::Level::Warn;
        let mut state = self.lock();
        if entry == state.last {
            state.repeats += 1;
            if alarm && let Some((_, repeats)) = state.recent.back_mut() {
                *repeats += 1;
            }
            return;
        }
        if state.repeats > 0 {
            let note = format!(
                "(this process's previous line repeated {} more times)",
                state.repeats
            );
            state.repeats = 0;
            let repeated_alarm = state.last.starts_with("WARN") || state.last.starts_with("ERROR");
            self.write(&mut state, &note, repeated_alarm);
        }
        self.write(&mut state, &entry, alarm);
        if alarm {
            if state.recent.len() == RECENT_LINES {
                state.recent.pop_front();
            }
            let line = format!("{} {entry}", timestamp());
            state.recent.push_back((line, 0));
        }
        state.last = entry;
    }

    fn flush(&self) {}
}

/// Append to the log, first moving a full one aside as the previous log.
/// Each write opens the file afresh, so formats in other processes that
/// share it, and a rotation one of them made, are followed.
fn append(path: &Path, text: &str) -> bool {
    if std::fs::metadata(path).is_ok_and(|meta| meta.len() >= ROTATE_AT) {
        let _ = std::fs::rename(path, previous(path));
    }
    if let Some(folder) = path.parent() {
        let _ = std::fs::create_dir_all(folder);
    }
    std::fs::OpenOptions::new()
        .create(true)
        .append(true)
        .open(path)
        .and_then(|mut file| file.write_all(text.as_bytes()))
        .is_ok()
}

fn previous(path: &Path) -> PathBuf {
    let stem = path
        .file_stem()
        .map_or_else(String::new, |s| s.to_string_lossy().into_owned());
    path.with_file_name(format!("{stem} (previous).log"))
}

/// UTC, to the millisecond, so lines match a host's crash report.
fn timestamp() -> String {
    let since = std::time::SystemTime::now()
        .duration_since(std::time::UNIX_EPOCH)
        .unwrap_or_default();
    let seconds = since.as_secs();
    let (year, month, day) = civil_date(seconds / 86_400);
    let time = seconds % 86_400;
    format!(
        "{year:04}-{month:02}-{day:02} {:02}:{:02}:{:02}.{:03}Z",
        time / 3600,
        time / 60 % 60,
        time % 60,
        since.subsec_millis()
    )
}

/// The calendar date `days` after 1970-01-01, by Howard Hinnant's
/// `civil_from_days`.
pub(crate) fn civil_date(days: u64) -> (u64, u64, u64) {
    let z = days + 719_468;
    let era = z / 146_097;
    let day_of_era = z % 146_097;
    let year_of_era =
        (day_of_era - day_of_era / 1460 + day_of_era / 36_524 - day_of_era / 146_096) / 365;
    let day_of_year = day_of_era - (365 * year_of_era + year_of_era / 4 - year_of_era / 100);
    let shifted_month = (5 * day_of_year + 2) / 153;
    let day = day_of_year - (153 * shifted_month + 2) / 5 + 1;
    let month = if shifted_month < 10 {
        shifted_month + 3
    } else {
        shifted_month - 9
    };
    let year = year_of_era + era * 400 + u64::from(month <= 2);
    (year, month, day)
}

#[cfg(test)]
mod tests {
    use super::*;
    use log::Log as _;

    fn folder(name: &str) -> PathBuf {
        let folder =
            std::env::temp_dir().join(format!("swanky-editor-log-{}-{name}", std::process::id()));
        let _ = std::fs::remove_dir_all(&folder);
        folder
    }

    fn send(log: &Log, level: log::Level, target: &str, message: &str) {
        log.log(
            &log::Record::builder()
                .level(level)
                .target(target)
                .args(format_args!("{message}"))
                .build(),
        );
    }

    #[test]
    fn the_log_counts_repeats_hides_the_home_folder_and_keeps_out_other_chatter() {
        let folder = folder("repeats");
        let path = folder.join("editor.log");
        let log = Log::new(Some(path.clone()), Some("/Users/someone".into()));
        let warning = "shader cache at /Users/someone/Library/Caches is not writable";
        for _ in 0..3 {
            send(&log, log::Level::Warn, "wgpu_hal::dx12", warning);
        }
        send(
            &log,
            log::Level::Info,
            truce_iced::diagnostics::LIFECYCLE,
            "close",
        );
        send(&log, log::Level::Info, "wgpu_core::device", "every frame");
        send(
            &log,
            log::Level::Warn,
            "truce_core::audio",
            "an audio thread warning",
        );

        let written = std::fs::read_to_string(&path).unwrap();
        assert!(!written.contains("someone"), "{written}");
        assert_eq!(written.matches("~/Library/Caches").count(), 1, "{written}");
        assert!(written.contains("repeated 2 more times"), "{written}");
        assert!(written.contains("close"), "{written}");
        assert!(!written.contains("every frame"), "{written}");
        assert!(!written.contains("audio thread"), "{written}");
        let recent = log.recent();
        assert_eq!(recent.len(), 1, "{recent:?}");
        assert!(recent[0].ends_with("(repeated 2 more times)"), "{recent:?}");
        let _ = std::fs::remove_dir_all(folder);
    }

    #[test]
    fn a_full_log_becomes_the_previous_one_and_only_two_are_kept() {
        let folder = folder("rotation");
        std::fs::create_dir_all(&folder).unwrap();
        let path = folder.join("editor.log");
        let full = "x".repeat(ROTATE_AT as usize);
        std::fs::write(&path, &full).unwrap();
        std::fs::write(previous(&path), "older").unwrap();

        let log = Log::new(Some(path.clone()), None);
        send(
            &log,
            log::Level::Error,
            "truce_iced::pump",
            "gpu init failed",
        );

        let current = std::fs::read_to_string(&path).unwrap();
        assert!(current.contains("gpu init failed"), "{current}");
        assert!(current.len() < 1024);
        assert_eq!(std::fs::read_to_string(previous(&path)).unwrap(), full);
        assert_eq!(std::fs::read_dir(&folder).unwrap().count(), 2);
        let _ = std::fs::remove_dir_all(folder);
    }

    #[test]
    fn a_host_that_refuses_the_write_still_gets_the_recent_errors() {
        let folder = folder("refused");
        std::fs::create_dir_all(&folder).unwrap();
        // A file where the log's folder should be cannot be written through.
        let blocked = folder.join("blocked");
        std::fs::write(&blocked, "").unwrap();
        let log = Log::new(Some(blocked.join("editor.log")), None);
        send(
            &log,
            log::Level::Error,
            "swanky_amp",
            "a preset import panicked",
        );

        let summary = summary_of(Some(&log));
        assert!(summary.contains("refused the write"), "{summary}");
        assert!(summary.contains("a preset import panicked"), "{summary}");
        let _ = std::fs::remove_dir_all(folder);
    }

    #[test]
    fn timestamps_name_the_utc_calendar_date() {
        assert_eq!(civil_date(0), (1970, 1, 1));
        // 2026-10-05 and a leap day.
        assert_eq!(civil_date(20_731), (2026, 10, 5));
        assert_eq!(civil_date(19_782), (2024, 2, 29));
    }
}
