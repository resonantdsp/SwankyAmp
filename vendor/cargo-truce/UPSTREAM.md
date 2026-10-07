# Vendored cargo-truce patches

Source: crates.io `cargo-truce` 6.3.0. The credential change is kept on
[`azure-exclude-credentials`](https://github.com/gmcgoldr/truce/tree/azure-exclude-credentials)
in a fork of [truce](https://github.com/truce-audio/truce), branched from tag
`v6.3.0`.
The upstream `LICENSE` (Truce License 1.0), `LICENSE-MIT` and `LICENSE-APACHE`
texts are included unchanged. Section 2.2 of the Truce Framework Rider
explicitly excludes audio plug-ins, plug-in suites, analyzers and validators
from Covered Framework Offerings; the Rider separately governs covered
commercial framework products and services.

Both Swanky Amp products carry this crate. Every section before "Where the
products differ" is the same change in both copies.

## Trusted Signing credential chain

Windows binaries and the installer are signed through Azure Artifact Signing.
The signing library authenticates with `DefaultAzureCredential`, which walks its
whole credential chain. A hosted GitHub runner is an Azure VM whose instance
metadata service answers but carries no identity, so the managed-identity
attempt stalls rather than failing: `signtool` never returns and the candidate
job runs until it is cancelled. Nothing outside cargo-truce can prevent it,
because cargo-truce writes the signing metadata file that would say which
credential types to skip.

The only source change reads `TRUCE_AZURE_EXCLUDE_CREDENTIALS` alongside the
other `TRUCE_AZURE_*` variables and writes the named types into that metadata as
the `ExcludeCredentials` field the library already understands. Unset, the
metadata is byte-for-byte what 6.3.0 produced. Microsoft's own
[trusted-signing-action](https://github.com/Azure/trusted-signing-action)
excludes every type but `azureclicredential` by default, for the same reason;
the candidate workflow sets the same list.

## Audio Unit version 2 Info.plist

6.3.0 writes every AU v2 component with `CFBundleVersion` 1 and component
version 65536 (1.0.0), whatever the plugin's version, while truce-au reports
the crate version at runtime. Logic and GarageBand key their validation cache
on the component version, so an update that leaves it unchanged can keep a
stale cached result. The component also always claims `sandboxSafe`, which
Apple's `AudioComponent.h` reserves for components that need no network or
file access outside a sandboxed host's container; one that does must describe
it in a `resourceUsage` dictionary instead.

The change writes the plist once, in `au2_info_plist` in
`src/commands/package/stage.rs`, for both staging and `install`. The bundle
version is the plugin's version without a pre-release suffix, and the
component version packs it the way truce-au does. A `[plugin.au_resource_usage]`
table in `truce.toml` (`network_client`, `files_read_write`) replaces
`sandboxSafe` with the matching `resourceUsage` keys; without it the component
is sandbox-safe as before.

## Windows installers for all users only

6.3.0's unscoped Windows installer opens Inno Setup's "Choose installation
mode" page, and installing only for the current user puts the VST3 in
`%LOCALAPPDATA%\Programs\Common\VST3`. Ableton Live 10 and a default Reaper
never scan that folder, so the plug-in silently goes missing. A Windows package
run therefore always builds the all-users installer: administrator elevation,
the common CLAP, VST3 and Program Files folders, and no mode page. `--system`
is accepted, and `--user`, `--ask` and any other `preferred_scope` are refused.
The installer keeps the unsuffixed `<crate>-<version>-windows.exe` name. The
`.iss` generator's per-user branches stay as upstream wrote them, unreachable
from a package run. macOS packaging is unchanged and still offers both. This
is product policy rather than an upstream fix, so an upstream release replaces
it only with a setting that pins Windows packages to all users.

## Bundle versions

6.3.0 writes `CFBundleVersion` 1 into the CLAP, VST3 and VST2 bundles and
`CFBundleVersion` 1 with `CFBundleShortVersionString` 1.0 into the standalone
app, whatever the plugin's version, so Finder and anything else that reads a
bundle's version see every release as version 1. Staging in
`src/commands/package/stage.rs` now writes both keys as the plugin's version,
without a pre-release suffix, in every bundle and the app, read the same way
as the Audio Unit change above.

## Removal

`just setup` installs cargo-truce from this directory instead of crates.io.
Remove the directory, the setup recipe's `--path` and this file together once
a pinned upstream release carries these changes.

## Where the products differ

### Swanky Amp

This source-only copy was first taken from `resonantdsp/SwankyAmpPro` commit
`47842d2ece1a558fbab85cb8cd68564654414d35` on September 20, 2026.

This copy has no `previous_names` key, so its installers replace only bundles
of the current name, as 6.3.0's do. The `cargo truce screenshot` help no
longer names the standalone's Cmd+S / Ctrl+S, which Swanky Amp's standalone
does not have (see `vendor/truce-standalone/UPSTREAM.md`). The Swanky Amp
repository carries no other Swanky Amp Pro release, licensing, bake-store or
product code.
