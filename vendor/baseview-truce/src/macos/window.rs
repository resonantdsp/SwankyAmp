use std::cell::{Cell, RefCell};
use std::collections::VecDeque;
use std::ffi::c_void;
use std::mem::ManuallyDrop;
use std::ptr;
use std::rc::{Rc, Weak};

use keyboard_types::KeyboardEvent;
use objc2::rc::{autoreleasepool, Retained};
use objc2::runtime::NSObjectProtocol;
use objc2::{msg_send, MainThreadMarker, MainThreadOnly};
use objc2_app_kit::{
    NSApplication, NSApplicationActivationPolicy, NSBackingStoreType, NSEvent, NSPasteboard,
    NSPasteboardTypeString, NSView, NSWindow, NSWindowStyleMask,
};
use objc2_core_foundation::{
    kCFAllocatorDefault, kCFRunLoopCommonModes, CFRetained, CFRunLoop, CFRunLoopSource,
    CFRunLoopSourceContext, CFRunLoopTimer, CFRunLoopTimerContext,
};
use objc2_foundation::{NSNotificationCenter, NSPoint, NSRect, NSSize, NSString};
use raw_window_handle::{
    AppKitDisplayHandle, AppKitWindowHandle, HasRawDisplayHandle, HasRawWindowHandle,
    RawDisplayHandle, RawWindowHandle,
};

use crate::{
    Event, EventStatus, MouseCursor, Size, WindowHandler, WindowInfo, WindowOpenOptions,
    WindowScalePolicy,
};

use super::keyboard::KeyboardState;
use super::view::{create_view, BASEVIEW_STATE_IVAR};

#[cfg(feature = "opengl")]
use crate::gl::{GlConfig, GlContext};
use crate::macos::RetainedCell;

pub struct WindowHandle {
    state: Rc<WindowState>,
}

impl WindowHandle {
    pub fn close(&mut self) {
        self.state.window_inner.close();
    }

    pub fn is_open(&self) -> bool {
        self.state.window_inner.open.get()
    }
}

unsafe impl HasRawWindowHandle for WindowHandle {
    fn raw_window_handle(&self) -> RawWindowHandle {
        self.state.window_inner.raw_window_handle()
    }
}

pub(super) struct WindowInner {
    open: Cell<bool>,

    /// Only set if we created the parent window, i.e. we are running in
    /// parentless mode
    ns_app: RetainedCell<NSApplication>,
    /// Only set if we created the parent window, i.e. we are running in
    /// parentless mode
    ns_window: RetainedCell<NSWindow>,

    /// Only set when running in parented mode.
    parent_ns_window: RetainedCell<NSWindow>,

    /// Our subclassed NSView
    ns_view: RetainedCell<NSView>,

    /// Run loop source another thread signals to run a frame now, ahead
    /// of its schedule. Installed by `init`, invalidated by `close`.
    frame_source: RefCell<Option<CFRetained<CFRunLoopSource>>>,

    #[cfg(feature = "opengl")]
    pub(super) gl_context: Option<GlContext>,
}

/// Wakes a window's frame loop from any thread. The display link's thread
/// signals it at every refresh so the frame runs right after the vsync,
/// and a renderer that comes by a swapchain image late signals it so the
/// paint is not held for the next refresh. The frame is skipped if the
/// window is already inside one.
pub struct FrameWaker {
    source: CFRetained<CFRunLoopSource>,
    run_loop: CFRetained<CFRunLoop>,
}

// SAFETY: CFRunLoop and its sources are documented as thread-safe, and
// the waker only signals the source and wakes the loop.
unsafe impl Send for FrameWaker {}
unsafe impl Sync for FrameWaker {}

impl FrameWaker {
    pub fn wake(&self) {
        self.source.signal();
        self.run_loop.wake_up();
    }
}

