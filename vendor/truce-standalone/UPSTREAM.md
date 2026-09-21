# Standalone dynamic-latency restart fix

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

Keep the fix here until a pinned upstream release includes equivalent dynamic
latency handling; remove the Cargo patch and this directory together when
upgrading to that release.
