//! Surface-agnostic iced render pipeline shared by the desktop
//! (baseview) and iOS (`CAMetalLayer`) editors.
//!
//! `IcedRuntime` owns the wgpu device/surface/renderer plus the iced
//! `UserInterface` build/update/draw/cache cycle. The windowing host
//! creates the wgpu surface and feeds input events; everything from
//! `init_render` onward is identical across platforms. Only
//! `recover_device` (a baseview-driven GPU-loss rebuild) is desktop-only.

use std::fmt::Debug;
use std::sync::Arc;

use crate::iced::{Color, Event, Point, Size, Task};
use iced_wgpu::wgpu;
use truce_core::editor::PluginContext;
use truce_gui::EditorScale;
use truce_gui::layout::GridLayout;
use truce_params::Params;

use crate::auto_layout;
use crate::param_cache::ParamCache;
use crate::param_message::{Message, ParamMessage};

/// Event-to-paint latency, for measuring input response inside a host where
/// no profiler reaches. Set `TRUCE_ICED_INPUT_TRACE` to a file path and every
/// key event's answer is appended to it; a plug-in's standard error belongs to
/// the host and is rarely readable, and nothing in the stack installs a `log`
/// sink, so a file is the one place the measurement reliably lands. Compiled
/// out of a release build, and with the variable unset it costs one atomic
/// load on the paths it instruments.
#[cfg(debug_assertions)]
pub(crate) mod input_trace {
    use std::io::Write;
    use std::sync::{LazyLock, Mutex};
    use std::time::Instant;

    static SINK: LazyLock<Option<Mutex<std::fs::File>>> = LazyLock::new(|| {
        let path = std::env::var_os("TRUCE_ICED_INPUT_TRACE")?;
        std::fs::OpenOptions::new()
            .create(true)
            .append(true)
            .open(path)
            .ok()
            .map(Mutex::new)
    });

    pub(crate) fn enabled() -> bool {
        SINK.is_some()
    }

    /// Report the interval between the input arriving and the frame that
    /// answered it being handed to the compositor - the last moment this
    /// process can observe, one present short of the photons.
    pub(crate) fn painted(queued: Instant) {
        let Some(sink) = SINK.as_ref() else {
            return;
        };
        let Ok(mut file) = sink.lock() else {
            return;
        };
        let _ = writeln!(
            file,
            "input to paint: {:.2} ms",
            queued.elapsed().as_secs_f64() * 1e3
        );
    }
}

/// Extract a readable message from a `catch_unwind` panic payload.
#[cfg(not(target_os = "ios"))]
pub(crate) fn panic_message(e: &(dyn std::any::Any + Send)) -> String {
    e.downcast_ref::<&str>()
        .map(|s| (*s).to_string())
        .or_else(|| e.downcast_ref::<String>().cloned())
        .unwrap_or_else(|| "unknown panic".to_string())
}

/// The editor's wgpu instance. Release builds drop wgpu's default
/// `VALIDATION_INDIRECT_CALL`: nothing here issues an indirect draw or
/// dispatch, and the flag costs every device a validation compute pipeline
/// compiled at creation. Debug builds keep wgpu's build defaults.
#[cfg(not(target_os = "ios"))]
pub(crate) fn editor_instance() -> wgpu::Instance {
    let flags = if cfg!(debug_assertions) {
        wgpu::InstanceFlags::from_build_config()
    } else {
        wgpu::InstanceFlags::empty()
    };
    wgpu::Instance::new(&wgpu::InstanceDescriptor {
        backends: editor_backends(),
        flags,
        ..Default::default()
    })
}

/// wgpu backends for the editor surface. DX12 on Windows; Metal on macOS;
/// `PRIMARY` (Vulkan) on Linux.
#[cfg(not(target_os = "ios"))]
pub(crate) fn editor_backends() -> wgpu::Backends {
    #[cfg(target_os = "windows")]
    {
        wgpu::Backends::DX12
    }
    #[cfg(target_os = "macos")]
    {
        wgpu::Backends::METAL
    }
    #[cfg(not(any(target_os = "windows", target_os = "macos")))]
    {
        wgpu::Backends::PRIMARY
    }
}

/// The viewport's scale factor: device pixels per design point.
// Display DPI times an interface zoom; both bounded, so the narrowing is safe.
#[allow(clippy::cast_possible_truncation)]
pub(crate) fn viewport_scale(display: f64, zoom: f64) -> f32 {
    (display * zoom) as f32
}

/// A design size magnified by a zoom, in whole logical points.
#[allow(clippy::cast_possible_truncation, clippy::cast_sign_loss)]
pub(crate) fn zoomed(design: (u32, u32), zoom: f64) -> (u32, u32) {
    let side = |v: u32| ((f64::from(v) * zoom).round() as u32).max(1);
    (side(design.0), side(design.1))
}

// IcedPlugin trait - what plugin authors implement

/// Trait for plugin-specific iced UI logic.
///
/// Plugin authors implement this for full control over the iced view.
/// For zero-code UIs, use `IcedEditor::from_layout()` instead.
pub trait IcedPlugin<P: Params>: Sized + 'static {
    /// Plugin-specific message type. Use `()` if you have no custom messages.
    type Message: Debug + Clone + Send;

    /// Create the initial model.
    fn new(params: Arc<P>) -> Self;

    /// Handle a message (param change or plugin-specific).
    ///
    /// `Message::Tick` arrives once per rendered frame, after the host
    /// parameter sync and before `view`; use it to refresh model state
    /// derived from data the runtime cannot see. Default: no-op.
    fn update(
        &mut self,
        _message: Message<Self::Message>,
        _params: &ParamCache<P>,
        _ctx: &PluginContext<P>,
    ) -> Task<Message<Self::Message>> {
        Task::none()
    }

    /// Event subscriptions (e.g. `crate::iced::keyboard::listen()`,
    /// `crate::iced::event::listen_with`). truce-iced drives the recipes each
    /// frame and routes their messages back through `update`. Default: none.
    fn subscription(&self) -> crate::iced::Subscription<Message<Self::Message>> {
        crate::iced::Subscription::none()
    }

    /// Build the view.
    fn view<'a>(
        &'a self,
        params: &'a ParamCache<P>,
    ) -> crate::iced::Element<'a, Message<Self::Message>>;

    /// Custom theme (default: truce dark).
    fn theme(&self) -> crate::iced::Theme {
        crate::theme::truce_dark_theme()
    }

    /// How far this model wants the whole interface magnified: the window
    /// is the editor's design size times this, and every widget, text run
    /// and shader draws at the design size and the display's scale times
    /// this. Only an editor built with [`crate::IcedEditor::zoom`] follows
    /// it; it may change from frame to frame, and the editor resizes its
    /// window and asks the host to follow. Default: 1.
    fn zoom(&self) -> f64 {
        1.0
    }

    /// Window title.
    fn title(&self) -> String {
        String::from("Plugin")
    }

    /// The editor's native window, once it exists; it lives as long as the
    /// model does. A native dialog takes it as owner so the dialog stays in
    /// front of the host. Default: ignored.
    fn window_opened(&mut self, _window: raw_window_handle::RawWindowHandle) {}

    /// Plugin state was restored (preset recall, undo, session load).
    /// Re-read any cached custom state. Parameter values update automatically.
    fn state_changed(&mut self) {}

    /// Whether the editor should repaint this frame even with no UI
    /// input, param, or meter change. Default `false` - the idle gate
    /// skips redundant frames. Return `true` while the plugin has new
    /// data the runtime can't see (e.g. a lock-free queue drained inside
    /// `view()`) so it's drained and shown promptly instead of waiting
    /// for a stray UI event.
    fn needs_redraw(&self) -> bool {
        false
    }
}

