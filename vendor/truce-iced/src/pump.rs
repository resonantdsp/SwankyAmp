//! Surface pump for the iced editor: owns the wgpu surface and every
//! swapchain call, on a dedicated thread on Windows and macOS and
//! inline elsewhere.
//!
//! Per-wgpu-version copy of `truce_gpu::pump` - iced pins its own wgpu
//! major through `iced_wgpu`, so the surface/device types are distinct
//! from the rest of truce and the pump can't be shared (same situation
//! as `crate::platform::create_wgpu_surface`). Keep the two in sync.
//!
//! Rationale (see `truce_gpu::pump` for the full story): on Windows
//! the editor frame loop runs on the host's GUI thread, and any wgpu
//! call that enters the graphics driver - device creation, swapchain
//! configure, acquire, present - can park that thread in the kernel
//! forever on a stalled driver, freezing the DAW. The threaded pump
//! moves all of those to its own thread and pre-acquires frames; the
//! GUI thread only encodes + submits into an already-acquired texture.
//!
//! On macOS the motive is pacing. Metal's `nextDrawable` blocks until
//! the compositor hands a drawable back, which under vsync is about a
//! refresh after the previous present; acquired inline, that wait held
//! the GUI thread for most of every frame and input queued behind it.
//! The pump thread absorbs the wait, and when the drawable lands after
//! the GUI's frame has already looked for it, the pump wakes the GUI so
//! the paint still makes the coming refresh.

#[cfg(any(target_os = "windows", target_os = "macos"))]
use std::sync::Condvar;
use std::sync::atomic::AtomicBool;
#[cfg(any(target_os = "windows", target_os = "macos"))]
use std::sync::atomic::Ordering;
use std::sync::{Arc, Mutex, PoisonError};
use std::time::Instant;

use iced_wgpu::wgpu;

use crate::diagnostics::stage;

/// What the init closure returns: the GUI-side product (device
/// handles, ...) plus the device + configuration the pump needs for
/// `surface.configure`.
pub(crate) type PumpInit<T> = (T, wgpu::Device, wgpu::SurfaceConfiguration);

/// GPU init, run once the instance / adapter / surface exist (on the
/// pump thread where there is one, inline elsewhere). Fails with the
/// cause, which leaves the editor blank for good and the host running.
/// Must NOT configure the surface - the pump does that with the
/// returned configuration.
pub(crate) type PumpInitFn<T> = Box<
    dyn FnOnce(
            &wgpu::Instance,
            &wgpu::Adapter,
            &wgpu::Surface<'static>,
        ) -> Result<PumpInit<T>, String>
        + Send,
>;

/// Where the pump's GPU init stands, as the GUI thread sees it.
pub(crate) enum Init<T> {
    Pending,
    Ready(T),
    /// Final: the pump has given up and nothing will be drawn. The
    /// cause is already in the log. (Inline init fails in `spawn`.)
    #[cfg_attr(not(any(target_os = "windows", target_os = "macos")), allow(dead_code))]
    Failed,
}

/// Latest-wins mailbox between the GUI thread and the pump thread.
// The bools are independent protocol flags (want / taken / waiting /
// shutdown / exited), not a state machine in disguise; an enum would
// obscure which combinations are legal.
#[allow(clippy::struct_excessive_bools)]
#[cfg(any(target_os = "windows", target_os = "macos"))]
#[derive(Default)]
struct Slot {
    resize: Option<(u32, u32)>,
    held: Option<wgpu::SurfaceTexture>,
    want_frame: bool,
    present: Option<wgpu::SurfaceTexture>,
    /// A frame is out with the GUI thread (taken, not yet presented
    /// or discarded). wgpu allows only ONE outstanding acquired
    /// texture per surface, so the pump must not acquire while set.
    taken: bool,
    /// The GUI thread looked for a frame and found none; wake it when
    /// one lands rather than leave the paint to its next scheduled frame.
    waiting: bool,
    shutdown: bool,
    exited: bool,
}

