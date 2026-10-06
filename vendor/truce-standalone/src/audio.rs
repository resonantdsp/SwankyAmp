//! Shared cpal audio setup + callback. One implementation used by
//! both `windowed` and `headless` runners.
//!
//! Both the input and output cpal streams are owned by dedicated
//! worker threads (cpal `Stream` is `!Send` on macOS, so it can't
//! cross threads). UI / menu / CLI callers manipulate them through
//! `Send + Sync` controllers (`InputController`, `OutputController`)
//! that talk to the workers via `mpsc` channels:
//!
//! - **Toggle / enable** for input (drop the cpal input stream when
//!   off - saves CPU and skips the OS mic permission prompt) and
//!   output (mute - keep the stream open so processing keeps ticking,
//!   just zero-fill the speaker buffer).
//! - **Switch device** for either side. Worker drops the old stream
//!   and opens a new one against the requested device name; on
//!   failure the previous device's name remains in place and the
//!   audio callback keeps running unchanged. Picking an input that
//!   belongs to an interface with outputs moves the output there too,
//!   unless an output was chosen, so both streams run on one clock.
//! - **Buffer size**, which reopens both streams at the new size.
//! - **Driver** on Windows, ASIO or WASAPI (see [`crate::driver`]). An
//!   ASIO interface is one device for input and output, so on ASIO the
//!   output worker opens the input stream with the output and the input
//!   worker only lets it through or not.
//!
//! Device, buffer and driver choices made here are remembered on this
//! machine (see [`crate::settings`]).

use crossbeam_queue::ArrayQueue;
use std::sync::atomic::{AtomicBool, AtomicU32, AtomicUsize, Ordering};
use std::sync::{Arc, Mutex, Weak, mpsc};

use cpal::traits::{DeviceTrait, HostTrait, StreamTrait};

use truce_core::buffer::RawBufferScratch;
use truce_core::cast::{sample_count_usize, sample_rate_u32};
use truce_core::chunked_process::{ChunkedProcess, process_chunked};
use truce_core::config::{AudioConfig, ProcessMode};
use truce_core::events::{EVENT_LIST_PREALLOC, Event, EventBody, EventList};
use truce_core::export::PluginExport;
use truce_core::info::PluginCategory;
use truce_params::{ParamInfo, Params};

use crate::cli::Options;
use crate::driver;
use crate::format::{build_input, build_output};
use crate::settings::{self, AudioDriver, SettingsStore};
use crate::setup::{self, InputNeed};
use crate::transport::Transport;
use crate::vlog;

type BoxErr = Box<dyn std::error::Error>;

/// Per-stream audio-callback scratch for the channel-pointer arrays
/// fed into [`RawBufferScratch::build`]. cpal's stream closure must
/// be `Send + 'static`, but `Vec<*const f32>` / `Vec<*mut f32>` are
/// `!Send` because raw pointers don't carry thread-safety. The cpal
/// closure runs on a single dedicated audio thread per stream and the
/// pointer values are written + consumed within one callback (they
/// always alias `input_bufs` / `channel_bufs` on the same stack
/// frame), so the closure capture is sound.
struct CallbackPtrScratch {
    inputs: Vec<*const f32>,
    outputs: Vec<*mut f32>,
}
// SAFETY: see [`CallbackPtrScratch`] doc.
unsafe impl Send for CallbackPtrScratch {}

/// Widest interleaved mic-input frame the ring carries. The input
/// callback normalizes the capture device's frames to the ring width
/// (the output stream's channel count); this bounds the fixed-size
/// frame so the ring is a lock-free, alloc-free `ArrayQueue`. A wider
/// output folds its extra channels onto these.
const MAX_INPUT_RING_CHANNELS: usize = 16;

/// One interleaved mic-input frame, fixed-width so the ring never
/// allocates. Only the first `width` lanes are meaningful (the ring
/// width; see [`normalize_input_frame`]).
#[derive(Clone, Copy)]
struct InputFrame {
    samples: [f32; MAX_INPUT_RING_CHANNELS],
}

/// Lock-free hand-off from the input (capture) audio thread to the
/// output (render) audio thread. Frame-granular so a dropped frame never
/// splits an interleaved frame (which would shift channel alignment).
/// What it holds is audible delay, so [`RingReader`] keeps it short.
struct InputRing {
    frames: ArrayQueue<InputFrame>,
    /// Frames the capture callback delivered last time. A device that
    /// captures in larger blocks than it renders legitimately queues a
    /// whole capture block, so the reader allows that much to wait.
    capture_block: AtomicUsize,
}

impl InputRing {
    fn new(capacity: usize) -> Self {
        Self {
            frames: ArrayQueue::new(capacity.max(1)),
            capture_block: AtomicUsize::new(0),
        }
    }

    /// Queue one capture callback's interleaved `data` (`channels` per
    /// frame), each frame normalized to `width` lanes. When the ring is
    /// full the oldest frames make way. No lock, no allocation.
    fn capture(&self, data: &[f32], channels: usize, width: usize) {
        if channels == 0 {
            return;
        }
        self.capture_block
            .store(data.len() / channels, Ordering::Relaxed);
        for frame in data.chunks_exact(channels) {
            self.frames.force_push(normalize_input_frame(frame, width));
        }
    }

    fn drop_oldest(&self, count: usize) {
        for _ in 0..count {
            if self.frames.pop().is_none() {
                break;
            }
        }
    }

    fn clear(&self) {
        while self.frames.pop().is_some() {}
    }
}

/// The render side of [`InputRing`], which keeps the delay between
/// capturing input and playing it near one render block, so it cannot
/// build up over a session.
///
/// Input queued beyond this block, one capture block and a small margin
/// is dropped before the block is read: that is the backlog a stall, a
/// reopened stream or startup leaves. Separate input and output devices
/// run on separate clocks, so a surplus can also creep up slowly; any
/// surplus that stayed queued for a whole window is dropped down to the
/// margin at the window's end. Judging the surplus over a window rather
/// than per block lets jitter between the two callbacks pass without
/// dropping audio that is about to be needed.
struct RingReader {
    /// Surplus kept as a cushion against callback jitter.
    margin: usize,
    /// Render frames over which the least surplus is judged.
    window: usize,
    rendered: usize,
    least_surplus: usize,
}

impl RingReader {
    fn new(sample_rate: f64) -> Self {
        let rate = sample_count_usize(sample_rate);
        Self {
            // Half a millisecond, and half a second.
            margin: (rate / 2000).max(8),
            window: (rate / 2).max(1),
            rendered: 0,
            least_surplus: usize::MAX,
        }
    }

    /// Hand up to `frames` queued input frames to `each` with their index
    /// in the render block, oldest first, after dropping backlog. Frames
    /// the ring lacks are left to the caller's silence.
    fn read(&mut self, ring: &InputRing, frames: usize, mut each: impl FnMut(usize, &InputFrame)) {
        let ceiling = frames + ring.capture_block.load(Ordering::Relaxed) + self.margin;
        ring.drop_oldest(ring.frames.len().saturating_sub(ceiling));
        self.least_surplus = self
            .least_surplus
            .min(ring.frames.len().saturating_sub(frames));
        for i in 0..frames {
            let Some(frame) = ring.frames.pop() else {
                break;
            };
            each(i, &frame);
        }
        self.rendered += frames;
        if self.rendered >= self.window {
            ring.drop_oldest(self.least_surplus.saturating_sub(self.margin));
            self.rendered = 0;
            self.least_surplus = usize::MAX;
        }
    }
}

/// Normalize one native capture frame (`src`, `src.len()` interleaved
/// channels) to a ring frame of `width` channels. A mono source
/// broadcasts to every lane (so a mono mic feeds both plugin inputs); a
/// wider source is truncated, a narrower one zero-fills past its
/// channels. Pure arithmetic - safe on the audio thread.
fn normalize_input_frame(src: &[f32], width: usize) -> InputFrame {
    let mut frame = InputFrame {
        samples: [0.0; MAX_INPUT_RING_CHANNELS],
    };
    let w = width.min(MAX_INPUT_RING_CHANNELS);
    if src.len() == 1 {
        for lane in &mut frame.samples[..w] {
            *lane = src[0];
        }
    } else {
        for (lane, &s) in frame.samples[..w].iter_mut().zip(src.iter()) {
            *lane = s;
        }
    }
    frame
}

/// A queued MIDI event the UI thread hands off to the audio callback.
pub struct MidiEvent {
    pub body: EventBody,
    /// Plugin MIDI input port this event targets. Device input stamps
    /// the port its `--midi-input` slot maps to; the QWERTY keyboard
    /// uses `0`.
    pub port: u8,
}

/// Shared audio-thread resources handed back from `start_audio`.
///
/// The output stream is owned by a worker thread, not by this
/// struct, so `AudioHandles` is fully `Send`. The worker exits
/// when the controller channel closes (all `OutputController`
/// clones dropped).
pub struct AudioHandles<P: PluginExport> {
    /// Event queue the caller pushes MIDI into; drained by the audio
    /// callback each block.
    pub pending: Arc<ArrayQueue<MidiEvent>>,
    /// Editor-initiated custom-state (`load_state`) blobs. The UI thread
    /// pushes here instead of locking the plugin, and the audio callback
    /// drains and applies one at the block top under its per-block lock -
    /// so a slow `load_state` never stalls the callback's `try_lock` (the
    /// VST3 `StateLoadQueue` pattern; capacity 1, newest wins). Custom
    /// state only; params restore atomically through `set_param`.
    pub pending_state: Arc<ArrayQueue<Vec<u8>>>,
    /// Plugin instance shared between caller and audio callback.
    pub plugin: Arc<Mutex<P>>,
    /// Audio config (sample rate, channels) resolved from the device.
    pub sample_rate: f64,
    pub channels: usize,
    pub is_effect: bool,
    /// `Send + Sync` handle for toggling mic input and switching
    /// the input device. Backed by a worker thread that owns the
    /// (`!Send`) cpal input stream.
    pub input: InputController,
    /// `Send + Sync` handle for switching the output device.
    /// Backed by a worker thread that owns the (`!Send`) cpal
    /// output stream.
    pub output: OutputController,
    /// Shared transport state; UI thread toggles play/stop, audio
    /// thread advances position each block.
    pub transport: Transport,
    /// What the launch found about the devices, for the settings panel.
    pub(crate) launch: setup::Launch,
    /// Live-mode `--input-file` source (gated on the `playback`
    /// feature). Exposed so the runner can poll
    /// `playback.is_eof()` to drive clean shutdown when paired
    /// with `--output-file`.
    #[cfg(feature = "playback")]
    pub playback: Option<Arc<crate::playback::PlaybackSource>>,
    /// Live-mode `--sidechain-file` source (gated on the `playback`
    /// feature). Feeds the sidechain input bus independently of
    /// `playback`, so the main and sidechain buses run separate files.
    #[cfg(feature = "playback")]
    pub sidechain_playback: Option<Arc<crate::playback::PlaybackSource>>,
    /// Live-mode `--output-file` capture sink. The runner calls
    /// `take_capture().finalize()` on its way out so the WAV
    /// header gets the correct sample count.
    #[cfg(feature = "playback")]
    pub capture: Option<crate::playback::CaptureSink>,
    /// Why the output could not start at launch, when it could not. The
    /// handles still work, so a window can open for another device to be
    /// chosen; nothing plays until one starts.
    pub output_error: Option<String>,
}

// ---------------------------------------------------------------------------
// Channel routing
// ---------------------------------------------------------------------------

/// How the plugin's channels map onto the audio device's channels.
///
/// Stored encoded in an `AtomicUsize` on each controller (so the menu
/// can update it lock-free) and decoded in the audio callback. The
/// default, `Direct`, is the historical 1:1 mapping and is what every
/// non-multichannel-aware caller gets.
#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum ChannelRoute {
    /// Plugin channel N ↔ device channel N, across every channel.
    /// Preserves multichannel plugins; for a stereo plugin on a
    /// 4-out interface this is the same as `Stereo { base: 0 }`.
    Direct,
    /// Plugin channels 0 and 1 ↔ device channels `base` and `base+1`.
    /// Other device outputs are silenced; other device inputs ignored.
    Stereo { base: usize },
    /// A single device channel `base`. On output the plugin's first
    /// two channels fold down (sum) into it; on input it feeds both
    /// plugin input channels.
    Mono { base: usize },
}

impl ChannelRoute {
    /// Pack into the `usize` the controllers store. `Direct` is 0 so a
    /// freshly-zeroed atomic decodes to the default mapping.
    #[must_use]
    pub fn encode(self) -> usize {
        match self {
            ChannelRoute::Direct => 0,
            ChannelRoute::Stereo { base } => 1 + base * 2,
            ChannelRoute::Mono { base } => 2 + base * 2,
        }
    }

    /// Parse a CLI / env spec into a route. Channel numbers are
    /// 1-based (matching the menu labels): `direct` / `all` →
    /// [`Self::Direct`], `N` → [`Self::Mono`] on channel N, `N-M` →
    /// [`Self::Stereo`] pair starting at N (requires `M == N + 1`).
    /// Returns `None` for anything malformed.
    #[must_use]
    pub fn parse(spec: &str) -> Option<Self> {
        let s = spec.trim().to_ascii_lowercase();
        if s == "direct" || s == "all" {
            return Some(ChannelRoute::Direct);
        }
        if let Some((a, b)) = s.split_once('-') {
            let a: usize = a.trim().parse().ok()?;
            let b: usize = b.trim().parse().ok()?;
            if a >= 1 && b == a + 1 {
                return Some(ChannelRoute::Stereo { base: a - 1 });
            }
            return None;
        }
        let c: usize = s.parse().ok()?;
        (c >= 1).then(|| ChannelRoute::Mono { base: c - 1 })
    }

    /// The spec [`Self::parse`] reads back as this route.
    #[must_use]
    pub fn spec(self) -> String {
        match self {
            ChannelRoute::Direct => "direct".to_owned(),
            ChannelRoute::Stereo { base } => format!("{}-{}", base + 1, base + 2),
            ChannelRoute::Mono { base } => (base + 1).to_string(),
        }
    }

    /// How the settings panel names the route, in the Settings menu's words.
    #[must_use]
    pub fn label(self) -> String {
        match self {
            ChannelRoute::Direct => "All channels (direct)".to_owned(),
            ChannelRoute::Stereo { base } => format!("Channels {} & {}", base + 1, base + 2),
            ChannelRoute::Mono { base } => format!("Channel {} (mono)", base + 1),
        }
    }

    /// The first device channel the route reads or writes; `None` for the
    /// direct mapping, which fits any device.
    fn base(self) -> Option<usize> {
        match self {
            ChannelRoute::Direct => None,
            ChannelRoute::Stereo { base } | ChannelRoute::Mono { base } => Some(base),
        }
    }

    /// Inverse of [`Self::encode`].
    #[must_use]
    pub fn decode(v: usize) -> Self {
        if v == 0 {
            return ChannelRoute::Direct;
        }
        let k = v - 1;
        if k.is_multiple_of(2) {
            ChannelRoute::Stereo { base: k / 2 }
        } else {
            ChannelRoute::Mono { base: (k - 1) / 2 }
        }
    }
}

// ---------------------------------------------------------------------------
// Closing
// ---------------------------------------------------------------------------

/// How long the output takes to fade to silence when the standalone closes.
const CLOSE_FADE: std::time::Duration = std::time::Duration::from_millis(5);
/// Whole silent buffers the output writes after its fade before it stops.
/// A driver double-buffers, and some, ASIO among them, replay the buffers
/// they hold as they stop, so both must be silent by then.
const CLOSE_SILENT_BUFFERS: u8 = 2;
/// How long the output worker waits for the fade before stopping the
/// streams anyway, for a device that has stopped calling back. A device
/// running larger buffers than this allows for gets four of its buffers.
const CLOSE_FADE_WAIT: std::time::Duration = std::time::Duration::from_millis(250);
/// How long closing waits for the workers to stop their streams. Past it
/// the process exits with whatever is left, as it would without waiting.
const CLOSE_WAIT: std::time::Duration = std::time::Duration::from_secs(1);

/// The close request the output's audio callback answers by fading out.
#[derive(Default)]
struct CloseFade {
    requested: AtomicBool,
    /// Set by the callback once the device holds only silence.
    silent: AtomicBool,
    /// Frames in the buffers the callback is fading, which bound the wait.
    buffer_frames: AtomicUsize,
}

/// One output stream's fade to silence, owned by its audio callback.
struct FadeOut {
    shared: Arc<CloseFade>,
    gain: f32,
    step: f32,
    silent_buffers: u8,
}

impl FadeOut {
    fn new(shared: Arc<CloseFade>, sample_rate: f64) -> Self {
        shared.silent.store(false, Ordering::Release);
        // A stream opened after closing began never plays.
        let gain = if shared.requested.load(Ordering::Acquire) {
            0.0
        } else {
            1.0
        };
        #[allow(clippy::cast_possible_truncation)]
        let step = (1.0 / (CLOSE_FADE.as_secs_f64() * sample_rate).max(1.0)) as f32;
        Self {
            shared,
            gain,
            step,
            silent_buffers: 0,
        }
    }

    fn apply(&mut self, data: &mut [f32], channels: usize) {
        if !self.shared.requested.load(Ordering::Acquire) {
            return;
        }
        self.shared
            .buffer_frames
            .store(data.len() / channels.max(1), Ordering::Relaxed);
        if self.gain > 0.0 {
            for frame in data.chunks_mut(channels.max(1)) {
                self.gain = (self.gain - self.step).max(0.0);
                for sample in frame {
                    *sample *= self.gain;
                }
            }
            return;
        }
        data.fill(0.0);
        self.silent_buffers = self.silent_buffers.saturating_add(1);
        if self.silent_buffers >= CLOSE_SILENT_BUFFERS {
            self.shared.silent.store(true, Ordering::Release);
        }
    }
}

