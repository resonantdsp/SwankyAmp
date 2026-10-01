//! Keeps the plug-in's code mapped for the life of the host process.
//!
//! The editor starts threads that are never joined: the release-notice check,
//! the save dialog and the preset import. Windows hosts unload a plug-in's
//! library when its last instance goes, and a thread still running then would
//! return into unmapped code and take the host down. Pinning the library
//! before the first of them starts costs one mapping that outlives the last
//! instance. macOS does not unload a bundle's image in practice.

#[cfg(windows)]
pub(crate) fn stay_loaded() {
    use std::sync::Once;
    use windows_sys::Win32::Foundation::HMODULE;
    use windows_sys::Win32::System::LibraryLoader::{
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, GET_MODULE_HANDLE_EX_FLAG_PIN, GetModuleHandleExW,
    };

    static PINNED: Once = Once::new();
    PINNED.call_once(|| {
        let mut module: HMODULE = std::ptr::null_mut();
        // SAFETY: with FROM_ADDRESS the name is read as an address inside
        // the module to find, here this function's own; the handle written
        // to `module` is pinned and deliberately never released.
        unsafe {
            GetModuleHandleExW(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN,
                stay_loaded as *const u16,
                &mut module,
            );
        }
    });
}

#[cfg(not(windows))]
pub(crate) fn stay_loaded() {}