#[cfg(any(target_os = "windows", target_os = "macos"))]
struct Shared {
    slot: Mutex<Slot>,
    cv: Condvar,
}

#[cfg(any(target_os = "windows", target_os = "macos"))]
fn lock(slot: &Mutex<Slot>) -> std::sync::MutexGuard<'_, Slot> {
    slot.lock().unwrap_or_else(PoisonError::into_inner)
}

/// Synchronous surface owner for the platforms where swapchain calls
/// stay on the calling thread.
#[cfg(not(any(target_os = "windows", target_os = "macos")))]
struct InlineState {
    surface: wgpu::Surface<'static>,
    device: wgpu::Device,
    config: wgpu::SurfaceConfiguration,
}

#[cfg(not(any(target_os = "windows", target_os = "macos")))]
fn lock_inline(state: &Mutex<InlineState>) -> std::sync::MutexGuard<'_, InlineState> {
    state.lock().unwrap_or_else(PoisonError::into_inner)
}

/// Cheap cloneable handle for per-frame pump operations.
#[derive(Clone)]
pub(crate) struct PumpClient {
    #[cfg(any(target_os = "windows", target_os = "macos"))]
    shared: Arc<Shared>,
    #[cfg(not(any(target_os = "windows", target_os = "macos")))]
    state: Arc<Mutex<InlineState>>,
}

impl PumpClient {
    /// Reconfigure the surface (physical pixels). Queued latest-wins
    /// to the pump thread where there is one; inline elsewhere.
    pub(crate) fn resize(&self, phys_w: u32, phys_h: u32) {
        #[cfg(any(target_os = "windows", target_os = "macos"))]
        {
            let mut slot = lock(&self.shared.slot);
            slot.resize = Some((phys_w, phys_h));
            drop(slot);
            self.shared.cv.notify_all();
        }
        #[cfg(not(any(target_os = "windows", target_os = "macos")))]
        {
            let mut state = lock_inline(&self.state);
            state.config.width = phys_w.max(1);
            state.config.height = phys_h.max(1);
            let InlineState {
                surface,
                device,
                config,
                ..
            } = &mut *state;
            surface.configure(device, config);
        }
    }

    /// Whether a frame is ready to paint into, asking the pump for one
    /// when it is not: the pump then wakes the GUI thread as soon as it
    /// has it (macOS) or for the next tick to find (Windows). Only
    /// meaningful where the pump has a thread.
    #[cfg(any(target_os = "windows", target_os = "macos"))]
    pub(crate) fn request_frame(&self) -> bool {
        let mut slot = lock(&self.shared.slot);
        slot.want_frame = true;
        let ready = slot.held.is_some();
        slot.waiting = !ready;
        drop(slot);
        if !ready {
            self.shared.cv.notify_all();
        }
        ready
    }

    /// Get a frame to paint into; `None` means skip this paint and
    /// retry on a later tick. Callers should verify the texture's size
    /// still matches their target and discard it on a mismatch.
    pub(crate) fn try_take_frame(&self) -> Option<wgpu::SurfaceTexture> {
        #[cfg(any(target_os = "windows", target_os = "macos"))]
        {
            let mut slot = lock(&self.shared.slot);
            slot.want_frame = true;
            let frame = slot.held.take();
            if frame.is_some() {
                slot.taken = true;
            }
            drop(slot);
            self.shared.cv.notify_all();
            frame
        }
        #[cfg(not(any(target_os = "windows", target_os = "macos")))]
        {
            let mut state = lock_inline(&self.state);
            let mut acquired = None;
            // `Outdated` / `Lost` persist until a reconfigure (even
            // same-size clears the flag); `Timeout` is transient.
            for _ in 0..2 {
                match state.surface.get_current_texture() {
                    Ok(frame) => {
                        acquired = Some(frame);
                        break;
                    }
                    Err(wgpu::SurfaceError::Outdated | wgpu::SurfaceError::Lost) => {
                        let InlineState {
                            surface,
                            device,
                            config,
                            ..
                        } = &mut *state;
                        surface.configure(device, config);
                    }
                    Err(e) => {
                        log::warn!("iced surface acquire error: {e}");
                        break;
                    }
                }
            }
            acquired
        }
    }