/// Fade the output to silence and stop every audio stream, input and
/// output, so that no driver is left playing what it last held. The
/// workers then exit, so nothing reopens a stream afterwards. Returns once
/// both have stopped, or after a short bound. Closing twice is harmless.
pub fn close_streams(input: &InputController, output: &OutputController) {
    output.fade.requested.store(true, Ordering::Release);
    let deadline = std::time::Instant::now() + CLOSE_WAIT;
    let wait = |acks: &mpsc::Receiver<()>| {
        let _ = acks.recv_timeout(deadline.saturating_duration_since(std::time::Instant::now()));
    };
    // The command queue is bounded, and full while a slow reopen works
    // through queued menu choices, so a blocking send could outlast the
    // bound.
    let (stopped, acks) = mpsc::channel();
    let mut close = OutputCmd::Close(stopped);
    loop {
        match output.cmd_tx.try_send(close) {
            Err(mpsc::TrySendError::Full(cmd)) if std::time::Instant::now() < deadline => {
                close = cmd;
                std::thread::sleep(std::time::Duration::from_millis(1));
            }
            _ => break,
        }
    }
    // The input stops after the output has faded, so the plugin never
    // hears its input cut while the output is still at full level.
    wait(&acks);
    let (stopped, acks) = mpsc::channel();
    let _ = input.cmd_tx.send(InputCmd::Close(stopped));
    wait(&acks);
}

// ---------------------------------------------------------------------------
// InputController
// ---------------------------------------------------------------------------

/// `Send + Sync` handle for managing mic input from the UI thread.
///
/// Cloneable; multiple holders can request toggles or device
/// switches. The actual `cpal::Stream` (`!Send` on macOS) lives on
/// a dedicated worker thread spawned by `start_audio`.
#[derive(Clone)]
pub struct InputController {
    /// Audio callback reads this every block to decide whether to
    /// drain the input ring or zero-fill. Worker thread updates it
    /// when a toggle completes (or fails).
    pub enabled: Arc<AtomicBool>,
    /// True if an input device is configured (default or
    /// CLI-named). When false, toggling on is a no-op.
    pub has_device: bool,
    /// Sender for input commands. Worker blocks on the matching
    /// receiver. Closing the channel exits the worker.
    cmd_tx: mpsc::Sender<InputCmd>,
    /// Worker mirrors the resolved device name here after each
    /// open so the menu can render a checkmark on the active
    /// device. `None` = default device or no device available.
    current_name: Arc<Mutex<Option<String>>>,
    /// How device input channels map onto the plugin's input bus,
    /// encoded per [`ChannelRoute`]. Read by the output callback when
    /// summing the input ring into the plugin bus; lets a stereo
    /// plugin pull from device inputs 3-4, or a mono source feed both
    /// plugin inputs. Shared with the callback.
    channel_route: Arc<AtomicUsize>,
    /// Asks the output worker to follow a picked input onto its
    /// interface's outputs.
    output_cmd: Arc<mpsc::SyncSender<OutputCmd>>,
    /// Whether an output device was chosen (by flag, saved choice or the
    /// menu), which stops the output following the input.
    output_chosen: Arc<AtomicBool>,
    /// Remembers the input channels chosen from the menu.
    pub(crate) settings: SettingsStore,
    /// The channels the open input stream records; set by the worker.
    opened_channels: Arc<AtomicUsize>,
}

enum InputCmd {
    SetEnabled(bool),
    SetDevice(Option<String>),
    /// Reopen an open stream at the current buffer size.
    Reopen,
    /// The output moved to another driver; follow it.
    DriverChanged,
    /// Stop the stream, answer, and exit.
    Close(mpsc::Sender<()>),
}

impl InputController {
    /// Toggle the input. Returns immediately; the worker thread
    /// processes the request asynchronously.
    pub fn set_enabled(&self, on: bool) {
        let _ = self.cmd_tx.send(InputCmd::SetEnabled(on));
    }

    /// Read the current state. Source of truth for the audio
    /// callback's zero-fill decision.
    #[must_use]
    pub fn is_enabled(&self) -> bool {
        self.enabled.load(Ordering::Relaxed)
    }

    /// Switch the input device by name. Pass `None` to fall back
    /// to the system default. If the input is currently enabled,
    /// the worker re-opens the stream against the new device; if
    /// disabled, the change takes effect on the next enable. The choice
    /// is remembered for the next launch. When no output device has been
    /// chosen and the input belongs to an interface with outputs, the
    /// output moves to that interface. On ASIO this chooses the
    /// interface, for output as well.
    pub fn set_device(&self, name: Option<String>) {
        if driver::on_asio() {
            let _ = self.output_cmd.send(OutputCmd::SetDevice(name));
            return;
        }
        if let Some(input) = &name
            && !self.output_chosen.load(Ordering::Relaxed)
        {
            let _ = self.output_cmd.send(OutputCmd::FollowInput(input.clone()));
        }
        let _ = self.cmd_tx.send(InputCmd::SetDevice(name));
    }

    /// Play through `name` and remember it, as [`setup::choose_input`]
    /// asks. On ASIO the interface opens first, for output too, and the
    /// input goes live only once it has: a failed switch would otherwise
    /// leave the interface it fell back to live.
    pub(crate) fn choose(&self, name: String) {
        if driver::on_asio() {
            let _ = self.output_cmd.send(OutputCmd::ChooseInterface(name));
            return;
        }
        self.set_device(Some(name));
        self.set_enabled(true);
    }

    /// How many channels the last opened input stream records.
    pub(crate) fn opened_channels(&self) -> usize {
        self.opened_channels.load(Ordering::Relaxed)
    }

    /// Currently-resolved input device name, or `None` if no
    /// device has been opened (or the worker resolved to the
    /// system default with no nameable device).
    #[must_use]
    pub fn current_name(&self) -> Option<String> {
        self.current_name.lock().ok().and_then(|g| g.clone())
    }

    /// Choose how device input channels feed the plugin's input bus.
    /// Takes effect on the next audio block, and is remembered for the next
    /// launch: a guitar on input 2 would otherwise be silent at every one.
    pub fn set_channel_route(&self, route: ChannelRoute) {
        self.channel_route.store(route.encode(), Ordering::Relaxed);
        self.settings
            .update(|s| s.input_channels = Some(route.spec()));
    }

    /// The current input channel routing.
    #[must_use]
    pub fn channel_route(&self) -> ChannelRoute {
        ChannelRoute::decode(self.channel_route.load(Ordering::Relaxed))
    }
}

// ---------------------------------------------------------------------------
// OutputController
// ---------------------------------------------------------------------------

/// `Send + Sync` handle for managing the output device from the
/// UI thread. Cloneable; clones share the worker.
#[derive(Clone)]
pub struct OutputController {
    /// Audio callback reads this every block to decide whether to
    /// zero-fill the output buffer (mute). Worker thread (and direct
    /// callers via `set_enabled`) update it.
    pub enabled: Arc<AtomicBool>,
    /// The worker's commands. Only the controllers hold it, so the worker
    /// exits once they are all dropped. Bounded, so the audio callback can
    /// queue a latency restart without allocating.
    cmd_tx: Arc<mpsc::SyncSender<OutputCmd>>,
    current_name: Arc<Mutex<Option<String>>>,
    /// How the plugin's output bus maps onto device output channels,
    /// encoded per [`ChannelRoute`]. Read by the output callback when
    /// writing the plugin bus into the device buffer; lets a stereo
    /// plugin drive device outputs 3-4, or fold down to a mono output.
    /// Shared with the callback.
    channel_route: Arc<AtomicUsize>,
    /// The plugin's active bus-layout index (into `P::bus_layouts()`). The
    /// worker updates it after a `SetLayout` switch; the Bus Layout menu
    /// reads it to mark the active entry. The index (not the channel totals)
    /// is the identity so two layouts sharing totals stay distinct.
    layout: Arc<AtomicUsize>,
    /// Buffer size the open streams run at, in frames; 0 when the device
    /// refused a fixed size and runs at its own.
    buffer_frames: Arc<AtomicU32>,
    fade: Arc<CloseFade>,
}

enum OutputCmd {
    /// A device the user chose; remembered, and it ends following the
    /// input. On ASIO, the interface.
    SetDevice(Option<String>),
    /// The ASIO interface the player chose as the input: open it,
    /// remember it, then let the input through.
    ChooseInterface(String),
    /// Move both streams to this driver, and remember it.
    SetDriver(AudioDriver),
    /// Move to the outputs of the interface this input belongs to, if it
    /// has any and no output has been chosen since the request was sent.
    FollowInput(String),
    /// Reopen both streams at this many frames.
    SetBufferSize(u32),
    /// The plugin reported a latency its processing state was not
    /// prepared for; reset it and reopen the output.
    RestartLatency,
    /// Switch the plugin to the declared bus layout at this index. The index
    /// is the layout's unambiguous identity - two layouts can share channel
    /// totals but split main/sidechain differently, so the worker resolves
    /// the widths from the index. It reopens the stream at those dimensions
    /// and `reset()`s the plugin so its per-channel DSP re-prepares, and
    /// keeps the device stream at a hardware-supported width (mapping the
    /// plugin output onto it), so an asymmetric layout or a width the device
    /// can't open natively still works.
    SetLayout { index: usize },
    /// The driver asked to be reset, which it does when its own settings
    /// change, such as a buffer size set in its control panel.
    Reset,
    /// Wait for the fade, stop the streams, answer, and exit.
    Close(mpsc::Sender<()>),
}

fn queue_latency_restart(
    requested_latency: u32,
    active_latency: &AtomicU32,
    restart_pending: &AtomicBool,
    commands: &Weak<mpsc::SyncSender<OutputCmd>>,
) {
    if requested_latency != active_latency.load(Ordering::Acquire)
        && !restart_pending.swap(true, Ordering::AcqRel)
        && commands
            .upgrade()
            .is_none_or(|commands| commands.try_send(OutputCmd::RestartLatency).is_err())
    {
        restart_pending.store(false, Ordering::Release);
    }
}

fn prepare_plugin<P: PluginExport>(
    plugin: &mut P,
    sample_rate: f64,
    max_frames: usize,
    reset: bool,
    active_latency: &AtomicU32,
    restart_pending: &AtomicBool,
) -> u32 {
    if reset {
        plugin.reset(&AudioConfig::new(sample_rate, max_frames));
    }
    let latency = plugin.latency();
    active_latency.store(latency, Ordering::Release);
    restart_pending.store(false, Ordering::Release);
    latency
}

impl OutputController {
    /// Mute / unmute the output. The cpal stream stays open either
    /// way - disabling just makes the audio callback zero-fill its
    /// buffer, so the plugin keeps processing (transport ticks,
    /// MIDI is consumed) while the speakers are silent.
    pub fn set_enabled(&self, on: bool) {
        self.enabled.store(on, Ordering::Relaxed);
    }

    /// Read the current mute state. Source of truth for the audio
    /// callback's zero-fill decision.
    #[must_use]
    pub fn is_enabled(&self) -> bool {
        self.enabled.load(Ordering::Relaxed)
    }

    /// Switch the output device by name. Pass `None` to fall back
    /// to the system default. Failure to open is logged but
    /// non-fatal - the previous stream remains running. A device that
    /// opens is remembered for the next launch.
    pub fn set_device(&self, name: Option<String>) {
        let _ = self.cmd_tx.send(OutputCmd::SetDevice(name));
    }

    /// Reopen the input and output streams at `frames` per buffer. A
    /// device that cannot run at that size is clamped to the nearest size
    /// it reports, and one that refuses the stream keeps its previous
    /// size, with a message either way. The accepted size is remembered
    /// for the next launch.
    pub fn set_buffer_size(&self, frames: u32) {
        let _ = self.cmd_tx.send(OutputCmd::SetBufferSize(frames));
    }

    /// The buffer size the streams run at, or `None` when the device
    /// runs at its own default.
    #[must_use]
    pub fn buffer_size(&self) -> Option<u32> {
        Some(self.buffer_frames.load(Ordering::Relaxed)).filter(|&n| n > 0)
    }

    /// Move both streams to `driver` (ASIO or WASAPI on Windows), onto the
    /// device last chosen for it or else its default, and remember the
    /// choice. A driver that fails to open leaves the streams where they
    /// were, with a message.
    pub fn set_driver(&self, driver: AudioDriver) {
        let _ = self.cmd_tx.send(OutputCmd::SetDriver(driver));
    }

    /// Switch the plugin to the declared bus layout at `index`. The plugin is
    /// `reset()` and re-prepared at that layout's dimensions; the device
    /// stream stays at a hardware-supported width and the plugin output is
    /// mapped onto it (so a mono layout plays through a stereo-only device).
    pub fn set_layout(&self, index: usize) {
        let _ = self.cmd_tx.send(OutputCmd::SetLayout { index });
    }

    /// The plugin's active bus-layout index (into `P::bus_layouts()`).
    #[must_use]
    pub fn current_index(&self) -> usize {
        self.layout.load(Ordering::Relaxed)
    }

    /// Currently-resolved output device name, or `None` if not
    /// resolvable.
    #[must_use]
    pub fn current_name(&self) -> Option<String> {
        self.current_name.lock().ok().and_then(|g| g.clone())
    }

    /// Choose how the plugin's output bus maps onto device output
    /// channels. Takes effect on the next audio block.
    pub fn set_channel_route(&self, route: ChannelRoute) {
        self.channel_route.store(route.encode(), Ordering::Relaxed);
    }

    /// The current output channel routing.
    #[must_use]
    pub fn channel_route(&self) -> ChannelRoute {
        ChannelRoute::decode(self.channel_route.load(Ordering::Relaxed))
    }
}

// ---------------------------------------------------------------------------
// Device enumeration helpers (used by `--list-devices` + menus).
// ---------------------------------------------------------------------------

/// Print available audio devices and return. Used by `--list-devices`.
pub fn list_devices() {
    println!("Audio devices");
    println!("Output:");
    let (default_out, outs) = enumerate_devices(true);
    for name in outs {
        let marker = if default_out.as_deref() == Some(name.as_str()) {
            " (default)"
        } else {
            ""
        };
        println!("  {name}{marker}");
    }
    println!("Input:");
    let (default_in, ins) = enumerate_devices(false);
    for name in ins {
        let marker = if default_in.as_deref() == Some(name.as_str()) {
            " (default)"
        } else {
            ""
        };
        println!("  {name}{marker}");
    }
    if driver::asio_built() {
        println!("ASIO interfaces (input and output):");
        for name in driver::asio_drivers() {
            println!("  {name}");
        }
    }
}

/// Snapshot of available output devices (`(default_name, all_names)`).
#[must_use]
pub fn list_output_devices() -> (Option<String>, Vec<String>) {
    enumerate_devices(true)
}

/// Snapshot of available input devices (`(default_name, all_names)`).
#[must_use]
pub fn list_input_devices() -> (Option<String>, Vec<String>) {
    enumerate_devices(false)
}

fn enumerate_devices(output: bool) -> (Option<String>, Vec<String>) {
    if driver::on_asio() {
        return (None, driver::asio_drivers());
    }
    let host = driver::host();
    let default_name = if output {
        host.default_output_device()
    } else {
        host.default_input_device()
    }
    .and_then(|d| device_label(&d));
    let names = devices(&host, output)
        .filter_map(|d| device_label(&d))
        .collect();
    (default_name, names)
}

/// An input as the settings panel needs to know it.
#[derive(Clone, Debug)]
pub(crate) struct InputDetail {
    pub name: String,
    pub built_in_microphone: bool,
}

/// Every input and whether it is the computer's own microphone, from what
/// the host reports without opening the device: ALSA would open each one.
/// ASIO drivers are named only: listing more would load each.
fn input_details() -> Vec<InputDetail> {
    if driver::on_asio() {
        return driver::asio_drivers()
            .into_iter()
            .map(|name| InputDetail {
                name,
                built_in_microphone: false,
            })
            .collect();
    }
    let host = driver::host();
    let built_in = crate::microphone::BuiltIn::find();
    devices(&host, false)
        .filter_map(|device| {
            let name = device_label(&device)?;
            Some(InputDetail {
                built_in_microphone: built_in.is(&device, &name),
                name,
            })
        })
        .collect()
}

/// The host's devices, listed as they are asked for: cpal loads each ASIO
/// driver in turn to list it, so a search that stops early loads fewer.
fn devices(host: &cpal::Host, output: bool) -> Box<dyn Iterator<Item = cpal::Device>> {
    let found = if output {
        host.output_devices()
            .map(|d| Box::new(d) as Box<dyn Iterator<Item = cpal::Device>>)
    } else {
        host.input_devices()
            .map(|d| Box::new(d) as Box<dyn Iterator<Item = cpal::Device>>)
    };
    found.unwrap_or_else(|_| Box::new(std::iter::empty()))
}

/// The name menus, flags and saved settings know a device by.
///
/// WASAPI names an endpoint by its kind ("Speakers", "Microphone"), which
/// every interface shares, so on Windows the label carries the interface
/// in brackets as the Sound control panel does: "Speakers (UMC202HD
/// 192k)".
fn device_label(device: &cpal::Device) -> Option<String> {
    let description = device.description().ok()?;
    let name = description.name();
    #[cfg(target_os = "windows")]
    if let Some(interface) = description.driver()
        && interface != name
    {
        return Some(format!("{name} ({interface})"));
    }
    Some(name.to_string())
}

/// Background-refreshed cache of cpal device names.
///
/// `CoreAudio` enumeration is slow - hundreds of milliseconds with a
/// few devices connected - and the macOS menu used to run it
/// synchronously on the main thread every time a device submenu
/// opened, which made the submenu visibly lag. The menu now reads
/// cached names (instant) and fires an off-thread refresh so the
/// *next* open reflects hot-plugged or removed devices. Cloneable;
/// all clones share one cache.
#[derive(Clone)]
pub struct DeviceCache {
    inner: Arc<Mutex<DeviceNames>>,
    refreshing: Arc<AtomicBool>,
}

