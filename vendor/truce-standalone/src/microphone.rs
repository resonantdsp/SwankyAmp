//! Which input is the computer's own microphone, which feeds back through
//! its own speakers.
//!
//! macOS says so exactly: Core Audio reports the built-in transport and the
//! internal-microphone data source, which a headset or line jack on the
//! same chip does not. Windows reports the endpoint's form factor and bus,
//! so a microphone on the onboard HD Audio chip counts, whether built in
//! or plugged into the computer's own jack, and a microphone array behind
//! another driver, such as Intel Smart Sound, is not recognised. ALSA and
//! ASIO do not say, so nothing is recognised there.

/// The built-in microphones found when listing the inputs.
pub(crate) struct BuiltIn {
    #[cfg(target_os = "macos")]
    names: Vec<String>,
}

impl BuiltIn {
    pub(crate) fn find() -> Self {
        Self {
            #[cfg(target_os = "macos")]
            names: core_audio::built_in_microphones(),
        }
    }

    #[cfg_attr(target_os = "windows", allow(clippy::unused_self))]
    pub(crate) fn is(&self, device: &cpal::Device, name: &str) -> bool {
        #[cfg(target_os = "macos")]
        {
            let _ = device;
            self.names.iter().any(|built_in| built_in == name)
        }
        #[cfg(target_os = "windows")]
        {
            use cpal::traits::DeviceTrait;
            let _ = name;
            device.description().is_ok_and(|description| {
                description.device_type() == cpal::DeviceType::Microphone
                    && description.interface_type() == cpal::InterfaceType::BuiltIn
            })
        }
        #[cfg(not(any(target_os = "macos", target_os = "windows")))]
        {
            let _ = (device, name);
            false
        }
    }
}

#[cfg(target_os = "macos")]
mod core_audio {
    use std::ffi::{CStr, c_char, c_void};

    #[repr(C)]
    struct Address {
        selector: u32,
        scope: u32,
        element: u32,
    }

    #[link(name = "CoreAudio", kind = "framework")]
    unsafe extern "C" {
        fn AudioObjectGetPropertyDataSize(
            object: u32,
            address: *const Address,
            qualifier_size: u32,
            qualifier: *const c_void,
            size: *mut u32,
        ) -> i32;
        fn AudioObjectGetPropertyData(
            object: u32,
            address: *const Address,
            qualifier_size: u32,
            qualifier: *const c_void,
            size: *mut u32,
            data: *mut c_void,
        ) -> i32;
    }

    #[link(name = "CoreFoundation", kind = "framework")]
    unsafe extern "C" {
        fn CFStringGetCString(
            string: *const c_void,
            buffer: *mut c_char,
            size: isize,
            encoding: u32,
        ) -> u8;
        fn CFRelease(object: *const c_void);
    }

    const fn code(name: [u8; 4]) -> u32 {
        u32::from_be_bytes(name)
    }

    const SYSTEM: u32 = 1;
    const GLOBAL: u32 = code(*b"glob");
    const INPUT: u32 = code(*b"inpt");
    const UTF8: u32 = 0x0800_0100;

    fn size(object: u32, selector: u32, scope: u32) -> Option<u32> {
        let address = Address {
            selector,
            scope,
            element: 0,
        };
        let mut size = 0;
        // SAFETY: Core Audio writes the property's size into `size`.
        let status = unsafe {
            AudioObjectGetPropertyDataSize(
                object,
                &raw const address,
                0,
                std::ptr::null(),
                &raw mut size,
            )
        };
        (status == 0).then_some(size)
    }

    /// Reads a property into `data`, `size` bytes long.
    ///
    /// # Safety
    ///
    /// `data` must have room for `size` bytes of the property's type.
    unsafe fn read(object: u32, selector: u32, scope: u32, size: u32, data: *mut c_void) -> bool {
        let address = Address {
            selector,
            scope,
            element: 0,
        };
        let mut size = size;
        // SAFETY: the caller gives room for `size` bytes.
        unsafe {
            AudioObjectGetPropertyData(
                object,
                &raw const address,
                0,
                std::ptr::null(),
                &raw mut size,
                data,
            ) == 0
        }
    }

    fn code_of(object: u32, selector: u32, scope: u32) -> Option<u32> {
        let mut value = 0u32;
        // SAFETY: these properties are one UInt32.
        unsafe { read(object, selector, scope, 4, (&raw mut value).cast()) }.then_some(value)
    }

    /// The device's name as cpal reports it.
    fn name(object: u32) -> Option<String> {
        let mut string: *const c_void = std::ptr::null();
        let size = u32::try_from(size_of::<*const c_void>()).ok()?;
        // SAFETY: the name is one CFStringRef, which we own and release.
        unsafe {
            if !read(
                object,
                code(*b"lnam"),
                GLOBAL,
                size,
                (&raw mut string).cast(),
            ) || string.is_null()
            {
                return None;
            }
            let mut buffer = [0 as c_char; 512];
            let copied = CFStringGetCString(string, buffer.as_mut_ptr(), 512, UTF8) != 0;
            CFRelease(string);
            copied.then(|| {
                CStr::from_ptr(buffer.as_ptr())
                    .to_string_lossy()
                    .into_owned()
            })
        }
    }

    /// The inputs on the built-in transport whose source is the internal
    /// microphone.
    pub(super) fn built_in_microphones() -> Vec<String> {
        let Some(bytes) = size(SYSTEM, code(*b"dev#"), GLOBAL) else {
            return Vec::new();
        };
        let mut devices = vec![0u32; bytes as usize / 4];
        // SAFETY: `devices` has room for the `bytes` the list takes.
        if !unsafe {
            read(
                SYSTEM,
                code(*b"dev#"),
                GLOBAL,
                bytes,
                devices.as_mut_ptr().cast(),
            )
        } {
            return Vec::new();
        }
        devices
            .into_iter()
            .filter(|&device| {
                code_of(device, code(*b"tran"), GLOBAL) == Some(code(*b"bltn"))
                    && size(device, code(*b"stm#"), INPUT).is_some_and(|streams| streams > 0)
                    && code_of(device, code(*b"ssrc"), INPUT) == Some(code(*b"imic"))
            })
            .filter_map(name)
            .collect()
    }
}