    /// Present a painted frame (handed to the pump thread where there
    /// is one, presented inline elsewhere).
    // `self` is unused inline-only; the signature is the cross-
    // platform pump API.
    #[allow(clippy::unused_self)]
    pub(crate) fn present(&self, frame: wgpu::SurfaceTexture) {
        #[cfg(any(target_os = "windows", target_os = "macos"))]
        {
            let mut slot = lock(&self.shared.slot);
            slot.present = Some(frame);
            slot.taken = false;
            drop(slot);
            self.shared.cv.notify_all();
        }
        #[cfg(not(any(target_os = "windows", target_os = "macos")))]
        {
            frame.present();
        }
    }

    /// Release a taken frame that won't be painted (stale size after
    /// a raced resize), so the pump may acquire again - wgpu allows
    /// only one outstanding acquired texture per surface. On Windows
    /// the frame is presented unrendered rather than dropped: DX12
    /// replenishes the frame-latency waitable only on present, and a
    /// dropped acquire burns a slot until every acquire blocks wgpu's
    /// full 1 s timeout. The recycled old-frame content matches what
    /// the compositor is already showing mid-churn. Metal recycles a
    /// dropped drawable, so macOS drops it and only clears the flag.
    // `self` is unused inline-only; the signature is the cross-
    // platform pump API.
    #[allow(clippy::unused_self)]
    pub(crate) fn discard(&self, frame: wgpu::SurfaceTexture) {
        #[cfg(target_os = "windows")]
        self.present(frame);
        #[cfg(target_os = "macos")]
        {
            drop(frame);
            let mut slot = lock(&self.shared.slot);
            slot.taken = false;
            drop(slot);
            self.shared.cv.notify_all();
        }
        #[cfg(not(any(target_os = "windows", target_os = "macos")))]
        drop(frame);
    }
}

/// Owning handle for the pump. Where the pump has a thread, dropping
/// the handle shuts it down (bounded join, then detach).
pub(crate) struct SurfacePump<T: Send + 'static> {
    client: PumpClient,
    init: InitDelivery<T>,
    #[cfg(any(target_os = "windows", target_os = "macos"))]
    join: Option<std::thread::JoinHandle<()>>,
}

enum InitDelivery<T> {
    #[cfg_attr(any(target_os = "windows", target_os = "macos"), allow(dead_code))]
    Now(Option<T>),
    /// One message: the product, or nothing when init failed (the
    /// sender is dropped unsent, which also covers a thread that ends
    /// any other way).
    #[cfg(any(target_os = "windows", target_os = "macos"))]
    Chan(std::sync::mpsc::Receiver<T>),
}

/// The handle that runs a GUI frame ahead of schedule. Only macOS has
/// one; elsewhere the type has no values, so the option is always `None`.
#[cfg(target_os = "macos")]
type FrameWaker = baseview::FrameWaker;
#[cfg(target_os = "windows")]
type FrameWaker = std::convert::Infallible;

#[cfg(target_os = "macos")]
fn wake(waker: &Option<FrameWaker>) {
    if let Some(waker) = waker {
        waker.wake();
    }
}
#[cfg(target_os = "windows")]
fn wake(_: &Option<FrameWaker>) {}