// CoreVideo's display link: the refresh clock of the display, delivered on
// its own thread. Declared here rather than through a binding crate so the
// frame driver has no dependency beyond the framework itself.
#[link(name = "CoreVideo", kind = "framework")]
unsafe extern "C" {
    fn CVDisplayLinkCreateWithActiveCGDisplays(display_link_out: *mut *mut c_void) -> i32;
    fn CVDisplayLinkSetOutputCallback(
        display_link: *mut c_void,
        callback: unsafe extern "C" fn(
            *mut c_void,
            *const c_void,
            *const c_void,
            u64,
            *mut u64,
            *mut c_void,
        ) -> i32,
        user_info: *mut c_void,
    ) -> i32;
    fn CVDisplayLinkStart(display_link: *mut c_void) -> i32;
    fn CVDisplayLinkStop(display_link: *mut c_void) -> i32;
    fn CVDisplayLinkRelease(display_link: *mut c_void);
}

unsafe extern "C" fn display_link_callback(
    _display_link: *mut c_void,
    _now: *const c_void,
    _output_time: *const c_void,
    _flags_in: u64,
    _flags_out: *mut u64,
    user_info: *mut c_void,
) -> i32 {
    // `user_info` is the `FrameWaker` the window leaked to the link; the
    // window stops the link before freeing it.
    let waker: &FrameWaker = unsafe { &*user_info.cast::<FrameWaker>() };
    waker.wake();
    0
}

unsafe extern "C-unwind" fn frame_source_callback(info: *mut c_void) {
    // `info` is the window's NSView, retained by `WindowInner` while the
    // source is valid; `close` invalidates the source before releasing
    // the view. The state ivar is null until `init` has stored it.
    let view: &NSView = unsafe { &*info.cast::<NSView>() };
    if let Some(window_state) = unsafe { WindowState::try_from_view(view) } {
        window_state.trigger_frame_if_idle();
    }
}

impl WindowInner {
    /// Schedule the frame source on this thread's run loop, in the common
    /// modes so a wake lands during native tracking loops too. Without a
    /// run loop the window has no waker.
    fn install_frame_source(&self) {
        let (Some(ns_view), Some(run_loop)) = (self.ns_view.get(), CFRunLoop::current()) else {
            return;
        };
        let mut context = CFRunLoopSourceContext {
            version: 0,
            info: Retained::as_ptr(&ns_view) as *mut c_void,
            retain: None,
            release: None,
            copyDescription: None,
            equal: None,
            hash: None,
            schedule: None,
            cancel: None,
            perform: Some(frame_source_callback),
        };
        let Some(source) = (unsafe { CFRunLoopSource::new(kCFAllocatorDefault, 0, &mut context) })
        else {
            return;
        };
        // SAFETY: `kCFRunLoopCommonModes` is a CoreFoundation constant.
        run_loop.add_source(Some(&source), unsafe { kCFRunLoopCommonModes });
        *self.frame_source.borrow_mut() = Some(source);
    }

    fn frame_waker(&self) -> Option<FrameWaker> {
        let source = self.frame_source.borrow().as_ref()?.clone();
        let run_loop = CFRunLoop::current()?;
        Some(FrameWaker { source, run_loop })
    }

