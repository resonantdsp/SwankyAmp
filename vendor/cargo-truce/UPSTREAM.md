# Vendored cargo-truce patches

Source: crates.io `cargo-truce` 6.3.0 with the two patches below. The first is
kept on
[`azure-exclude-credentials`](https://github.com/gmcgoldr/truce/tree/azure-exclude-credentials)
in a fork of [truce](https://github.com/truce-audio/truce), branched from tag
`v6.3.0`. The upstream `LICENSE` (Truce License 1.0), `LICENSE-MIT` and
`LICENSE-APACHE` texts are included unchanged. Section 2.2 of the Truce
Framework Rider explicitly excludes audio plug-ins, plug-in suites, analyzers
and validators from Covered Framework Offerings; the Rider separately governs
covered commercial framework products and services.

This source-only copy was taken from `resonantdsp/SwankyAmpPro` commit
`47842d2ece1a558fbab85cb8cd68564654414d35` on September 20, 2026. The Free
repository carries no other Pro release, licensing, bake-store or product code.

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

## Scoped Windows installer name

A package run given an install scope (`--user`, `--system`, or
`preferred_scope` in `truce.toml`) looks for
`<crate>-<version>-windows-<scope>.exe`, the same suffix the macOS `.pkg`
carries, but the Inno Setup script it generates names the output without the
suffix. ISCC succeeds and the run then fails with "ISCC reported success but
installer is missing". Only the unscoped default (`ask`) worked, which is why
Pro, which passes no scope, never saw it. The candidate workflow passes
`--system` so the silent CI install lands in the system paths it verifies.

The change adds the scope suffix to `OutputBaseFilename` in both the per-plugin
and suite `[Setup]` sections of `src/commands/package/windows.rs`, so the file
ISCC writes is the one the run expects. An unscoped run names its installer
exactly as 6.3.0 did. Upstream `main` still writes the unsuffixed name as of
`truce-audio/truce@25791270cf7ca1309cb6bdc6fa75a6fe94617d1c`.

## Removal

`just setup` installs cargo-truce from this directory instead of crates.io.
Remove the directory, the setup recipe's `--path` and this file together once a
pinned upstream release carries both changes.