/// How the pump thread comes by its surface: built on the thread from
/// a `Send`-able HWND on Windows; built on the GUI thread on macOS,
/// where attaching a `CAMetalLayer` to the `NSView` belongs to the
/// main thread, then moved across along with the window's frame waker.
#[cfg(any(target_os = "windows", target_os = "macos"))]
enum SurfaceSource {
    #[cfg(target_os = "windows")]
    Hwnd(isize),
    #[cfg(target_os = "macos")]
    Ready(wgpu::Instance, wgpu::Surface<'static>, Option<FrameWaker>),
}

/// What the pump thread starts from: its instance and surface, and the
/// waker that runs a GUI frame as soon as a frame it waited for lands.
#[cfg(any(target_os = "windows", target_os = "macos"))]
struct Opened {
    instance: wgpu::Instance,
    surface: wgpu::Surface<'static>,
    #[cfg_attr(target_os = "windows", allow(dead_code))]
    waker: Option<FrameWaker>,
}

impl<T: Send + 'static> SurfacePump<T> {
    /// Build the pump for a baseview window. On Windows and macOS this
    /// spawns the pump thread and returns immediately (poll
    /// [`Self::take_init`]); elsewhere init runs synchronously and
    /// `take_init` succeeds on the first call. Fails with the cause.
    ///
    /// # Safety
    /// The window must remain valid while the pump holds a surface on it.
    /// On Windows the pump thread's lease keeps it alive through a close;
    /// on macOS the surface retains its layer.
    pub(crate) unsafe fn spawn(
        window: &baseview::Window,
        device_lost: &Arc<AtomicBool>,
        init: PumpInitFn<T>,
    ) -> Result<Self, String> {
        #[cfg(target_os = "windows")]
        {
            use raw_window_handle::HasRawWindowHandle;
            let raw_window_handle::RawWindowHandle::Win32(handle) = window.raw_window_handle()
            else {
                return Err("the window is not a Win32 window".into());
            };
            let hwnd = handle.hwnd as isize;
            if hwnd == 0 {
                return Err("the window has no handle".into());
            }
            Self::spawn_threaded(
                SurfaceSource::Hwnd(hwnd),
                device_lost.clone(),
                init,
                window.lease(),
            )
        }
        #[cfg(target_os = "macos")]
        {
            let started = Instant::now();
            let instance = crate::runtime::editor_instance();
            let started = stage("instance", started);
            let surface = unsafe { crate::platform::create_wgpu_surface(&instance, window) }
                .ok_or("no surface for the window")?;
            stage("surface", started);
            Self::spawn_threaded(
                SurfaceSource::Ready(instance, surface, window.frame_waker()),
                device_lost.clone(),
                init,
                (),
            )
        }
        #[cfg(not(any(target_os = "windows", target_os = "macos")))]
        {
            let _ = device_lost;
            let started = Instant::now();
            let instance = crate::runtime::editor_instance();
            let started = stage("instance", started);
            let surface = unsafe { crate::platform::create_wgpu_surface(&instance, window) }
                .ok_or("no surface for the window")?;
            let started = stage("surface", started);
            let adapter =
                pollster::block_on(instance.request_adapter(&wgpu::RequestAdapterOptions {
                    power_preference: wgpu::PowerPreference::LowPower,
                    compatible_surface: Some(&surface),
                    force_fallback_adapter: false,
                }))
                .map_err(|e| format!("no adapter: {e}"))?;
            crate::diagnostics::note_adapter(&adapter.get_info(), started);
            let (product, device, config) = init(&instance, &adapter, &surface)?;
            let started = Instant::now();
            surface.configure(&device, &config);
            stage("swapchain", started);
            Ok(Self {
                client: PumpClient {
                    state: Arc::new(Mutex::new(InlineState {
                        surface,
                        device,
                        config,
                    })),
                },
                init: InitDelivery::Now(Some(product)),
            })
        }
    }

    /// `window_lease` keeps the native window alive while the thread
    /// may still hold a surface on it, and drops once the thread is done.
    #[cfg(any(target_os = "windows", target_os = "macos"))]
    fn spawn_threaded(
        source: SurfaceSource,
        device_lost: Arc<AtomicBool>,
        init: PumpInitFn<T>,
        window_lease: impl Send + 'static,
    ) -> Result<Self, String> {
        let shared = Arc::new(Shared {
            slot: Mutex::new(Slot::default()),
            cv: Condvar::new(),
        });
        let (init_tx, init_rx) = std::sync::mpsc::channel();
        let thread_shared = shared.clone();
        let spawned = std::thread::Builder::new()
            .name("truce-iced-pump".into())
            .spawn(move || {
                run(&thread_shared, source, &device_lost, init, init_tx);
                // The lease goes before `exited`, so a close that saw the
                // pump exit finds the window free to destroy.
                drop(window_lease);
                mark_exited(&thread_shared);
            });
        let join = spawned.map_err(|e| format!("no GPU thread: {e}"))?;
        Ok(Self {
            client: PumpClient { shared },
            init: InitDelivery::Chan(init_rx),
            join: Some(join),
        })
    }

