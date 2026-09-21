# CLAP state notification fix

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

The public contract is described in
[CLAP parameters](https://github.com/free-audio/clap/blob/main/include/clap/ext/params.h).
`clap-validator` 0.4.1 detects the missing notification in its state reproducibility
checks. Run the validator against the built product bundle when changing this
adapter. Keep the fix here until a pinned upstream release includes it; remove the
Cargo patch and this directory together when upgrading to that release.
