# truce-clap

CLAP format wrapper for the truce audio plugin framework.

## Overview

Bridges a truce `PluginExport` implementation to the
[CLAP](https://cleveraudio.org/) plugin API. The `export_clap!` macro generates
the CLAP entry point, plugin descriptor, and all required extension callbacks so
the plugin appears as a native CLAP plugin to any compatible host.

User plugins typically take a direct optional dep on this crate
(`truce-clap = { workspace = true, optional = true }`) gated behind a
`clap` Cargo feature; the `truce::plugin!` macro emits a
`::truce_clap::export_clap!(...)` call when that feature is on. `cargo
truce build --clap` / `install --clap` selects it at the CLI.

## What it handles

- CLAP entry point and plugin factory
- Plugin descriptor (name, ID, vendor, features)
- Parameter mapping (clap-params extension)
- Audio processing bridge
- State save/restore (clap-state extension)
- GUI embedding (clap-gui extension)
- Note port configuration (clap-note-ports extension)

## Key macro

- **`export_clap!`** -- generates the CLAP entry point for a `PluginExport` type

Part of [truce](https://github.com/truce-audio/truce). [Docs](https://truce.audio/docs/).
