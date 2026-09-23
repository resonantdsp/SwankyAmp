# Real-time reset lifecycle hook

Source: crates.io `truce-plugin` 6.3.0, upstream commit
`ff6b573c7d845638656b03bbe4b4436559dd9725`, `crates/truce-plugin` in
[truce](https://github.com/truce-audio/truce).
The governing `LicenseRef-TruceLicense-1.0` text and its MIT and Apache
license texts are included unchanged.

This copy exposes `reset_realtime` on the plugin logic traits and forwards it
through the sample-precision bridge. Its default is a no-op for stateless
plugins. Keep this copy until a pinned upstream release provides an equivalent
lifecycle distinction.
