# Swanky Amp

Swanky Amp is Resonant DSP's free guitar amplifier. This repository is being rebuilt in Rust for version 2. The current version 2 tree is the product shell: it passes audio through unchanged and proves the plugin, iced editor, standalone app, bundle build, and format-validation paths before the amplifier model and finished interface land.

The released JUCE 1.4.0 source is preserved at the `juce-1.4.0` tag. Version 2 deliberately uses a new host and installation identity, `Swanky Amp 2` / `com.resonantdsp.swanky-amp-2`, so it installs beside the released `Swanky Amp` and does not take over old sessions.

## Development

Install Rust through [rustup](https://rustup.rs/) and install [just](https://github.com/casey/just). The repository pins its Rust toolchain. Run the complete per-change gate with:

```sh
just
```

The gate checks formatting, lints the shell with and without the plugin-format features, runs its tests, and checks the [released reference renderer](verification/reference/README.md). It does not claim to validate artwork before an artwork package exists.

After `just setup`, open the standalone shell with:

```sh
just run
```

Bundle validation is a separate platform check:

```sh
just setup
just validate
```

`setup` installs cargo-truce 6.3.0 inside this checkout and downloads checksum-verified builds of pluginval and clap-validator. `validate` builds and installs the CLAP and VST3 bundles and runs both validators. GitHub Actions builds the standalone and runs the same bundle validation on macOS and Windows without signing or repository secrets.

## Source and licences

Swanky Amp is licensed under GPLv3 or later; see [LICENSE](LICENSE). The version 2 shell contains no Swanky Amp Pro product DSP, licensing logic, artwork, impulse responses, Blender sources, or production tooling. Later amplifier work uses the released Free source as its model authority.

Three framework patches were copied from the corresponding vendored upstream sources in the Swanky Amp Pro checkout because the shell exercises their public behavior:

- `vendor/baseview-truce`: frame delivery and host keyboard/modifier fixes.
- `vendor/truce-iced`: iced input, focus, redraw, and clipboard fixes.
- `vendor/truce-clap`: host state notification required by clap-validator.

Each directory carries its unchanged upstream licence files, original manifest, source reference, and a focused `UPSTREAM.md` description of the local changes. Everything else resolves from the pinned Cargo lockfile.