impl Default for DeviceCache {
    fn default() -> Self {
        Self::new()
    }
}

#[derive(Default)]
struct DeviceNames {
    outputs: Vec<String>,
    inputs: Vec<InputDetail>,
    /// False until the first enumeration lands. Distinguishes "not
    /// warmed yet" from "warmed and genuinely empty" so a machine with
    /// no inputs doesn't re-enumerate on every read.
    warmed: bool,
}

impl DeviceCache {
    /// Create the cache and warm it on a background thread.
    #[must_use]
    pub fn new() -> Self {
        let cache = Self {
            inner: Arc::new(Mutex::new(DeviceNames::default())),
            refreshing: Arc::new(AtomicBool::new(false)),
        };
        cache.refresh_async();
        cache
    }

    /// Cached output device names. Blocks once on a cold read (a menu
    /// opened before the warm-up finished) so the list is never
    /// spuriously empty.
    #[must_use]
    pub fn outputs(&self) -> Vec<String> {
        self.ensure_warm();
        self.inner
            .lock()
            .map(|g| g.outputs.clone())
            .unwrap_or_default()
    }

    /// Cached input device names. Same cold-read guarantee as
    /// [`Self::outputs`].
    #[must_use]
    pub fn inputs(&self) -> Vec<String> {
        self.ensure_warm();
        self.inner
            .lock()
            .map(|g| g.inputs.iter().map(|input| input.name.clone()).collect())
            .unwrap_or_default()
    }

    /// The inputs as last listed, without waiting for a first listing.
    pub(crate) fn peek_inputs(&self) -> Vec<InputDetail> {
        self.inner
            .lock()
            .map(|g| g.inputs.clone())
            .unwrap_or_default()
    }

    /// The outputs as last listed, without waiting for a first listing.
    pub(crate) fn peek_outputs(&self) -> Vec<String> {
        self.inner
            .lock()
            .map(|g| g.outputs.clone())
            .unwrap_or_default()
    }

    fn ensure_warm(&self) {
        // Check (and release the lock) before the slow enumeration so
        // we never hold the mutex across a CoreAudio round-trip.
        match self.inner.lock() {
            Ok(g) if g.warmed => return,
            Ok(_) => {}
            Err(_) => return,
        }
        let (_, outputs) = enumerate_devices(true);
        let inputs = input_details();
        if let Ok(mut names) = self.inner.lock() {
            names.outputs = outputs;
            names.inputs = inputs;
            names.warmed = true;
        }
    }

    /// Re-enumerate both device lists on a background thread, storing
    /// the result for the next read. No-op while a refresh is already
    /// in flight, so rapid menu reopens don't pile up threads.
    pub fn refresh_async(&self) {
        if self.refreshing.swap(true, Ordering::AcqRel) {
            return;
        }
        let inner = Arc::clone(&self.inner);
        let refreshing = Arc::clone(&self.refreshing);
        std::thread::spawn(move || {
            let (_, outputs) = enumerate_devices(true);
            let inputs = input_details();
            if let Ok(mut names) = inner.lock() {
                names.outputs = outputs;
                names.inputs = inputs;
                names.warmed = true;
            }
            refreshing.store(false, Ordering::Release);
        });
    }
}

// ---------------------------------------------------------------------------
// start_audio
// ---------------------------------------------------------------------------

/// Resolve devices, instantiate the plugin, spawn input + output
/// worker threads, return the handles the caller needs to push MIDI
/// and reach the workers.
///
/// # Errors
///
/// Returns an error if the requested input/output device can't be
/// found (or no default exists), the device's default stream config
/// can't be queried, or any of the cpal stream-build calls fail.
///
/// # Panics
///
/// Panics if the plugin's mutex is poisoned while it is being set up.
#[allow(clippy::too_many_lines)]
pub fn start_audio<P: PluginExport>(opts: &Options) -> Result<AudioHandles<P>, BoxErr> {
    let is_effect = P::info().category == PluginCategory::Effect;
    let settings = SettingsStore::open(settings::path_for(P::info().vendor, P::info().name));
    let saved = settings.saved();

    driver::set_active(settings::launch_driver(
        opts.driver,
        saved.driver,
        driver::asio_installed,
    ));
    // Resolve initial output device synchronously so we can pull
    // its default config (sample rate, channels) before spawning
    // the worker, which opens it.
    let LaunchDevices {
        input: input_device,
        output: initial_output,
        input_pick,
        output_missing,
    } = launch_devices(opts, &saved, is_effect)?;
    let launch = setup::Launch {
        input_named: opts.input_device.is_some()
            || (driver::on_asio() && opts.output_device.is_some()),
        input_missing: match &input_pick {
            InputPick::Missing(name) => Some(name.clone()),
            _ => None,
        },
        output_missing,
    };
    let output_chosen = Arc::new(AtomicBool::new(
        opts.output_device.is_some() || saved.output_device.is_some(),
    ));

    // A device that will not report its config will not start either; a
    // stand-in shape lets the launch go on to report it as refused.
    let default_config = initial_output.default_output_config().unwrap_or_else(|e| {
        eprintln!("could not query the audio output's config: {e}");
        cpal::SupportedStreamConfig::new(
            2,
            cpal::SAMPLE_RATE_48K,
            cpal::SupportedBufferSize::Unknown,
            cpal::SampleFormat::F32,
        )
    });
    let launch_output_name = device_label(&initial_output);

    // The plugin runs a declared bus layout; the device stream tries to
    // match its output width but falls back to the device default (the
    // plugin output then maps onto whatever channels the device gives).
    let layout_index = selected_layout_index::<P>(opts);
    let (num_in, num_out, num_main_in) = layout_at_index::<P>(layout_index);
    let requested_channels = u16::try_from(num_out).ok().filter(|&c| c > 0);
    let buffer_request = settings::launch_buffer_size(opts.buffer_size, saved.buffer_size);
    let config = resolve_config(
        &initial_output,
        &default_config,
        opts,
        requested_channels,
        buffer_request,
    );
    let sample_rate = f64::from(config.sample_rate);
    let channels = config.channels as usize;
    let buffer_frames = Arc::new(AtomicU32::new(buffer_request));
    let stream_rate = Arc::new(AtomicU32::new(config.sample_rate));

    // A chosen input that is not connected stays the worker's device, so
    // turning the input on opens it if it is back and otherwise says it is
    // not connected, rather than opening the system default.
    let input_label = match &input_pick {
        InputPick::Missing(name) if !driver::on_asio() => Some(name.clone()),
        _ => input_device.as_ref().and_then(device_label),
    };

    // Capacity 256: covers a generous MIDI burst within a single
    // audio callback period. ArrayQueue is lock-free MPMC - the MIDI
    // input thread pushes, the audio thread drains, neither blocks.
    // On overflow the producer drops the oldest event (see midi.rs).
    let pending: Arc<ArrayQueue<MidiEvent>> = Arc::new(ArrayQueue::new(256));
    // Capacity 1, newest-wins: only the most recent editor state-load matters
    // if several arrive before the audio thread drains one.
    let pending_state: Arc<ArrayQueue<Vec<u8>>> = Arc::new(ArrayQueue::new(1));
    let initial_max_frames = max_block_frames(
        fit_buffer_size(config.buffer_size, default_config.buffer_size()),
        default_config.buffer_size(),
    );
    let plugin = Arc::new(Mutex::new({
        let mut p = P::create();
        p.init();
        p.reset(&AudioConfig::new(sample_rate, initial_max_frames));
        // Apply `--state <path>` BEFORE snapping smoothers so the
        // first audio block sees the restored values, not defaults
        // ramping toward them.
        if let Some(path) = opts.state_path.as_deref() {
            crate::state::load_into(&mut p, path);
        }
        // `--preset` layers on top of `--state` (both pre-snap so
        // the first block sees restored values), resolved through
        // the same store `--list-presets` uses.
        if let Some(sel) = opts.preset.as_deref() {
            crate::presets::apply_on_launch::<P>(opts.presets_dir.as_deref(), &mut p, sel);
        }
        p.params().snap_smoothers();
        p
    }));

    let (output_cmd_tx, output_cmd_rx) = mpsc::sync_channel::<OutputCmd>(8);
    let output_cmd_tx = Arc::new(output_cmd_tx);
    let input_setup = setup_input_pipeline(
        input_label.as_deref(),
        &input_pick,
        opts,
        is_effect,
        channels,
        sample_rate,
        InputLinks {
            buffer_frames: Arc::clone(&buffer_frames),
            sample_rate: Arc::clone(&stream_rate),
            output_cmd: Arc::clone(&output_cmd_tx),
            output_chosen: Arc::clone(&output_chosen),
            settings: settings.clone(),
        },
    );
    let input_ring = input_setup.ring;
    let input_enabled = input_setup.enabled;
    let input_ring_width = input_setup.ring_width;
    let input_controller = input_setup.controller;
    let flagged = opts.input_channels.as_deref().filter(|spec| {
        let valid = ChannelRoute::parse(spec).is_some();
        if !valid {
            eprintln!(
                "--input-channels: ignoring invalid '{spec}' \
                 (expected 'direct', a channel like '3', or a pair like '3-4')"
            );
        }
        valid
    });
    // A missing device is judged when it returns, by the output width the
    // ring carries.
    let device_channels = match (&input_pick, &input_device) {
        (InputPick::Missing(_), _) | (_, None) => channels,
        (_, Some(device)) => device
            .default_input_config()
            .map_or(0, |config| usize::from(config.channels()))
            .min(channels),
    };
    let route = launch_input_route(flagged, saved.input_channels.as_deref(), device_channels);
    input_controller
        .channel_route
        .store(route.encode(), Ordering::Relaxed);

    let transport = Transport::new(opts.bpm.unwrap_or(120.0), sample_rate);

    let output_current_name = Arc::new(Mutex::new(None));
    let (open_result_tx, open_result_rx) = mpsc::channel::<Result<(), String>>();

    // Output defaults to enabled - the user launched standalone to
    // hear the plugin. `--output-enabled off` (or the config file)
    // can flip the launch state.
    let output_enabled = Arc::new(AtomicBool::new(opts.output_enabled.unwrap_or(true)));

    let output_channel_route = Arc::new(AtomicUsize::new(0));
    // Shared active bus-layout index. Seeded with the launch selection; the
    // worker updates it on a `SetLayout` switch. The index (not the channel
    // totals) is the identity so two layouts sharing totals stay distinct.
    let output_layout_shared = Arc::new(AtomicUsize::new(layout_index));
    let active_latency = Arc::new(AtomicU32::new(
        plugin
            .lock()
            .expect("plugin mutex poisoned after initial reset")
            .latency(),
    ));
    let latency_restart_pending = Arc::new(AtomicBool::new(false));
    let fade = Arc::new(CloseFade::default());
    let output_controller = OutputController {
        enabled: Arc::clone(&output_enabled),
        cmd_tx: output_cmd_tx,
        current_name: Arc::clone(&output_current_name),
        channel_route: Arc::clone(&output_channel_route),
        layout: Arc::clone(&output_layout_shared),
        buffer_frames: Arc::clone(&buffer_frames),
        fade: Arc::clone(&fade),
    };
    // Apply `--output-channels` (and its env var) once at launch. The
    // native menus override this live; on Linux (no menu) the CLI is
    // the only way to pick channels. Input is applied below, once its
    // controller exists.
    if let Some(spec) = opts.output_channels.as_deref() {
        match ChannelRoute::parse(spec) {
            Some(route) => output_controller.set_channel_route(route),
            None => eprintln!(
                "--output-channels: ignoring invalid '{spec}' \
                 (expected 'direct', a channel like '3', or a pair like '3-4')"
            ),
        }
    }

    // Decode `--input-file` (if set) once at startup against the
    // resolved device sample-rate / channel-count. Hard error on
    // unreadable / unparseable file - we fail noisily here rather
    // than letting the audio worker silently emit zeros.
    #[cfg(feature = "playback")]
    let playback = match &opts.input_file {
        // `num_main_in > 0`: a layout with no main input bus has nowhere
        // to route the file, and decoding to a zero width divides by zero
        // in `PlaybackSource::from_wav`.
        Some(path) if is_effect && num_main_in > 0 => {
            // Decode to the plugin's MAIN-bus width, not the device
            // stream width: the callback mixes this into
            // `input_bufs[..num_main_in]`, and a main bus wider than the
            // device (e.g. a 5.1 layout through a stereo interface) would
            // otherwise truncate the file to the device channel count and
            // feed silence to the plugin's extra channels. The offline
            // path pins the same split.
            let src = crate::playback::PlaybackSource::from_wav(path, sample_rate, num_main_in)?;
            vlog!(
                "Playback: {} → input bus (one-shot, sums with mic when enabled)",
                path.display()
            );
            Some(Arc::new(src))
        }
        Some(_) => {
            // A non-effect (no input bus) or a layout with no main input
            // has nowhere to feed the file; warn and ignore rather than
            // failing.
            eprintln!("--input-file ignored: plugin has no main input bus");
            None
        }
        None => None,
    };

    // Decode `--sidechain-file` against the sidechain bus width. A
    // plugin with no sidechain bus (or a non-effect) has nowhere to
    // route it, so warn and ignore rather than fail.
    #[cfg(feature = "playback")]
    let sidechain_playback = {
        let sc_width = num_in.saturating_sub(num_main_in);
        match &opts.sidechain_file {
            Some(path) if is_effect && sc_width > 0 => {
                let src = crate::playback::PlaybackSource::from_wav(path, sample_rate, sc_width)?;
                vlog!("Sidechain: {} → sidechain bus (one-shot)", path.display());
                Some(Arc::new(src))
            }
            Some(_) => {
                eprintln!("--sidechain-file ignored: plugin has no sidechain input bus");
                None
            }
            None => None,
        }
    };

    // `--output-file` capture sink. Created here so any
    // filesystem error (missing parent dir, unwritable target,
    // …) propagates back to the runner before audio starts.
    #[cfg(feature = "playback")]
    let capture = match &opts.output_file {
        Some(path) => {
            let sink = crate::playback::CaptureSink::create(path, sample_rate, channels)?;
            vlog!(
                "Capture: {} ({} Hz, {} ch, f32) - pre-mute output",
                path.display(),
                sample_rate,
                channels,
            );
            Some(sink)
        }
        None => None,
    };

    let res = OutputResources {
        plugin: Arc::clone(&plugin),
        pending: Arc::clone(&pending),
        pending_state: Arc::clone(&pending_state),
        input_ring: Arc::clone(&input_ring),
        input_enabled: Arc::clone(&input_enabled),
        ring_width: Arc::clone(&input_ring_width),
        output_enabled: Arc::clone(&output_enabled),
        transport: transport.clone(),
        current_name: Arc::clone(&output_current_name),
        input_channel_route: Arc::clone(&input_controller.channel_route),
        output_channel_route: Arc::clone(&output_channel_route),
        layout: Arc::clone(&output_layout_shared),
        promised_max_frames: AtomicUsize::new(initial_max_frames),
        promised_rate: AtomicU32::new(config.sample_rate),
        active_latency,
        latency_restart_pending,
        buffer_frames: Arc::clone(&buffer_frames),
        sample_rate: stream_rate,
        reset_pending: Arc::new(AtomicBool::new(false)),
        fade,
        commands: Arc::downgrade(&output_controller.cmd_tx),
        output_chosen,
        input_cmd: input_controller.cmd_tx.clone(),
        settings,
        #[cfg(feature = "playback")]
        playback: playback.clone(),
        #[cfg(feature = "playback")]
        sidechain_playback: sidechain_playback.clone(),
        #[cfg(feature = "playback")]
        capture: capture.as_ref().map(super::playback::CaptureSink::pusher),
    };

    let worker = OutputWorker {
        res,
        config,
        num_in,
        num_out,
        num_main_in,
        is_effect,
        device: initial_output,
        streams: None,
    };
    std::thread::Builder::new()
        .name("truce-standalone-output".into())
        .spawn(move || worker.run(&output_cmd_rx, &open_result_tx))
        .map_err(|e| format!("could not spawn output worker: {e}"))?;

    // Wait for the worker's first open, so the launch knows whether the
    // output started before the editor opens.
    let output_error = match open_result_rx.recv() {
        Ok(Ok(())) => None,
        // A device that is there but refuses to start, held by another
        // program or in a bad state, is reported as unavailable rather than
        // ending the launch, so another can be chosen.
        Ok(Err(e)) => {
            setup::report_refused_output(Some(
                launch_output_name.unwrap_or_else(|| "The audio output".to_owned()),
            ));
            Some(e)
        }
        Err(e) => return Err(format!("output worker exited before reporting: {e}").into()),
    };

    if !output_enabled.load(Ordering::Relaxed) {
        vlog!(
            "Output: muted at launch - toggle from the Settings menu or \
             pass --output-enabled on"
        );
    }

    Ok(AudioHandles {
        pending,
        pending_state,
        plugin,
        sample_rate,
        channels,
        is_effect,
        input: input_controller,
        output: output_controller,
        transport,
        launch,
        #[cfg(feature = "playback")]
        playback,
        #[cfg(feature = "playback")]
        sidechain_playback,
        #[cfg(feature = "playback")]
        capture,
        output_error,
    })
}

/// Result of driving a parameter-dependent latency change through the
/// standalone adapter's callback-to-worker lifecycle.
#[doc(hidden)]
pub struct DynamicLatencyTransition {
    pub active_before: u32,
    pub requested_after_process: u32,
    pub active_after_restart: u32,
    pub restart_queued: bool,
}