    pub(super) fn close(&self) {
        if self.open.get() {
            self.open.set(false);
            let Some(ns_view) = self.ns_view.take() else {
                return;
            };

            // Local autorelease pool so any ObjC objects autoreleased
            // by the teardown below drain here instead of escaping
            // into an outer host pool — critical for AAX / Pro Tools
            // where `-[DFW_NSApplication sendEvent:]` wraps the
            // plugin-close callback in its own pool.
            autoreleasepool(|_| unsafe {
                // Take back ownership of the NSView's Rc<WindowState>
                let state_ptr: *const c_void = *ns_view
                    .class()
                    .instance_variable(BASEVIEW_STATE_IVAR)
                    .unwrap()
                    .load::<*const c_void>(&ns_view);

                let window_state = Rc::from_raw(state_ptr as *mut WindowState);

                // Cancel the frame timer. `invalidate` removes it from
                // whichever run loop it was scheduled on (not necessarily
                // the current one), so no stray tick can fire after the
                // state is dropped below. Then reclaim the `Weak` the
                // timer context borrowed - safe now that the timer is
                // dead and can no longer touch it.
                // Stop the display link before anything it can wake goes
                // away; `CVDisplayLinkStop` returns once no callback is
                // running, so the waker can follow it out.
                let display_link = window_state.display_link.replace(ptr::null_mut());
                if !display_link.is_null() {
                    CVDisplayLinkStop(display_link);
                    CVDisplayLinkRelease(display_link);
                }
                let waker = window_state.display_link_waker.replace(ptr::null());
                if !waker.is_null() {
                    drop(Box::from_raw(waker.cast_mut()));
                }
                if let Some(frame_timer) = window_state.frame_timer.take() {
                    frame_timer.invalidate();
                }
                let weak_ptr = window_state.timer_weak.replace(ptr::null());
                if !weak_ptr.is_null() {
                    drop(Weak::from_raw(weak_ptr));
                }
                // The frame source borrows the view; a signal after this
                // point must find nothing to run.
                if let Some(frame_source) = self.frame_source.borrow_mut().take() {
                    frame_source.invalidate();
                }

                // Deregister NSView from NotificationCenter.
                let notification_center = NSNotificationCenter::defaultCenter();
                notification_center.removeObserver(&ns_view);

                drop(window_state);

                // Close the window if in non-parented mode
                if let Some(ns_window) = self.ns_window.take() {
                    ns_window.close();
                }

                // Strip residual ties to the host window before detaching
                // and releasing. Any of these left behind leaves a
                // dangling back-reference somewhere in AppKit (responder
                // chain, tracking-area registry, layer contents queue)
                // that can blow up inside the host's later autorelease-
                // pool drain. Seen in Pro Tools as a crash inside
                // `-[DFW_NSContainer dealloc]` at a tiny address, where
                // the container messages its stale reference to our
                // view.
                if let Some(window) = ns_view.window() {
                    window.makeFirstResponder(None);
                }
                for area in ns_view.trackingAreas().to_vec().into_iter().rev() {
                    ns_view.removeTrackingArea(&area);
                }
                if let Some(layer) = ns_view.layer() {
                    layer.setContents(None);
                }

                // Ensure that the NSView is detached from the parent window
                ns_view.removeFromSuperview();
                drop(ns_view);

                // If in non-parented mode, we want to also quit the app altogether
                let app = self.ns_app.take();
                if let Some(app) = app {
                    app.stop(Some(&app));
                }
            });
        }
    }

    fn raw_window_handle(&self) -> RawWindowHandle {
        let mut handle = AppKitWindowHandle::empty();

        if self.open.get() {
            let ns_window = self.ns_window.get().or(self.parent_ns_window.get());

            handle.ns_window = match ns_window {
                None => ptr::null_mut(),
                Some(view) => (&*view as *const NSWindow) as *mut _,
            };

            handle.ns_view = match self.ns_view.get() {
                None => ptr::null_mut(),
                Some(view) => (&*view as *const NSView) as *mut _,
            };
        }

        handle.into()
    }
}

pub struct Window<'a> {
    inner: &'a WindowInner,
}

impl<'a> Window<'a> {
    pub fn open_parented<P, H, B>(parent: &P, options: WindowOpenOptions, build: B) -> WindowHandle
    where
        P: HasRawWindowHandle,
        H: WindowHandler + 'static,
        B: FnOnce(&mut crate::Window) -> H,
        B: Send + 'static,
    {
        autoreleasepool(|_| {
            let scaling = match options.scale {
                WindowScalePolicy::ScaleFactor(scale) => scale,
                WindowScalePolicy::SystemScaleFactor => 1.0,
            };

            let window_info = WindowInfo::from_logical_size(options.size, scaling);

            let handle = if let RawWindowHandle::AppKit(handle) = parent.raw_window_handle() {
                handle
            } else {
                panic!("Not a macOS window");
            };

            let ns_view = create_view(&options);
            let parent_window = unsafe { Retained::retain(handle.ns_window as *mut NSWindow) };
            let parent_view = unsafe { Retained::retain(handle.ns_view as *mut NSView) };

            let window_inner = WindowInner {
                open: Cell::new(true),
                ns_app: RetainedCell::empty(),
                ns_window: RetainedCell::empty(),
                parent_ns_window: RetainedCell::with(parent_window.clone()),
                ns_view: RetainedCell::new(ns_view.clone()),
                frame_source: RefCell::new(None),

                #[cfg(feature = "opengl")]
                gl_context: options
                    .gl_config
                    .map(|gl_config| Self::create_gl_context(None, &ns_view, gl_config)),
            };

            let window_handle = Self::init(window_inner, window_info, build);

            if let Some(parent_view) = parent_view {
                parent_view.addSubview(&ns_view);
            }

            window_handle
        })
    }

