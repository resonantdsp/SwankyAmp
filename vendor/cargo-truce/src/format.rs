//! Plug-in format identity (CLAP / VST3 / VST2 / LV2 / AU / AAX).
//!
//! `Format` is decoupled from any particular subcommand: install,
//! uninstall, doctor, validate, package, and scaffold all need to
//! talk about "the CLAP version of this plug-in" without redefining
//! a label-or-extension table. Per-format methods live here; the
//! one method that depends on install scope ([`Format::dir`])
//! borrows [`InstallScope`] from `install_scope`.

use std::path::PathBuf;

use crate::install_scope::InstallScope;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub(crate) enum Format {
    Clap,
    Vst3,
    Vst2,
    Lv2,
    #[cfg_attr(not(target_os = "macos"), allow(dead_code))]
    Au2,
    #[cfg_attr(not(target_os = "macos"), allow(dead_code))]
    Au3,
    #[cfg_attr(not(any(target_os = "macos", target_os = "windows")), allow(dead_code))]
    Aax,
}

impl Format {
    /// Human-readable display name (`"CLAP"`, `"VST3"`, `"AU v2"`,
    /// …). Used for log/UI labels in `doctor`, `validate`, and
    /// install/uninstall messaging.
    pub(crate) fn label(self) -> &'static str {
        match self {
            Self::Clap => "CLAP",
            Self::Vst3 => "VST3",
            Self::Vst2 => "VST2",
            Self::Lv2 => "LV2",
            Self::Au2 => "AU v2",
            Self::Au3 => "AU v3",
            Self::Aax => "AAX",
        }
    }

    /// Per-format install directory for the requested scope. Returns
    /// `None` for combinations not addressable by [`InstallScope`]
    /// alone (AAX is system-only and lives at a fixed location;
    /// AU v3 ships as a host app).
    #[cfg_attr(not(target_os = "macos"), allow(dead_code))]
    pub(crate) fn dir(self, scope: InstallScope) -> Option<PathBuf> {
        match self {
            Self::Clap => Some(scope.clap_dir()),
            Self::Vst3 => Some(scope.vst3_dir()),
            Self::Vst2 => Some(scope.vst2_dir()),
            Self::Lv2 => Some(scope.lv2_dir()),
            #[cfg(target_os = "macos")]
            Self::Au2 => Some(scope.au_v2_dir()),
            #[cfg(not(target_os = "macos"))]
            Self::Au2 => None,
            Self::Au3 | Self::Aax => None,
        }
    }
}
