# Latency change reaches the host's property listeners

Source: crates.io `truce-au` 6.3.0, upstream commit
`ff6b573c7d845638656b03bbe4b4436559dd9725`, `crates/truce-au` in
[truce](https://github.com/truce-audio/truce). The published crate carries no
license files; the `LICENSE`, `LICENSE-MIT` and `LICENSE-APACHE` texts here are
the same upstream texts the other vendored truce crates include.

When the plugin's latency changes, the published AU v2 shim broadcasts it with
`AUEventListenerNotify` only. A host learns of property changes through the
listeners it registered with `AudioUnitAddPropertyListener`, which that call
never reaches: a test host listening for `kAudioUnitProperty_Latency` saw no
callback when the Oversampling choice moved the reported latency from 32 to
48 samples. The one change in `shim/au_v2_shim.c` also calls those listeners
from `truce_au_v2_host_latency_changed`, on the notifier thread that already
runs it, off the audio thread.

# Editor-requested resize in the Audio Unit v2

An AU v2 host such as Logic sizes its plug-in window from the frame of the view
the plug-in hands it, and the published wrapper pins that container view to
the size it had when it was opened. `PluginContext::request_resize` resized
only the editor inside it, so an editor that changes its own size (the
interface zoom) was clipped by the old container. The request now also sets
the container's frame through `truce_au_resize_view` in `shim/au_v2_view.m`,
after the editor has taken the size, and the container still pins itself to
what the editor reports. Logic, and any host that observes the view's frame,
follows. AU v2 has no resize protocol, so a host that ignores frame changes
keeps the old window. The change touches `shim/au_v2_view.m` (the new function
and the container's doc comment), its declaration in `src/ffi.rs`, and
`cb_gui_open` in `src/lib.rs`, which captures the container and resizes it once
the editor has accepted the size. It is the same change as Swanky Amp Pro's
copy of this crate.

Keep this copy until a pinned upstream release notifies property listeners of
a latency change and lets an AU v2 editor resize its container; remove the
Cargo patch and this directory together then.