// AutoPlugin - built-in plugin for GridLayout auto mode

/// Built-in `IcedPlugin` that generates a view from a `GridLayout`.
pub struct AutoPlugin {
    pub(crate) layout: GridLayout,
}

impl<P: Params> IcedPlugin<P> for AutoPlugin {
    type Message = (); // No custom messages in auto mode

    fn new(_params: Arc<P>) -> Self {
        panic!("AutoPlugin must be created via IcedEditor::from_layout");
    }

    fn view<'a>(&'a self, params: &'a ParamCache<P>) -> crate::iced::Element<'a, Message<()>> {
        auto_layout::auto_view(&self.layout, params)
    }
}

// IcedProgram - holds the plugin model + the shadow state the runtime
// reads / writes each frame. Used to implement `iced_runtime::Program`,
// but that trait no longer exists in iced 0.14; the runtime drives
// this type directly via `dispatch` / `view`.

pub(crate) struct IcedProgram<P: Params + 'static, M: IcedPlugin<P>> {
    pub(crate) plugin: M,
    pub(crate) param_cache: ParamCache<P>,
    pub(crate) context: PluginContext<P>,
    pub(crate) meter_ids: Vec<u32>,
}

impl<P: Params + 'static, M: IcedPlugin<P>> IcedProgram<P, M> {
    fn apply_param_message(&self, msg: &ParamMessage) {
        match msg {
            ParamMessage::BeginEdit(id) => self.context.begin_edit(*id),
            ParamMessage::SetNormalized(id, val) => self.context.set_param(*id, *val),
            ParamMessage::EndEdit(id) => self.context.end_edit(*id),
            ParamMessage::Batch(msgs) => {
                for m in msgs {
                    self.apply_param_message(m);
                }
            }
        }
    }

    /// Handle a single message: forward param events to the host, sync
    /// the shadow cache on `Tick`, and hand every message to the
    /// plugin's own `update`. The plugin may return a `Task` -
    /// truce-iced doesn't run an executor for embedded use, so the
    /// task is dropped. Plugin code that needs async work should
    /// thread it through its own host hooks rather than relying on
    /// iced's task runtime.
    pub(crate) fn dispatch(&mut self, message: Message<M::Message>) {
        if let Message::Param(ref param_msg) = message {
            self.apply_param_message(param_msg);
        }
        if matches!(message, Message::Tick) {
            let _ = self.poll_data();
        }
        let _: Task<Message<M::Message>> =
            self.plugin
                .update(message, &self.param_cache, &self.context);
    }

    /// Deliver the per-frame hook. `tick()` has already synced the host
    /// data for this frame, so the plugin is notified without paying for
    /// a second sync.
    pub(crate) fn notify_frame(&mut self) {
        let _: Task<Message<M::Message>> =
            self.plugin
                .update(Message::Tick, &self.param_cache, &self.context);
    }

    pub(crate) fn view(&self) -> crate::iced::Element<'_, Message<M::Message>> {
        self.plugin.view(&self.param_cache)
    }

    /// Sync the shadow param/meter caches from the host, returning
    /// whether any value moved this frame. Drives the editor's idle
    /// gate: host automation and live meters that change here force a
    /// repaint even with no UI input.
    pub(crate) fn poll_data(&mut self) -> bool {
        let params_changed = !self.param_cache.sync(&self.context).is_empty();
        let meters_changed = self.param_cache.sync_meters(&self.context, &self.meter_ids);
        params_changed || meters_changed
    }
}

// IcedRuntime - active iced state (exists only while editor is open)

pub(crate) struct IcedRuntime<P: Params, M: IcedPlugin<P>> {
    /// Rendering pipeline - initialized lazily when the baseview window
    /// finishes building and a wgpu surface is available.
    pub(crate) render: Option<RenderState<P, M>>,
    /// Messages waiting for the next frame to dispatch them: subscription
    /// messages drained ahead of the idle gate, and those of input a key
    /// delivery ran early. A frame that stops short of dispatching keeps them.
    sub_backlog: Vec<Message<M::Message>>,
    /// Cursor position in logical coordinates, or `None` while the
    /// pointer is outside the window (and before it first arrives), so
    /// hover states clear when it leaves.
    pub(crate) cursor_position: Option<Point>,
    /// Pending iced events queued by mouse callbacks.
    pub(crate) pending_events: Vec<Event>,
    /// When the oldest undrawn input arrived, for the event-to-paint trace.
    #[cfg(debug_assertions)]
    pub(crate) input_queued: Option<std::time::Instant>,
    /// Plugin creation info (consumed during render init).
    pub(crate) program: Option<IcedProgram<P, M>>,
    /// Editor size for viewport.
    pub(crate) size: (u32, u32),
    /// Live scale factor (clone of the editor's). Source of truth for
    /// every render path; written by `Editor::set_scale_factor` and
    /// the baseview `Resized` handler, observed each `tick()`.
    pub(crate) scale: EditorScale,
    /// The interface zoom the window is at (see [`IcedPlugin::zoom`]).
    /// Physical pixels come from the window's logical size and `scale`;
    /// the viewport's scale factor is `scale * zoom`, so the widget tree
    /// keeps laying out at the design size.
    pub(crate) zoom: f64,
    /// Last scale value the surface/viewport were configured for. When
    /// `scale.get()` diverges from this, `tick()` reconfigures and
    /// updates this snapshot.
    pub(crate) last_applied_scale: f64,
    /// Custom font's TrueType bytes. Family name is recovered by
    /// `crate::font::apply_font` from the TTF `name` table.
    pub(crate) font: Option<&'static [u8]>,
    /// Set when the wgpu device is lost (GPU reset) or a render panic is
    /// swallowed in `on_frame`. Polled at the top of `on_frame`, which then
    /// rebuilds the render pipeline; without it the editor would render
    /// against a dead device (a frozen / black surface). Shared into
    /// `set_device_lost_callback`, which fires off-thread.
    pub(crate) device_lost: Arc<std::sync::atomic::AtomicBool>,
    /// Subscription runtime: drives `IcedPlugin::subscription` recipes
    /// (keyboard, event listeners). A 1-thread pool polls the recipe
    /// streams; their messages arrive on `sub_rx` and are drained each
    /// frame. `Send` (`ThreadPool`), so `IcedRuntime` stays `Send`.
    pub(crate) sub_runtime: SubRuntime<Message<M::Message>>,
    pub(crate) sub_rx: crate::iced::futures::channel::mpsc::UnboundedReceiver<Message<M::Message>>,
    /// Stable window id stamped on broadcast events (single-window editor).
    pub(crate) window_id: crate::iced::window::Id,
    /// Idle gate: force a full render on the next `tick()` regardless of
    /// input/data state. Set on the first frame, after a resize, and
    /// after a device-loss rebuild.
    pub(crate) force_render: bool,
    /// Idle gate: a widget asked to redraw on the very next frame
    /// (`RedrawRequest::NextFrame`) - keep rendering continuously while
    /// set (active animation).
    pub(crate) animate: bool,
    /// Idle gate: the time a widget asked to be redrawn at
    /// (`RedrawRequest::At`, e.g. a `text_input` caret blink). `tick()`
    /// renders once this instant passes.
    pub(crate) redraw_at: Option<std::time::Instant>,
    /// Owns the wgpu surface + every blocking swapchain call (see
    /// `crate::pump`); [`Self::adopt_pump`] builds the pipeline from
    /// its init product. Desktop only - iOS keeps the surface inline
    /// in [`RenderState`].
    #[cfg(not(target_os = "ios"))]
    pub(crate) pump: Option<crate::pump::SurfacePump<PumpProduct>>,
    #[cfg(not(target_os = "ios"))]
    pub(crate) client: Option<crate::pump::PumpClient>,
    /// The GPU could not be set up and never will be for this window:
    /// nothing is drawn, recovered or queued from here on.
    #[cfg(not(target_os = "ios"))]
    pub(crate) gpu_failed: bool,
    /// Pipeline rebuilds since a frame last reached the screen.
    #[cfg(not(target_os = "ios"))]
    rebuilds_unshown: u8,
    /// When the editor opened, or its pipeline began a rebuild, until the
    /// first frame that follows reaches the screen.
    #[cfg(not(target_os = "ios"))]
    awaiting_first_frame: Option<std::time::Instant>,
}