    /// Poll for the init closure's product (non-blocking). `Ready`
    /// comes exactly once; poll no further after it.
    pub(crate) fn take_init(&mut self) -> Init<T> {
        match &mut self.init {
            InitDelivery::Now(product) => product.take().map_or(Init::Pending, Init::Ready),
            #[cfg(any(target_os = "windows", target_os = "macos"))]
            InitDelivery::Chan(rx) => match rx.try_recv() {
                Ok(product) => Init::Ready(product),
                Err(std::sync::mpsc::TryRecvError::Empty) => Init::Pending,
                Err(std::sync::mpsc::TryRecvError::Disconnected) => Init::Failed,
            },
        }
    }

    pub(crate) fn client(&self) -> PumpClient {
        self.client.clone()
    }
}

#[cfg(any(target_os = "windows", target_os = "macos"))]
impl<T: Send + 'static> Drop for SurfacePump<T> {
    /// Closing an editor never waits on the pump for longer than one
    /// bound, join included. A pump still inside a driver call past it
    /// (a wedge, or a setup still compiling shaders on a cold cache) is
    /// detached holding its surface; when the call returns, the pump sees
    /// the shutdown, drops the surface and ends. On Windows the pump thread
    /// holds a lease on the window, so an editor closed before the host
    /// destroys its parent window hides and detaches the window and
    /// destroys it only once the lease drops; a parent destroyed first
    /// still takes the window with it. On macOS the surface keeps its own
    /// retained `CAMetalLayer`. The plug-in must pin its library before
    /// opening the editor (Pro does, in `src/pin.rs`), so a detached pump
    /// never returns into unloaded code.
    fn drop(&mut self) {
        let started = Instant::now();
        let mut slot = lock(&self.client.shared.slot);
        slot.shutdown = true;
        self.client.shared.cv.notify_all();
        let (slot, _) = self
            .client
            .shared
            .cv
            .wait_timeout_while(slot, SHUTDOWN_WAIT, |s| !s.exited)
            .unwrap_or_else(PoisonError::into_inner);
        let exited = slot.exited;
        drop(slot);
        let Some(join) = self.join.take() else {
            return;
        };
        // Past `exited` the thread holds nothing and only returns.
        if exited {
            let _ = join.join();
            stage("GPU released", started);
        } else {
            log::warn!(
                "the GPU thread was still in the driver after {} ms; detached",
                SHUTDOWN_WAIT.as_millis()
            );
        }
    }
}

#[cfg(any(target_os = "windows", target_os = "macos"))]
const SHUTDOWN_WAIT: std::time::Duration = std::time::Duration::from_secs(1);

/// Create a wgpu surface for a raw Win32 HWND (`Send`-able input, so
/// the pump thread builds its own surface).
///
/// # Safety
/// `hwnd` must be a valid window handle that outlives the surface.
#[cfg(target_os = "windows")]
unsafe fn surface_from_hwnd(
    instance: &wgpu::Instance,
    hwnd: isize,
) -> Result<wgpu::Surface<'static>, String> {
    let hwnd = std::num::NonZeroIsize::new(hwnd).ok_or("the window has no handle")?;
    let mut win32 = wgpu::rwh::Win32WindowHandle::new(hwnd);
    win32.hinstance = crate::platform::current_module_hinstance();
    let target = wgpu::SurfaceTargetUnsafe::RawHandle {
        raw_display_handle: wgpu::rwh::RawDisplayHandle::Windows(
            wgpu::rwh::WindowsDisplayHandle::new(),
        ),
        raw_window_handle: wgpu::rwh::RawWindowHandle::Win32(win32),
    };
    unsafe { instance.create_surface_unsafe(target) }
        .map_err(|e| format!("surface creation failed: {e}"))
}

