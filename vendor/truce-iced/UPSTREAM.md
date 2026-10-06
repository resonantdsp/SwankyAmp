# Native focus and view updates

Source: crates.io `truce-iced` 6.3.0, upstream commit
`ff6b573c7d845638656b03bbe4b4436559dd9725`, `crates/truce-iced` in
[truce](https://github.com/truce-audio/truce).
The upstream `LICENSE` (Truce License 1.0), `LICENSE-MIT` and `LICENSE-APACHE`
texts are included unchanged.

The published editor drops native focus events before they reach iced widgets.
Consequently a knob cannot end its drag when another window takes focus.
The source change forwards baseview Focused/Unfocused as their iced equivalents.
No product control, layout, rendering or parameter definitions belong here.

Mouse moves, button presses and releases, and wheel events carry their own
modifier snapshot. The published bridge discards it, so a host that keeps
keyboard focus leaves Alt and Shift unknown to the widgets on their first
gesture. The bridge now queues an iced `ModifiersChanged` event before each
corresponding mouse event, using the same conversion as keyboard input. Native
host qualification is still needed to establish which events a host delivers;
the product interaction tests exercise the resulting iced event contract.

The runtime also draws before dispatching messages, then can idle when only
plugin view state changed. Every click consequently shows its result a frame
late, and switching tabs leaves the previous view visible until another input
arrives. A frame now dispatches the messages its own events produced and rebuilds
the view from the result before drawing, so a control responds in the frame that
received the input. Captured input still schedules a further frame: a pick list
can open or close its menu without publishing a plugin message, and a host may
apply a parameter edit on its own thread after the frame re-reads it. Native
opening, selection and dismissal must remain responsive while host parameters and
audio displays are idle.

Two further sources of latency are removed. The published runtime vetoes a whole
tick - input processing included - whenever the previous swapchain acquire waited
more than a few milliseconds, which under vsync is every paint; the veto is gone,
leaving vsync to pace the swapchain and the Windows pump thread to keep the host's
GUI thread clear. The surface also queued two display frames where the editor
renders in well under one, so it now asks for one.

`Message::Tick` reaches `IcedPlugin::update` once per rendered frame, after the
host parameter sync and before `view`, so a plugin can refresh model state from
data the runtime cannot see without a shared-mutability workaround around the
immutable `view`.

The product's widget event check protects drag interruption. Native focus switching
and editor closure still need real-host qualification; forwarding an event is not
proof that every host delivers it. Remove the Cargo patch and this directory when
a pinned upstream release provides the same event contract.

# Swapchain waits off the window thread on macOS

The published editor acquires its swapchain image inline on macOS. Metal hands
a drawable back about a refresh after the previous present, so the window
thread spent most of every frame inside `nextDrawable`, painted on every second
refresh and let input queue behind the wait. The source change runs the surface
pump the crate already uses on Windows on macOS as well, with the surface made
on the window thread and moved across, and asks for three drawables so the
frame after a refresh has one to paint into. A frame that finds no image skips
its build and draw, and the pump wakes the window through baseview's frame
waker when the image lands, so the paint still makes the coming refresh. A
refused acquire now waits for the next request instead of retrying without
pause. Linux keeps the inline surface.

A message can also move the model onto a view whose derived state the frame's
first `Message::Tick` never saw, so the runtime delivers the tick again after
dispatching before it rebuilds: switching tabs no longer paints a frame of the
placeholder panel while the new layout is measured.

# A clipboard for the widgets

The published runtime hands iced's widgets `clipboard::Null`, so no editor can
copy or paste: text copied, cut or pasted in a field is dropped. The source
change adds `truce_iced::clipboard`, a text-only `iced_core::Clipboard` over
[`arboard`](https://crates.io/crates/arboard) (MIT OR Apache-2.0), and hands it
to both `UserInterface::update` calls in the runtime. The information panel's
Copy diagnostics writes through the same module. The screenshot path keeps
`Null`: it renders a frame and dispatches no input, so no widget there can ask.

The connection is thread-local and kept open, because X11 serves a paste from
the process that owns the selection and a connection opened per call would take
the copied text with it. `Kind::Primary` is X11's middle-click selection, which
no plugin window owns, so it is served by nothing rather than by the standard
clipboard. iOS has no `arboard` backend and pastes through the platform's own
text input, so the module is empty there.

`arboard` is a dependency only of the desktop targets, with default features
off because the defaults add image support and with it the `image` crate. Of
what it needs - `objc2`, `objc2-app-kit` and `objc2-foundation` on macOS,
`x11rb`, `parking_lot` and `percent-encoding` on Linux, `clipboard-win`,
`error-code` and `windows-sys` 0.52 on Windows - only `clipboard-win` and
`error-code` are new to the tree; the rest, `windows-sys` 0.52 included, were
already locked.

Remove the Cargo patch and this directory when a pinned upstream release gives
its widgets a real clipboard.

# A frame for the keystroke that asked for it

An input event is pushed onto the runtime's queue and nothing asks for a
frame; the queue is drained by whichever frame the display clock next
schedules. In the standalone that costs at most one refresh and reads as
instant. In a host the display link's tick reaches the window through a run
loop source on the host's own GUI thread, behind whatever that thread is
doing, so the same design shows up as lag while typing. The source change
wakes the window's frame source when a key event is queued on macOS, so the
frame runs on the next pass of the run loop rather than at the next refresh.
Display pacing is otherwise unchanged: nothing else requests a frame, and a
frame that finds no drawable still defers to the pump.

`TRUCE_ICED_INPUT_TRACE`, set to a file path, appends the interval between a
key event arriving and the frame that answered it being handed to the
compositor, for measuring input response inside a host where no profiler
reaches. A file rather than standard error or `log`: a plug-in's standard
error belongs to the host and nothing in the stack installs a log sink. The
trace is compiled out of a release build and costs one atomic load when the
variable is unset.

Remove the Cargo patch and this directory when a pinned upstream release
answers input the same way.

# Interface zoom

The published editor either keeps a fixed size or reflows its widget tree
into whatever size the host gives it. A player who needs a larger or smaller
window gets neither: a fixed interface cannot grow, and a reflowed one changes
its layout. `IcedEditor::zoom` makes the size given to `new` a design size the
widget tree always lays out at, and the window that size times a zoom. The
viewport's scale factor is the display's scale times the zoom, so iced
rasterises text, vector drawing and shader primitives at the magnified size
rather than stretching a finished frame, and every widget scales without
knowing about it. Cursor positions and pixel wheel deltas are divided back to
design points.

`IcedPlugin::zoom` is how the plugin model chooses. When it changes, the
window handler resizes its own window, reports the new size through
`Editor::size`, and then calls `PluginContext::request_resize`, in that order,
because a host answering the request compares the size it is given with the
one the editor reports. The editor stays fixed-size to the host
(`can_resize` false), so no host offers a drag handle or feeds a size back
through `set_size`; CLAP and VST3 both let a fixed-size view request a resize.
This is the same change as Swanky Amp Pro's copy of this crate.

Remove the Cargo patch and this directory when a pinned upstream release
offers an interface zoom.

# An editor that says what happened to it

The published editor reports GPU trouble only through `log`, says nothing of
how long opening or closing took, and swallows the message of a panic during
GPU setup, so an editor that stays blank or opens slowly in one host leaves
no trace of why. The crate still installs no sink; a plug-in does, and Swanky Amp
writes its own log file.

- **Lifecycle records:** each open and close stage with its duration (open,
  window, instance, surface, adapter, device, shaders, swapchain, first frame;
  close, GPU released, closed), a device loss and its rebuild, at `Info` under
  `truce_iced::diagnostics::LIFECYCLE`. A close that waits out its bound is a
  warning. Nothing is recorded per frame.
- **The GPU:** `truce_iced::diagnostics::gpu` names the adapter the editor
  last chose, with its backend and driver, for a support report.
- **A failed editor is not blank:** `IcedEditor::failure_note` gives one line
  the window shows in native text, through baseview's `Window::show_note`,
  once GPU setup has failed for good.

Remove these when an upstream release offers the same record.

# A GPU thread that is bounded, final and compiles iced's shaders

The published pump releases a stale frame while still holding its slot lock,
so the window thread can wait on a driver present for the lock; the frame is
now taken out first. A failed GPU setup read as one still pending: the editor
waited forever and queued every input event. Setup now reports pending, ready
or failed; a failure is final, releases the pump, stops input queueing and
device-loss recovery, and its cause is logged once where it happened.

The pump reported its exit before its surface and device dropped, and closing
the editor then joined it without bound. It now drops frames, surface and
device before reporting, and the close waits one second in total, join
included. A pump still inside a driver call past that, wedged or still
compiling shaders on a cold cache, is detached holding its surface, and a
setup that finishes after the close never configures it. On Windows the pump
thread holds a lease on the window from baseview, so an editor closed before
the host destroys its parent window is hidden and detached from it instead,
and destroyed on its own thread once the pump has let go; a parent destroyed
first still takes the window with it. On macOS the surface keeps its own
retained `CAMetalLayer`. A plug-in must pin its library before opening the
editor, as Swanky Amp does, so a detached pump never returns into unloaded code.

iced's engine is built on the pump thread during setup, so its shaders compile
there rather than on the window thread. A plugin's own pipelines and textures
are still created on the window thread by the first frame that draws them.
Every adapter request asks for the low-power GPU, so a dual-GPU laptop does
not wake its discrete card for the editor. The surface format is the sRGB one
the surface offers, as iced's own compositor chooses: iced writes linear
colour, and Metal lists `Bgra8Unorm` first, which showed the macOS editor far
darker than Windows and the offscreen captures.

Remove these with the rest of this directory when a pinned upstream release
covers them.

# Less GPU work at open

The editor's devices ask for `MemoryHints::MemoryUsage`: the default
`Performance` has DX12 allocate in 256 MB device and 64 MB host blocks, so a
device's first allocations commit that much for an interface that uses a few.
Release builds create the instance without wgpu's default
`VALIDATION_INDIRECT_CALL`, which compiles a validation compute pipeline on
every device; nothing in iced or the product issues an indirect draw or
dispatch. Debug builds keep wgpu's build defaults.

# The host keeps its keys

The published editor reports every key event `Captured`, so a host never sees
a key while the editor has the focus and Space stops starting the transport
once a knob is touched. A key press now runs through the widget tree at once,
behind any input still queued, and the editor keeps it only when a widget
captured it or a focused text field holds the keyboard (`keeps_key`), which
keeps every key typed into the field from the host. Every other key is
reported `Ignored` for the platform layer to hand to the host. A release, and
an auto-repeat, goes where its press went. The messages that pass produces
wait for the next frame, which dispatches them before building its interface,
so no plugin message is dispatched inside the platform's key delivery. A press
arriving while such messages still wait is queued for that frame and kept only
if a text field holds the keyboard, so a text field never starts from a value
that lacks an earlier key.

`IcedPlugin::window_opened` hands the model the editor's native window, so a
native dialog can take it as owner and stay in front of the host.

Remove it when a pinned upstream release decides key by key.

# Frames that can be shown

Windows now looks for a swapchain image before building a frame, as macOS
already did, so a frame with nothing to paint into is not built and drawn for
nothing; its input waits for the next tick. A frame is also skipped while the
host's top-level window is minimised: a child window reports itself visible
and not iconic when only its host is minimised, so the published check alone
kept the editor painting there.

A panicking frame, or a panicking pump, used to arm device-loss recovery every
time, so a failure that survives a rebuild rebuilt the GPU pipeline without
end. Two rebuilds are now allowed without a frame reaching the screen; a third
ends in the same final failure as a failed GPU setup. A presented frame resets
the count, so device losses spread over a session never add up.

The runtime reported the last cursor position after the pointer left the
window, so hover highlights stayed lit. The cursor is now unavailable from
the moment the pointer leaves until it moves over the window again, and the
first position after it was away is preceded by an iced `CursorEntered`, so a
plugin can follow the pointer's arrival without reacting to every move. iOS
keeps its touch as the cursor after the touch ends, so a tap whose press and
release share a frame still lands; there `CursorEntered` comes only with the
first touch.

Remove these with the rest of this directory when a pinned upstream release
covers them.