/// How many times the pipeline is rebuilt without a frame reaching the
/// screen before the editor gives up. A lost device, reported or seen as a
/// panic, is cured by one rebuild; a failure that survives rebuilds is a
/// bug that would otherwise rebuild the GPU pipeline without end.
#[cfg(not(target_os = "ios"))]
const REBUILDS_UNSHOWN: u8 = 2;

/// What the pump's init closure hands back to the GUI thread: the iced
/// engine, its shaders compiled on the pump thread. The iced
/// program/model must never cross threads (no `Send` bound on plugin
/// models), so the renderer around the engine is built at adoption, in
/// [`IcedRuntime::adopt_pump`].
#[cfg(not(target_os = "ios"))]
pub(crate) struct PumpProduct {
    engine: iced_wgpu::Engine,
    device: wgpu::Device,
    surface_config: wgpu::SurfaceConfiguration,
}

/// The iced subscription runtime, parameterised by the editor's message
/// type: a thread-pool executor plus the channel its recipes publish to.
type SubRuntime<Msg> = iced_runtime::futures::Runtime<
    crate::iced::futures::executor::ThreadPool,
    crate::iced::futures::channel::mpsc::UnboundedSender<Msg>,
    Msg,
>;

/// Holds the full wgpu + iced rendering pipeline.
///
/// Replaces what `iced_runtime::program::State` used to encapsulate
/// in our 0.13 setup: we own the plugin model + the `UserInterface`
/// cache that lets iced reuse layout work between frames, and drive
/// the build / update / draw / extract-cache cycle by hand each
/// `tick()`.
pub(crate) struct RenderState<P: Params + 'static, M: IcedPlugin<P>> {
    /// Cloned wgpu handle for surface (re)configuration. The "primary"
    /// device + queue handles live inside `renderer`'s `Engine`.
    pub(crate) device: wgpu::Device,
    /// iOS only: the surface owned inline (`CAMetalLayer` path), with
    /// every swapchain call on the calling thread. Desktop editors
    /// leave this `None` - the surface lives with the pump
    /// (`IcedRuntime::client`), which on Windows keeps blocking
    /// swapchain calls off the host's GUI thread.
    pub(crate) surface: Option<wgpu::Surface<'static>>,
    pub(crate) surface_config: wgpu::SurfaceConfiguration,
    pub(crate) renderer: iced_wgpu::Renderer,
    pub(crate) program: IcedProgram<P, M>,
    /// `iced_runtime::UserInterface` cache between frames. Holds widget
    /// internal state (focus, scroll positions, ...) so we don't lose
    /// it between layout passes. `None` only mid-`tick()` between
    /// build and extract.
    pub(crate) ui_cache: Option<iced_runtime::user_interface::Cache>,
    /// Most recent mouse interaction reported by the UI's draw pass.
    /// Polled by the baseview handler to update the OS cursor.
    pub(crate) interaction: crate::iced::mouse::Interaction,
    /// Whether a focused widget (e.g. a `text_input`) currently wants
    /// keyboard input, from the UI's last `InputMethod` strategy. The
    /// iOS host drives `becomeFirstResponder` off this to raise/dismiss
    /// the soft keyboard.
    pub(crate) wants_keyboard: bool,
    pub(crate) viewport: iced_graphics::Viewport,
    pub(crate) theme: crate::iced::Theme,
    pub(crate) bg_color: Color,
}

/// What a `UserInterface::update` pass reported about the tree it left
/// behind: the cursor shape and IME intent to publish, and when the tree
/// wants to be painted again.
struct UiReport {
    interaction: crate::iced::mouse::Interaction,
    wants_keyboard: bool,
    redraw: crate::iced::window::RedrawRequest,
}

impl UiReport {
    /// Read an update result. `None` for `Outdated`: the widget tree
    /// changed under the update, so its report describes a tree that no
    /// longer exists and the caller should repaint instead of trusting it.
    fn read(state: iced_runtime::user_interface::State) -> Option<Self> {
        match state {
            iced_runtime::user_interface::State::Updated {
                mouse_interaction,
                input_method,
                redraw_request,
                ..
            } => Some(Self {
                interaction: mouse_interaction,
                // `InputMethod::Enabled` means a focused widget wants text
                // input; the iOS host raises the soft keyboard on this.
                wants_keyboard: matches!(input_method, crate::iced::InputMethod::Enabled { .. }),
                redraw: redraw_request,
            }),
            iced_runtime::user_interface::State::Outdated => None,
        }
    }
}