    pub fn open_blocking<H, B>(options: WindowOpenOptions, build: B)
    where
        H: WindowHandler + 'static,
        B: FnOnce(&mut crate::Window) -> H,
        B: Send + 'static,
    {
        autoreleasepool(|_| {
            let Some(mtm) = MainThreadMarker::new() else {
                panic!("macOS: open_blocking can only be called on the main thread!")
            };

            // Creates the global NSApplication instance, if it doesn't exist yet
            let app = NSApplication::sharedApplication(mtm);

            let _ = app.setActivationPolicy(NSApplicationActivationPolicy::Regular);

            let scaling = match options.scale {
                WindowScalePolicy::ScaleFactor(scale) => scale,
                WindowScalePolicy::SystemScaleFactor => 1.0,
            };

            let rect = NSRect::new(
                NSPoint::ZERO,
                NSSize { width: options.size.width, height: options.size.height },
            );

            let window_info = WindowInfo::from_logical_size(options.size, scaling);

            // SAFETY: This is safe because of the setReleasedWhenClosed(false) below
            let ns_window = unsafe {
                NSWindow::initWithContentRect_styleMask_backing_defer(
                    NSWindow::alloc(mtm),
                    rect,
                    NSWindowStyleMask::Titled
                        | NSWindowStyleMask::Closable
                        | NSWindowStyleMask::Miniaturizable,
                    NSBackingStoreType::Buffered,
                    false,
                )
            };

            // SAFETY: setReleasedWhenClosed is always safe to call with `false` (worst case is a memory leak)
            unsafe { ns_window.setReleasedWhenClosed(false) };

            ns_window.center();

            let title = NSString::from_str(&options.title);
            ns_window.setTitle(&title);

            ns_window.makeKeyAndOrderFront(None);

            let ns_view = create_view(&options);
            let window_inner = WindowInner {
                open: Cell::new(true),
                ns_app: RetainedCell::new(app.clone()),
                parent_ns_window: RetainedCell::empty(),
                ns_view: RetainedCell::new(ns_view.clone()),
                frame_source: RefCell::new(None),

                #[cfg(feature = "opengl")]
                gl_context: options.gl_config.map(|gl_config| {
                    Self::create_gl_context(Some(&ns_window), &ns_view, gl_config)
                }),

                ns_window: RetainedCell::new(ns_window.clone()),
            };

            let _ = Self::init(window_inner, window_info, build);

            ns_window.setContentView(Some(&ns_view));
            let () = unsafe { msg_send![&*ns_window, setDelegate: &*ns_view] };

            app.run();
        })
    }

    fn init<H, B>(window_inner: WindowInner, window_info: WindowInfo, build: B) -> WindowHandle
    where
        H: WindowHandler + 'static,
        B: FnOnce(&mut crate::Window) -> H,
        B: Send + 'static,
    {
        window_inner.install_frame_source();
        let mut window = crate::Window::new(Window { inner: &window_inner });
        let window_handler = Box::new(build(&mut window));

        let ns_view = window_inner.ns_view.get().unwrap();

        let window_state = Rc::new(WindowState {
            window_inner,
            window_handler: RefCell::new(window_handler),
            keyboard_state: KeyboardState::new(),
            frame_timer: RetainedCell::empty(),
            timer_weak: Cell::new(ptr::null()),
            display_link: Cell::new(ptr::null_mut()),
            display_link_waker: Cell::new(ptr::null()),
            window_info: Cell::new(window_info),
            deferred_events: RefCell::default(),
        });

        let window_state_ptr = Rc::into_raw(Rc::clone(&window_state));

        unsafe {
            // This creates a cyclic reference: WindowState > WindowInner > NSView > WindowState.
            // This cycle gets broken in WindowInner::close and everything is released properly.
            // However, this means the cycle holds and the whole leaks if close() is not called. (e.g. if simply dropped)
            // This should be refactored at some point to fix this issue.
            ns_view
                .class()
                .instance_variable(BASEVIEW_STATE_IVAR)
                .unwrap()
                .load_ptr::<*const c_void>(&ns_view)
                .write(window_state_ptr as *const c_void);

            WindowState::setup_frame_driver(&window_state);
        }

        WindowHandle { state: window_state }
    }

