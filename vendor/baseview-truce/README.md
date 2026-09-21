# baseview

A low-level windowing system geared towards making audio plugin UIs.

`baseview` abstracts the platform-specific windowing APIs (winapi, cocoa, xcb) into a platform-independent API, but otherwise gets out of your way so you can write plugin UIs.

This is a fork of [RustAudio/baseview](https://github.com/RustAudio/baseview) (published on crates.io as `baseview-truce`) carrying patches that haven't yet made it into the upstream crate:

- **Pro Tools (AAX) teardown crash fix** on macOS — see [Pro Tools (AAX) fix](#pro-tools-aax-fix).
- **Editor frame-timer use-after-free fix** on macOS: the repaint timer could fire after the `WindowState` was freed (AU v3 view-service teardown), segfaulting the editor. See [macOS editor frame-timer fix](#macos-editor-frame-timer-fix).
- **Host-driven NSView resize → `Resized` events** on macOS — see [macOS frame-change Resized events](#macos-frame-change-resized-events).
- **`Window::set_mouse_cursor` for macOS** — upstream is `todo!()`, see [macOS cursor implementation](#macos-cursor-implementation).
- **`hit_test` gated behind `opengl` cfg** so CPU-only renderers (wgpu via `CAMetalLayer`, CoreGraphics blit) get AppKit's default hit-testing back — see [CPU-only hit-test gate](#cpu-only-hit-test-gate).
- **Windows frame pacing via a multimedia timer** on Windows — replaces the low-priority, coalescing `WM_TIMER` that drove `on_frame` with a non-coalescing posted-message timer, fixing slow / bursty editor repaints inside busy DAWs, plus a re-entrancy guard so a render that pumps the message queue can't abort the host — see [Windows frame pacing](#windows-frame-pacing).
- **Embed-parent resize tracking** on Linux/X11 — mirrors the host embed window's size onto the child so editors follow a host-driven resize even when the DAW resizes the parent directly instead of calling the plugin resize API (Bitwig) — see [Linux embed-parent resize](#linux-embed-parent-resize).

> **Note:** This package is a temporary fork intended to live only until these patches are merged upstream into [RustAudio/baseview](https://github.com/RustAudio/baseview). Once upstream carries the fixes, switch back to the canonical crate — there is nothing here that should outlive that merge.

## Pro Tools (AAX) fix

Upstream baseview on macOS crashes Pro Tools the moment a plugin editor is closed (or another plugin's editor is opened, which closes the first). This section describes the crash we actually observed, why it happens, and the minimal patch that fixes it.

### Crash signature

```
Thread 0 Crashed:: Main Thread Dispatch queue: com.apple.main-thread
0  libobjc.A.dylib                 objc_msgSend + 56
1  DFW                             -[DFW_NSContainer dealloc] + 56
2  libobjc.A.dylib                 AutoreleasePoolPage::releaseUntil
3  libobjc.A.dylib                 objc_autoreleasePoolPop + 244
4  DFW                             -[DFW_NSApplication sendEvent:] + 2016
5  AppKit                          -[NSApplication _handleEvent:]
6  AppKit                          -[NSApplication run]
7  DFW                             DFW_EventLoop::RunApplicationEventLoop
```

`EXC_BAD_ACCESS` with invalid addresses that varied between runs — `0x0`, `0x5`, `0x6`, `0x0f007fffffffffc0`. The address changes every time, which is the classic signature of dereferencing a freed object whose memory has been reused for unrelated data.

The crash happens deep inside Pro Tools' own event dispatch: `sendEvent:` holds an outer autorelease pool, plugin code runs inside it (our `close()` is called from that event), the pool drains after the event handler returns, and one of the autoreleased objects — always a `DFW_NSContainer` (Avid's private subclass of `NSView`) — tries to message one of its ivars during dealloc. The ivar's pointer is stale: it references an object we destroyed during plugin close.

### Root cause

When baseview's `WindowInner::close()` tears the view down it calls `removeFromSuperview` and then `release`. That is not enough.

While the view was attached, AppKit and the host embedded it in several back-referencing registries that **are not** cleared by `removeFromSuperview`:

- **Window first responder.** Our view can become first responder (it handles keyboard events and overrides `acceptsFirstResponder` to `YES`). `NSWindow.firstResponder` is a raw pointer; on the OS versions Pro Tools ships on it isn't always zeroing-weak, and even where it is, some hosts query or keep a parallel reference.
- **Tracking-area registry.** Baseview creates an `NSTrackingArea` with `owner: self` and adds it to the view. AppKit keeps the tracking area alive; its `owner` back-pointer to our view is not cleared by normal view teardown.
- **Layer contents.** If the view is layer-backed (wgpu via a `CAMetalLayer`, CoreGraphics blit via `setContents:`), the layer holds an image that in turn holds references into the view's rendering context.

Pro Tools' `DFW_NSContainer` — the container view Pro Tools wraps around the plugin embedding area — walks one of these registries during its own dealloc and messages what is now a freed pointer. Because the crash happens inside Pro Tools' outer pool drain, every host framework (CLAP, VST3 on other DAWs) that doesn't wrap plugin events in their own pools this way is unaffected. It's specific to the AAX + DFW shape.

### The fix

`src/macos/window.rs`, inside `WindowInner::close()`, before `removeFromSuperview` + `release`:

1. Wrap the body in a local `NSAutoreleasePool` and drain it at the end. Any ObjC object we autorelease during teardown gets released **here**, not in the host's outer pool.
2. `[window makeFirstResponder: nil]` if we're a responder.
3. Enumerate `view.trackingAreas` and `removeTrackingArea:` each one.
4. `[view.layer setContents: nil]` to drop the layer's image.

That's the whole patch — about 35 added lines in a single file. See the `git diff` vs upstream master.

## macOS editor frame-timer fix

On macOS baseview drives `WindowHandler::on_frame` from a 15 ms `CFRunLoopTimer`. In an AU v3 view-service (Logic, and any AUv3 host that runs the editor in a separate view process) the plugin editor could segfault when its window was opened or closed. Because the crash lives in the editor's paint timer, an audio-only validation like `auval` never reaches it; it only fires once a host actually shows the UI.

### Crash signature

```
EXC_BAD_ACCESS (SIGSEGV), KERN_INVALID_ADDRESS at 0x0000000000000018
0  <Plugin>AU        baseview::macos::window::WindowState::setup_timer::timer_callback
1  CoreFoundation    __CFRUNLOOP_IS_CALLING_OUT_TO_A_TIMER_CALLBACK_FUNCTION__
2  CoreFoundation    __CFRunLoopDoTimer
3  CoreFoundation    __CFRunLoopRun
```

The fault address is a small fixed offset (`0x18`, a field within `WindowState`) off a null/freed base: the timer callback dereferencing a `WindowState` that no longer exists.

### Root cause

`setup_timer` stored a non-owning raw `*const WindowState` in the `CFRunLoopTimerContext` (`retain` / `release` are `None`), so the timer did not keep the state alive. Teardown then cancelled the timer with `CFRunLoop::current().remove_timer(...)`, but that targets whichever run loop is *current at close time*, which in an AU view-service is not guaranteed to be the loop `setup_timer` scheduled the timer on. When they differ the removal silently no-ops, the `WindowState` is dropped anyway, and the next 15 ms tick dereferences freed memory. The callback had no liveness check, so a surviving timer was fatal.

### The fix

`src/macos/window.rs`, two changes:

1. **Weak handle in the timer context.** The context now holds a `Weak<WindowState>` (via `Weak::into_raw`) instead of a raw pointer. `timer_callback` upgrades it and skips the frame if the state is gone, so a stray tick after teardown is a harmless no-op instead of a use-after-free. The `Weak` is stored on the `WindowState` and reclaimed / dropped at close.
2. **Loop-agnostic cancellation.** Teardown calls `CFRunLoopTimer::invalidate()` instead of `remove_timer` on the current loop. `invalidate` removes the timer from whatever loop it was scheduled on, so no tick can outlive the drop regardless of which run loop closes the window.

This is the same "editor close crash" family as the [Pro Tools (AAX) fix](#pro-tools-aax-fix) but a different object: there it is AppKit registries retaining a freed view; here it is the frame timer outliving the window state.

## macOS frame-change Resized events

Upstream baseview on macOS only fires `WindowEvent::Resized` from `viewDidChangeBackingProperties:`, which AppKit only calls on **backing-scale** changes (the view moves to a different monitor). Every other path that mutates the NSView's frame size — the parent's `autoresizingMask` shrinking / growing the child during a host-window drag, the host directly calling `setFrameSize:` on the embedded view, even baseview's own `Window::resize` trampoline — runs **without** firing `Resized`.

For plugin editors that render through a `CAMetalLayer` (wgpu, anything blitting through `setContents:`) this is the difference between a clean resize and squashed knobs:

- The NSView's frame grows (autoresize works fine).
- The CAMetalLayer's frame implicitly tracks the NSView (good).
- The CAMetalLayer's `drawableSize` (the size of the texture wgpu / CoreGraphics actually paints into) **stays at the old logical size**.
- AppKit composites the small texture into the larger frame, stretching it across the new bounds.

The fix is a single `setFrameSize:` override on baseview's NSView subclass. It calls `super` first (so AppKit's bookkeeping — intrinsic content size, propagation to subview autoresize masks, etc. — runs unchanged), reads the new bounds, and emits `WindowEvent::Resized` with the same `WindowInfo` shape `viewDidChangeBackingProperties:` uses. Backends (egui / iced / slint / vizia) already react to `Resized` by reconfiguring their surfaces, so this single override fixes resize for every backend and every plugin format that embeds via `setFrameSize:`.

LV2 in particular relies on this path heavily: the LV2 UI spec gives the host a `ui:resize` extension to push size changes through, but in practice most hosts (Ardour, Reaper LV2, jalv-gtk on macOS) just resize the parent NSView and expect the child's autoresize mask to do the rest. Without this patch, the editor's wgpu surface stays at the original size and the user sees stretched / squashed content.

## macOS cursor implementation

Upstream `src/macos/cursor.rs` returns `todo!()` for every cursor variant — calling `Window::set_mouse_cursor` on macOS crashes. This fork ports the whole [`MouseCursor`](src/window.rs) enum to the corresponding AppKit `NSCursor`s via `objc2-app-kit`, with `NSCursor::arrowCursor`, `iBeamCursor`, `pointingHandCursor`, `crosshairCursor`, etc. mapped one-to-one where AppKit has a direct equivalent and falling back to the closest cursor for variants AppKit doesn't ship (e.g. `MouseCursor::Hand` → `pointingHandCursor`, `Help` → `arrowCursor`).

The implementation also handles dynamic cursor updates: AppKit's cursor only sticks while the cursor is over the view, so the fork installs the cursor inside the `cursorUpdate:` path so it persists across `NSTrackingArea` re-entries instead of reverting to whatever cursor the host's outer container last set.

## CPU-only hit-test gate

Upstream baseview's `-[NSView hitTest:]` override always runs, even when the consumer isn't using the OpenGL render path. That override exists to redirect hit-tests away from a GL render subview so input events land on baseview's main view; with no GL subview present it has nothing to redirect and can leave events unhandled (cursor reverts to the host's last-set cursor, drags don't start cleanly).

This fork gates the `hitTest:` method registration behind `#[cfg(feature = "opengl")]`. Consumers using baseview purely for windowing + CPU rendering (truce-gui via wgpu / CoreGraphics, anyone painting through `setContents:`) get AppKit's default hit-testing back, which behaves correctly for top-level NSViews.

## Windows frame pacing

Upstream baseview on Windows drives `WindowHandler::on_frame` from a 15 ms `WM_TIMER` (`src/win/window.rs`). The upstream code even flags this as a placeholder ("should be replaced by proper window redrawing/damage/vsync handling"). For a plugin editor embedded as a `WS_CHILD` of a busy DAW it produces visibly **slow and bursty** repaints, and every wgpu/GL backend (egui, iced, …) inherits it because they all render from `on_frame`.

### Why `WM_TIMER` is the wrong driver

`WM_TIMER` is the lowest-priority Windows message:

- **It only fires when the queue is otherwise empty.** A DAW floods its GUI thread with messages (automation, meters, mouse), so the editor's timer starves, then catches up in a clump — frames arrive in bursts instead of evenly.
- **Missed intervals coalesce.** Windows posts at most one `WM_TIMER` no matter how many intervals elapsed, so a stall is never made up.
- **Resolution is ~15.6 ms.** A 15 ms request rounds up to the next system tick; under coalescing the effective rate often drops to ~31 ms (~32 fps), the "slow" half of the symptom.

### The fix

`src/win/window.rs` replaces the `WM_TIMER` with a **winmm multimedia timer** (`timeSetEvent`, `TIME_PERIODIC`) whose callback *posts* a custom `BV_FRAME_TICK` message:

- A **posted** message is delivered at normal priority and is never coalesced, so frames keep a steady cadence even under a saturated message pump.
- `uResolution = 1` raises the system timer resolution for the timer's lifetime, so the 15 ms interval is honoured instead of rounding up to the default tick.
- A shared `frame_pending` `AtomicBool` gates the callback so at most **one** frame is ever queued: a stalled pump coalesces to a single catch-up frame rather than a backlog that floods the queue and repaints in a burst.
- Lifecycle: the timer starts in `after_create` (its first tick fires ~one interval later, so the `WM_SHOWWINDOW` posted by `open` is handled first and the child window paints in the right order) and is torn down in `before_destroy`, with a `Drop` on `WindowState` as a safety net. `TIME_KILL_SYNCHRONOUS` guarantees no callback is in flight before the callback context is freed. If `timeSetEvent` ever fails the code falls back to the original `WM_TIMER`, so the editor can never end up with no frame source.

Enabling the API only adds the `Win32_Media` feature to the existing `windows-sys` dependency.

### Re-entrancy guard

Delivering frames reliably surfaced a latent crash: on Windows a wgpu/DXGI `Present` inside `on_frame` can pump the message queue, dispatching a queued `BV_FRAME_TICK` **re-entrantly** while the handler is still borrowed. `handle_on_frame` / `handle_event` did an unconditional `RefCell::borrow_mut`, so the nested call panicked, and since the window proc is `extern "system"` (no `catch_unwind`) the panic unwound across the FFI boundary and aborted the host (`STATUS_FATAL_APP_EXIT`, `0x40000015`). The lazy `WM_TIMER` almost never had a tick queued at that instant, so the bug stayed hidden until frames were posted reliably.

Both entry points now use `try_borrow_mut` and skip the re-entrant call (the next tick renders normally; a re-entrant event is reported `Ignored`) instead of panicking.

## Linux embed-parent resize

Upstream baseview on X11 only resizes its window from `Window::resize` (the plugin's own request) or a `ConfigureNotify` on that window. When a plugin editor is embedded, X11 does **not** auto-resize a child when its parent changes size, so the child only tracks the host if the host explicitly drives the plugin's resize API (CLAP `gui.set_size`, VST3 `onSize`), which then calls `Window::resize`.

Bitwig on Linux breaks that assumption: during an interactive resize it grows its **embed parent window directly** and never calls the plugin's resize API with the new size (it only echoes the current size). The plugin's child window stays at its original size, the render surface stays small, and the uncovered part of the enlarged embed shows as a black margin until the window is moved (which makes Bitwig re-sync the child). Because the gap is below the GUI layer, it hits every backend (egui, iced, slint, vizia) and both plugin formats.

The fix, entirely in `src/x11/`:

- On `open_parented`, select `STRUCTURE_NOTIFY` on the host-supplied embed parent (stored as `WindowInner::embed_parent_id`; `None` for top-level windows parented to the root, so nothing changes there).
- In the event loop, a `ConfigureNotify` for the embed parent mirrors the parent's new size onto the child via `configure_window`. The child's own `ConfigureNotify` then flows through the existing path, emitting `WindowEvent::Resized` so backends reconfigure their surfaces exactly as they do for any other resize.

This is X11-only and no-ops for non-embedded windows, so macOS / Windows and standalone top-level windows are unaffected.

## Release scripts

`scripts/` carries the publishing workflow for the fork:

- `scripts/bump.sh <version>` — bump the version in `Cargo.toml` + workspace examples, regenerate `Cargo.lock`, and commit.
- `scripts/release.sh` — drives the full release: verify → bump → publish, with confirmation prompts at each step.
- `scripts/publish.sh` — `cargo publish` to crates.io once a release commit is tagged.
- `scripts/verify.sh` — clippy + tests + docs pass before release.
- `scripts/sync-upstream.sh` — fetch RustAudio/baseview's `master` and either merge or rebase the truce-fork patches on top, used to pick up upstream changes before bumping. Keeps the patch set small by replaying onto the latest upstream rather than letting the fork drift.

## License

Licensed under either of <a href="LICENSE-APACHE">Apache License, Version 2.0</a> or <a href="LICENSE-MIT">MIT license</a> at your option.

Unless you explicitly state otherwise, any contribution intentionally submitted for inclusion in Baseview by you, as defined in the Apache-2.0 license, shall be dual licensed as above, without any additional terms or conditions.
