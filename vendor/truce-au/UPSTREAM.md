# Vendored truce-au patches

Source: crates.io `truce-au` 6.3.0, upstream commit
`ff6b573c7d845638656b03bbe4b4436559dd9725`, `crates/truce-au` in
[truce](https://github.com/truce-audio/truce). The published crate carries no
license files; the `LICENSE`, `LICENSE-MIT` and `LICENSE-APACHE` texts here are
the same upstream texts the other vendored truce crates include.

Both Swanky Amp products carry this crate. Every section before "Where the
products differ" is the same change in both copies.

Remove the Cargo patch and this directory when a pinned upstream release lets
an AU v2 editor resize its container and notifies property listeners of a
latency change.

# Editor-requested resize in the Audio Unit v2

An AU v2 host such as Logic sizes its plug-in window from the frame of the view
the plug-in hands it, and the published wrapper pins that container view to
the size it had when it was opened. `PluginContext::request_resize` resized
only the editor inside it, so an editor that changes its own size (the
interface zoom) was clipped by the old container. The request now also sets
the container's frame through `truce_au_resize_view`, after the editor has
taken the size, and the container still pins itself to what the editor
reports. Logic, and any host that observes the view's frame, follows. AU v2
has no resize protocol, so a host that ignores frame changes keeps the old
window.

The change touches three places, so another fork of this crate can carry it
by hand:

- `shim/au_v2_view.m`: the new `truce_au_resize_view` function, which calls
  `setFrameSize:` on the container, and the container's doc comment.
- `src/ffi.rs`: its `extern "C"` declaration, macOS only.
- `src/lib.rs`, `cb_gui_open`: the container pointer is captured as
  `container`, and the `request_resize` closure calls `truce_au_resize_view`
  once the editor has accepted the size and the `gui` cell is released.

# Latency change reaches the host's property listeners

When the plugin's latency changes, the published AU v2 shim broadcasts it with
`AUEventListenerNotify` only. A host learns of property changes through the
listeners it registered with `AudioUnitAddPropertyListener`, which that call
never reaches: a test host listening for `kAudioUnitProperty_Latency` saw no
callback when the Oversampling choice moved the reported latency from 32 to
48 samples. One call in
`shim/au_v2_shim.c`, in `truce_au_v2_host_latency_changed`, also notifies
those listeners, on the notifier thread that already runs it, off the audio
thread.

# Where the products differ

Swanky Amp's copy notifies the property listeners before the
`AUEventListenerNotify` broadcast, and keeps the crate's own `Cargo.lock`.
