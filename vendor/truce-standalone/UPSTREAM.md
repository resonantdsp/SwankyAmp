# Standalone latency restart, input latency and remembered audio settings

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

The buffer, device and ring changes follow the same fix in Swanky Amp Pro's
copy of this crate. Keep these fixes here until a pinned upstream release
includes equivalent handling; remove the Cargo patch and this directory
together when upgrading to that release.