/// Adapter smoke path for plugins whose latency follows a parameter.
///
/// This processes a real block after `change`, observes the request through
/// the same bounded callback handoff as the cpal path, then runs the output
/// worker's reset operation with the current parameter store.
#[doc(hidden)]
pub fn dynamic_latency_transition<P, F>(change: F) -> DynamicLatencyTransition
where
    P: PluginExport,
    F: FnOnce(&P::Params),
{
    const SAMPLE_RATE: f64 = 44_100.;
    const FRAMES: usize = 64;

    let mut plugin = P::create();
    plugin.init();
    plugin.reset(&AudioConfig::new(SAMPLE_RATE, FRAMES));
    let active_before = plugin.latency();
    change(plugin.params());

    let layout = P::bus_layouts().into_iter().next().unwrap_or_default();
    let input = vec![vec![P::Sample::default(); FRAMES]; layout.total_input_channels() as usize];
    let input_refs: Vec<&[P::Sample]> = input.iter().map(Vec::as_slice).collect();
    let mut output =
        vec![vec![P::Sample::default(); FRAMES]; layout.total_output_channels() as usize];
    let mut output_refs: Vec<&mut [P::Sample]> =
        output.iter_mut().map(Vec::as_mut_slice).collect();
    let mut buffer = truce_core::buffer::AudioBuffer::from_slices_checked(
        &input_refs,
        &mut output_refs,
        FRAMES,
    );
    let events = EventList::with_capacity(0);
    let transport = truce_core::events::TransportInfo::default();
    let mut output_events = EventList::with_capacity(0);
    let mut context = truce_core::process::ProcessContext::new(
        &transport,
        SAMPLE_RATE,
        FRAMES,
        &mut output_events,
    );
    plugin.process(&mut buffer, &events, &mut context);
    let requested_after_process = plugin.latency();

    let plugin = Arc::new(Mutex::new(plugin));
    let active_latency = Arc::new(AtomicU32::new(active_before));
    let restart_pending = Arc::new(AtomicBool::new(false));
    let (restart_tx, restart_rx) = mpsc::sync_channel(1);
    let restart_tx = Arc::new(restart_tx);
    queue_latency_restart(
        requested_after_process,
        &active_latency,
        &restart_pending,
        &Arc::downgrade(&restart_tx),
    );
    let worker_plugin = Arc::clone(&plugin);
    let worker_latency = Arc::clone(&active_latency);
    let worker_pending = Arc::clone(&restart_pending);
    let (restart_queued, active_after_restart) = std::thread::spawn(move || {
        let restart_queued = matches!(restart_rx.try_recv(), Ok(OutputCmd::RestartLatency));
        let latency = prepare_plugin(
            &mut *worker_plugin
                .lock()
                .expect("plugin mutex poisoned in latency smoke worker"),
            SAMPLE_RATE,
            FRAMES,
            restart_queued,
            &worker_latency,
            &worker_pending,
        );
        (restart_queued, latency)
    })
    .join()
    .expect("latency smoke worker panicked");

    DynamicLatencyTransition {
        active_before,
        requested_after_process,
        active_after_restart,
        restart_queued,
    }
}

/// State produced by [`setup_input_pipeline`] that `start_audio`
/// needs to wire into the output worker (`ring` / `enabled` go into
/// `OutputResources`) and the public handles (`controller`).
struct InputSetup {
    controller: InputController,
    ring: Arc<InputRing>,
    enabled: Arc<AtomicBool>,
    /// Ring frame width (= the live output stream's channel count). The
    /// output worker updates it on a `SetLayout` switch; the input
    /// producer reads it so its normalization tracks a runtime width
    /// change instead of freezing at the launch width.
    ring_width: Arc<AtomicUsize>,
}

/// What the input side shares with the rest of the host.
struct InputLinks {
    buffer_frames: Arc<AtomicU32>,
    sample_rate: Arc<AtomicU32>,
    output_cmd: Arc<mpsc::SyncSender<OutputCmd>>,
    output_chosen: Arc<AtomicBool>,
    settings: SettingsStore,
}

/// The devices a launch opens: the input (effects only) and the output.
/// On ASIO the input and output are one interface, named by a flag, else
/// the saved interface, else the first installed driver that loads; when
/// none loads, the launch runs on WASAPI.
fn launch_devices(
    opts: &Options,
    saved: &settings::Settings,
    is_effect: bool,
) -> Result<LaunchDevices, String> {
    if driver::on_asio() {
        let host = driver::host();
        let (interface, input_pick) = launch_asio_interface(&host, opts, saved);
        if let Some(interface) = interface {
            let input = (is_effect && interface.supports_input()).then(|| interface.clone());
            return Ok(LaunchDevices {
                input,
                output: interface,
                input_pick,
                output_missing: None,
            });
        }
        eprintln!("no ASIO driver could be opened; using Windows (WASAPI)");
        driver::set_active(AudioDriver::Wasapi);
    }
    let host = driver::host();
    let (input, input_pick) = if is_effect {
        launch_input(&host, opts, saved)
    } else {
        (None, InputPick::Default)
    };
    let chosen_input = input.as_ref().filter(|_| input_pick == InputPick::Chosen);
    let (output, output_missing) = launch_output(&host, opts, saved, chosen_input)?;
    Ok(LaunchDevices {
        input,
        output,
        input_pick,
        output_missing,
    })
}

/// The input channels a launch feeds the plugin from: a flag's for this
/// launch, else the saved choice read as `--input-channels` reads it, else
/// channel 1 alone, since a guitar is one channel. A saved channel the
/// device does not have would leave the input silent with no word, so it
/// gives way to channel 1 and stays saved for a device that has it.
fn launch_input_route(
    flagged: Option<&str>,
    saved: Option<&str>,
    device_channels: usize,
) -> ChannelRoute {
    if let Some(route) = flagged.and_then(ChannelRoute::parse) {
        return route;
    }
    saved
        .and_then(ChannelRoute::parse)
        .filter(|route| route.base().is_none_or(|base| base < device_channels))
        .unwrap_or(ChannelRoute::Mono { base: 0 })
}

struct LaunchDevices {
    input: Option<cpal::Device>,
    output: cpal::Device,
    input_pick: InputPick,
    /// The saved output, when it was not connected and the default plays.
    output_missing: Option<String>,
}

/// How a launch came by its input device. Only a device the player chose
/// may start live: the system default is often a built-in microphone
/// beside the built-in speakers, and an amplifier between them howls.
#[derive(Clone, Debug, PartialEq, Eq)]
enum InputPick {
    /// Named by a flag or the saved choice, and connected.
    Chosen,
    /// Named by a flag or the saved choice, and not connected.
    Missing(String),
    /// Nothing was chosen.
    Default,
}

fn launch_asio_interface(
    host: &cpal::Host,
    opts: &Options,
    saved: &settings::Settings,
) -> (Option<cpal::Device>, InputPick) {
    let flagged = opts.output_device.as_ref().or(opts.input_device.as_ref());
    let named = flagged.or(saved.asio_device.as_ref());
    let mut pick = InputPick::Default;
    if let Some(name) = named {
        let found = if flagged.is_some() {
            find_flagged_device(host, name, true)
        } else {
            find_device(host, name, true)
        };
        if let Some(interface) = found {
            return (Some(interface), InputPick::Chosen);
        }
        eprintln!("the ASIO interface '{name}' is not available; trying the others installed");
        pick = InputPick::Missing(name.clone());
    }
    // The first own driver that loads ends the search, which loads each
    // driver listed before it.
    let mut generic = None;
    for interface in devices(host, true) {
        if device_label(&interface).is_some_and(|label| !driver::is_generic(&label)) {
            return (Some(interface), pick);
        }
        generic.get_or_insert(interface);
    }
    (generic, pick)
}

/// The installed ASIO interfaces whose drivers load, an interface's own
/// drivers before the generic ones.
fn asio_interfaces(host: &cpal::Host) -> Vec<cpal::Device> {
    let mut interfaces: Vec<cpal::Device> = devices(host, true).collect();
    interfaces.sort_by_key(|device| device_label(device).is_none_or(|l| driver::is_generic(&l)));
    interfaces
}

/// The input device a launch opens, and how it came by it. A saved device
/// that is absent today opens nothing and stays saved for when it returns.
fn launch_input(
    host: &cpal::Host,
    opts: &Options,
    saved: &settings::Settings,
) -> (Option<cpal::Device>, InputPick) {
    let found = match (&opts.input_device, &saved.input_device) {
        (Some(name), _) => (name, find_flagged_device(host, name, false)),
        (None, Some(name)) => (name, find_device(host, name, false)),
        (None, None) => return (host.default_input_device(), InputPick::Default),
    };
    match found {
        (_, Some(device)) => (Some(device), InputPick::Chosen),
        (name, None) => {
            eprintln!("the input device '{name}' is not available");
            (None, InputPick::Missing(name.clone()))
        }
    }
}

/// The output device a launch opens, and the saved output when it was not
/// connected. A flag must match a device; a saved choice falls back to the
/// default when its device is absent. With neither, a chosen input that
/// belongs to an interface with outputs takes the output along, so both
/// streams run on the interface's clock.
fn launch_output(
    host: &cpal::Host,
    opts: &Options,
    saved: &settings::Settings,
    chosen_input: Option<&cpal::Device>,
) -> Result<(cpal::Device, Option<String>), String> {
    if let Some(name) = &opts.output_device {
        let device = find_flagged_device(host, name, true).ok_or_else(|| {
            format!(
                "no output device matching '{name}'. \
                 Run with --list-devices to see available outputs."
            )
        })?;
        return Ok((device, None));
    }
    let mut missing = None;
    if let Some(name) = &saved.output_device {
        if let Some(device) = find_device(host, name, true) {
            return Ok((device, None));
        }
        eprintln!("the saved output device '{name}' is not available; using the system default");
        missing = Some(name.clone());
    } else if let Some(device) = chosen_input
        .and_then(|input| companion_output(host, input))
        .and_then(|label| find_device(host, &label, true))
    {
        return Ok((device, None));
    }
    let device = host.default_output_device().ok_or_else(|| {
        "no default audio output device. \
         Plug in or enable an output, then retry."
            .to_string()
    })?;
    Ok((device, missing))
}

/// Allocate the input ring + control channels, and (for effects) spawn
/// the input worker thread on `input_name`. Turns the input on when the
/// launch asked for it and, where the application's default asked, the
/// device was chosen.
fn setup_input_pipeline(
    input_name: Option<&str>,
    pick: &InputPick,
    opts: &Options,
    is_effect: bool,
    channels: usize,
    sample_rate: f64,
    links: InputLinks,
) -> InputSetup {
    // Storage for ~100 ms of capture frames: room for a capture device
    // that delivers much larger blocks than the output renders. The
    // render side keeps what is actually queued far shorter (see
    // `RingReader`). Frame width = the output stream's channel count;
    // the producer normalizes the capture device's native width onto it.
    let input_ring = Arc::new(InputRing::new(sample_count_usize(sample_rate) / 10));
    // Seeded with the launch output width; the output worker restamps it
    // through `open_output_stream` on every (re)open, so a `SetLayout`
    // switch propagates the new width to the input producer.
    let ring_width = Arc::new(AtomicUsize::new(channels));

    if is_effect && input_name.is_none() {
        eprintln!("Note: no input device found - input-enable will be a no-op.");
    }

    let input_enabled = Arc::new(AtomicBool::new(false));
    let has_input_device = input_name.is_some();
    let (input_cmd_tx, input_cmd_rx) = mpsc::channel::<InputCmd>();
    let input_current_name = Arc::new(Mutex::new(input_name.map(str::to_owned)));

    let opened_channels = Arc::new(AtomicUsize::new(0));
    let controller = InputController {
        enabled: Arc::clone(&input_enabled),
        has_device: has_input_device,
        cmd_tx: input_cmd_tx,
        current_name: Arc::clone(&input_current_name),
        channel_route: Arc::new(AtomicUsize::new(0)),
        output_cmd: links.output_cmd,
        output_chosen: links.output_chosen,
        settings: links.settings.clone(),
        opened_channels: Arc::clone(&opened_channels),
    };

    if is_effect {
        let worker = InputWorker {
            ring: Arc::clone(&input_ring),
            ring_width: Arc::clone(&ring_width),
            sample_rate: links.sample_rate,
            enabled: Arc::clone(&input_enabled),
            current_name: Arc::clone(&input_current_name),
            buffer_frames: links.buffer_frames,
            settings: links.settings,
            opened_channels,
        };
        let device_name = input_name.map(str::to_owned);
        std::thread::Builder::new()
            .name("truce-standalone-input".into())
            .spawn(move || worker.run(&input_cmd_rx, device_name))
            .ok();
    }

    let asked = is_effect && opts.input_enabled.unwrap_or(false);
    let want_input_enabled = asked && (!opts.input_needs_choice || *pick == InputPick::Chosen);
    if want_input_enabled {
        controller.set_enabled(true);
    }

    if is_effect {
        vlog!(
            "Input:  {} ({})",
            input_name.unwrap_or("(none)"),
            if want_input_enabled {
                "enabled"
            } else {
                {
                    #[cfg(target_os = "macos")]
                    {
                        "disabled - press Cmd+I in the window or pass --input-enabled on"
                    }
                    #[cfg(not(target_os = "macos"))]
                    {
                        "disabled - press Ctrl+I in the window or pass --input-enabled on"
                    }
                }
            }
        );
    }

    InputSetup {
        controller,
        ring: input_ring,
        enabled: input_enabled,
        ring_width,
    }
}

// ---------------------------------------------------------------------------
// Output worker
// ---------------------------------------------------------------------------

/// Resources the output callback needs. Held by the worker; new
/// streams clone the inner Arcs so `process()` keeps seeing the
/// same plugin / pending / transport state across device switches.
struct OutputResources<P: PluginExport> {
    plugin: Arc<Mutex<P>>,
    pending: Arc<ArrayQueue<MidiEvent>>,
    /// Editor-initiated `load_state` blobs, drained at the block top (see
    /// [`AudioHandles::pending_state`]).
    pending_state: Arc<ArrayQueue<Vec<u8>>>,
    input_ring: Arc<InputRing>,
    input_enabled: Arc<AtomicBool>,
    /// Mic-ring frame width, restamped by `open_output_stream` on every
    /// (re)open so a `SetLayout` switch propagates the new output channel
    /// count to the input producer (shared with the input worker).
    ring_width: Arc<AtomicUsize>,
    /// Drives the audio callback's mute / unmute decision (UI thread
    /// flips it via `OutputController::set_enabled`).
    output_enabled: Arc<AtomicBool>,
    transport: Transport,
    current_name: Arc<Mutex<Option<String>>>,
    /// Input channel routing (encoded [`ChannelRoute`]). Shared with
    /// `InputController` (menu writes it).
    input_channel_route: Arc<AtomicUsize>,
    /// Output channel routing (encoded [`ChannelRoute`]). Shared with
    /// `OutputController` (menu writes it).
    output_channel_route: Arc<AtomicUsize>,
    /// The plugin's active bus layout as a packed `(num_in, num_out)`,
    /// shared with `OutputController` so the Bus Layout menu can mark the
    /// active entry. The worker updates it after a `SetLayout` switch.
    layout: Arc<AtomicUsize>,
    /// The `max_frames` and sample rate the plugin was last `reset()`
    /// with. A stream that differs in either renews the promise before
    /// its first callback.
    promised_max_frames: AtomicUsize,
    promised_rate: AtomicU32,
    /// Latency of the processing state prepared by the output worker.
    active_latency: Arc<AtomicU32>,
    /// Coalesces repeated callback observations until the worker reopens.
    latency_restart_pending: Arc<AtomicBool>,
    /// Buffer size the streams run at (see [`OutputController`]); the
    /// input worker opens at it too.
    buffer_frames: Arc<AtomicU32>,
    /// Sample rate the streams run at; the input worker opens at it too.
    sample_rate: Arc<AtomicU32>,
    /// Set while an ASIO driver's reset request waits for the worker, so a
    /// burst of them, one from each stream, reopens the streams once.
    reset_pending: Arc<AtomicBool>,
    fade: Arc<CloseFade>,
    /// Where the streams send a reset request or a latency restart. Weak,
    /// so the worker still exits when the controllers are dropped.
    commands: Weak<mpsc::SyncSender<OutputCmd>>,
    /// Set once the user chooses an output, which ends following the
    /// input.
    output_chosen: Arc<AtomicBool>,
    /// Reopens the input after a buffer size change, and moves it with
    /// the driver.
    input_cmd: mpsc::Sender<InputCmd>,
    settings: SettingsStore,
    /// Optional `.wav` playback source (gated on the `playback`
    /// feature). When present, summed into the input bus alongside
    /// the mic ring - see the matrix in `cli.rs::HELP`.
    #[cfg(feature = "playback")]
    playback: Option<Arc<crate::playback::PlaybackSource>>,
    /// Optional `.wav` sidechain source (gated on `playback`). Feeds
    /// the sidechain input bus, independent of the main `playback`.
    #[cfg(feature = "playback")]
    sidechain_playback: Option<Arc<crate::playback::PlaybackSource>>,
    /// Optional `--output-file` capture pusher. Cloned into each
    /// cpal callback closure, so device switches don't tear down
    /// the capture. The owning `CaptureSink` lives on
    /// `AudioHandles`; finalize is the runner's responsibility.
    #[cfg(feature = "playback")]
    capture: Option<crate::playback::CapturePusher>,
}

/// The streams the output worker holds open. On ASIO that includes the
/// interface's input: cpal shares an ASIO driver's buffers between an
/// input and an output built on one device at one buffer size, and the
/// driver runs callbacks in the order they were added, so an input built
/// first reaches the output within the same buffer.
struct OpenStreams {
    _duplex_input: Option<cpal::Stream>,
    _output: cpal::Stream,
}

/// A stream opened by [`open_output_stream`], and the shape it runs at.
struct Opened {
    streams: OpenStreams,
    config: cpal::StreamConfig,
}

