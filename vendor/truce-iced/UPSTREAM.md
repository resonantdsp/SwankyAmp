# Native focus and view updates

Source: crates.io `truce-iced` 6.3.0, upstream commit
`ff6b573c7d845638656b03bbe4b4436559dd9725`, `crates/truce-iced` in
[truce](https://github.com/truce-audio/truce).
The upstream license texts are included unchanged.

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
paste: a product key field a player is meant to paste into cannot be pasted
into, and copy and cut from any text field are dropped as well. The source
change adds `truce_iced::clipboard`, a text-only `iced_core::Clipboard` over
[`arboard`](https://crates.io/crates/arboard) (MIT OR Apache-2.0), and hands it
to both `UserInterface::update` calls in the runtime. The screenshot path keeps
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
