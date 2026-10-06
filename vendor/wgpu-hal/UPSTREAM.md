# The system's shader compiler

Source: crates.io `wgpu-hal` 27.0.4, upstream commit
`af91efa93da2af9366b252ed7b9a089175f4874e`, `wgpu-hal` in
[wgpu](https://github.com/gfx-rs/wgpu).
The upstream license texts are included unchanged.

The published crate loads the DirectX 12 backend's shader compiler, FXC, by
the bare name `d3dcompiler_47.dll`. Windows resolves that name against the
host's own directory first, and Ableton Live 10 carries an older copy there
that rejects the `cs_5_1` target with error X3506. wgpu's indirect-dispatch
validation shader then fails to compile, device creation fails and the editor
stays blank. `src/dx12/shader_compilation.rs` loads the copy in the Windows
system directory by its full path and falls back to the bare name only when
that fails; the `dx12` feature gains the `Win32_System_SystemInformation`
binding it needs. No other backend or platform is touched.

Remove the Cargo patch and this directory when a pinned upstream release loads
the compiler from the system directory, or when the editor moves to a wgpu
release that does.

# One device, on the GPU Windows would choose

The published backend creates a D3D12 device on every adapter while
enumerating them, to read its capabilities, and wgpu then keeps one. Each
device wakes its GPU and commits memory, so a dual-GPU laptop woke its
discrete card for an editor drawn on the integrated one.
`auxil/dxgi/factory.rs` now lists hardware adapters in the order
`IDXGIFactory6::EnumAdapterByGpuPreference` gives, and `dx12/instance.rs`
exposes only the first that creates a device. Software adapters (WARP) are
listed after every hardware adapter, so a machine with a working GPU never
creates a WARP device, while one with no DirectX 12 hardware driver, such as
a virtual machine, still draws on the CPU as upstream does.

The preference is the player's per-program choice in Windows' graphics
settings when there is one, and the minimum-power order otherwise. Microsoft
documents `DXGI_GPU_PREFERENCE_UNSPECIFIED` as the plain `EnumAdapters1`
order and the explicit preferences as fixed orders, and says nothing of the
setting, so the backend reads it where Windows records it,
`HKCU\Software\Microsoft\DirectX\UserGpuPreferences`, under the running
executable (the host's, for a plug-in): `GpuPreference=2` asks for high
performance, anything else for minimum power. Windows older than 10 1803 has
no `IDXGIFactory6` and keeps the `EnumAdapters1` order. The `dx12` feature
gains the `Win32_System_Registry` binding.

# A shader cache shared across devices and runs

The published FXC cache belongs to one device, so each editor recompiled every
shader, and FXC is the slowest step of opening one. `dx12/fxc_cache.rs` keeps
FXC's output for the whole process and, once
`wgpu_hal::dx12::set_shader_cache_dir` names a directory, on disk. An entry is
found only under the inputs that produce it: HLSL source and name, entry
point, target, compile flags and the file version of the system
`d3dcompiler_47.dll` (read with the `Win32_Storage_FileSystem` binding). A
compiler found only by its bare name has no known version and is not cached.
Each file carries its key and a checksum of the bytecode; anything that does
not match is a miss and is rewritten, and a failed write costs only the
compile. Files written for an older compiler or shader are never removed,
nor is a `.partial` file left by a process that died mid-write; each holds
its source and bytecode, tens of kilobytes. DXC is not cached beyond the device, as before.

Remove these with the rest of this directory when a pinned upstream release
makes the same choices.