/// The output worker's state: it owns the (`!Send`) cpal streams for its
/// lifetime.
struct OutputWorker<P: PluginExport> {
    res: OutputResources<P>,
    /// The device stream's channel count, the sample rate the plugin runs
    /// at, and the buffer size chosen, which a device may fit to its own
    /// range. `channels` is the *device* stream width, which need not
    /// equal the plugin's bus - a mono plugin on a stereo-only device runs
    /// `num_out == 1` but the stream stays at 2.
    config: cpal::StreamConfig,
    num_in: usize,
    num_out: usize,
    // Main-input width of the active layout (channels past it are the
    // sidechain). Resolved by index from the selected layout, so it's
    // reassigned - not re-derived from ambiguous totals - on a runtime
    // `SetLayout` switch below.
    num_main_in: usize,
    is_effect: bool,
    /// The device the streams last opened on. Changing the buffer size or
    /// layout reopens it as it is, and a failed switch returns to it.
    /// cpal finds an ASIO interface only by loading each driver listed
    /// before it, so a device is looked up only when the interface or
    /// driver changes, or the driver asks for a reset.
    device: cpal::Device,
    streams: Option<OpenStreams>,
}

impl<P: PluginExport> OutputWorker<P> {
    fn run(
        mut self,
        cmd_rx: &mpsc::Receiver<OutputCmd>,
        open_result: &mpsc::Sender<Result<(), String>>,
    ) {
        let requested_buffer = self.config.buffer_size;
        let mut initial = self.reopen(false, false);
        if let (Err(e), cpal::BufferSize::Fixed(frames)) = (&initial, self.config.buffer_size) {
            eprintln!(
                "could not open the output with a {frames}-frame buffer ({e}); \
                 trying the device's own buffer size"
            );
            self.config.buffer_size = cpal::BufferSize::Default;
            initial = self.reopen(false, false);
        }
        // A launch that cannot start keeps the player's buffer size for the
        // device they choose next.
        if initial.is_err() {
            self.config.buffer_size = requested_buffer;
        }
        if let Err(e) = &initial
            && driver::on_asio()
        {
            eprintln!("could not open the ASIO interface ({e}); using Windows (WASAPI)");
            // Windows audio is often the laptop's own microphone and
            // speakers, so the input goes off before the input worker
            // follows the driver, and the player is told why.
            let _ = self.res.input_cmd.send(InputCmd::SetEnabled(false));
            if self.is_effect {
                setup::report_failure(Some(InputNeed::FellBack(
                    device_label(&self.device).unwrap_or_else(|| "The ASIO interface".to_owned()),
                )));
            }
            initial = self.switch_driver(AudioDriver::Wasapi);
            // Later reopens must not reach back to the ASIO interface while
            // the launch runs on WASAPI.
            if initial.is_err()
                && let Some(device) = driver::host().default_output_device()
            {
                self.device = device;
            }
        }
        let _ = open_result.send(initial);

        while let Ok(cmd) = cmd_rx.recv() {
            match cmd {
                OutputCmd::SetDevice(name) => self.set_device(name.as_deref()),
                OutputCmd::ChooseInterface(name) => self.choose_interface(&name),
                OutputCmd::SetDriver(target) => self.set_driver(target),
                OutputCmd::FollowInput(input) => self.follow_input(&input),
                OutputCmd::SetBufferSize(frames) => self.set_buffer_size(frames),
                OutputCmd::SetLayout { index } => self.set_layout(index),
                OutputCmd::RestartLatency => self.restart_latency(),
                OutputCmd::Reset => self.reset(),
                OutputCmd::Close(stopped) => {
                    self.close();
                    // The plugin and the rest go before the answer, so none
                    // of it is cut short by the process exiting.
                    drop(self);
                    let _ = stopped.send(());
                    return;
                }
            }
        }
    }

    /// Stop the streams once the callback has faded the device to silence.
    /// Dropping the last stream on an ASIO driver stops and releases it, on
    /// this thread, which loaded it.
    fn close(&mut self) {
        if self.streams.is_some() {
            let start = std::time::Instant::now();
            let rate = f64::from(self.config.sample_rate.max(1));
            while !self.res.fade.silent.load(Ordering::Acquire) {
                #[allow(clippy::cast_precision_loss)]
                let buffers = std::time::Duration::from_secs_f64(
                    4.0 * self.res.fade.buffer_frames.load(Ordering::Relaxed) as f64 / rate,
                );
                if start.elapsed() >= CLOSE_FADE_WAIT.max(buffers) {
                    break;
                }
                std::thread::sleep(std::time::Duration::from_millis(1));
            }
        }
        self.streams = None;
    }

    fn current_name(&self) -> Option<String> {
        self.res.current_name.lock().ok().and_then(|g| g.clone())
    }

    /// Close the streams and open them on `device`. `fit` lets a device
    /// that cannot run the current channel count or sample rate run at its
    /// own, the plugin prepared again for it: a driver or ASIO interface
    /// switch needs that, while a WASAPI device switch keeps the shape it
    /// has.
    fn open_on(&mut self, device: cpal::Device, force_reset: bool, fit: bool) -> Result<(), String> {
        // Drop the old streams BEFORE building new ones - some backends
        // won't open a second exclusive stream against the same device,
        // and an ASIO driver's buffers are rebuilt under any stream left.
        self.streams = None;
        let opened = open_output_stream::<P>(
            &device,
            self.config,
            self.num_in,
            self.num_out,
            self.num_main_in,
            self.is_effect,
            force_reset,
            fit,
            &self.res,
        )?;
        self.config.channels = opened.config.channels;
        self.config.sample_rate = opened.config.sample_rate;
        self.streams = Some(opened.streams);
        // A device that refused at launch and has since started is no
        // longer unavailable, whichever change reopened it.
        let opened_name = device_label(&device);
        if let Some(name) = &opened_name {
            setup::output_started(name);
        }
        self.device = device;
        Ok(())
    }

    /// Close the streams and open `name`, or the default device for
    /// `None`.
    fn open(&mut self, name: Option<&str>, force_reset: bool, fit: bool) -> Result<(), String> {
        // Closed before the lookup, since cpal lists no other ASIO driver
        // while a stream holds one.
        self.streams = None;
        let host = driver::host();
        let device = match name {
            Some(n) => {
                find_device(&host, n, true).ok_or_else(|| format!("no output device matching '{n}'"))?
            }
            None => host
                .default_output_device()
                .ok_or_else(|| "no default audio output device".to_string())?,
        };
        self.open_on(device, force_reset, fit)
    }

    /// Reopen the streams on the device they last opened on.
    fn reopen(&mut self, force_reset: bool, fit: bool) -> Result<(), String> {
        self.open_on(self.device.clone(), force_reset, fit)
    }

    /// Reopen the device that was playing, else the default device, so a
    /// failed change never leaves the host silent.
    fn restore(&mut self, force_reset: bool, fit: bool) {
        if self.reopen(force_reset, fit).is_err()
            && let Err(e) = self.open(None, force_reset, fit)
        {
            eprintln!("failed to restore the audio output: {e}");
        }
    }

    /// Move the output to `name`, restoring the device that was playing
    /// when the new one fails. Returns whether the switch took.
    fn switch_device(&mut self, name: Option<&str>) -> bool {
        let fit = driver::on_asio();
        let Err(e) = self.open(name, false, fit) else {
            return true;
        };
        eprintln!("output device switch failed: {e}; restoring previous device");
        self.restore(false, fit);
        false
    }

    fn set_device(&mut self, name: Option<&str>) {
        if !self.switch_device(name) {
            return;
        }
        let chosen = self.current_name();
        if driver::on_asio() {
            self.res.settings.update(|s| s.asio_device = chosen);
        } else {
            self.res.output_chosen.store(true, Ordering::Relaxed);
            self.res.settings.update(|s| s.output_device = chosen);
        }
    }

    /// Open the ASIO interface `name` as the player's input, unless it is
    /// already the one playing, and let its input through once it opens.
    fn choose_interface(&mut self, name: &str) {
        if self.current_name().as_deref() != Some(name) && !self.switch_device(Some(name)) {
            setup::report_failure(Some(InputNeed::DidNotOpen(name.to_owned())));
            return;
        }
        let chosen = self.current_name();
        self.res.settings.update(|s| s.asio_device = chosen);
        let _ = self.res.input_cmd.send(InputCmd::SetEnabled(true));
    }

    fn set_driver(&mut self, target: AudioDriver) {
        let previous = driver::active();
        if target == previous {
            return;
        }
        if target == AudioDriver::Asio && !driver::asio_installed() {
            eprintln!("no ASIO driver is installed");
            return;
        }
        match self.switch_driver(target) {
            Ok(()) => {
                // The old driver's output is no longer what plays.
                setup::report_refused_output(None);
                vlog!("audio driver: {}", target.name());
                self.res.settings.update(|s| s.driver = Some(target));
            }
            Err(e) => {
                eprintln!(
                    "could not open the {} driver ({e}); staying on {}",
                    target.name(),
                    previous.name()
                );
                driver::set_active(previous);
                let _ = self.res.input_cmd.send(InputCmd::DriverChanged);
                self.restore(false, true);
            }
        }
    }

    /// Move both streams to `target`, onto the device last chosen for it,
    /// else its default. The input worker follows.
    fn switch_driver(&mut self, target: AudioDriver) -> Result<(), String> {
        let saved = self.res.settings.saved();
        // Closed before the input moves, so an interface the old driver
        // held is free when the input reopens on the new one.
        self.streams = None;
        driver::set_active(target);
        let _ = self.res.input_cmd.send(InputCmd::DriverChanged);
        match target {
            AudioDriver::Asio => self.open_asio(saved.asio_device.as_deref()),
            AudioDriver::Wasapi => {
                self.res
                    .output_chosen
                    .store(saved.output_device.is_some(), Ordering::Relaxed);
                self.open(saved.output_device.as_deref(), false, true)
                    .or_else(|_| self.open(None, false, true))
            }
        }
    }

    /// Open the ASIO interface `saved`, else the first installed one that
    /// opens.
    fn open_asio(&mut self, saved: Option<&str>) -> Result<(), String> {
        let host = driver::host();
        if let Some(interface) = saved.and_then(|name| find_device(&host, name, true))
            && self.open_on(interface, false, true).is_ok()
        {
            return Ok(());
        }
        let mut result = Err("no ASIO interface could be opened".to_string());
        for interface in asio_interfaces(&host) {
            if saved.is_some() && device_label(&interface).as_deref() == saved {
                continue;
            }
            result = self.open_on(interface, false, true);
            if result.is_ok() {
                break;
            }
        }
        result
    }

    fn follow_input(&mut self, input: &str) {
        if self.res.output_chosen.load(Ordering::Relaxed) || driver::on_asio() {
            return;
        }
        let host = driver::host();
        let Some(target) =
            find_device(&host, input, false).and_then(|device| companion_output(&host, &device))
        else {
            return;
        };
        if self.current_name().as_deref() == Some(target.as_str()) {
            return;
        }
        vlog!("output device: {target} (follows the input)");
        // Only an output nobody chose follows the input, so what it clears
        // is a launch device that refused to start.
        if self.switch_device(Some(&target)) {
            setup::report_refused_output(None);
        }
    }

    fn set_buffer_size(&mut self, frames: u32) {
        let previous = self.config.buffer_size;
        self.config.buffer_size = cpal::BufferSize::Fixed(frames);
        let fit = driver::on_asio();
        if let Err(e) = self.reopen(false, fit) {
            eprintln!(
                "the output device refused a {frames}-frame buffer ({e}); \
                 keeping the previous size"
            );
            self.config.buffer_size = previous;
            self.restore(false, fit);
        } else {
            let accepted = Some(self.res.buffer_frames.load(Ordering::Relaxed)).filter(|&n| n > 0);
            self.res.settings.update(|s| s.buffer_size = accepted);
            let _ = self.res.input_cmd.send(InputCmd::Reopen);
        }
    }

    fn set_layout(&mut self, index: usize) {
        let (new_in, new_out, new_main_in) = layout_at_index::<P>(index);
        let new_out_dev = u16::try_from(new_out).unwrap_or(u16::MAX);
        // Snapshot the current widths so a failed switch can revert
        // to them rather than leaving the host silent.
        let (old_in, old_out, old_main_in, old_channels) = (
            self.num_in,
            self.num_out,
            self.num_main_in,
            self.config.channels,
        );
        // Keep the device stream at a width the hardware can open.
        // Prefer the layout's output width (so a surround device
        // plays surround), else keep the current stream width and
        // map the plugin output onto it (a mono layout plays
        // through a stereo-only device instead of being rejected).
        if device_supports_output_channels(&self.device, new_out_dev) {
            self.config.channels = new_out_dev;
        }
        self.num_in = new_in;
        self.num_out = new_out;
        self.num_main_in = new_main_in;
        if let Err(e) = self.reopen(true, false) {
            eprintln!("bus-layout switch failed: {e}; reverting to the previous layout");
            // Revert the widths and reopen at the previous layout so
            // audio keeps running (and the plugin is re-prepared for
            // the arrangement it's actually being handed).
            self.num_in = old_in;
            self.num_out = old_out;
            self.num_main_in = old_main_in;
            self.config.channels = old_channels;
            self.restore(true, false);
        } else {
            self.res.layout.store(index, Ordering::Relaxed);
        }
    }

    /// Prepare the plugin for the latency it now reports and reopen the
    /// streams on the device they run on.
    fn restart_latency(&mut self) {
        let requested = self
            .res
            .plugin
            .lock()
            .expect("plugin mutex poisoned before latency restart")
            .latency();
        if requested == self.res.active_latency.load(Ordering::Acquire) {
            self.res.latency_restart_pending.store(false, Ordering::Release);
            return;
        }
        let fit = driver::on_asio();
        if let Err(e) = self.reopen(true, fit) {
            eprintln!("latency restart failed: {e}; restoring the output");
            self.res.latency_restart_pending.store(false, Ordering::Release);
            self.restore(true, fit);
        }
    }

    /// Answer an ASIO driver's reset request. ASIO asks for the driver to
    /// be initialised again, and its settings may have changed, so the
    /// device is looked up again to learn them.
    fn reset(&mut self) {
        vlog!("the audio driver asked to be reset; reopening");
        self.streams = None;
        // What the closed streams asked for is answered; a request from
        // the streams opened next is a new reset.
        self.res.reset_pending.store(false, Ordering::Release);
        let name = self.current_name();
        let fit = driver::on_asio();
        if let Err(e) = self.open(name.as_deref(), false, fit) {
            eprintln!("could not reopen the audio device: {e}");
            self.restore(false, fit);
        }
    }
}

/// Fit `config` to a device that may not run its channel count or sample
/// rate: keep what the device offers, else run at the device's own rate
/// when it cannot run this one, at the current width if the device offers
/// it at that rate, else the layout's, else the device's own.
fn fit_to_device(
    device: &cpal::Device,
    supported: &cpal::SupportedStreamConfig,
    config: &mut cpal::StreamConfig,
    num_out: usize,
) {
    let ranges: Vec<cpal::SupportedStreamConfigRange> = device
        .supported_output_configs()
        .map(Iterator::collect)
        .unwrap_or_default();
    let offers = |channels: u16, rate: u32| {
        ranges.iter().any(|r| {
            (channels == 0 || r.channels() == channels)
                && r.min_sample_rate() <= rate
                && rate <= r.max_sample_rate()
        })
    };
    if offers(config.channels, config.sample_rate) {
        return;
    }
    if !offers(0, config.sample_rate) {
        config.sample_rate = supported.sample_rate();
    }
    let layout = u16::try_from(num_out).unwrap_or(0);
    config.channels = [config.channels, layout]
        .into_iter()
        .find(|&channels| channels > 0 && offers(channels, config.sample_rate))
        .unwrap_or_else(|| supported.channels());
}

/// The error handler for the output worker's streams. An ASIO driver asks
/// for a reset when its own settings change, which the worker answers by
/// reopening the streams; anything else is reported.
fn stream_error_handler<P: PluginExport>(
    res: &OutputResources<P>,
) -> impl FnMut(cpal::Error) + Send + 'static {
    let asio = driver::on_asio();
    let pending = Arc::clone(&res.reset_pending);
    let commands = res.commands.clone();
    move |err| {
        if !asio || err.kind() != cpal::ErrorKind::StreamInvalidated {
            report_stream_error("Audio error", &err);
        } else if !pending.swap(true, Ordering::AcqRel)
            && commands
                .upgrade()
                .is_none_or(|commands| commands.try_send(OutputCmd::Reset).is_err())
        {
            // A full queue drops this request; the next one is sent.
            pending.store(false, Ordering::Release);
        }
    }
}

/// Report a stream error. Xruns are left out: cpal reports them from the
/// audio thread, where printing would only cause more.
fn report_stream_error(context: &str, err: &cpal::Error) {
    if err.kind() != cpal::ErrorKind::Xrun {
        eprintln!("{context}: {err}");
    }
}

/// Build the interface's inputs on the ASIO `device` the output is about to
/// open on, at the same rate and buffer size, capturing into the ring
/// while the input is enabled once played. `None` when the interface has
/// no inputs or they refuse to open, which leaves the input silent.
fn build_duplex_input<P: PluginExport>(
    device: &cpal::Device,
    output: cpal::StreamConfig,
    frame_bound: usize,
    res: &OutputResources<P>,
) -> Option<cpal::Stream> {
    let supported = device
        .default_input_config()
        .ok()
        .filter(|c| c.channels() > 0)?;
    let config = cpal::StreamConfig {
        channels: supported.channels(),
        sample_rate: output.sample_rate,
        buffer_size: output.buffer_size,
    };
    let channels = config.channels as usize;
    let ring = Arc::clone(&res.input_ring);
    let ring_width = Arc::clone(&res.ring_width);
    let enabled = Arc::clone(&res.input_enabled);
    let stream = build_input(
        device,
        config,
        supported.sample_format(),
        frame_bound * channels,
        move |data| {
            if enabled.load(Ordering::Relaxed) {
                ring.capture(data, channels, ring_width.load(Ordering::Relaxed));
            }
        },
        stream_error_handler(res),
    );
    match stream {
        Ok(stream) => Some(stream),
        Err(e) => {
            eprintln!("the interface's inputs did not open ({e}); the input stays silent");
            None
        }
    }
}

