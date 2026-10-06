# Multisampled meshes cover only their own region

Source: crates.io `iced_wgpu` 0.14.0 from
[iced](https://github.com/iced-rs/iced). The crate is MIT licensed; the license
applies unchanged.

The published renderer draws every layer that holds meshes into a 4x
multisampled texture the size of the whole frame: it clears that texture,
resolves it and blends the result over the whole frame, however small the
meshes are. On the amp view the meshes cover under a tenth of the window, yet
a running display paid for full-window traffic every frame, which kept an
integrated GPU busy.

`src/triangle.rs` gives each mesh layer the frame region its meshes' clip
bounds cover. `src/triangle/msaa.rs` gives each layer its own multisampled
target of exactly that size, because every layer is prepared before any is
drawn; it projects the meshes into the target, offsets their scissors, and
blits the target back over that region alone. Snapping is still computed
against the frame's projection, so the output matches the published renderer
to rasterization rounding at edges.

Each layer's projection now depends on its region, so one mesh cache drawn in
two layers in the same frame would be uploaded for the last of them only. The
editor draws no shared caches.

Keep the change here until a pinned upstream release sizes the multisampled
target to the meshes; remove the Cargo patch and this directory together when
upgrading to that release.
