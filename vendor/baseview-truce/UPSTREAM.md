# Vendored baseview-truce patches

Source: crates.io `baseview-truce` 0.1.1-truce.13, upstream commit
`a860a62b6471a549f113026b236242a90a3c9d8e` in
[baseview](https://github.com/truce-audio/baseview).
The upstream license texts are included unchanged. `README.md` is the fork's
own, with its Windows frame pacing section brought in line with the change
below.

Remove the Cargo patch and this directory when a pinned upstream release
carries every change below.

# macOS frames from the display clock

The published crate paints on a 15 ms timer that knows nothing of the
display. Once the renderer waits for the swapchain, each tick lands where the
compositor left it, and on a 60 Hz display that was every second refresh with
the window thread blocked in between. The source change drives frames from a
`CVDisplayLink` instead, so a frame runs right after each refresh and its paint
lands in the next one; the timer remains the fallback when no display link can
be created. The display link's thread reaches the window through a run loop
source, exposed as `Window::frame_waker` so a renderer that comes by a
swapchain image late can run the frame at once as well. A wake that arrives
while the window is already inside a frame is skipped.

The published crate also schedules its timer in the run loop's default mode
only. AppKit runs its own mode while a native tracking loop is active -
dragging or resizing the standalone window, holding a menu open - so the
editor froze mid-gesture. The frame source and the fallback timer are both
scheduled in the common modes, which include the tracking modes.

# macOS command-key chords inside a host

The published crate installs `keyDown:`, `keyUp:` and `flagsChanged:` on its
NSView and nothing else. A command-key chord never reaches `keyDown:` in a
plug-in window: AppKit offers every key equivalent to the key window's view
hierarchy and then to the host's menu, and a host whose Edit menu owns
Command-V consumes it before the view is asked. The source change adds
`performKeyEquivalent:` to the view. It claims Command-A, C, V and X - the
editing chords a plug-in's own text fields implement - but only while the
view, or a subview under it, is the window's first responder, and delivers
them as ordinary key events; every other chord, and every chord arriving while
the focus sits in the host's own fields, falls through to the menu untouched.
Windows needs no equivalent: the crate already hooks `WH_GETMESSAGE` and
intercepts keyboard messages addressed to its own windows before the host's
pump can translate an accelerator.

# macOS click position

The published view sends button events without a position, so a click with no
move before it - the first click into a host in the background, whose tracking
area reports no moves - lands wherever the pointer was last seen, or nowhere
once the editor treats a cursor that left as unavailable. Each button event is
now preceded by a cursor move to the event's own location, as winit does.

# Windows modifier state on mouse events

The published keyboard backend tests `GetKeyState` with `0x80`, the pressed
bit for a byte of keyboard state. `GetKeyState` returns a 16-bit value whose
pressed bit is `0x8000`, so Alt was absent from mouse events even while held.
The source change corrects the Alt, Control and Shift masks and both AltGr
checks. Toggle-state masks and the byte masks used to construct keyboard state
for layout translation are unchanged. Mouse events continue to take Control
and Shift from `wParam`; Alt and AltGr use the corrected key-state checks.

# Windows DPI awareness

The published window sets the whole process to per-monitor DPI awareness when
its window is created. In a plug-in that process is the host's: the call
either fails (Ableton Live 10 stayed DPI-unaware) or changes the host's DPI
mode mid-session. The call is removed. The standalone declares per-monitor
awareness in the manifest `cargo truce run` and `cargo truce package` embed
in its executable, and the editor reads its window's own DPI either way.

# Keys the editor declines reach the host

The published Windows window swallows every key addressed to it: the
`WH_GETMESSAGE` hook takes the message out of the host's loop and the window
procedure answers it whatever the handler reported, so Space and every other
host shortcut stopped working once the editor had the focus. A key the handler
reports `Ignored` is now posted on to the parent window, the host's, where the
host's loop translates and dispatches it as one of its own. A handler busy
mid-frame never saw the key, so that key is dropped rather than handed over.
Alt and F10 alone stay with the editor, as Alt is held for its gestures and a
forwarded release would open the host's menu bar; a window without a parent
keeps the published handling, so Alt+F4 still closes the standalone. On macOS
a declined key already went to `super` and up the responder chain; one the
keyboard state cannot translate now goes the same way instead of being
dropped.

# Windows frames from the display

The published window paints on a multimedia timer, `timeSetEvent` with a
1 ms resolution, which raises the timer resolution of the whole process -
in a plug-in, the host's - for as long as an editor is open, and ticks at
66 Hz whatever the display does. The source change drives frames from a
thread per window that waits for each desktop composition with `DwmFlush`
and posts the same frame tick, still at most one outstanding. A composition
that fails, or comes back sooner than 2 ms after the last tick, as it does
while nothing is being composed, falls back to a 16 ms interval. A post that
fails, for example on a full message queue, clears the pending flag, so the
next composition tries again rather than no frame ever being posted. The
`WM_TIMER` fallback remains for a thread that cannot be started.

Closing the window stops the thread: it holds a lock while it posts, so no
tick reaches the window once the close has cleared its flag. The close does
not wait for the thread, which exits when its current wait returns, normally
within one refresh. That is safe only because the products pin their library
before an editor opens, so the thread never returns into unloaded code; an
embedder that does not pin must not take this change as it stands.

# Windows close that a renderer can outlast

The published window closes by posting itself a message and destroys itself
with the handler still inside it, so a renderer whose swapchain lives on
another thread had its window destroyed under it, and a host that destroys
its own window straight after closing the editor destroyed this one before the
message arrived. A close on the window's own thread now runs at once: it drops
the handler while the window is still attached, then destroys the window; a
close re-entered from inside the handler is posted and runs once the handler
returns. A renderer can hold a `WindowLease` from `Window::lease`; a close that
finds one outstanding hands focus and capture back, hides the window and
detaches it from its parent instead, and the last lease to drop has the window
destroyed on its own thread.

# No drag-and-drop registration

The published window registers itself as a drop target, calling
`OleInitialize` on the host's GUI thread and `RegisterDragDrop` on Windows and
registering file-name drag types on macOS, though nothing built on it handles a
drop. The registration, its handlers and the `windows` crate it needed are
removed; the drag event types remain and are never sent.

# One line of native text

A renderer whose GPU setup failed leaves the published window blank.
`Window::show_note` puts one line of native text centred in it: a `STATIC`
child window on Windows, created once the event has been handled because a
child's creation calls back into this window, and a selectable `NSTextField`
label on macOS. It is a no-op on X11.
