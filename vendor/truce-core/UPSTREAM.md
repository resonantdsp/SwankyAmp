# Real-time reset lifecycle hook

Source: crates.io `truce-core` 6.3.0, upstream commit
`ff6b573c7d845638656b03bbe4b4436559dd9725`, `crates/truce-core` in
[truce](https://github.com/truce-audio/truce).
The governing `LicenseRef-TruceLicense-1.0` text and its MIT and Apache
license texts are included unchanged.

This copy adds the format-facing `reset_realtime` lifecycle hook. Its default
is a no-op for stateless plugins; stateful implementations override it when a
format can reset an active instance on the audio thread. Keep this copy until
a pinned upstream release provides an equivalent lifecycle distinction.
