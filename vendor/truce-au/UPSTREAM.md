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

Keep this copy until a pinned upstream release notifies property listeners of
a latency change; remove the Cargo patch and this directory together then.