    pub fn close(&mut self) {
        self.inner.close();
    }

    pub fn has_focus(&mut self) -> bool {
        let view = self.inner.ns_view.get().unwrap();
        let Some(window) = view.window() else {
            return false;
        };

        if !window.isKeyWindow() {
            return false;
        }

        let Some(first_responder) = window.firstResponder() else {
            return false;
        };

        view.isEqual(Some(&*first_responder))
    }

    pub fn focus(&mut self) {
        let view = self.inner.ns_view.get().unwrap();
        if let Some(window) = view.window() {
            window.makeFirstResponder(Some(&view));
        }
    }

    pub fn resize(&mut self, size: Size) {
        if self.inner.open.get() {
            // NOTE: macOS gives you a personal rave if you pass in fractional pixels here. Even
            // though the size is in fractional pixels.
            let size = NSSize::new(size.width.round(), size.height.round());

            if let Some(view) = self.inner.ns_view.get() {
                view.setFrameSize(size);
                view.setNeedsDisplay(true);
            }

            // When using OpenGL the `NSOpenGLView` needs to be resized separately? Why? Because
            // macOS.
            #[cfg(feature = "opengl")]
            if let Some(gl_context) = &self.inner.gl_context {
                gl_context.resize(size);
            }

            // If this is a standalone window then we'll also need to resize the window itself
            if let Some(ns_window) = self.inner.ns_window.get() {
                ns_window.setContentSize(size);
            }
        }
    }

    /// See the X11 implementation. On macOS the Retina backing scale is driven
    /// by AppKit through the parent `NSView`/`NSWindow`, not by a host content
    /// scale reported after attach, so this is a no-op here.
    pub fn set_scale_factor(&mut self, _scale: f64) {}

    pub fn set_mouse_cursor(&mut self, mouse_cursor: MouseCursor) {
        unsafe { super::cursor::set_cursor(mouse_cursor) };
    }

    /// A handle another thread can use to run this window's next frame
    /// now. `None` when the window runs without a run loop.
    pub fn frame_waker(&self) -> Option<FrameWaker> {
        self.inner.frame_waker()
    }

    #[cfg(feature = "opengl")]
    pub fn gl_context(&self) -> Option<&GlContext> {
        self.inner.gl_context.as_ref()
    }

    #[cfg(feature = "opengl")]
    fn create_gl_context(
        ns_window: Option<&NSWindow>, ns_view: &NSView, config: GlConfig,
    ) -> GlContext {
        let mut handle = AppKitWindowHandle::empty();
        handle.ns_window = match ns_window {
            Some(ns_window) => ns_window as *const NSWindow as *mut c_void,
            None => ptr::null_mut(),
        };
        handle.ns_view = ns_view as *const NSView as *mut c_void;
        let handle = RawWindowHandle::AppKit(handle);

        unsafe { GlContext::create(&handle, config).expect("Could not create OpenGL context") }
    }
}

pub(super) struct WindowState {
    pub(super) window_inner: WindowInner,
    window_handler: RefCell<Box<dyn WindowHandler>>,
    keyboard_state: KeyboardState,
    frame_timer: RetainedCell<CFRunLoopTimer>,
    /// Raw `Weak<WindowState>` handed to the frame timer's context. Kept
    /// so teardown can reclaim and drop it after the timer is invalidated.
    timer_weak: Cell<*const WindowState>,
    /// The display link driving frames, and the waker it signals. Null when
    /// the frame timer drives them instead.
    display_link: Cell<*mut c_void>,
    display_link_waker: Cell<*const FrameWaker>,
    /// The last known window info for this window.
    pub window_info: Cell<WindowInfo>,