/// Resolve the pump thread's instance + surface from its source.
#[cfg(any(target_os = "windows", target_os = "macos"))]
fn open_surface(source: SurfaceSource) -> Result<Opened, String> {
    match source {
        #[cfg(target_os = "windows")]
        SurfaceSource::Hwnd(hwnd) => {
            let started = Instant::now();
            let instance = crate::runtime::editor_instance();
            let started = stage("instance", started);
            // SAFETY: the pump's window lease keeps the hwnd alive - see `SurfacePump::spawn`.
            let surface = unsafe { surface_from_hwnd(&instance, hwnd) }?;
            stage("surface", started);
            Ok(Opened {
                instance,
                surface,
                waker: None,
            })
        }
        #[cfg(target_os = "macos")]
        SurfaceSource::Ready(instance, surface, waker) => Ok(Opened {
            instance,
            surface,
            waker,
        }),
    }
}

/// Let go of a frame that will never be painted. Windows presents it
/// (see `PumpClient::discard`); Metal recycles a dropped drawable, and
/// presenting one that was never painted would flash its old contents.
#[cfg(any(target_os = "windows", target_os = "macos"))]
fn release_unpainted(frame: wgpu::SurfaceTexture) {
    #[cfg(target_os = "windows")]
    frame.present();
    #[cfg(not(target_os = "windows"))]
    drop(frame);
}