impl<P: Params + 'static, M: IcedPlugin<P>> IcedRuntime<P, M> {
    /// Build a runtime around a plugin program, before any wgpu surface
    /// exists. The windowing host calls [`Self::init_render`] once it has
    /// a surface. Shared by the desktop (baseview) and iOS (`CAMetalLayer`)
    /// editors so the subscription worker + channel wiring stays in one
    /// place.
    pub(crate) fn new(
        size: (u32, u32),
        scale: EditorScale,
        font: Option<&'static [u8]>,
        program: IcedProgram<P, M>,
    ) -> Self {
        // One worker thread polls the subscription recipe streams; idle
        // when no subscription is active.
        let sub_executor = crate::iced::futures::executor::ThreadPool::builder()
            .pool_size(1)
            .create()
            .expect("spawn subscription executor thread");
        let (sub_tx, sub_rx) = crate::iced::futures::channel::mpsc::unbounded();
        Self {
            render: None,
            sub_backlog: Vec::new(),
            cursor_position: None,
            pending_events: Vec::new(),
            #[cfg(debug_assertions)]
            input_queued: None,
            program: Some(program),
            size,
            scale,
            // init_render writes the real value; this placeholder never
            // reaches a render call.
            last_applied_scale: 0.0,
            zoom: 1.0,
            font,
            device_lost: Arc::new(std::sync::atomic::AtomicBool::new(false)),
            sub_runtime: iced_runtime::futures::Runtime::new(sub_executor, sub_tx),
            sub_rx,
            window_id: crate::iced::window::Id::unique(),
            // Paint the first frame unconditionally; the gate takes over
            // once there's something on screen.
            force_render: true,
            animate: false,
            redraw_at: None,
            #[cfg(not(target_os = "ios"))]
            pump: None,
            #[cfg(not(target_os = "ios"))]
            client: None,
            #[cfg(not(target_os = "ios"))]
            gpu_failed: false,
            #[cfg(not(target_os = "ios"))]
            rebuilds_unshown: 0,
            #[cfg(not(target_os = "ios"))]
            awaiting_first_frame: Some(std::time::Instant::now()),
        }
    }

    /// Spawn the surface pump for the editor window (see `crate::pump`):
    /// GPU init and every blocking swapchain call run there - off the
    /// host's GUI thread on Windows, where a stalled driver used to
    /// freeze the DAW. [`Self::adopt_pump`] builds the iced pipeline
    /// once init lands. Returns whether the pump spawned.
    #[cfg(not(target_os = "ios"))]
    pub(crate) fn spawn_pump(&mut self, window: &baseview::Window) -> bool {
        let (lw, lh) = self.size;
        let render_scale = self.scale.get();
        let w = truce_gui::to_physical_px(lw, render_scale).max(1);
        let h = truce_gui::to_physical_px(lh, render_scale).max(1);
        let lost_flag = self.device_lost.clone();
        // SAFETY: the editor drops the pump (via this runtime) before
        // closing its baseview window.
        let pump = unsafe {
            crate::pump::SurfacePump::spawn(
                window,
                &self.device_lost,
                Box::new(move |_, adapter, surface| {
                    let started = std::time::Instant::now();
                    let (device, queue) =
                        match pollster::block_on(adapter.request_device(&wgpu::DeviceDescriptor {
                            label: Some("truce-iced"),
                            required_features: wgpu::Features::empty(),
                            required_limits: adapter.limits(),
                            experimental_features: wgpu::ExperimentalFeatures::default(),
                            // `Performance` has DX12 allocate in 256 MB blocks, for
                            // an interface that needs a few MB.
                            memory_hints: wgpu::MemoryHints::MemoryUsage,
                            trace: wgpu::Trace::Off,
                        })) {
                            Ok(dq) => dq,
                            Err(e) => return Err(format!("no device: {e}")),
                        };
                    crate::diagnostics::stage("device", started);
                    // Raise the shared flag on device loss (GPU reset) so the
                    // next `on_frame` rebuilds the pipeline instead of rendering
                    // against a dead device.
                    device.set_device_lost_callback(move |reason, msg| {
                        lost_flag.store(true, std::sync::atomic::Ordering::Release);
                        log::warn!("iced wgpu device lost: {reason:?} - {msg}");
                    });

                    let surface_caps = surface.get_capabilities(adapter);
                    let surface_format = surface_format(&surface_caps.formats)
                        .ok_or("the surface offers no formats")?;
                    let alpha_mode = if surface_caps
                        .alpha_modes
                        .contains(&wgpu::CompositeAlphaMode::PostMultiplied)
                    {
                        wgpu::CompositeAlphaMode::PostMultiplied
                    } else {
                        surface_caps.alpha_modes[0]
                    };
                    let surface_config = wgpu::SurfaceConfiguration {
                        usage: wgpu::TextureUsages::RENDER_ATTACHMENT,
                        format: surface_format,
                        width: w,
                        height: h,
                        // Windows: a Fifo (AutoVsync) present blocks when the
                        // child-window swapchain backs up - freezing the host
                        // (REAPER) when it lands on the GUI thread and risking
                        // a GPU-watchdog (TDR) hang. Non-blocking present
                        // there; other platforms keep vsync.
                        #[cfg(target_os = "windows")]
                        present_mode: wgpu::PresentMode::AutoNoVsync,
                        #[cfg(not(target_os = "windows"))]
                        present_mode: wgpu::PresentMode::AutoVsync,
                        // macOS: the compositor keeps the frame on screen
                        // and the one it shows next, so with two drawables
                        // the frame after a refresh has nothing to paint
                        // into until the following one; a third keeps the
                        // queue at one frame while painting every refresh.
                        #[cfg(target_os = "macos")]
                        desired_maximum_frame_latency: 2,
                        #[cfg(not(target_os = "macos"))]
                        desired_maximum_frame_latency: 1,
                        alpha_mode,
                        view_formats: vec![],
                    };
                    let started = std::time::Instant::now();
                    let engine = new_engine(adapter, device.clone(), queue, surface_format);
                    crate::diagnostics::stage("shaders", started);
                    let product = PumpProduct {
                        engine,
                        device: device.clone(),
                        surface_config: surface_config.clone(),
                    };
                    Ok((product, device, surface_config))
                }),
            )
        };
        match pump {
            Ok(p) => {
                self.client = Some(p.client());
                self.pump = Some(p);
                true
            }
            Err(cause) => {
                log::error!("iced: no surface pump ({cause}); editor stays blank");
                self.fail_gpu();
                false
            }
        }
    }

    /// Give up on drawing for good: release the pump, drop the queued
    /// input and stop the subscriptions nothing will ever drain.
    #[cfg(not(target_os = "ios"))]
    fn fail_gpu(&mut self) {
        self.gpu_failed = true;
        self.pump = None;
        self.client = None;
        self.pending_events = Vec::new();
        self.sub_runtime.track(std::iter::empty());
    }

    /// Adopt the pump's init product and build the iced pipeline
    /// around it (first tick on macOS / Linux, whenever the pump
    /// thread finishes on Windows - the editor is blank until then
    /// and the host stays responsive throughout).
    #[cfg(not(target_os = "ios"))]
    pub(crate) fn adopt_pump(&mut self) {
        if self.render.is_some() {
            return;
        }
        let Some(pump) = self.pump.as_mut() else {
            return;
        };
        let product = match pump.take_init() {
            crate::pump::Init::Pending => return,
            crate::pump::Init::Ready(product) => product,
            crate::pump::Init::Failed => {
                self.fail_gpu();
                return;
            }
        };
        let PumpProduct {
            engine,
            device,
            surface_config,
        } = product;
        self.finish_init(engine, device, surface_config, None);
    }

    /// Reconfigure the surface to a physical size, keeping the local
    /// configuration copy in step. Routes through the pump's client
    /// (queued latest-wins; never blocks on Windows).
    #[cfg(not(target_os = "ios"))]
    pub(crate) fn reconfigure_surface_px(&mut self, pw: u32, ph: u32) {
        if let Some(render) = self.render.as_mut() {
            render.surface_config.width = pw.max(1);
            render.surface_config.height = ph.max(1);
            if let Some(surface) = &render.surface {
                surface.configure(&render.device, &render.surface_config);
            } else if let Some(client) = &self.client {
                client.resize(pw.max(1), ph.max(1));
            }
        }
    }

    /// Initialize the wgpu + iced rendering pipeline from a pre-created
    /// surface. iOS (`CAMetalLayer`) only: the surface is owned inline
    /// by the `RenderState`. Desktop editors go through
    /// [`Self::spawn_pump`] + [`Self::adopt_pump`] instead.
    //
    // `instance` and `surface` are threaded into the iced renderer; the
    // owned-arg shape avoids a clone at the call site.
    #[cfg(target_os = "ios")]
    #[allow(clippy::needless_pass_by_value)]
    pub(crate) fn init_render(
        &mut self,
        instance: wgpu::Instance,
        surface: wgpu::Surface<'static>,
    ) -> bool {
        let (lw, lh) = self.size;
        // Read from the shared cell (clone of the editor's scale). Re-
        // querying `truce_gui::backing_scale()` would drop a host-
        // supplied value.
        let render_scale = self.scale.get();
        let w = truce_gui::to_physical_px(lw, render_scale);
        let h = truce_gui::to_physical_px(lh, render_scale);

        let adapter =
            match pollster::block_on(instance.request_adapter(&wgpu::RequestAdapterOptions {
                power_preference: wgpu::PowerPreference::LowPower,
                compatible_surface: Some(&surface),
                force_fallback_adapter: false,
            })) {
                Ok(a) => a,
                Err(e) => {
                    log::warn!("no suitable GPU adapter found: {e}");
                    return false;
                }
            };

        let (device, queue) =
            match pollster::block_on(adapter.request_device(&wgpu::DeviceDescriptor {
                label: Some("truce-iced"),
                required_features: wgpu::Features::empty(),
                required_limits: adapter.limits(),
                experimental_features: wgpu::ExperimentalFeatures::default(),
                memory_hints: wgpu::MemoryHints::default(),
                trace: wgpu::Trace::Off,
            })) {
                Ok(dq) => dq,
                Err(e) => {
                    log::error!("failed to create wgpu device: {e}");
                    return false;
                }
            };
        // Raise the shared flag on device loss (GPU reset) so the next
        // frame rebuilds the pipeline instead of rendering against a dead
        // device. The flag is per-generation (see `recover_device`).
        let lost_flag = self.device_lost.clone();
        device.set_device_lost_callback(move |reason, msg| {
            lost_flag.store(true, std::sync::atomic::Ordering::Release);
            log::warn!("iced wgpu device lost: {reason:?} - {msg}");
        });

        let surface_caps = surface.get_capabilities(&adapter);
        let Some(surface_format) = surface_format(&surface_caps.formats) else {
            log::warn!("no surface formats available");
            return false;
        };
        let alpha_mode = if surface_caps
            .alpha_modes
            .contains(&wgpu::CompositeAlphaMode::PostMultiplied)
        {
            wgpu::CompositeAlphaMode::PostMultiplied
        } else {
            surface_caps.alpha_modes[0]
        };

        let surface_config = wgpu::SurfaceConfiguration {
            usage: wgpu::TextureUsages::RENDER_ATTACHMENT,
            format: surface_format,
            width: w.max(1),
            height: h.max(1),
            present_mode: wgpu::PresentMode::AutoVsync,
            desired_maximum_frame_latency: 1,
            alpha_mode,
            view_formats: vec![],
        };
        surface.configure(&device, &surface_config);

        let engine = new_engine(&adapter, device.clone(), queue, surface_config.format);
        self.finish_init(engine, device, surface_config, Some(surface))
    }

    /// Resize the runtime to a new logical size (iOS host-driven
    /// resize). Updates the cached logical size, reconfigures the inline
    /// wgpu surface to the new physical pixel count, and rebuilds the
    /// iced viewport so the next frame lays out against the new size.
    /// No-op until the render pipeline is live.
    #[cfg(target_os = "ios")]
    pub(crate) fn resize(&mut self, logical_w: u32, logical_h: u32) {
        self.size = (logical_w, logical_h);
        let render_scale = self.scale.get();
        let pw = truce_gui::to_physical_px(logical_w, render_scale).max(1);
        let ph = truce_gui::to_physical_px(logical_h, render_scale).max(1);
        let Some(render) = self.render.as_mut() else {
            return;
        };
        render.surface_config.width = pw;
        render.surface_config.height = ph;
        if let Some(surface) = &render.surface {
            surface.configure(&render.device, &render.surface_config);
        }
        render.viewport = iced_graphics::Viewport::with_physical_size(
            Size::new(pw, ph),
            viewport_scale(render_scale, self.zoom),
        );
        // The idle gate is exempt on iOS (every tick renders), but flag a
        // forced paint so the reflow lands even if that ever changes.
        self.force_render = true;
    }

    /// Build the iced renderer / [`RenderState`] around an initialized
    /// engine. `surface` is `Some` on iOS (inline swapchain) and `None`
    /// on desktop, where the pump owns it.
    fn finish_init(
        &mut self,
        engine: iced_wgpu::Engine,
        device: wgpu::Device,
        mut surface_config: wgpu::SurfaceConfiguration,
        surface: Option<wgpu::Surface<'static>>,
    ) -> bool {
        let Some(program) = self.program.take() else {
            return false;
        };

        let (lw, lh) = self.size;
        let render_scale = self.scale.get();
        self.last_applied_scale = render_scale;
        let w = truce_gui::to_physical_px(lw, render_scale).max(1);
        let h = truce_gui::to_physical_px(lh, render_scale).max(1);
        // The configuration was sized when init started; a host resize
        // or scale change may have landed since (on Windows init runs
        // on the pump thread). Re-sync before the first paint.
        if (surface_config.width, surface_config.height) != (w, h) {
            surface_config.width = w;
            surface_config.height = h;
            if let Some(s) = &surface {
                s.configure(&device, &surface_config);
            }
            #[cfg(not(target_os = "ios"))]
            if surface.is_none()
                && let Some(client) = &self.client
            {
                client.resize(w, h);
            }
        }

        let default_font = if let Some(data) = self.font {
            crate::font::apply_font(data)
        } else {
            crate::iced::Font::DEFAULT
        };
        let renderer = iced_wgpu::Renderer::new(engine, default_font, crate::iced::Pixels(14.0));

        // Scale is a display DPI factor (typically 1.0..=3.0); the
        // narrowing here is a documented host convention loss, not a
        // numeric overflow.
        #[allow(clippy::cast_possible_truncation)]
        let viewport = iced_graphics::Viewport::with_physical_size(
            Size::new(w, h),
            viewport_scale(render_scale, self.zoom),
        );
        let theme = program.plugin.theme();

        let bg = crate::theme::truce_dark_theme().palette().background;

        self.render = Some(RenderState {
            device,
            surface,
            surface_config,
            renderer,
            program,
            ui_cache: Some(iced_runtime::user_interface::Cache::new()),
            interaction: crate::iced::mouse::Interaction::default(),
            wants_keyboard: false,
            viewport,
            theme,
            bg_color: bg,
        });

        // The fresh pipeline must paint even if the idle gate sees no
        // other change.
        self.force_render = true;
        log::info!("gpu active (wgpu, {w}x{h})");
        true
    }

    /// Rebuild the pump + renderer after a device loss, salvaging the
    /// plugin program. Widget state in `ui_cache` is lost. Returns
    /// whether the pump respawned; the pipeline itself is rebuilt by
    /// `adopt_pump` once the new init lands.
    #[cfg(not(target_os = "ios"))]
    pub(crate) fn recover_device(&mut self, window: &baseview::Window) -> bool {
        if self.rebuilds_unshown >= REBUILDS_UNSHOWN {
            log::error!("iced: no frame survived {REBUILDS_UNSHOWN} rebuilds; editor stays blank");
            self.fail_gpu();
            return false;
        }
        self.rebuilds_unshown += 1;
        log::info!(
            target: crate::diagnostics::LIFECYCLE,
            "device lost; rebuilding the GPU setup (attempt {})",
            self.rebuilds_unshown
        );
        self.awaiting_first_frame = Some(std::time::Instant::now());
        // Give the new device generation a fresh lost-flag so the dying
        // device's own callback can't re-arm recovery and cause a redundant
        // second rebuild; `spawn_pump` clones this into the new callback.
        self.device_lost = Arc::new(std::sync::atomic::AtomicBool::new(false));
        // The rebuilt surface starts blank - force a paint on the next
        // tick even if the idle gate would otherwise skip it.
        self.force_render = true;
        // Drop the old pump/device/renderer; keep the program.
        if let Some(RenderState { program, .. }) = self.render.take() {
            self.program = Some(program);
        }
        self.pump = None;
        self.client = None;
        self.spawn_pump(window)
    }

    /// Drive one frame: update iced state + present to surface.
    // One frame's full pipeline (sync, gate, build, draw, present) in
    // source order; splitting it would scatter the borrow of `render`.
    #[allow(clippy::too_many_lines)]
    pub(crate) fn tick(&mut self) {
        #[cfg(not(target_os = "ios"))]
        let tick_started = self.awaiting_first_frame.map(|_| std::time::Instant::now());
        // Adopt the pump's GPU init product once it lands (first tick
        // on macOS / Linux; whenever the pump thread finishes on
        // Windows - blank but responsive until then).
        #[cfg(not(target_os = "ios"))]
        self.adopt_pump();
        // No paint pacing here. Vsync already paces the swapchain, and a
        // hold that skips the whole tick also skips input processing, so
        // it costs a frame of latency for every frame it defers. The
        // Windows GUI thread - the reason pacing existed - is kept clear
        // by the pump thread instead (see `crate::pump`).
        let Some(render) = self.render.as_mut() else {
            return;
        };

        // Pick up host-driven scale changes (CLAP `set_scale`, VST3
        // `IPlugViewContentScaleSupport`) that landed in the shared
        // cell since the last frame. The Resized path applies its own
        // scale changes inline so this branch only fires when scale
        // moved without a corresponding window event.
        //
        // Bit-level comparison rather than `!=` so the implicit
        // invariant - "values come through `EditorScale::set` /
        // `.get()`, both of which round-trip via `to_bits` /
        // `from_bits`, so equal inputs produce equal stored bits" -
        // is explicit at the comparison site. `2.0 != 2.0` would
        // never be true via this path today, but a clippy lint and
        // a future refactor that narrowed the type to `f32` somewhere
        // could turn the implicit guarantee into an actual NaN-flavored
        // bug.
        let cur_scale = self.scale.get();
        let scale_changed = cur_scale.to_bits() != self.last_applied_scale.to_bits();
        if scale_changed {
            let (lw, lh) = self.size;
            let pw = truce_gui::to_physical_px(lw, cur_scale);
            let ph = truce_gui::to_physical_px(lh, cur_scale);
            render.surface_config.width = pw;
            render.surface_config.height = ph;
            if let Some(surface) = &render.surface {
                surface.configure(&render.device, &render.surface_config);
            }
            #[cfg(not(target_os = "ios"))]
            if render.surface.is_none()
                && let Some(client) = &self.client
            {
                client.resize(pw.max(1), ph.max(1));
            }
            render.viewport = iced_graphics::Viewport::with_physical_size(
                Size::new(pw, ph),
                viewport_scale(cur_scale, self.zoom),
            );
            self.last_applied_scale = cur_scale;
        }

        // Sync params + meters from the host first (cheap atomic reads)
        // so the view rebuilt below sees fresh shadow values, and learn
        // whether any host-side value moved this frame.
        let data_changed = render.program.poll_data();

        // Drain subscription messages that arrived since the last frame
        // into the backlog. A non-empty backlog forces a render so
        // time-driven subscriptions (e.g. `iced::time::every`) aren't
        // stalled by the idle gate; the messages are dispatched below.
        while let Ok(message) = self.sub_rx.try_recv() {
            self.sub_backlog.push(message);
        }

        // Idle gate: skip the whole frame - no view rebuild, no GPU
        // present - when nothing needs redrawing. This is what keeps the
        // host responsive: baseview's frame timer still fires on the
        // host's GUI thread every tick, but an idle editor returns
        // immediately instead of rebuilding + presenting. Errs toward
        // rendering; any uncertainty paints.
        let timer_due = self
            .redraw_at
            .is_some_and(|t| std::time::Instant::now() >= t);
        // iOS is exempt: it's driven by `CADisplayLink` (no host
        // message pump to free), and its per-frame `RedrawRequested`
        // re-issues `request_input_method` to keep the soft keyboard up,
        // so every frame must run.
        let should_render = cfg!(target_os = "ios")
            || self.force_render
            || scale_changed
            || !self.pending_events.is_empty()
            || data_changed
            || self.animate
            || timer_due
            || render.program.plugin.needs_redraw()
            || !self.sub_backlog.is_empty();
        if !should_render {
            return;
        }
        // The pump acquires on its own thread; a frame with no image to
        // paint into would build and draw for nothing. Leave the input
        // queued for the frame that has one: on macOS the pump wakes this
        // thread the moment it lands, on Windows the next tick finds it.
        #[cfg(any(target_os = "windows", target_os = "macos"))]
        if let Some(client) = &self.client
            && !client.request_frame()
        {
            self.force_render = true;
            return;
        }
        self.force_render = false;

        let cursor = cursor_at(self.cursor_position);
        let logical_size = render.viewport.logical_size();
        let style = iced_runtime::core::renderer::Style {
            text_color: Color::from_rgb(0.90, 0.90, 0.92),
        };

        // The backlog came before this frame's input. A text field edits
        // its own copy of the model's value, so the model must hold what
        // earlier keys typed before the tree is built for later ones.
        if !self.sub_backlog.is_empty() {
            for message in std::mem::take(&mut self.sub_backlog) {
                render.program.dispatch(message);
            }
            let _ = render.program.poll_data();
        }

        // Give the plugin its per-frame hook before the view is built,
        // so model state it derives from data the runtime cannot see is
        // fresh in the frame that shows it.
        render.program.notify_frame();

        // Build the user interface for this frame from the current
        // model. The borrow of `render.program` is dropped at
        // `into_cache()`, after which we can re-enter `dispatch` for
        // each collected message.
        let mut messages: Vec<Message<M::Message>> = Vec::new();
        let cache = render
            .ui_cache
            .take()
            .unwrap_or_else(iced_runtime::user_interface::Cache::new);
        let view_element = render.program.view();
        let mut user_interface = iced_runtime::UserInterface::build(
            view_element,
            logical_size,
            cache,
            &mut render.renderer,
        );

        let mut pending_events = std::mem::take(&mut self.pending_events);
        // Feed a per-frame `RedrawRequested` like iced_winit does: focused
        // widgets re-evaluate on it (text_input blinks its caret and, while
        // focused, re-issues its `request_input_method` - the signal the iOS
        // host reads to keep the soft keyboard up). Without it, on a frame
        // with no input events nothing requests IME and the keyboard would
        // drop. Appended last so it observes focus set by this frame's input.
        pending_events.push(Event::Window(crate::iced::window::Event::RedrawRequested(
            std::time::Instant::now(),
        )));
        let (ui_state, statuses) = user_interface.update(
            &pending_events,
            cursor,
            &mut render.renderer,
            &mut crate::clipboard::Clipboard,
            &mut messages,
        );
        let mut report = UiReport::read(ui_state);

        // Subscription pump: keep `IcedPlugin::subscription` recipes tracked
        // and broadcast this frame's events to them, so `keyboard::listen` /
        // `event::listen_with` fire. The worker thread polls the streams, so
        // their messages may land a frame later; drain whatever is ready and
        // fold it in with the widget messages.
        let recipes =
            iced_runtime::futures::subscription::into_recipes(render.program.plugin.subscription());
        self.sub_runtime.track(recipes);
        for (event, status) in pending_events.iter().zip(&statuses) {
            self.sub_runtime
                .broadcast(iced_runtime::futures::subscription::Event::Interaction {
                    window: self.window_id,
                    event: event.clone(),
                    status: *status,
                });
        }
        while let Ok(message) = self.sub_rx.try_recv() {
            messages.push(message);
        }

        // Captured input can open an overlay without publishing a message;
        // a host may apply a parameter edit on its own thread, after this
        // frame has already re-read it. Either way, repaint next tick.
        if !messages.is_empty()
            || statuses
                .iter()
                .any(|status| *status == iced_runtime::core::event::Status::Captured)
        {
            self.force_render = true;
        }

        // Messages the rebuilt tree publishes arrive too late to be shown
        // this frame; they are dispatched below, once nothing borrows the
        // program, and the forced repaint above carries them.
        let mut late_messages: Vec<Message<M::Message>> = Vec::new();
        if !messages.is_empty() {
            // Draw the model the messages produced, not the one they
            // replaced. `into_cache()` releases the view's borrow of the
            // program so the messages can be dispatched, and the tree is
            // rebuilt from the result before anything is drawn.
            render.ui_cache = Some(user_interface.into_cache());
            for message in messages {
                render.program.dispatch(message);
            }
            // Parameter edits the plugin just made reach the shadow cache
            // only by way of the host, so re-read before the rebuild, and
            // give the plugin its frame hook again: a message can move the
            // model onto a view whose derived state the first hook never saw.
            let _ = render.program.poll_data();
            render.program.notify_frame();

            let cache = render
                .ui_cache
                .take()
                .unwrap_or_else(iced_runtime::user_interface::Cache::new);
            let view_element = render.program.view();
            user_interface = iced_runtime::UserInterface::build(
                view_element,
                logical_size,
                cache,
                &mut render.renderer,
            );
            // Only the redraw event: the input events were consumed by the
            // tree that produced the messages, and the subscriptions have
            // already seen them.
            let redraw = [Event::Window(crate::iced::window::Event::RedrawRequested(
                std::time::Instant::now(),
            ))];
            let (ui_state, _) = user_interface.update(
                &redraw,
                cursor,
                &mut render.renderer,
                &mut crate::clipboard::Clipboard,
                &mut late_messages,
            );
            report = UiReport::read(ui_state);
        }

        user_interface.draw(&mut render.renderer, &render.theme, &style, cursor);

        render.ui_cache = Some(user_interface.into_cache());

        // Nothing borrows the program any more, so the late messages and
        // the frame's report can land.
        for message in late_messages {
            render.program.dispatch(message);
        }
        if let Some(report) = report {
            render.interaction = report.interaction;
            render.wants_keyboard = report.wants_keyboard;
            match report.redraw {
                crate::iced::window::RedrawRequest::NextFrame => {
                    self.animate = true;
                    self.redraw_at = None;
                }
                crate::iced::window::RedrawRequest::At(t) => {
                    self.animate = false;
                    self.redraw_at = Some(t);
                }
                crate::iced::window::RedrawRequest::Wait => {
                    self.animate = false;
                    self.redraw_at = None;
                }
            }
        } else {
            // `Outdated`: the widget tree changed under us; rebuild and
            // repaint next frame rather than trusting this frame's state.
            self.force_render = true;
        }

        // Present: get surface texture, render, submit. iced 0.14's
        // `Renderer::present` builds its own encoder + submits to the
        // queue internally, so we no longer manage either by hand.
        let inline_surface = render.surface.is_some();
        let frame = if let Some(surface) = &render.surface {
            // iOS: acquire inline on the calling thread.
            match surface.get_current_texture() {
                Ok(f) => f,
                Err(wgpu::SurfaceError::Timeout | wgpu::SurfaceError::Outdated) => {
                    surface.configure(&render.device, &render.surface_config);
                    return;
                }
                Err(e) => {
                    log::warn!("surface error: {e}");
                    return;
                }
            }
        } else {
            // Desktop: take the pump's frame. On Windows this never
            // blocks (the pump pre-acquires on its own thread).
            #[cfg(target_os = "ios")]
            return;
            #[cfg(not(target_os = "ios"))]
            {
                let Some(client) = &self.client else {
                    return;
                };
                let Some(frame) = client.try_take_frame() else {
                    // Pump still acquiring, or a transient error - the
                    // frame's CPU work is done; repaint once one is
                    // ready instead of waiting for the next change.
                    self.force_render = true;
                    return;
                };
                if (frame.texture.width(), frame.texture.height())
                    != (render.surface_config.width, render.surface_config.height)
                {
                    // A resize raced the acquire; discard the stale-
                    // size frame (the pump reconfigures + reacquires).
                    client.discard(frame);
                    self.force_render = true;
                    return;
                }
                frame
            }
        };

        let view = frame
            .texture
            .create_view(&wgpu::TextureViewDescriptor::default());

        let _ = render.renderer.present(
            Some(render.bg_color),
            render.surface_config.format,
            &view,
            &render.viewport,
        );

        if inline_surface {
            frame.present();
            #[cfg(debug_assertions)]
            if let Some(queued) = self.input_queued.take() {
                input_trace::painted(queued);
            }
            return;
        }
        #[cfg(not(target_os = "ios"))]
        if let Some(client) = &self.client {
            client.present(frame);
            if let (Some(since), Some(tick_started)) =
                (self.awaiting_first_frame.take(), tick_started)
            {
                let after = if self.rebuilds_unshown > 0 {
                    "the device loss"
                } else {
                    "open"
                };
                log::info!(
                    target: crate::diagnostics::LIFECYCLE,
                    "first frame {} ms, shown {} ms after {after}",
                    tick_started.elapsed().as_millis(),
                    since.elapsed().as_millis()
                );
            }
            self.rebuilds_unshown = 0;
        }
        #[cfg(debug_assertions)]
        if let Some(queued) = self.input_queued.take() {
            input_trace::painted(queued);
        }
    }

    /// Note that input has arrived, for the event-to-paint trace.
    pub(crate) fn note_input(&mut self) {
        #[cfg(debug_assertions)]
        if input_trace::enabled() && self.input_queued.is_none() {
            self.input_queued = Some(std::time::Instant::now());
        }
    }

    /// Queue a cursor move event. Coordinates are in the window's logical
    /// points, which a zoomed interface divides back to its design points.
    #[allow(clippy::cast_possible_truncation)]
    pub(crate) fn queue_cursor_move(&mut self, x: f32, y: f32) {
        let zoom = self.zoom as f32;
        let position = Point::new(x / zoom, y / zoom);
        // Platforms differ on whether and when they report an entry, so
        // the first position after the pointer was away is what says it.
        if self.cursor_position.replace(position).is_none() {
            self.pending_events
                .push(Event::Mouse(crate::iced::mouse::Event::CursorEntered));
        }
        self.pending_events
            .push(Event::Mouse(crate::iced::mouse::Event::CursorMoved {
                position,
            }));
    }

    /// Queue the pointer leaving the window. A frame's events share the
    /// cursor the batch ends with, as in iced's own shells.
    #[cfg(not(target_os = "ios"))]
    pub(crate) fn queue_cursor_left(&mut self) {
        self.cursor_position = None;
        self.pending_events
            .push(Event::Mouse(crate::iced::mouse::Event::CursorLeft));
    }

    /// The zoom the plugin model now asks for, when it is not the one the
    /// window is at.
    #[cfg(not(target_os = "ios"))]
    pub(crate) fn wanted_zoom(&self) -> Option<f64> {
        let wanted = self.render.as_ref()?.program.plugin.zoom();
        (wanted.is_finite() && wanted > 0.0 && (wanted - self.zoom).abs() > 1.0e-9)
            .then_some(wanted)
    }

    /// Take a new logical window size: the viewport, the surface and the
    /// next frame all follow it.
    #[cfg(not(target_os = "ios"))]
    pub(crate) fn apply_logical_size(&mut self, w: u32, h: u32) {
        self.size = (w, h);
        self.force_render = true;
        let scale = self.scale.get();
        let pw = truce_gui::to_physical_px(w, scale);
        let ph = truce_gui::to_physical_px(h, scale);
        if let Some(ref mut render) = self.render {
            render.viewport = iced_graphics::Viewport::with_physical_size(
                Size::new(pw, ph),
                viewport_scale(scale, self.zoom),
            );
        }
        self.reconfigure_surface_px(pw, ph);
    }

    /// Run a key through the interface now, behind the input still queued
    /// ahead of it, and say whether the editor keeps it. The platform needs
    /// the answer before the key can go on to the host. The messages wait
    /// for the next frame, so no plugin message is dispatched inside the
    /// platform's key delivery, which on Windows can be a host's own
    /// message peek.
    ///
    /// While an earlier key's messages still wait, the tree would start from
    /// a model that lacks them and a text field would drop what that key
    /// typed. The key then waits for the frame too, kept only if a text
    /// field holds the keyboard.
    #[cfg(not(target_os = "ios"))]
    pub(crate) fn offer_key(&mut self, key: Event) -> bool {
        let Some(render) = self.render.as_mut() else {
            return false;
        };
        let _ = render.program.poll_data();
        let waiting = !self.sub_backlog.is_empty();
        let mut events = if waiting {
            Vec::new()
        } else {
            std::mem::take(&mut self.pending_events)
        };
        let cache = render
            .ui_cache
            .take()
            .unwrap_or_else(iced_runtime::user_interface::Cache::new);
        let mut user_interface = iced_runtime::UserInterface::build(
            render.program.view(),
            render.viewport.logical_size(),
            cache,
            &mut render.renderer,
        );
        if waiting {
            let kept = keeps_key(
                &mut user_interface,
                &render.renderer,
                iced_core::event::Status::Ignored,
            );
            render.ui_cache = Some(user_interface.into_cache());
            // A declined key is the host's alone.
            if kept {
                self.pending_events.push(key);
            }
            return kept;
        }
        events.push(key);
        let mut messages = Vec::new();
        let (_, statuses) = user_interface.update(
            &events,
            cursor_at(self.cursor_position),
            &mut render.renderer,
            &mut crate::clipboard::Clipboard,
            &mut messages,
        );
        let kept = statuses
            .last()
            .is_some_and(|status| keeps_key(&mut user_interface, &render.renderer, *status));
        render.ui_cache = Some(user_interface.into_cache());
        for (event, status) in events.iter().zip(&statuses) {
            self.sub_runtime
                .broadcast(iced_runtime::futures::subscription::Event::Interaction {
                    window: self.window_id,
                    event: event.clone(),
                    status: *status,
                });
        }
        self.sub_backlog.append(&mut messages);
        self.force_render = true;
        kept
    }

    /// Whether the UI's last frame had a focused widget wanting keyboard
    /// input. Drives the iOS soft keyboard. `false` until the first frame
    /// renders.
    #[cfg_attr(not(target_os = "ios"), allow(dead_code))]
    pub(crate) fn wants_keyboard(&self) -> bool {
        self.render.as_ref().is_some_and(|r| r.wants_keyboard)
    }
}

