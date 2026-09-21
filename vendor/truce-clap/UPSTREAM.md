# CLAP state and dynamic-latency notification fixes

Source: crates.io `truce-clap` 6.3.0, upstream commit
`ff6b573c7d845638656b03bbe4b4436559dd9725`, `crates/truce-clap` in
[truce](https://github.com/truce-audio/truce).
The upstream `LICENSE` (Truce License 1.0), `LICENSE-MIT` and `LICENSE-APACHE`
texts are included unchanged.

The published adapter restores parameter values without notifying the host.
Hosts can consequently retain stale controls after session or preset loading.
The only source changes notify `clap_host_params.rescan` with
`CLAP_PARAM_RESCAN_VALUES` after a successful state or preset parameter restore.
Both entry points are main-thread CLAP callbacks.

The published adapter also updates its latency cache and calls
`clap_host_latency.changed` while the plugin remains active. CLAP requires the
reported latency to stay constant through an activation. This copy requests a
restart when processing first observes a different requested latency, then
publishes and notifies the freshly reset latency during the next activation.
An active CLAP reset calls the real-time lifecycle hook, preserving the active
latency while clearing the current processing history. The full off-thread
reset remains the activation path that adopts the requested latency.

The public contract is described in
[CLAP parameters](https://github.com/free-audio/clap/blob/main/include/clap/ext/params.h).
`clap-validator` 0.4.1 detects the missing notification in its state reproducibility
checks. Run the validator against the built product bundle when changing this
adapter. Keep the fix here until a pinned upstream release includes it; remove the
Cargo patch and this directory together when upgrading to that release.