#[allow(clippy::too_many_arguments, clippy::too_many_lines)]
fn open_output_stream<P: PluginExport>(
    device: &cpal::Device,
    mut config: cpal::StreamConfig,
    // The plugin's bus is (`num_in`, `num_out`), mapped onto the device
    // channels (`config.channels`) by the route.
    num_in: usize,
    num_out: usize,
    // Main-input width of the selected layout; channels [num_main_in,
    // num_in) are the sidechain bus. Resolved by the caller from the
    // selected layout index (see `layout_at_index`).
    num_main_in: usize,
    is_effect: bool,
    // Force a `reset()` even when the frame bound didn't grow. A bus-layout
    // switch changes the channel arrangement, so the plugin has to re-prepare
    // its per-channel DSP state; every format wrapper couples an arrangement
    // change to a reset. Device switches (same layout) pass `false`.
    force_reset: bool,
    // Let a device that can't run `config`'s channel count or rate run at
    // its own (see `OutputWorker::open`).
    fit: bool,
    res: &OutputResources<P>,
) -> Result<Opened, String> {
    let resolved_name = device_label(device);

    let plugin_a = Arc::clone(&res.plugin);
    let pending_a = Arc::clone(&res.pending);
    let pending_state_a = Arc::clone(&res.pending_state);
    let ring_a = Arc::clone(&res.input_ring);
    let enabled_a = Arc::clone(&res.input_enabled);
    let out_enabled_a = Arc::clone(&res.output_enabled);
    let in_route_a = Arc::clone(&res.input_channel_route);
    let out_route_a = Arc::clone(&res.output_channel_route);
    let active_latency_a = Arc::clone(&res.active_latency);
    let latency_restart_pending_a = Arc::clone(&res.latency_restart_pending);
    let commands_a = res.commands.clone();
    let transport_a = res.transport.clone();
    #[cfg(feature = "playback")]
    let playback_a = res.playback.clone();
    #[cfg(feature = "playback")]
    let sidechain_playback_a = res.sidechain_playback.clone();
    #[cfg(feature = "playback")]
    let capture_a = res.capture.clone();

    // The bound for the scratch below comes from *this* device's reported
    // range - hot-plug re-opens may land on a device with a different
    // maximum - and so do the stream's sample format, and with `fit` its
    // channel count and rate.
    let supported = device
        .default_output_config()
        .map_err(|e| format!("could not query the output config for the scratch bound: {e}"))?;
    if fit {
        fit_to_device(device, &supported, &mut config, num_out);
    }
    // Device interleave stride.
    let channels = config.channels as usize;
    let sample_rate = f64::from(config.sample_rate);

    // Per-stream audio-callback scratch. Owned by the move-closure so
    // it lives across callbacks but never crosses threads - cpal calls
    // the closure on a single dedicated audio thread per stream.
    // Amortizes the `vec![0.0; num_frames]` per-channel allocation and
    // the `channel_bufs.clone()` for the effect input mirror, plus the
    // two `EventList::default()`s per block (input drain + plugin output)
    // - both `clear()`ed and reused, capacity-preserving.
    let mut channel_bufs: Vec<Vec<f32>> = Vec::with_capacity(channels);
    let mut input_bufs: Vec<Vec<f32>> = Vec::with_capacity(channels);
    let mut event_list = EventList::with_capacity(EVENT_LIST_PREALLOC);
    let mut output_events = EventList::with_capacity(EVENT_LIST_PREALLOC);
    let mut sub_event_scratch = EventList::with_capacity(EVENT_LIST_PREALLOC);
    // Cached for `chunked_process::process_chunked`. Built once at
    // callback setup; static for the lifetime of the cpal stream.
    // `plugin_a` is locked once here (stream setup, not audio thread)
    // to pull `param_infos` + the `params_arc` clone the chunker uses
    // as its `&dyn Params` handle. The chunker can't call
    // `plugin.params()` itself because process_chunked already holds
    // `&mut plugin` for the duration of the `process()` calls.
    let (param_infos, params_arc) = {
        let p = plugin_a
            .lock()
            .expect("plugin mutex poisoned at audio setup");
        (p.params().param_infos(), p.params_arc())
    };
    let min_subblock_samples = P::info().automation.min_subblock_samples;
    // Raw-pointer arrays + `RawBufferScratch` reused across callbacks.
    // The pointer arrays mirror `input_bufs` / `channel_bufs` each
    // block; the scratch wraps the raw->slice conversion plus the
    // alias-detection copy fallback used by every format wrapper.
    let mut ptr_scratch = CallbackPtrScratch {
        inputs: Vec::with_capacity(channels),
        outputs: Vec::with_capacity(channels),
    };
    let mut scratch: RawBufferScratch<<P as truce_core::plugin::PluginRuntime>::Sample> =
        RawBufferScratch::default();
    // Pre-grow the widening / alias-copy scratch to the stream's frame
    // bound (the same number `reset` hands the plugin) so an f64
    // plugin's first callback doesn't allocate its per-channel scratch
    // inside cpal's real-time callback. Every format wrapper does this
    // at its setup hook; the standalone was the one caller that didn't.
    let asked = config.buffer_size;
    config.buffer_size = fit_buffer_size(asked, supported.buffer_size());
    if let (
        cpal::BufferSize::Fixed(asked),
        cpal::BufferSize::Fixed(fitted),
        cpal::SupportedBufferSize::Range { min, max },
    ) = (asked, config.buffer_size, supported.buffer_size())
        && asked != fitted
    {
        eprintln!(
            "the output device takes buffers of {min} to {max} frames; \
             using {fitted} instead of {asked}"
        );
    }
    let frame_bound = max_block_frames(config.buffer_size, supported.buffer_size());
    // The plugin sized its DSP for the bound and rate it was last
    // `reset()` with. A device whose maximum exceeds the bound could
    // deliver blocks past that promise, and a plugin prepared for larger
    // blocks than it gets may add latency it need not (a partitioned
    // convolution, say), so any change renews the promise, as a host does
    // when its buffer size or rate changes. No callback is running - the
    // old stream is already dropped. A layout switch also has to
    // re-prepare the plugin for the new channel arrangement, so
    // `force_reset` triggers it regardless.
    let bound_changed = frame_bound != res.promised_max_frames.load(Ordering::Relaxed)
        || config.sample_rate != res.promised_rate.load(Ordering::Relaxed);
    if bound_changed {
        res.promised_max_frames
            .store(frame_bound, Ordering::Relaxed);
        res.promised_rate
            .store(config.sample_rate, Ordering::Relaxed);
    }
    {
        let mut p = plugin_a
            .lock()
            .expect("plugin mutex poisoned at audio setup");
        let latency_changed = p.latency() != res.active_latency.load(Ordering::Acquire);
        prepare_plugin(
            &mut *p,
            sample_rate,
            frame_bound,
            bound_changed || force_reset || latency_changed,
            &res.active_latency,
            &res.latency_restart_pending,
        );
    }
    scratch.ensure_capacity(num_in, num_out, frame_bound);
    // `num_main_in` (the main/sidechain split of the selected layout) is
    // resolved by the caller and passed in - the layout is fixed for the
    // stream's lifetime.

    let duplex_input = if driver::on_asio() && is_effect {
        build_duplex_input(device, config, frame_bound, res)
    } else {
        None
    };

    let mut reader = RingReader::new(sample_rate);
    let mut fade = FadeOut::new(Arc::clone(&res.fade), sample_rate);
    let output = build_output(
        device,
        config,
        supported.sample_format(),
        frame_bound * channels,
        move |data: &mut [f32]| {
            audio_callback::<P>(
                data,
                channels,
                num_in,
                num_main_in,
                num_out,
                sample_rate,
                is_effect,
                &plugin_a,
                &pending_a,
                &pending_state_a,
                &ring_a,
                &mut reader,
                &enabled_a,
                &out_enabled_a,
                &in_route_a,
                &out_route_a,
                &active_latency_a,
                &latency_restart_pending_a,
                &commands_a,
                &transport_a,
                &mut channel_bufs,
                &mut input_bufs,
                &mut event_list,
                &mut output_events,
                &mut sub_event_scratch,
                &param_infos,
                &params_arc,
                min_subblock_samples,
                &mut ptr_scratch,
                &mut scratch,
                #[cfg(feature = "playback")]
                playback_a.as_ref(),
                #[cfg(feature = "playback")]
                sidechain_playback_a.as_ref(),
                #[cfg(feature = "playback")]
                capture_a.as_ref(),
            );
            fade.apply(data, channels);
        },
        stream_error_handler(res),
    )?;

    // Both play once both are built: building the output starts the driver
    // again, and a reset request some drivers send while starting would
    // otherwise reach an input already playing and reopen the streams.
    let duplex_input = duplex_input.filter(|input| match input.play() {
        Ok(()) => true,
        Err(e) => {
            eprintln!("the interface's inputs did not start ({e}); the input stays silent");
            false
        }
    });
    output
        .play()
        .map_err(|e| format!("could not start output stream: {e}"))?;

    // Publish the new stream's channel count as the mic-ring frame width
    // so the input producer normalizes onto it after a layout switch.
    res.ring_width.store(channels, Ordering::Relaxed);
    res.buffer_frames.store(
        match config.buffer_size {
            cpal::BufferSize::Fixed(frames) => frames,
            cpal::BufferSize::Default => 0,
        },
        Ordering::Relaxed,
    );
    if res.sample_rate.swap(config.sample_rate, Ordering::Relaxed) != config.sample_rate {
        res.transport.set_sample_rate(sample_rate);
    }
    if let Ok(mut g) = res.current_name.lock() {
        g.clone_from(&resolved_name);
    }

    vlog!(
        "Output: {} @ {} Hz, {} ch, buffer {:?}",
        resolved_name.as_deref().unwrap_or("(unnamed)"),
        sample_rate,
        channels,
        config.buffer_size,
    );
    Ok(Opened {
        streams: OpenStreams {
            _duplex_input: duplex_input,
            _output: output,
        },
        config,
    })
}

// ---------------------------------------------------------------------------
// Input worker
// ---------------------------------------------------------------------------

/// The input worker's state: it owns the (`!Send`) cpal input stream
/// for its lifetime.
struct InputWorker {
    ring: Arc<InputRing>,
    ring_width: Arc<AtomicUsize>,
    /// The rate the output runs at, which the input opens at.
    sample_rate: Arc<AtomicU32>,
    enabled: Arc<AtomicBool>,
    current_name: Arc<Mutex<Option<String>>>,
    buffer_frames: Arc<AtomicU32>,
    settings: SettingsStore,
    opened_channels: Arc<AtomicUsize>,
}

impl InputWorker {
    fn run(&self, cmd_rx: &mpsc::Receiver<InputCmd>, initial_device_name: Option<String>) {
        let mut stream: Option<cpal::Stream> = None;
        let mut device_name = initial_device_name;
        let mut want_enabled = false;

        while let Ok(cmd) = cmd_rx.recv() {
            match cmd {
                InputCmd::SetEnabled(on) => {
                    want_enabled = on;
                    self.apply(&mut stream, want_enabled, device_name.as_deref());
                }
                InputCmd::SetDevice(name) => {
                    device_name = name;
                    if want_enabled {
                        // Drop old before opening new - some backends
                        // won't open a second exclusive stream against
                        // the same device.
                        stream = None;
                        self.enabled.store(false, Ordering::Relaxed);
                        self.apply(&mut stream, true, device_name.as_deref());
                    } else if let Ok(mut g) = self.current_name.lock() {
                        // Reflect the chosen device immediately even
                        // though we haven't opened a stream - the menu
                        // checkmark should match the user's pick.
                        g.clone_from(&device_name);
                    }
                    // The computer's own microphone plays for this session
                    // only: yesterday's headphones may not be on at the next
                    // launch, which then asks for an input.
                    let chosen = self
                        .current_name
                        .lock()
                        .ok()
                        .and_then(|g| g.clone())
                        .filter(|name| !is_own_microphone(name));
                    self.settings.update(|s| s.input_device = chosen);
                }
                InputCmd::Reopen => {
                    if stream.is_some() {
                        stream = None;
                        self.enabled.store(false, Ordering::Relaxed);
                        self.apply(&mut stream, true, device_name.as_deref());
                    }
                }
                InputCmd::DriverChanged => {
                    stream = None;
                    self.enabled.store(false, Ordering::Relaxed);
                    self.ring.clear();
                    // The new driver may open a device the player never
                    // chose, so the input waits for them; the editor says
                    // it is off.
                    want_enabled = false;
                    if !driver::on_asio() {
                        // An absent saved input stays the device, so turning
                        // the input on says it is not connected rather than
                        // opening the system default.
                        device_name = self.settings.saved().input_device;
                        if let Ok(mut g) = self.current_name.lock() {
                            g.clone_from(&device_name);
                        }
                    }
                    self.apply(&mut stream, want_enabled, device_name.as_deref());
                }
                InputCmd::Close(stopped) => {
                    self.enabled.store(false, Ordering::Relaxed);
                    drop(stream.take());
                    let _ = stopped.send(());
                    return;
                }
            }
        }
        drop(stream);
    }

    fn apply(&self, stream: &mut Option<cpal::Stream>, want: bool, device_name: Option<&str>) {
        if driver::on_asio() {
            // The output worker opens the interface's inputs with its
            // outputs; this only lets what they capture through.
            *stream = None;
            if want != self.enabled.load(Ordering::Relaxed) {
                self.ring.clear();
            }
            self.enabled.store(want, Ordering::Relaxed);
            if want {
                setup::report_failure(None);
            }
            return;
        }
        let currently = stream.is_some();
        if want == currently {
            return;
        }
        if !want {
            *stream = None;
            self.enabled.store(false, Ordering::Relaxed);
            // Drain stale frames so re-enabling doesn't replay old audio.
            self.ring.clear();
            return;
        }
        let host = driver::host();
        let device = match device_name {
            Some(name) => find_device(&host, name, false),
            None => host.default_input_device(),
        };
        let Some(dev) = device else {
            self.enabled.store(false, Ordering::Relaxed);
            setup::report_failure(Some(match device_name {
                Some(name) => InputNeed::NotConnected(name.to_owned()),
                None => InputNeed::Choose,
            }));
            return;
        };
        match self.open(&dev) {
            Ok(s) => {
                *stream = Some(s);
                self.enabled.store(true, Ordering::Relaxed);
                if let Ok(mut g) = self.current_name.lock() {
                    *g = device_label(&dev);
                }
                setup::report_failure(None);
            }
            Err(e) => {
                eprintln!("mic enable failed: {e}");
                self.enabled.store(false, Ordering::Relaxed);
                setup::report_failure(Some(InputNeed::DidNotOpen(
                    device_label(&dev).unwrap_or_else(|| "The input".to_owned()),
                )));
            }
        }
    }

    /// Open `device` at the output's buffer size, or at its own size when
    /// it refuses that one.
    fn open(&self, device: &cpal::Device) -> Result<cpal::Stream, BoxErr> {
        let mut input = resolve_input_config(
            device,
            self.ring_width.load(Ordering::Relaxed),
            f64::from(self.sample_rate.load(Ordering::Relaxed)),
            self.buffer_frames.load(Ordering::Relaxed),
        );
        self.opened_channels
            .store(usize::from(input.stream.channels), Ordering::Relaxed);
        match build_and_play_input_stream(
            device,
            &input,
            Arc::clone(&self.ring_width),
            Arc::clone(&self.ring),
        ) {
            Err(e) if input.stream.buffer_size != cpal::BufferSize::Default => {
                eprintln!(
                    "the input device refused a {:?} buffer ({e}); using its own buffer size",
                    input.stream.buffer_size
                );
                input.stream.buffer_size = cpal::BufferSize::Default;
                build_and_play_input_stream(
                    device,
                    &input,
                    Arc::clone(&self.ring_width),
                    Arc::clone(&self.ring),
                )
            }
            result => result,
        }
    }
}

/// How an input stream opens on a device: its shape, the sample format the
/// device delivers, and the largest block it may deliver.
struct InputConfig {
    stream: cpal::StreamConfig,
    format: cpal::SampleFormat,
    frame_bound: usize,
}

/// Resolve an input `StreamConfig` for `device`. Prefers the render
/// side's `(channels, sample_rate)` so the two clocks match, but many
/// capture devices can't open that shape (a mono USB mic on a stereo
/// render stream, a 44.1 kHz interface against a 48 kHz output). On any
/// mismatch, fall back to the device's own default config so the mic
/// still opens. A fallback whose rate differs from the render rate is
/// not sample-rate-converted, so the ring drifts within what the reader
/// sheds - opening at all beats a permanently-unusable mic. The buffer
/// matches the output's (`buffer_frames`, 0 for the device's own size),
/// fitted to what the device reports it takes. The format is the device's
/// preferred one where it offers that shape in it.
fn resolve_input_config(
    device: &cpal::Device,
    channels: usize,
    sample_rate: f64,
    buffer_frames: u32,
) -> InputConfig {
    let buffer_size = if buffer_frames > 0 {
        cpal::BufferSize::Fixed(buffer_frames)
    } else {
        cpal::BufferSize::Default
    };
    // Channel count < u16::MAX (typical: 1-8); sample rate goes through
    // `cast::sample_rate_u32` which debug-asserts the (positive,
    // ≤ u32::MAX) preconditions.
    #[allow(clippy::cast_possible_truncation)]
    let ideal = cpal::StreamConfig {
        channels: channels as u16,
        sample_rate: sample_rate_u32(sample_rate),
        buffer_size,
    };
    // If the device advertises the ideal shape, trust it; else drop to
    // the device default. `supported_input_configs` ranges tell us
    // without a throwaway `build_input_stream`.
    let ideal_formats: Vec<cpal::SampleFormat> = device
        .supported_input_configs()
        .map(|ranges| {
            ranges
                .filter(|c| {
                    c.channels() == ideal.channels
                        && c.min_sample_rate() <= ideal.sample_rate
                        && c.max_sample_rate() >= ideal.sample_rate
                })
                .map(|c| c.sample_format())
                .collect()
        })
        .unwrap_or_default();
    let default = device.default_input_config().ok();
    let (mut stream, format) = match &default {
        Some(def) if ideal_formats.contains(&def.sample_format()) => (ideal, def.sample_format()),
        _ if !ideal_formats.is_empty() => (ideal, ideal_formats[0]),
        Some(def) => {
            eprintln!(
                "mic: device can't open {} ch @ {} Hz; using its default {} ch @ {} Hz",
                ideal.channels,
                ideal.sample_rate,
                def.channels(),
                def.sample_rate(),
            );
            (def.config(), def.sample_format())
        }
        None => (ideal, cpal::SampleFormat::F32),
    };
    let supported_buffer = default
        .as_ref()
        .map_or(cpal::SupportedBufferSize::Unknown, |def| *def.buffer_size());
    stream.buffer_size = fit_buffer_size(buffer_size, &supported_buffer);
    InputConfig {
        stream,
        format,
        // Bounds the device's own size too, which a refused size falls
        // back to.
        frame_bound: max_block_frames(cpal::BufferSize::Default, &supported_buffer),
    }
}