    /// Events that will be triggered at the end of `window_handler`'s borrow.
    deferred_events: RefCell<VecDeque<Event>>,
}

impl WindowState {
    /// Gets the `WindowState` held by a given `NSView`.
    ///
    /// This method returns a cloned `Rc<WindowState>` rather than just a `&WindowState`, since the
    /// original `Rc<WindowState>` owned by the `NSView` can be dropped at any time
    /// (including during an event handler).
    ///
    /// # Safety
    ///
    /// `view` MUST be our own NSView, as created by `create_view`
    pub(super) unsafe fn from_view(view: &NSView) -> Rc<WindowState> {
        let state_ptr = view
            .class()
            .instance_variable(BASEVIEW_STATE_IVAR)
            .unwrap()
            .load::<*const c_void>(view)
            .cast::<WindowState>();

        let state_rc = Rc::from_raw(state_ptr);
        let state = Rc::clone(&state_rc);
        let _ = Rc::into_raw(state_rc);

        state
    }

    /// Trigger the event immediately and return the event status.
    /// Will panic if `window_handler` is already borrowed (see `trigger_deferrable_event`).
    pub(super) fn trigger_event(&self, event: Event) -> EventStatus {
        let mut window = crate::Window::new(Window { inner: &self.window_inner });
        let mut window_handler = self.window_handler.borrow_mut();
        let status = window_handler.on_event(&mut window, event);
        self.send_deferred_events(window_handler.as_mut());
        status
    }

    /// Trigger the event immediately if `window_handler` can be borrowed mutably,
    /// otherwise add the event to a queue that will be cleared once `window_handler`'s mutable borrow ends.
    /// As this method might result in the event triggering asynchronously, it can't reliably return the event status.
    pub(super) fn trigger_deferrable_event(&self, event: Event) {
        if let Ok(mut window_handler) = self.window_handler.try_borrow_mut() {
            let mut window = crate::Window::new(Window { inner: &self.window_inner });
            window_handler.on_event(&mut window, event);
            self.send_deferred_events(window_handler.as_mut());
        } else {
            self.deferred_events.borrow_mut().push_back(event);
        }
    }

    pub(super) fn trigger_frame(&self) {
        let mut window = crate::Window::new(Window { inner: &self.window_inner });
        let mut window_handler = self.window_handler.borrow_mut();
        window_handler.on_frame(&mut window);
        self.send_deferred_events(window_handler.as_mut());
    }

    /// Run a frame unless the handler is already inside one; a wake that
    /// arrives mid-frame is served by the next scheduled frame instead.
    fn trigger_frame_if_idle(&self) {
        let Ok(mut window_handler) = self.window_handler.try_borrow_mut() else {
            return;
        };
        let mut window = crate::Window::new(Window { inner: &self.window_inner });
        window_handler.on_frame(&mut window);
        self.send_deferred_events(window_handler.as_mut());
    }

    /// Like [`Self::from_view`], but `None` before `init` has stored the
    /// state on the view.
    ///
    /// # Safety
    ///
    /// `view` MUST be our own NSView, as created by `create_view`
    pub(super) unsafe fn try_from_view(view: &NSView) -> Option<Rc<WindowState>> {
        let state_ptr = view
            .class()
            .instance_variable(BASEVIEW_STATE_IVAR)
            .unwrap()
            .load::<*const c_void>(view);
        if state_ptr.is_null() {
            return None;
        }
        Some(unsafe { Self::from_view(view) })
    }

    pub(super) fn keyboard_state(&self) -> &KeyboardState {
        &self.keyboard_state
    }

    pub(super) fn process_native_key_event(&self, event: &NSEvent) -> Option<KeyboardEvent> {
        self.keyboard_state.process_native_event(event)
    }

    /// Drive frames from the display's refresh clock, so a frame runs right
    /// after each vsync and its paint lands in the next refresh. A 15 ms
    /// timer runs independently of the display and, once the renderer waits
    /// for the swapchain, lands on every second refresh; it remains the
    /// fallback when no display link can be made.
    unsafe fn setup_frame_driver(window_state: &Rc<WindowState>) {
        if !unsafe { Self::setup_display_link(window_state) } {
            unsafe { Self::setup_timer(window_state) };
        }
    }

