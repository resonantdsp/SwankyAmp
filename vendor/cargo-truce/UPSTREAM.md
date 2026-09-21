# Trusted Signing credential chain fix

Source: crates.io `cargo-truce` 6.3.0 with one patch, kept on
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

`just setup` installs cargo-truce from this directory instead of crates.io.
Remove the directory, the setup recipe's `--path` and this file together once a
pinned upstream release carries the setting.
