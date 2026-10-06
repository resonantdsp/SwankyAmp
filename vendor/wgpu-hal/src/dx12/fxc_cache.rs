//! FXC's output, shared by every device in the process and kept on disk.
//!
//! An entry is found only under the exact inputs that produced it: the HLSL
//! source, its name, the entry point, the target (stage and shader model), the
//! compile flags and the version of the `d3dcompiler_47.dll` that compiled it.
//! A file that is unreadable, truncated, or written for other inputs is a miss
//! and is rewritten; a cache that cannot be written only costs a compile.

use alloc::vec::Vec;
use std::{
    collections::HashMap,
    path::{Path, PathBuf},
    sync::{Mutex, OnceLock},
};

static DIRECTORY: OnceLock<PathBuf> = OnceLock::new();
static MEMORY: OnceLock<Mutex<HashMap<Vec<u8>, Vec<u8>>>> = OnceLock::new();

const MAGIC: &[u8; 8] = b"WGFXC\0\0\x01";

/// Keep compiled shaders in `directory` across processes. The first call in a
/// process wins; without one, shaders are shared only within the process.
pub fn set_shader_cache_dir(directory: PathBuf) {
    let _ = DIRECTORY.set(directory);
}

/// The inputs that decide FXC's output, as one byte string.
pub(super) fn key(
    compiler_version: u64,
    source: &str,
    source_name: Option<&core::ffi::CStr>,
    entry_point: &str,
    target: &str,
    flags: u32,
) -> Vec<u8> {
    let mut key = Vec::with_capacity(source.len() + 64);
    key.extend(compiler_version.to_le_bytes());
    key.extend(flags.to_le_bytes());
    for field in [
        target.as_bytes(),
        entry_point.as_bytes(),
        source_name.map_or(&[][..], |name| name.to_bytes()),
        source.as_bytes(),
    ] {
        key.extend((field.len() as u64).to_le_bytes());
        key.extend(field);
    }
    key
}

pub(super) fn get(key: &[u8]) -> Option<Vec<u8>> {
    let memory = MEMORY.get_or_init(Default::default);
    if let Some(bytecode) = memory.lock().ok()?.get(key) {
        return Some(bytecode.clone());
    }
    let bytecode = read(&path(DIRECTORY.get()?, key), key)?;
    if let Ok(mut memory) = memory.lock() {
        memory.insert(key.to_vec(), bytecode.clone());
    }
    Some(bytecode)
}

pub(super) fn put(key: Vec<u8>, bytecode: &[u8]) {
    if let Some(directory) = DIRECTORY.get() {
        write(directory, &path(directory, &key), &key, bytecode);
    }
    if let Ok(mut memory) = MEMORY.get_or_init(Default::default).lock() {
        memory.insert(key, bytecode.to_vec());
    }
}

/// A file's name only spreads entries out; the key stored inside decides a hit.
fn path(directory: &Path, key: &[u8]) -> PathBuf {
    directory.join(format!("{:016x}.fxc", fnv1a(key)))
}

fn fnv1a(bytes: &[u8]) -> u64 {
    bytes.iter().fold(0xcbf2_9ce4_8422_2325, |hash, &byte| {
        (hash ^ u64::from(byte)).wrapping_mul(0x0100_0000_01b3)
    })
}

/// `MAGIC`, the key's length and the key, the bytecode's checksum, then the
/// bytecode. D3D12 rejects a damaged shader only when it builds the pipeline,
/// which would fail the editor, so the checksum turns damage into a miss.
fn read(path: &Path, key: &[u8]) -> Option<Vec<u8>> {
    let file = std::fs::read(path).ok()?;
    let rest = file.strip_prefix(MAGIC)?;
    let (length, rest) = rest.split_first_chunk::<8>()?;
    let stored_key = rest.get(..usize::try_from(u64::from_le_bytes(*length)).ok()?)?;
    if stored_key != key {
        return None;
    }
    let (checksum, bytecode) = rest[key.len()..].split_first_chunk::<8>()?;
    (!bytecode.is_empty() && u64::from_le_bytes(*checksum) == fnv1a(bytecode))
        .then(|| bytecode.to_vec())
}

/// Written beside its final name and renamed into place, so another process
/// reading the entry sees the old file or the whole new one.
fn write(directory: &Path, path: &Path, key: &[u8], bytecode: &[u8]) {
    let mut file = Vec::with_capacity(MAGIC.len() + 16 + key.len() + bytecode.len());
    file.extend(MAGIC);
    file.extend((key.len() as u64).to_le_bytes());
    file.extend(key);
    file.extend(fnv1a(bytecode).to_le_bytes());
    file.extend(bytecode);
    static WRITES: core::sync::atomic::AtomicU32 = core::sync::atomic::AtomicU32::new(0);
    let write = WRITES.fetch_add(1, core::sync::atomic::Ordering::Relaxed);
    let partial = path.with_extension(format!("{}.{write}.partial", std::process::id()));
    let written = std::fs::create_dir_all(directory)
        .and_then(|()| std::fs::write(&partial, &file))
        .and_then(|()| std::fs::rename(&partial, path));
    if written.is_err() {
        let _ = std::fs::remove_file(&partial);
    }
}

/// The version resource of the compiler at `path`, as one number.
pub(super) fn compiler_version(path: &Path) -> Option<u64> {
    use std::os::windows::ffi::OsStrExt as _;
    use windows::{core::PCWSTR, Win32::Storage::FileSystem};

    let path: Vec<u16> = path.as_os_str().encode_wide().chain([0]).collect();
    let path = PCWSTR(path.as_ptr());
    unsafe {
        let size = FileSystem::GetFileVersionInfoSizeW(path, None);
        if size == 0 {
            return None;
        }
        let mut block = alloc::vec![0u8; size as usize];
        FileSystem::GetFileVersionInfoW(path, 0, size, block.as_mut_ptr().cast()).ok()?;
        let mut info: *mut core::ffi::c_void = core::ptr::null_mut();
        let mut length = 0u32;
        if !FileSystem::VerQueryValueW(
            block.as_ptr().cast(),
            windows::core::w!("\\"),
            &mut info,
            &mut length,
        )
        .as_bool()
            || info.is_null()
            || (length as usize) < size_of::<FileSystem::VS_FIXEDFILEINFO>()
        {
            return None;
        }
        let info = info.cast::<FileSystem::VS_FIXEDFILEINFO>().read_unaligned();
        Some(u64::from(info.dwFileVersionMS) << 32 | u64::from(info.dwFileVersionLS))
    }
}
