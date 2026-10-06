# Standalone latency restart, input latency, remembered audio settings and ASIO

Source: crates.io `truce-standalone` 6.3.0, upstream commit
`ff6b573c7d845638656b03bbe4b4436559dd9725`, `crates/truce-standalone` in
[truce](https://github.com/truce-audio/truce).
The governing `LicenseRef-TruceLicense-1.0` text and its MIT and Apache
license texts are included unchanged.

The published standalone adapter does not watch a running plugin's latency.
Plugins whose latency follows a parameter can therefore report the requested
delay without re-preparing their processing state. This copy detects a changed
latency after a process block, sends a bounded restart request to the existing
output worker, and lets that worker stop the device stream, reset the plugin,
and reopen the stream. Reset and stream allocation stay off the audio callback.

The published standalone also let a guitar played through it fall further and
further behind. Input reaches the output through a ring sized for 100 ms, and
the output only ever took one block from it, so whatever queued at startup,
after a stall, after a latency restart or from drift between two devices'
clocks stayed as delay for the session. The output now drops queued input
beyond its block, one capture block and half a millisecond before reading, and
drops any surplus that stayed queued for a whole half second, so the delay
stays near one block (`RingReader` in `audio.rs`).

It also ran at the device's default buffer size unless launched with
`--buffer`, and forgot its devices between launches. The Settings menu now
has a Buffer Size submenu of 32 to 1024 samples, 128 unless chosen, which
reopens both streams at the new size; a device that refuses it keeps its
previous size. The chosen input, output and buffer size are saved in
`standalone.cfg` under the vendor and plugin names in the machine's local
configuration directory (`settings.rs`); the `--input`, `--output` and
`--buffer` flags override them for one launch and are not saved. Picking an
input that belongs to an interface with outputs moves the output there when no
output has been chosen, so both streams run on the interface's clock. On
Windows a device is labelled as the Sound control panel names it, "Speakers
(UMC202HD 192k)", instead of cpal's bare endpoint kind, so interfaces can be
told apart and saved. The plugin is prepared again whenever the stream's block
bound changes, as a host does when its buffer size changes, as well as when
its latency changes.

The published standalone also runs only on cpal's default host, which on
Windows is WASAPI shared mode, adding about 10 ms each way. With the fork's
asio feature, which the Windows bundles enable, the Windows standalone runs on
ASIO when an ASIO driver is installed (`driver.rs`). The Settings menu gains an
Audio Driver submenu, ASIO or Windows (WASAPI), saved with the other choices;
the --driver flag overrides it for one launch. An ASIO interface is one device
for input and output: both device submenus list the installed ASIO drivers,
and the interface is saved apart from the WASAPI devices. A buffer's input
reaches the output in that same buffer. Streams convert to the device's sample
format, which for ASIO is commonly 32-bit integers (`format.rs`); a driver's
reset request reopens the streams; and a driver or interface switch that lands
on a device that cannot run the current rate prepares the plugin again at the
device's rate. The fork depends on cpal 0.18, whose ASIO backend fixes duplex
streams and driver reloading, and so on midir 0.11, which shares its ALSA
bindings; neither adds a crate to the macOS or Windows builds. ASIO is a
registered trademark of Steinberg Media Technologies GmbH.

A latency restart reaches the output worker the way a driver's reset request
does, through the worker's bounded command queue by a weak handle, so the
worker still ends with the host, and it reopens the device the streams run on
rather than looking one up again.

A fixed-size editor may still ask for a new size, which is how an interface
zoom resizes the window. The published standalone resizes the window but
leaves its content size pinned where the editor opened, so on macOS the zoom
button snapped it back, and on Windows the size-limits subclass clamped the
resize itself, leaving the window at its opening size; on both the pin now
follows the size the editor asked for.

The published help text gave `--input-enabled` a default of off, although an
application can set its own through `Defaults`, as Swanky Amp does to open
with its input on. The help now names the application's default first
(`cli.rs`).

An application can ask, through `Defaults::input_needs_choice`, that an
input its defaults turn on stays off unless it is a device the player chose,
by flag or from the Settings menu, and is connected: the system default, or
a stand-in for an unplugged interface, is often a built-in microphone beside
the speakers. A flag or environment variable that turns the input on is
obeyed as given, with one exception: when a saved ASIO interface loads but
will not open and the launch falls back to WASAPI, the input is turned off
first, whatever asked for it. The computer's own microphone is never saved
as the input, so a launch after it was chosen asks for an input again; a
flag that names it is obeyed. On WASAPI and the other hosts, a chosen input that is not
connected stays the input worker's device, so turning the input on opens it
once it is back rather than the system default. On ASIO the launch opens
another installed interface in its place, which turning the input on would
make live, so the editor asks the player to choose the interface first.
The input is off after any driver switch, which may open a device the
player never chose; a WASAPI input saved but absent stays the device. Saved and menu names
match a device's whole label; only a flag matches part of one.
Since a windowed app has no console and the menu is easy to miss, `setup.rs`
gives the plugin's editor the audio choices the Settings menu offers (input,
input channels, output), lets it change them, and reports what needs the
player: no input ever chosen, a missing device, an input that would not open or an ASIO interface
that fell back to WASAPI. Choosing an ASIO interface as
the input lets its input through only once it has opened. `microphone.rs`
says whether an input is the computer's own microphone: on macOS from Core
Audio's built-in transport and internal-microphone source, on Windows from
cpal's form factor and bus. Listing the inputs opens none of them, since
ALSA would open each one; the input channels on offer are those the open
input stream records. Swanky Amp shows these in its information panel.
The input channels chosen from
the menu are saved with the devices (`input_channels`), and
`--input-channels` overrides them for one launch. Without either the input
feeds the plugin from channel 1 alone, where upstream feeds every channel
straight through, since a guitar is one channel; a saved channel the device
does not have gives way to channel 1.

