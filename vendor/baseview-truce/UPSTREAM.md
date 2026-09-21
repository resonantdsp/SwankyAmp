# macOS frames during native tracking loops

Source: crates.io `baseview-truce` 0.1.1-truce.13, upstream commit
`a860a62b6471a549f113026b236242a90a3c9d8e` in
[baseview](https://github.com/truce-audio/baseview).
The upstream license texts are included unchanged.

The published crate schedules the macOS frame timer in the run loop's default
mode only. AppKit runs its own mode while a native tracking loop is active -
dragging or resizing the standalone window, holding a menu open - so the timer
stops firing for the duration and the editor freezes mid-gesture instead of
following it. The source change schedules the same 15 ms timer in the common
modes, which include the tracking modes. No other platform is touched.

Remove the Cargo patch and this directory when a pinned upstream release
schedules the timer the same way.

# macOS frames from the display clock

The published crate paints on a 15 ms timer that knows nothing of the
display. Once the renderer waits for the swapchain, each tick lands where the
compositor left it, and on a 60 Hz display that was every second refresh with
the window thread blocked in between. The source change drives frames from a
`CVDisplayLink` instead, so a frame runs right after each refresh and its paint
lands in the next one; the timer remains the fallback when no display link can
be created. The display link's thread reaches the window through a run loop
source scheduled in the common modes, exposed as `Window::frame_waker` so a
renderer that comes by a swapchain image late can run the frame at once as
well. No other platform is touched.

Remove the Cargo patch and this directory when a pinned upstream release drives
frames the same way.

# macOS command-key chords inside a host

The published crate installs `keyDown:`, `keyUp:` and `flagsChanged:` on its
NSView and nothing else. A command-key chord never reaches `keyDown:` in a
plug-in window: AppKit offers every key equivalent to the key window's view
hierarchy and then to the host's menu, and a host whose Edit menu owns
Command-V consumes it before the view is asked. The standalone has no such
menu, which is why paste worked there and not in Ableton Live. The source
change adds `performKeyEquivalent:` to the view. It claims Command-A, C, V and
X - the editing chords a plug-in's own text fields implement - but only while
the view, or a subview under it, is the window's first responder, and delivers
them as ordinary key events; every other chord, and every chord arriving while
the focus sits in the host's own fields, falls through to the menu untouched.
Windows needs no equivalent: the crate already hooks `WH_GETMESSAGE` and
intercepts keyboard messages addressed to its own windows before the host's
pump can translate an accelerator. No other platform is touched.

Remove the Cargo patch and this directory when a pinned upstream release
claims its key equivalents the same way.

# Windows modifier state on mouse events

The published keyboard backend tests `GetKeyState` with `0x80`, the pressed
bit for a byte of keyboard state. `GetKeyState` returns a 16-bit value whose
pressed bit is `0x8000`, so Alt was absent from mouse events even while held.
The source change corrects the Alt, Control and Shift masks and both AltGr
checks. Toggle-state masks and the byte masks used to construct keyboard state
for layout translation are unchanged. Mouse events continue to take Control
and Shift from `wParam`; Alt and AltGr use the corrected key-state checks.

Remove the Cargo patch and this directory when a pinned upstream release reads
the same modifier state. Windows real-host qualification remains necessary.