/// Build an input stream against the given device that hands captured
/// frames to `ring`. `ring_width` is the ring's frame width (the output
/// stream's channel count); the callback normalizes the device's native
/// frames onto it. Called from the worker thread.
fn build_and_play_input_stream(
    device: &cpal::Device,
    input: &InputConfig,
    ring_width: Arc<AtomicUsize>,
    ring: Arc<InputRing>,
) -> Result<cpal::Stream, BoxErr> {
    // The mic's channel count (`in_ch`) is fixed for the stream's life.
    let in_ch = input.stream.channels as usize;
    let stream = build_input(
        device,
        input.stream,
        input.format,
        input.frame_bound * in_ch,
        move |data| {
            // Re-read the ring width each block so a `SetLayout`
            // switch that changed the output channel count reaches
            // the producer.
            ring.capture(data, in_ch, ring_width.load(Ordering::Relaxed));
        },
        |err| report_stream_error("Input error", &err),
    )?;
    stream
        .play()
        .map_err(|e| format!("could not start input stream: {e}"))?;
    Ok(stream)
}

/// Whether the input labelled `name` is the computer's own microphone.
fn is_own_microphone(name: &str) -> bool {
    find_device(&driver::host(), name, false)
        .is_some_and(|device| crate::microphone::BuiltIn::find().is(&device, name))
}

/// The device labelled exactly `name`. Saved and menu names are whole
/// labels, so a missing device never resolves to another that shares part
/// of its name.
fn find_device(host: &cpal::Host, name: &str, output: bool) -> Option<cpal::Device> {
    devices(host, output).find(|device| device_label(device).as_deref() == Some(name))
}

/// The device labelled `name`, else the first whose label contains it,
/// ignoring case, so a flag can name a device by part of its label.
fn find_flagged_device(host: &cpal::Host, name: &str, output: bool) -> Option<cpal::Device> {
    let needle = name.to_lowercase();
    let mut partial = None;
    for (index, device) in devices(host, output).enumerate() {
        let Some(label) = device_label(&device) else {
            continue;
        };
        if label == name {
            return Some(device);
        }
        if partial.is_none() && label.to_lowercase().contains(&needle) {
            partial = Some(index);
        }
    }
    devices(host, output).nth(partial?)
}

/// The output side of the interface `input` belongs to, if it has one.
/// `CoreAudio` and ALSA present one device for both directions, which
/// keeps its identifier; WASAPI splits it into endpoints that share the
/// interface name.
fn companion_output(host: &cpal::Host, input: &cpal::Device) -> Option<String> {
    let id = input.id().ok();
    let interface = input
        .description()
        .ok()
        .and_then(|d| d.driver().map(str::to_owned));
    devices(host, true).find_map(|output| {
        let same_device = id.is_some() && output.id().ok() == id;
        let same_interface = interface.is_some()
            && output
                .description()
                .ok()
                .and_then(|d| d.driver().map(str::to_owned))
                == interface;
        if same_device || same_interface {
            device_label(&output)
        } else {
            None
        }
    })
}

/// Build the cpal `StreamConfig` honoring opts where possible. Falls
/// back to the device's default config for any unspecified or
/// unsupported choice.
/// The exact `(num_in, num_out)` channel counts of the bus layout the
/// standalone runs. `--bus-layout <index>` selects it (out-of-range warns
/// and falls back); with no selection the plugin's first (default) layout
/// is used. The plugin always runs a *declared* layout - never the
/// device's default channel count.
/// Returns `(total_in, total_out, main_in)` for the selected layout. The
/// main/sidechain split (`main_in`; channels past it are the sidechain the
/// standalone feeds from `--sidechain-file`) is read from the SELECTED
/// layout by index - not from a total-channel match, which picks the wrong
/// layout when two share totals but split differently, routing the
/// sidechain file over the main channels. The offline path pins the split
/// the same way.
fn selected_layout_index<P: PluginExport>(opts: &Options) -> usize {
    let count = P::bus_layouts().len();
    match opts.bus_layout {
        Some(i) if i < count => i,
        Some(i) => {
            eprintln!(
                "--bus-layout {i}: out of range (plugin declares {count} layout(s)); \
                 using the default layout"
            );
            0
        }
        None => 0,
    }
}

/// `(total_in, total_out, main_in)` for the declared layout at `idx`. The
/// layout index is the unambiguous identity (two layouts can share channel
/// totals but split main/sidechain differently), so both the initial
/// selection and a runtime `SetLayout` switch resolve widths from here.
fn layout_at_index<P: PluginExport>(idx: usize) -> (usize, usize, usize) {
    P::bus_layouts().get(idx).map_or((0, 0, 0), |l| {
        (
            l.total_input_channels() as usize,
            l.total_output_channels() as usize,
            l.inputs
                .first()
                .map_or(0, |b| b.channels.channel_count() as usize),
        )
    })
}

/// Whether the output device advertises a config with exactly `ch`
/// channels. Used to reject a `--bus-layout` wider than the hardware.
fn device_supports_output_channels(device: &cpal::Device, ch: u16) -> bool {
    device
        .supported_output_configs()
        .is_ok_and(|mut r| r.any(|c| c.channels() == ch))
}

fn resolve_config(
    device: &cpal::Device,
    default: &cpal::SupportedStreamConfig,
    opts: &Options,
    requested_channels: Option<u16>,
    buffer_frames: u32,
) -> cpal::StreamConfig {
    let mut channels = default.channels();
    // A `--bus-layout` selection runs the plugin at that layout's channel
    // count, so request it from the device. The device has to support the
    // count so the device stream matches (a 6-channel device plays 5.1
    // directly); otherwise keep the device default and map the plugin's
    // output onto it - the plugin still runs its declared layout.
    if let Some(req) = requested_channels {
        if req == channels {
            // Already the default - nothing to do.
        } else if device_supports_output_channels(device, req) {
            channels = req;
        } else {
            eprintln!(
                "bus-layout: device doesn't offer {req} output channels; \
                 keeping the {channels}-channel device stream and mapping \
                 the plugin's output onto it"
            );
        }
    }
    let mut sample_rate = default.sample_rate();

    if let Some(sr) = opts.sample_rate {
        // Verify the requested rate is in the supported set; fall
        // back silently if not.
        if let Ok(mut ranges) = device.supported_output_configs() {
            let desired = sr;
            let supported =
                ranges.any(|r| r.min_sample_rate() <= desired && r.max_sample_rate() >= desired);
            if supported {
                sample_rate = desired;
            } else {
                eprintln!(
                    "sample rate {sr} Hz not supported; \
                     using device default {}",
                    default.sample_rate()
                );
            }
        }
    }

    cpal::StreamConfig {
        channels,
        sample_rate,
        buffer_size: cpal::BufferSize::Fixed(buffer_frames),
    }
}

/// The range of buffer sizes a device reports, when it is one a device
/// could honour. cpal's WASAPI backend reports `0..=u32::MAX` whenever
/// the audio stack cannot say (every software stack), which says
/// nothing.
fn honoured_range(supported: &cpal::SupportedBufferSize) -> Option<(u32, u32)> {
    match *supported {
        cpal::SupportedBufferSize::Range {
            min,
            max: max @ 1..=32_768,
        } if min <= max => Some((min, max)),
        _ => None,
    }
}

/// A fixed buffer size clamped into the range the device reports.
fn fit_buffer_size(
    buffer: cpal::BufferSize,
    supported: &cpal::SupportedBufferSize,
) -> cpal::BufferSize {
    match (buffer, honoured_range(supported)) {
        (cpal::BufferSize::Fixed(frames), Some((min, max))) => {
            cpal::BufferSize::Fixed(frames.clamp(min.max(1), max))
        }
        _ => buffer,
    }
}

/// The largest block the plugin may be handed. A fixed size is only a
/// request - cpal promises nothing about callback sizes - so it bounds
/// the blocks where the device reports a range it honours; elsewhere, and
/// for the device's own size, the device's maximum does. A device that
/// reports no usable range gets the same generous fallback the VST3
/// wrapper uses for hosts that skip `setupProcessing`; sizing scratch to
/// WASAPI's `u32::MAX` would be a 17 GB allocation.
fn max_block_frames(buffer: cpal::BufferSize, supported: &cpal::SupportedBufferSize) -> usize {
    match (buffer, honoured_range(supported)) {
        (cpal::BufferSize::Fixed(frames), Some(_)) => frames as usize,
        (_, Some((_, max))) => max as usize,
        (_, None) => 8192,
    }
}

#[allow(clippy::too_many_arguments, clippy::too_many_lines)]
fn audio_callback<P: PluginExport>(
    data: &mut [f32],
    // Device interleave stride (the cpal stream's channel count). Kept
    // separate from the plugin's bus dimensions so a plugin bus that
    // doesn't match the device (a mono plugin on a stereo-only output, a
    // mono-in/stereo-out effect) maps onto the device channels via the
    // route rather than forcing a device stream at the plugin's width,
    // which the hardware may not offer.
    channels: usize,
    // The active bus layout's exact (input, output) channel counts. Input
    // scratch is sized to `num_in`, output to `num_out`, so an asymmetric
    // layout (1 -> 2, 2 -> 1) runs at its real dimensions instead of a
    // single collapsed width.
    num_in: usize,
    // Channels [0, num_main_in) are the main input bus; [num_main_in,
    // num_in) are the sidechain. The mic and `--input-file` feed the main
    // bus; `--sidechain-file` feeds the sidechain when the plugin has one.
    num_main_in: usize,
    num_out: usize,
    sample_rate: f64,
    is_effect: bool,
    plugin: &Arc<Mutex<P>>,
    pending: &Arc<ArrayQueue<MidiEvent>>,
    pending_state: &Arc<ArrayQueue<Vec<u8>>>,
    input_ring: &Arc<InputRing>,
    ring_reader: &mut RingReader,
    input_enabled: &Arc<AtomicBool>,
    output_enabled: &Arc<AtomicBool>,
    input_channel_route: &Arc<AtomicUsize>,
    output_channel_route: &Arc<AtomicUsize>,
    active_latency: &Arc<AtomicU32>,
    latency_restart_pending: &Arc<AtomicBool>,
    commands: &Weak<mpsc::SyncSender<OutputCmd>>,
    transport: &Transport,
    channel_bufs: &mut Vec<Vec<f32>>,
    input_bufs: &mut Vec<Vec<f32>>,
    event_list: &mut EventList,
    output_events: &mut EventList,
    sub_event_scratch: &mut EventList,
    param_infos: &[ParamInfo],
    params_arc: &Arc<P::Params>,
    min_subblock_samples: u32,
    ptr_scratch: &mut CallbackPtrScratch,
    scratch: &mut RawBufferScratch<<P as truce_core::plugin::PluginRuntime>::Sample>,
    #[cfg(feature = "playback")] playback: Option<&Arc<crate::playback::PlaybackSource>>,
    #[cfg(feature = "playback")] sidechain_playback: Option<&Arc<crate::playback::PlaybackSource>>,
    #[cfg(feature = "playback")] capture: Option<&crate::playback::CapturePusher>,
) {
    // `num_main_in` only routes the sidechain when the `playback` feature
    // supplies a file source to feed it.
    #[cfg(not(feature = "playback"))]
    let _ = num_main_in;
    let num_frames = data.len() / channels;

    let Ok(mut plugin) = plugin.try_lock() else {
        data.fill(0.0);
        // This block's input goes unplayed with it, so the input that
        // follows stays in step with the output instead of a block late.
        if is_effect && input_enabled.load(Ordering::Relaxed) {
            ring_reader.read(input_ring, num_frames, |_, _| {});
        }
        return;
    };

    // Apply an editor-initiated state load before this block's work, under
    // the `&mut plugin` we now hold. The UI thread only pushed the bytes to
    // the lock-free `pending_state`, so it never blocked us or stalled this
    // callback's `try_lock`. `load_state` legitimately allocates (a sampler
    // decoding, say); accepted here at the block top, the same handoff the
    // VST3 wrapper uses for its queued state.
    if let Some(bytes) = pending_state.pop()
        && let Err(e) = plugin.load_state(&bytes)
    {
        // Debug-only breadcrumb: this runs on the audio thread (the editor's
        // load pops off the handoff queue here), and `eprintln!` locks stderr
        // and allocates, so it must never fire in a release build. Matches
        // `truce_core::state::apply_state`, which defers the same log.
        #[cfg(debug_assertions)]
        eprintln!("truce-standalone: load_state failed: {e}");
        #[cfg(not(debug_assertions))]
        let _ = e;
    }

    // Drain queued MIDI only after the lock is held. A lost try_lock
    // (an editor state read in flight) returns early above, and events
    // drained before it would be wiped by the next callback's
    // `event_list.clear()` - dropped notes. Left in `pending` they
    // arrive one block late at offset 0 instead.
    event_list.clear();
    output_events.clear();
    while let Some(ev) = pending.pop() {
        event_list.push(Event {
            sample_offset: 0,
            port: ev.port,
            body: ev.body,
        });
    }

    // Re-shape the plugin's output scratch to (num_out, num_frames) and
    // zero it - the plugin writes here, and it maps onto the device buffer
    // afterward. `Vec::resize` only allocates when growing past capacity,
    // so a stable cpal stream (fixed layout + buffer size) doesn't allocate
    // after warm-up.
    channel_bufs.resize_with(num_out, Vec::new);
    for buf in channel_bufs.iter_mut() {
        buf.clear();
        buf.resize(num_frames, 0.0);
    }

    // Effect-only input plumbing: mic + file are independent input
    // sources that *sum* into the plugin's input bus (`input_bufs`, sized
    // `num_in`), separate from the output the plugin writes (`channel_bufs`,
    // sized `num_out`). Instruments skip the whole block and just clear
    // `input_bufs`.
    if is_effect {
        // Input scratch: (num_in, num_frames), zeroed. Same
        // resize-without-realloc trick as the output above.
        input_bufs.resize_with(num_in, Vec::new);
        for buf in input_bufs.iter_mut() {
            buf.clear();
            buf.resize(num_frames, 0.0);
        }
        // (1) Mic ring → input_bufs (per-block sum). Read up to one
        // block of frames off the lock-free ring (each already
        // normalized to the ring width `w`).
        if input_enabled.load(Ordering::Relaxed) {
            // Map device input channels onto the plugin's input bus per
            // the selected route. `Direct` is the 1:1 default (clamped to
            // `num_in`, so a narrower plugin bus drops the extra device
            // channels); `Stereo` pulls a chosen device pair into plugin in
            // 0/1; `Mono` feeds one device channel into both plugin inputs.
            // Bounds checks keep an out-of-range base (e.g. after a device
            // swap to fewer channels) from indexing past the frame.
            let route = ChannelRoute::decode(input_channel_route.load(Ordering::Relaxed));
            let n_in = input_bufs.len();
            let w = channels.min(MAX_INPUT_RING_CHANNELS);
            ring_reader.read(input_ring, num_frames, |i, popped| {
                let frame = &popped.samples[..w];
                match route {
                    ChannelRoute::Direct => {
                        for ch in 0..w.min(n_in) {
                            input_bufs[ch][i] += frame[ch];
                        }
                    }
                    ChannelRoute::Stereo { base } => {
                        if base < w && n_in > 0 {
                            input_bufs[0][i] += frame[base];
                        }
                        if n_in > 1 && base + 1 < w {
                            input_bufs[1][i] += frame[base + 1];
                        }
                    }
                    ChannelRoute::Mono { base } => {
                        if base < w && n_in > 0 {
                            let s = frame[base];
                            input_bufs[0][i] += s;
                            if n_in > 1 {
                                input_bufs[1][i] += s;
                            }
                        }
                    }
                }
            });
        }

        // (2) Playback files → their buses. The main file sums onto the
        // main bus (alongside the mic); the sidechain file feeds the
        // sidechain bus, so the two are independent sources you can drive
        // and test separately.
        #[cfg(feature = "playback")]
        {
            if let Some(src) = playback {
                src.mix_into(&mut input_bufs[..num_main_in], num_frames);
            }
            if let Some(src) = sidechain_playback
                && num_in > num_main_in
            {
                src.mix_into(&mut input_bufs[num_main_in..num_in], num_frames);
            }
        }
    } else {
        input_bufs.clear();
    }
    // Build raw-pointer arrays that mirror `input_bufs` / `channel_bufs`
    // and feed them through the shared `RawBufferScratch::build` helper.
    // Standalone never aliases input and output buffers (`input_bufs`
    // is a copy of `channel_bufs` for effects, plain empty for
    // instruments), so the alias-detection scratch path inside
    // `build` is dormant; routing through the same helper keeps
    // every host on a single unsafe path.
    ptr_scratch.inputs.clear();
    ptr_scratch.outputs.clear();
    for buf in input_bufs.iter() {
        ptr_scratch.inputs.push(buf.as_ptr());
    }
    for buf in channel_bufs.iter_mut() {
        ptr_scratch.outputs.push(buf.as_mut_ptr());
    }
    let num_frames_u32 = u32::try_from(num_frames).unwrap_or(u32::MAX);
    let num_in_u32 = u32::try_from(ptr_scratch.inputs.len()).unwrap_or(u32::MAX);
    let num_out_u32 = u32::try_from(ptr_scratch.outputs.len()).unwrap_or(u32::MAX);
    // SAFETY: the `*const f32` / `*mut f32` entries above all point
    // into `input_bufs` / `channel_bufs`, both alive for the rest of
    // this call (they're owned by the cpal closure and not mutated
    // until the next block); each `Vec<f32>` was sized to
    // `num_frames` above, satisfying `build`'s readability /
    // writability requirements.
    let mut audio_buffer = unsafe {
        scratch.build(
            ptr_scratch.inputs.as_ptr(),
            ptr_scratch.outputs.as_mut_ptr(),
            num_in_u32,
            num_out_u32,
            num_frames_u32,
            P::supports_in_place(),
        )
    };

    let transport_info = transport.tick_audio(num_frames);
    let mut transport_snap = transport_info;
    let chunk_args = ChunkedProcess {
        events: event_list,
        sub_event_scratch,
        transport: &mut transport_snap,
        sample_rate,
        // The standalone is a live host; offline render goes through
        // `offline.rs` + the driver, not this realtime path.
        process_mode: ProcessMode::Realtime,
        output_events,
        params_fn: None,
        meters_fn: None,
        param_infos,
        min_subblock_samples,
    };
    process_chunked(
        &mut *plugin,
        params_arc.as_ref() as &dyn Params,
        &mut audio_buffer,
        chunk_args,
    );
    queue_latency_restart(
        plugin.latency(),
        active_latency,
        latency_restart_pending,
        commands,
    );
    let _ = audio_buffer;
    // Narrow rendered f64 output back to host f32 when the plugin's
    // `Sample = f64`. No-op for `f32` plugins.
    // SAFETY: `ptr_scratch.outputs` lives through this function;
    // `num_out_u32` / `num_frames_u32` match the build above.
    unsafe {
        scratch.finish_widening(
            ptr_scratch.outputs.as_mut_ptr(),
            num_out_u32,
            num_frames_u32,
        );
    }

    let route = ChannelRoute::decode(output_channel_route.load(Ordering::Relaxed));
    write_output_to_device(
        data,
        channels,
        num_frames,
        channel_bufs,
        output_enabled.load(Ordering::Relaxed),
        route,
        #[cfg(feature = "playback")]
        capture,
    );
}

