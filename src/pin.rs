//! Keeps the plugin's code loaded once it has started threads it does not
//! join.
//!
//! A host may unload the plugin when its last instance goes (Bitwig, Cubase
//! and JUCE hosts do on Windows). A thread the plugin does not join that is
//! still running then returns into unmapped code and takes the host down.
//! Pinning the module, as the framework does for its own task pool, trades a
//! mapping kept until the host exits for that crash.
use std::ffi::c_void;

/// Pins this module for the life of the process. Call it before starting any
/// thread that is not joined when the plugin goes; only the first call acts.
pub(crate) fn keep_loaded() {
    static PINNED: std::sync::Once = std::sync::Once::new();
    PINNED.call_once(pin_current_module);
}

#[cfg(windows)]
fn pin_current_module() {
    unsafe extern "system" {
        fn GetModuleHandleExW(flags: u32, name: *const u16, module: *mut *mut c_void) -> i32;
    }
    // GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN:
    // the module holding this function, never to be unloaded.
    const PIN_FROM_ADDRESS: u32 = 0x0000_0004 | 0x0000_0001;
    // SAFETY: the name is the address of a live function in this module, and
    // the handle written back is deliberately never released.
    unsafe {
        let mut module: *mut c_void = std::ptr::null_mut();
        let _ = GetModuleHandleExW(
            PIN_FROM_ADDRESS,
            pin_current_module as *const u16,
            &raw mut module,
        );
    }
}

#[cfg(unix)]
fn pin_current_module() {
    use std::ffi::{c_char, c_int};
    #[repr(C)]
    struct DlInfo {
        dli_fname: *const c_char,
        dli_fbase: *mut c_void,
        dli_sname: *const c_char,
        dli_saddr: *mut c_void,
    }
    unsafe extern "C" {
        fn dladdr(address: *const c_void, info: *mut DlInfo) -> c_int;
        fn dlopen(filename: *const c_char, flags: c_int) -> *mut c_void;
    }
    // RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD | RTLD_NODELETE, whose values
    // differ between glibc and Darwin. Local, because Darwin otherwise makes
    // the plugin's symbols resolve process-wide; lazy, because glibc refuses
    // a mode with neither lazy nor now binding.
    #[cfg(target_os = "linux")]
    const FLAGS: c_int = 0x0001 | 0x0004 | 0x1000;
    #[cfg(not(target_os = "linux"))]
    const FLAGS: c_int = 0x0001 | 0x0004 | 0x0010 | 0x0080;
    // SAFETY: `dladdr` describes the loaded object holding this function, with
    // loader-owned strings valid for the immediate `dlopen`, which only
    // re-references that object; its handle is deliberately never closed.
    unsafe {
        let mut info: DlInfo = std::mem::zeroed();
        if dladdr(pin_current_module as *const c_void, &raw mut info) != 0
            && !info.dli_fname.is_null()
        {
            let _ = dlopen(info.dli_fname, FLAGS);
        }
    }
}

#[cfg(not(any(unix, windows)))]
fn pin_current_module() {}