/// Pump thread body: init, then serve resize / acquire / present
/// until shutdown.
#[cfg(any(target_os = "windows", target_os = "macos"))]
fn run<T: Send>(
    shared: &Shared,
    source: SurfaceSource,
    device_lost: &Arc<AtomicBool>,
    init: PumpInitFn<T>,
    init_tx: std::sync::mpsc::Sender<T>,
) {
    let built = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
        let Opened {
            instance,
            surface,
            waker,
        } = open_surface(source)?;
        let started = Instant::now();
        let adapter = pollster::block_on(instance.request_adapter(&wgpu::RequestAdapterOptions {
            power_preference: wgpu::PowerPreference::LowPower,
            compatible_surface: Some(&surface),
            force_fallback_adapter: false,
        }))
        .map_err(|e| format!("no adapter: {e}"))?;
        crate::diagnostics::note_adapter(&adapter.get_info(), started);
        let (product, device, config) = init(&instance, &adapter, &surface)?;
        // Setup can outlast the close's wait; a window closed meanwhile
        // may be gone, so its surface is never configured.
        if lock(&shared.slot).shutdown {
            return Ok(None);
        }
        let started = Instant::now();
        surface.configure(&device, &config);
        stage("swapchain", started);
        Ok(Some((product, device, config, surface, waker)))
    }))
    .unwrap_or_else(|e| {
        Err(format!(
            "panicked: {}",
            crate::runtime::panic_message(e.as_ref())
        ))
    });
    let (product, device, mut config, surface, waker) = match built {
        Ok(Some(built)) => built,
        Ok(None) => return,
        Err(cause) => {
            log::error!("iced surface pump: gpu init failed ({cause}); editor stays blank");
            return;
        }
    };
    let _ = init_tx.send(product);
    drop(init_tx);

    'work: loop {
        let (resize, present, need_acquire) = {
            let mut slot = lock(&shared.slot);
            loop {
                if slot.shutdown {
                    break 'work;
                }
                let need_acquire = slot.want_frame && slot.held.is_none() && !slot.taken;
                // A resize can't be applied while a frame is out with
                // the GUI thread: `surface.configure` panics if any
                // acquired texture is still alive. The GUI's present /
                // discard clears `taken` and notifies.
                let can_resize = slot.resize.is_some() && !slot.taken;
                if can_resize || slot.present.is_some() || need_acquire {
                    break;
                }
                slot = shared.cv.wait(slot).unwrap_or_else(PoisonError::into_inner);
            }
            let need_acquire = slot.want_frame && slot.held.is_none() && !slot.taken;
            let resize = if slot.taken { None } else { slot.resize.take() };
            (resize, slot.present.take(), need_acquire)
        };
        // Everything below can block inside the driver - that is the
        // point of this thread.
        let ok = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
            if let Some(frame) = present {
                frame.present();
            }
            if let Some((w, h)) = resize {
                // A frame acquired under the old configuration can't
                // be painted meaningfully - but on Windows it must be
                // PRESENTED, not dropped: DX12 replenishes the
                // swapchain's frame-latency waitable only on present,
                // so a dropped acquire burns a latency slot and once
                // starved every subsequent acquire blocks wgpu's full
                // 1 s timeout (measured; it was the multi-second
                // post-resize stall). Its recycled old-frame content
                // matches the stretched frame the compositor is showing
                // anyway.
                // Bound to a local first: a guard made in an `if let`
                // scrutinee lives through the body, and the GUI thread
                // would then wait on the slot for the driver's present.
                let stale = lock(&shared.slot).held.take();
                if let Some(stale) = stale {
                    release_unpainted(stale);
                }
                config.width = w.max(1);
                config.height = h.max(1);
                surface.configure(&device, &config);
            }
            // A drag queues resizes faster than configure + acquire
            // can run; if another one is already waiting, coalesce it
            // first - a frame acquired now would only be discarded.
            let resize_queued = lock(&shared.slot).resize.is_some();
            if need_acquire && !resize_queued {
                let mut acquired = None;
                for _ in 0..2 {
                    match surface.get_current_texture() {
                        Ok(frame) => {
                            acquired = Some(frame);
                            break;
                        }
                        Err(wgpu::SurfaceError::Outdated | wgpu::SurfaceError::Lost) => {
                            surface.configure(&device, &config);
                        }
                        Err(e) => {
                            log::warn!("iced surface pump acquire error: {e}");
                            break;
                        }
                    }
                }
                let mut slot = lock(&shared.slot);
                match acquired {
                    Some(frame) if slot.resize.is_none() => {
                        slot.held = Some(frame);
                        if slot.waiting {
                            slot.waiting = false;
                            drop(slot);
                            wake(&waker);
                        }
                    }
                    // A resize that raced in invalidates this frame; let
                    // it go and let the next loop pass reconfigure and
                    // reacquire.
                    Some(frame) => {
                        drop(slot);
                        release_unpainted(frame);
                    }
                    // An acquire the surface refused (occluded window,
                    // timeout) would otherwise be retried without pause;
                    // wait for the GUI thread's next request instead.
                    None => slot.want_frame = false,
                }
            }
        }));
        if let Err(e) = ok {
            device_lost.store(true, Ordering::Release);
            log::error!(
                "iced surface pump panicked ({}); flagging device loss for rebuild",
                crate::runtime::panic_message(e.as_ref())
            );
            break;
        }
    }
    // Everything GPU goes before the thread reports `exited`, frames before the
    // surface they came from, so a pump that reports it holds nothing a
    // closing window could outlive. A drop can panic (wgpu discards a
    // texture against a surface whose configure failed); swallow it so
    // teardown always completes.
    let (held, present) = {
        let mut slot = lock(&shared.slot);
        (slot.held.take(), slot.present.take())
    };
    let released = std::panic::catch_unwind(std::panic::AssertUnwindSafe(move || {
        drop(held);
        drop(present);
        drop(surface);
        drop(device);
        #[cfg(target_os = "macos")]
        drop(waker);
    }));
    if let Err(e) = released {
        log::warn!(
            "iced surface pump panicked releasing the GPU ({})",
            crate::runtime::panic_message(e.as_ref())
        );
    }
}

#[cfg(any(target_os = "windows", target_os = "macos"))]
fn mark_exited(shared: &Shared) {
    lock(&shared.slot).exited = true;
    shared.cv.notify_all();
}