    unsafe fn setup_display_link(window_state: &Rc<WindowState>) -> bool {
        let Some(waker) = window_state.window_inner.frame_waker() else {
            return false;
        };
        let mut display_link: *mut c_void = ptr::null_mut();
        if unsafe { CVDisplayLinkCreateWithActiveCGDisplays(&mut display_link) } != 0
            || display_link.is_null()
        {
            return false;
        }
        let waker = Box::into_raw(Box::new(waker));
        let started = unsafe {
            CVDisplayLinkSetOutputCallback(display_link, display_link_callback, waker.cast())
        } == 0
            && unsafe { CVDisplayLinkStart(display_link) } == 0;
        if !started {
            unsafe {
                CVDisplayLinkRelease(display_link);
                drop(Box::from_raw(waker));
            }
            return false;
        }
        window_state.display_link.set(display_link);
        window_state.display_link_waker.set(waker);
        true
    }

    unsafe fn setup_timer(window_state: &Rc<WindowState>) {
        unsafe extern "C-unwind" fn timer_callback(_: *mut CFRunLoopTimer, weak_ptr: *mut c_void) {
            // `weak_ptr` is a `Weak<WindowState>` (from `Weak::into_raw`),
            // borrowed without taking ownership - it's freed only at
            // teardown. A host can release the editor view without a clean
            // `close()`, leaving this timer scheduled after the state is
            // gone; upgrading a `Weak` skips the frame instead of
            // dereferencing freed memory.
            let weak = ManuallyDrop::new(unsafe { Weak::from_raw(weak_ptr as *const WindowState) });
            if let Some(window_state) = weak.upgrade() {
                window_state.trigger_frame();
            }
        }

        let Some(current_loop) = CFRunLoop::current() else {
            return;
        };

        // Non-owning handle for the timer context. Stored on the state so
        // teardown can reclaim and drop it once the timer is invalidated.
        let weak_ptr = Weak::into_raw(Rc::downgrade(window_state));
        window_state.timer_weak.set(weak_ptr);

        let mut timer_context = CFRunLoopTimerContext {
            version: 0,
            info: weak_ptr as *mut c_void,
            retain: None,
            release: None,
            copyDescription: None,
        };

        let Some(timer) = CFRunLoopTimer::new(
            kCFAllocatorDefault,
            0.0,
            0.015,
            0,
            0,
            Some(timer_callback),
            &mut timer_context,
        ) else {
            // Reclaim the `Weak` we handed to the (never-created) timer.
            window_state.timer_weak.set(ptr::null());
            drop(unsafe { Weak::from_raw(weak_ptr) });
            return;
        };

        // Common modes, not the default mode: a native tracking loop
        // (window drag, resize, menu) runs the run loop in its own mode,
        // and a default-mode-only timer stops firing for its duration -
        // the editor freezes until the user lets go.
        current_loop.add_timer(Some(&timer), kCFRunLoopCommonModes);

        window_state.frame_timer.set(timer.into());
    }

    fn send_deferred_events(&self, window_handler: &mut dyn WindowHandler) {
        let mut window = crate::Window::new(Window { inner: &self.window_inner });
        loop {
            let next_event = self.deferred_events.borrow_mut().pop_front();
            if let Some(event) = next_event {
                window_handler.on_event(&mut window, event);
            } else {
                break;
            }
        }
    }
}

unsafe impl<'a> HasRawWindowHandle for Window<'a> {
    fn raw_window_handle(&self) -> RawWindowHandle {
        self.inner.raw_window_handle()
    }
}

unsafe impl<'a> HasRawDisplayHandle for Window<'a> {
    fn raw_display_handle(&self) -> RawDisplayHandle {
        RawDisplayHandle::AppKit(AppKitDisplayHandle::empty())
    }
}

pub fn copy_to_clipboard(string: &str) {
    let pb = NSPasteboard::generalPasteboard();
    let ns_str = NSString::from_str(string);

    pb.clearContents();
    pb.setString_forType(&ns_str, unsafe { NSPasteboardTypeString });
}