/// Whether the editor keeps a key the interface was just given: a widget
/// used it, or a focused text field holds the keyboard, which keeps even the
/// keys the field gives no meaning so typing never reaches the host. Every
/// other key belongs to the host, so its shortcuts work while the editor has
/// focus.
pub fn keeps_key<Message, Theme, Renderer: iced_core::Renderer>(
    user_interface: &mut iced_runtime::UserInterface<'_, Message, Theme, Renderer>,
    renderer: &Renderer,
    status: iced_core::event::Status,
) -> bool {
    struct Focused(bool);
    impl iced_core::widget::Operation for Focused {
        fn traverse(&mut self, operate: &mut dyn FnMut(&mut dyn iced_core::widget::Operation)) {
            operate(self);
        }
        fn focusable(
            &mut self,
            _: Option<&iced_core::widget::Id>,
            _: iced_core::Rectangle,
            state: &mut dyn iced_core::widget::operation::Focusable,
        ) {
            self.0 |= state.is_focused();
        }
    }
    if status == iced_core::event::Status::Captured {
        return true;
    }
    let mut focused = Focused(false);
    user_interface.operate(renderer, &mut focused);
    focused.0
}

fn cursor_at(position: Option<Point>) -> crate::iced::mouse::Cursor {
    position.map_or(
        crate::iced::mouse::Cursor::Unavailable,
        crate::iced::mouse::Cursor::Available,
    )
}