/// Map the plugin's rendered output onto the interleaved device buffer
/// `data`. `channel_bufs` holds one `Vec<f32>` per plugin output channel
/// (each `num_frames` long); `channels` is the device interleave stride.
///
/// A layout with no output channels - a MIDI-only instrument *or* an
/// input-only analyzer / sink - leaves `channel_bufs` empty. There is then
/// nothing to route, and every path below indexes `channel_bufs[..]`
/// (`Direct` via `n_buf - 1`, `Stereo` / `Mono` via `[0]` / `[1]`), so the
/// empty case is silenced and returned first. Keeping that guard here, next
/// to the indexing it protects, is deliberate: cpal drives this from an
/// `extern "C"` callback on the OS audio thread, where a `0 - 1` underflow
/// panic (or an empty-`Vec` index) would abort the host process.
///
/// `output_enabled == false` is device mute: the plugin already ran, so the
/// `--output-file` capture copy is still taken (mute is speaker silence, not
/// a bounce cut), then the device buffer is zeroed.
fn write_output_to_device(
    data: &mut [f32],
    channels: usize,
    num_frames: usize,
    channel_bufs: &[Vec<f32>],
    output_enabled: bool,
    route: ChannelRoute,
    #[cfg(feature = "playback")] capture: Option<&crate::playback::CapturePusher>,
) {
    let n_buf = channel_bufs.len();
    if n_buf == 0 {
        data.fill(0.0);
        return;
    }

    // `--output-file` capture: hand a copy of the post-process, pre-mute
    // output to the writer thread. The capture path transfers Vec ownership
    // to the writer thread (channel-bounded `mpsc::sync_channel`), so the
    // per-block alloc here can't be amortized without a free-list pool. Left
    // as-is - `--output-file` is the offline render/capture path (often
    // paired with `--no-playback`), not the real-time playback hot path.
    #[cfg(feature = "playback")]
    if let Some(pusher) = capture {
        let mut interleaved = vec![0.0_f32; num_frames * channels];
        for frame in 0..num_frames {
            for ch in 0..channels {
                let ch_idx = ch.min(n_buf - 1);
                interleaved[frame * channels + ch] = channel_bufs[ch_idx][frame];
            }
        }
        pusher.submit(interleaved);
    }

    // Output mute: keep the plugin running (transport, MIDI, meters all still
    // tick) but zero-fill the device buffer so the speakers stay silent.
    // Cheaper and more responsive than tearing down the cpal stream.
    if !output_enabled {
        data.fill(0.0);
        return;
    }

    // Map the plugin's output bus onto device output channels per the
    // selected route. `Direct` is the 1:1 default; `Stereo` drives a chosen
    // device pair (other channels silent); `Mono` folds the plugin's first
    // two channels down into one device channel. The non-Direct modes clear
    // the buffer first since they only write the selected channels.
    match route {
        ChannelRoute::Direct => {
            for frame in 0..num_frames {
                for ch in 0..channels {
                    let ch_idx = ch.min(n_buf - 1);
                    data[frame * channels + ch] = channel_bufs[ch_idx][frame];
                }
            }
        }
        ChannelRoute::Stereo { base } => {
            data.fill(0.0);
            for frame in 0..num_frames {
                if base < channels {
                    data[frame * channels + base] = channel_bufs[0][frame];
                }
                if n_buf > 1 && base + 1 < channels {
                    data[frame * channels + base + 1] = channel_bufs[1][frame];
                }
            }
        }
        ChannelRoute::Mono { base } => {
            data.fill(0.0);
            if base < channels {
                for frame in 0..num_frames {
                    let mut v = channel_bufs[0][frame];
                    if n_buf > 1 {
                        v += channel_bufs[1][frame];
                    }
                    data[frame * channels + base] = v;
                }
            }
        }
    }
}

#[cfg(test)]
mod ring_tests {
    use super::{InputRing, RingReader};

    const RATE: f64 = 48_000.0;
    const BLOCK: usize = 128;
    /// The safety margin the ring may keep beyond a block, at most.
    const MARGIN: usize = 48;

    /// A mono input whose every sample is its own frame number, so what
    /// the output plays says how long ago it was captured.
    struct Input {
        ring: InputRing,
        captured: usize,
    }

    impl Input {
        fn new() -> Self {
            // The ring's production capacity, 100 ms.
            Self {
                ring: InputRing::new(4800),
                captured: 0,
            }
        }

        fn capture(&mut self, frames: usize) {
            #[allow(clippy::cast_precision_loss)]
            let data: Vec<f32> = (self.captured..self.captured + frames)
                .map(|n| n as f32)
                .collect();
            self.ring.capture(&data, 1, 1);
            self.captured += frames;
        }

        /// Render one block; returns the frame numbers it played.
        fn render(&self, reader: &mut RingReader) -> Vec<usize> {
            let mut played = Vec::new();
            #[allow(clippy::cast_possible_truncation, clippy::cast_sign_loss)]
            reader.read(&self.ring, BLOCK, |_, frame| {
                played.push(frame.samples[0] as usize);
            });
            played
        }

        /// Frames captured but not yet played: the delay the ring adds.
        fn queued(&self) -> usize {
            self.ring.frames.len()
        }
    }

    #[test]
    fn a_backlog_is_shed_instead_of_delaying_the_input() {
        let mut input = Input::new();
        let mut reader = RingReader::new(RATE);
        // A stalled output, or an input that started first, leaves 80 ms
        // captured and unplayed.
        for _ in 0..30 {
            input.capture(BLOCK);
        }
        let played = input.render(&mut reader);
        let newest = input.captured - 1;
        assert!(
            newest - played.last().unwrap() <= BLOCK + MARGIN,
            "the first block after the stall plays input captured {} frames ago",
            newest - played.last().unwrap()
        );
        // Then a second of steady running, one capture per render.
        for _ in 0..375 {
            input.capture(BLOCK);
            input.render(&mut reader);
        }
        assert!(
            input.queued() <= MARGIN,
            "{} frames stay queued beyond each block",
            input.queued()
        );
    }

    #[test]
    fn drift_between_separate_clocks_does_not_build_up_delay() {
        let mut input = Input::new();
        let mut reader = RingReader::new(RATE);
        // An input clock far faster than any real one: 129 frames
        // captured for every 128 played, for ten seconds.
        for _ in 0..3750 {
            input.capture(BLOCK + 1);
            input.render(&mut reader);
            assert!(
                input.queued() <= BLOCK + 1 + MARGIN,
                "{} frames queued after playing a block",
                input.queued()
            );
        }
    }

    #[test]
    fn input_captured_in_larger_blocks_plays_without_gaps() {
        let mut input = Input::new();
        let mut reader = RingReader::new(RATE);
        let mut played = Vec::new();
        // The input device delivers 512 frames at a time to an output
        // rendering 128, for two seconds.
        for _ in 0..187 {
            input.capture(4 * BLOCK);
            for _ in 0..4 {
                let block = input.render(&mut reader);
                assert_eq!(block.len(), BLOCK, "a block ran short of input");
                played.extend(block);
            }
        }
        assert!(
            played.windows(2).all(|pair| pair[1] == pair[0] + 1),
            "input was dropped between captures"
        );
    }
}

#[cfg(test)]
mod close_tests {
    use super::{CloseFade, FadeOut};
    use std::sync::Arc;
    use std::sync::atomic::Ordering;

    const RATE: f64 = 48_000.0;
    const CHANNELS: usize = 2;
    const BLOCK: usize = 128;

    fn render(fade: &mut FadeOut) -> Vec<f32> {
        let mut block = vec![0.5; BLOCK * CHANNELS];
        fade.apply(&mut block, CHANNELS);
        block
    }

    #[test]
    fn closing_fades_the_output_out_and_stops_only_on_silent_buffers() {
        let shared = Arc::new(CloseFade::default());
        let mut fade = FadeOut::new(Arc::clone(&shared), RATE);
        assert!(
            render(&mut fade).iter().all(|&s| s == 0.5),
            "the output plays untouched until closing"
        );

        shared.requested.store(true, Ordering::Release);
        // Short enough to feel instant: within 10 ms.
        let most = (RATE * 0.010) as usize / BLOCK + 1;
        let mut faded = Vec::new();
        while faded.last() != Some(&0.0) {
            assert!(faded.len() / (BLOCK * CHANNELS) < most, "the fade lasts too long");
            faded.extend(render(&mut fade));
        }
        assert!(faded[0] < 0.5, "the fade starts at once");
        assert!(
            faded.windows(2).all(|w| w[1] <= w[0]),
            "the fade never rises"
        );
        assert!(
            !shared.silent.load(Ordering::Acquire),
            "a buffer holding the fade is not yet silence"
        );

        assert!(render(&mut fade).iter().all(|&s| s == 0.0));
        assert!(
            !shared.silent.load(Ordering::Acquire),
            "one silent buffer leaves the other half of the driver's pair"
        );
        assert!(render(&mut fade).iter().all(|&s| s == 0.0));
        assert!(
            shared.silent.load(Ordering::Acquire),
            "two silent buffers let the stream stop"
        );
    }

    #[test]
    fn a_stream_opened_while_closing_plays_nothing() {
        let shared = Arc::new(CloseFade::default());
        shared.requested.store(true, Ordering::Release);
        let mut fade = FadeOut::new(shared, RATE);
        assert!(render(&mut fade).iter().all(|&s| s == 0.0));
    }
}

#[cfg(test)]
mod tests {
    use super::{ChannelRoute, write_output_to_device};

    /// Call `write_output_to_device` the same way `audio_callback` does,
    /// threading the `playback`-gated `capture` arg through so the test
    /// compiles in both feature configs.
    fn route(
        data: &mut [f32],
        channels: usize,
        num_frames: usize,
        channel_bufs: &[Vec<f32>],
        output_enabled: bool,
        route: ChannelRoute,
    ) {
        write_output_to_device(
            data,
            channels,
            num_frames,
            channel_bufs,
            output_enabled,
            route,
            #[cfg(feature = "playback")]
            None,
        );
    }

    #[test]
    fn zero_output_layout_silences_without_underflow() {
        // A MIDI-only instrument or an input-only analyzer / sink declares no
        // output buses, so `channel_bufs` is empty while the device stream
        // still asks for `channels` frames. Routing must not compute
        // `0usize - 1` or index an empty buffer (either aborts the cpal audio
        // thread); it silences the device and returns.
        let channels = 2;
        let num_frames = 4;
        let channel_bufs: Vec<Vec<f32>> = Vec::new();
        for &r in &[
            ChannelRoute::Direct,
            ChannelRoute::Stereo { base: 0 },
            ChannelRoute::Mono { base: 0 },
        ] {
            let mut data = vec![7.0_f32; num_frames * channels];
            route(&mut data, channels, num_frames, &channel_bufs, true, r);
            assert!(
                data.iter().all(|&s| s == 0.0),
                "zero-output layout must silence the device buffer ({r:?})"
            );
        }
    }

    #[test]
    fn direct_route_maps_and_clamps_channels() {
        let channels = 2;
        let num_frames = 2;
        // Mono plugin output on a stereo device: `ch.min(n_buf - 1)` folds
        // both device channels onto the single plugin channel.
        let mono = vec![vec![0.25_f32, 0.5]];
        let mut data = vec![0.0_f32; num_frames * channels];
        route(
            &mut data,
            channels,
            num_frames,
            &mono,
            true,
            ChannelRoute::Direct,
        );
        assert_eq!(data, vec![0.25, 0.25, 0.5, 0.5]);

        // Stereo plugin output maps 1:1.
        let stereo = vec![vec![0.1_f32, 0.2], vec![0.3, 0.4]];
        let mut data = vec![0.0_f32; num_frames * channels];
        route(
            &mut data,
            channels,
            num_frames,
            &stereo,
            true,
            ChannelRoute::Direct,
        );
        assert_eq!(data, vec![0.1, 0.3, 0.2, 0.4]);
    }

    #[test]
    fn muted_output_zeroes_device_buffer() {
        let channels = 2;
        let num_frames = 2;
        let stereo = vec![vec![0.1_f32, 0.2], vec![0.3, 0.4]];
        let mut data = vec![9.0_f32; num_frames * channels];
        route(
            &mut data,
            channels,
            num_frames,
            &stereo,
            false,
            ChannelRoute::Direct,
        );
        assert!(data.iter().all(|&s| s == 0.0), "mute silences the device");
    }

    #[test]
    fn encode_decode_roundtrips() {
        let cases = [
            ChannelRoute::Direct,
            ChannelRoute::Stereo { base: 0 },
            ChannelRoute::Stereo { base: 2 },
            ChannelRoute::Mono { base: 0 },
            ChannelRoute::Mono { base: 3 },
        ];
        for route in cases {
            assert_eq!(ChannelRoute::decode(route.encode()), route);
        }
    }

    #[test]
    fn direct_encodes_to_zero() {
        // A freshly-zeroed atomic must decode to the default mapping.
        assert_eq!(ChannelRoute::Direct.encode(), 0);
        assert_eq!(ChannelRoute::decode(0), ChannelRoute::Direct);
    }

    #[test]
    fn a_launch_feeds_the_amp_from_channel_one_unless_another_was_chosen() {
        use super::launch_input_route;
        let first = ChannelRoute::Mono { base: 0 };
        assert_eq!(launch_input_route(None, None, 2), first);
        assert_eq!(
            launch_input_route(None, Some("2"), 2),
            ChannelRoute::Mono { base: 1 },
            "a saved Channel 2 (mono) is read as channel 2"
        );
        assert_eq!(launch_input_route(None, Some("direct"), 2), ChannelRoute::Direct);
        assert_eq!(
            launch_input_route(None, Some("2"), 1),
            first,
            "a saved channel the device lacks left the input silent"
        );
        assert_eq!(
            launch_input_route(Some("1-2"), Some("2"), 2),
            ChannelRoute::Stereo { base: 0 }
        );
    }

    /// The input channels chosen from the menu are saved as a spec and must
    /// come back as the same route at the next launch.
    #[test]
    fn a_saved_route_reads_back_as_the_route_chosen() {
        for route in [
            ChannelRoute::Direct,
            ChannelRoute::Mono { base: 1 },
            ChannelRoute::Stereo { base: 2 },
        ] {
            assert_eq!(ChannelRoute::parse(&route.spec()), Some(route));
        }
    }

    #[test]
    fn parse_specs() {
        assert_eq!(ChannelRoute::parse("direct"), Some(ChannelRoute::Direct));
        assert_eq!(ChannelRoute::parse(" ALL "), Some(ChannelRoute::Direct));
        // 1-based in the spec, 0-based base internally.
        assert_eq!(
            ChannelRoute::parse("1"),
            Some(ChannelRoute::Mono { base: 0 })
        );
        assert_eq!(
            ChannelRoute::parse("3"),
            Some(ChannelRoute::Mono { base: 2 })
        );
        assert_eq!(
            ChannelRoute::parse("3-4"),
            Some(ChannelRoute::Stereo { base: 2 })
        );
        // Non-adjacent / reversed / zero / garbage are rejected.
        assert_eq!(ChannelRoute::parse("3-5"), None);
        assert_eq!(ChannelRoute::parse("4-3"), None);
        assert_eq!(ChannelRoute::parse("0"), None);
        assert_eq!(ChannelRoute::parse("x"), None);
    }
}
