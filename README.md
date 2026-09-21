# Swanky Amp

Swanky Amp is Resonant DSP's free guitar amplifier. Version 2 is a Rust rebuild with the released Free 1.4.0 amplifier model, an iced editor, a standalone app, and CLAP and VST3 formats. It accepts mono and stereo host layouts and processes stereo channels through independent amplifier paths.

The released JUCE 1.4.0 source is preserved at the `juce-1.4.0` tag. Version 2 deliberately uses a new host and installation identity, `Swanky Amp 2` / `com.resonantdsp.swanky-amp-2`, so it installs beside the released `Swanky Amp` and does not take over old sessions.

## Development

Install Rust through [rustup](https://rustup.rs/) and install [just](https://github.com/casey/just). The repository pins its Rust toolchain. Run the complete per-change gate with:

```sh
just
```

The gate checks formatting, lints with and without the plugin-format features, runs the behavioral tests, verifies the [released reference renderer](verification/reference/README.md), and compares the Rust amplifier against all ten released factory presets at 44.1 kHz and 1x processing.

Render one preset and its internal comparison seams with:

```sh
just render-model "high gain" /tmp/high-gain.wav
```

`just model-check` runs the ten-preset comparison by itself. It checks every active triode plus the tone stack, power amp, cabinet, and final output. The fixed acceptance bounds are 0.2% relative waveform RMS, 0.6% relative peak error, and 0.02 dB in each low, mid, and high band.

The versioned reference corpus captures the released cold startup, including its 1024-sample output mute. The Rust path settles its configured nonlinear state for one second before audio begins, and stages re-enter warm when the continuous stage-count control brings them back into the signal path. Model comparison therefore applies the same one-second silent pre-roll to the released chain and excludes it from the measured WAVs. The cold corpus and warmed comparison remain separate so the startup difference is explicit.

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

Swanky Amp is licensed under GPLv3 or later; see [LICENSE](LICENSE). The model authority is the exact Free 1.4.0 C++ wrapper and generated Faust headers preserved in `verification/reference/released` from the `juce-1.4.0` tag. The Rust port retains the released control mappings, detuning, fitted constants, stage behavior, calibration tables, old cubic knee, and old tone mapping. Small equation and filter primitives were selectively adapted from the separately implemented Pro code only where comparison proved that they express the released Free equations.

This repository contains no Pro parameter grids, cabinet impulse responses, pedals, gate, reverb, licensing logic, Blender sources, artwork production sources, or shared private DSP dependency.

Three framework patches were copied from the corresponding vendored upstream sources in the Swanky Amp Pro checkout because the plugin exercises their public behavior:

- `vendor/baseview-truce`: frame delivery and host keyboard/modifier fixes.
- `vendor/truce-iced`: iced input, focus, redraw, and clipboard fixes.
- `vendor/truce-clap`: host state notification required by clap-validator.

Each directory carries its unchanged upstream licence files, original manifest, source reference, and a focused `UPSTREAM.md` description of the local changes. Everything else resolves from the pinned Cargo lockfile.