/// The iced engine for a device: compiles iced's own pipelines.
fn new_engine(
    adapter: &wgpu::Adapter,
    device: wgpu::Device,
    queue: wgpu::Queue,
    format: wgpu::TextureFormat,
) -> iced_wgpu::Engine {
    iced_wgpu::Engine::new(
        adapter,
        device,
        queue,
        format,
        Some(iced_graphics::Antialiasing::MSAAx4),
        iced_graphics::Shell::headless(),
    )
}

/// The surface format the editor draws to. iced writes linear colour
/// (`iced_graphics::color::GAMMA_CORRECTION`, on without `web-colors`)
/// and so does the plugin's own linear-light shading, so the target must
/// encode to sRGB itself, as iced's own compositor chooses. The first
/// format a surface lists is not that everywhere: Metal lists
/// `Bgra8Unorm` first, which showed the editor far darker on macOS than
/// on Windows or in offscreen captures. A surface with no sRGB format
/// still gets drawn, too dark, rather than left blank.
fn surface_format(formats: &[wgpu::TextureFormat]) -> Option<wgpu::TextureFormat> {
    let srgb = formats.iter().copied().find(wgpu::TextureFormat::is_srgb);
    if srgb.is_none() && !formats.is_empty() {
        log::warn!("the surface offers no sRGB format; colours will be too dark");
    }
    srgb.or_else(|| formats.first().copied())
}