The published standalone exits with an error when the output device is
there but will not start, as CoreAudio, WASAPI or ASIO can refuse an
interface another program holds or one in a bad state. The windowed
standalone now opens without sound instead and reports the device through
`setup` as one that would not start, so the editor can offer another;
choosing one that starts plays as usual. Without a window the error still
ends the launch.

The published standalone never stops its audio streams: the workers that
own them live as long as the controllers, which the standalone keeps for the
whole process, so the process exits with its streams running. cpal stops an
ASIO driver only when its last stream is dropped, and a driver left running
replays the buffers it holds, which on Windows is the last buffer heard
looping after the window closes. Closing now hides the window at once, has
the audio callback fade the output to silence over 5 ms and write two whole
silent buffers, then stops the output (and on ASIO the interface's input) on
the output worker, then the input stream on its worker, and lets both
workers exit, before the editor and plugin are torn down
(`audio::close_streams`).
The close button, the macOS Quit item, which now closes the window instead
of terminating the app from inside `AppKit`, and the Ctrl-C handlers of the
capture modes all take that path. Quitting from the Dock or at logout
still terminates the app directly; CoreAudio stops with the process. The
waits are bounded, so a stalled device cannot hold the close.

The Mic Input and Audio Output items have no shortcuts. Cmd+I / Ctrl+I and
Cmd+O / Ctrl+O toggled them, and once the editor passed the keys it does not
use on to the standalone, a stray press while playing silenced the input or
the output. The items stay in the Settings menu. Mic Input and an editor's
input choice share the flag the audio callback reads, so both always show
the same state.

The buffer, device, ring, ASIO, zoom-pin, launch-failure, close and
shortcut changes follow the same fixes in Swanky Amp Pro's copy of this
crate. Keep these fixes here until a pinned upstream
release includes equivalent handling; remove the Cargo patch and this
directory together when upgrading to that release.
