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

`just model-check` runs the ten-preset comparison by itself. It checks every active triode plus the tone stack, power amp, cabinet, and final output. The fixed acceptance bounds are 0.2% relative waveform RMS, 0.65% relative peak error, and 0.02 dB in each low, mid, and high band. The peak bound covers the measured 0.627% level-11 power-stage difference from a noncontracting C++ build; RMS and band bounds remain unchanged and retain the timing, polarity, state, and voicing checks.

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

`setup` builds the repository's source-pinned cargo-truce 6.3.0 inside this
checkout and downloads checksum-verified builds of pluginval and clap-validator.
`validate` builds and installs the CLAP and VST3 bundles and runs both
validators. GitHub Actions builds the standalone and runs the same bundle
validation on macOS and Windows without signing or repository secrets.

## Releasing

The crate version in `Cargo.toml` is the version authority. `CHANGELOG.md` must
have the matching section. The local helpers do not push anything:

```sh
just version 2.0.1
just
git add Cargo.toml Cargo.lock CHANGELOG.md
git commit -m "Release version 2.0.1"
just tag-candidate       # creates the next v2.0.1-rc.N locally
git push origin v2.0.1-rc.1
```

`just version` preflights the changelog and prepares only those three version
files. It never stages or commits them. The tag helpers require a clean tracked
working tree so each tag describes the committed version that passed `just`.

Only `vX.Y.Z-rc.N` tags start `.github/workflows/candidate.yml`. A manual run is
a rehearsal and is accepted only from an administrator-owned `rehearsal/*`
branch; its artifacts use the commit hash and it creates no GitHub Release.
Stable `vX.Y.Z` tags never build.

The candidate workflow validates the committed artwork before packaging. It
builds a universal macOS package signed with the existing Resonant DSP Developer
ID identities, notarizes and staples it, and builds a Windows x64 installer
signed through the Free-specific Azure CI identity and shared Resonant DSP
publisher profile. Both installers are installed on clean runners; pluginval
and clap-validator inspect what was installed, and the workflows verify the
publisher identities. Linux packaging is attempted on Ubuntu 22.04. Its tarball
is included only if installing and validating it succeeds; a Linux failure does
not discard qualified macOS and Windows candidates and does not create an
unqualified Linux download.

The final job writes `release-record.json` with the RC tag, commit, version,
toolchain, patched cargo-truce version, Cargo lockfile and artwork hashes,
shipping identities, and each artifact's size and SHA-256. An RC tag creates a
draft GitHub Release once. A rerun refuses to replace an existing draft, so any
new bytes require a new RC number and a fresh review. Workflow artifacts are
also retained for rehearsals and inspection.

The public interface pull request must land before the first candidate. It owns
`assets/artwork.pack` and the `just validate-assets` recipe invoked by every
candidate platform; this release branch intentionally does not duplicate that
format contract.

### Signing setup

The repository's release-tag `v*` and `rehearsal/*` branch rules allow only
administrators to create, update or delete those refs. The protected `signing`
environment allows only `v*-rc.*` tags and `rehearsal/*` branches. Fork and
pull-request runs have no path to it. The seven Windows variables below are
configured for the Free-specific OIDC identity and shared Resonant DSP
publisher profile. Apple secrets and the release environment's website token
remain to be provisioned. Store the existing Apple material in `signing` as
`APPLE_CERTIFICATES_P12`, `APPLE_CERTIFICATES_PASSWORD`, `APPLE_API_KEY_P8`,
`APPLE_API_KEY_ID`, and `APPLE_API_ISSUER_ID`.

Create a Free-specific Azure application and service principal with a federated
identity scoped to this repository's `signing` environment. Its signer-only
role may use the existing Public Trust profile for the same Resonant DSP
publisher; Free does not need a second certificate profile or access to Pro
source and runtime resources. Configure these nonsecret repository variables:

- `AZURE_TENANT_ID`, `AZURE_CLIENT_ID`, and `AZURE_SUBSCRIPTION_ID`
- `TRUCE_AZURE_ACCOUNT`, `TRUCE_AZURE_PROFILE`, and `TRUCE_AZURE_ENDPOINT`
- `WINDOWS_SIGNER_SUBJECT`, the exact subject expected on the installer, CLAP,
  VST3 and standalone signatures

The workflow downloads Trusted Signing Client 1.0.95, logs in through GitHub
OIDC, and takes a signing-service token while the federated assertion is still
valid. Its checkout-local cargo-truce patch writes `ExcludeCredentials` so the
signing library uses that Azure CLI token instead of hanging in the hosted
runner's managed-identity probe. No client secret or signing key is created.

### Qualification and promotion

A person qualifies an RC's exact installers in real hosts, checks installation,
the interface and audio, and records the SHA-256 printed for
`release-record.json`. Acceptance remains a release decision; workflow success
does not make it one. Only after acceptance does an operator create the stable
tag on the same commit:

```sh
just tag-release
git push origin v2.0.1
```

The protected `promote` workflow must be dispatched from `master` (with
`gh workflow run promote.yml --ref master ...` or the equivalent UI choice),
the only branch its `release` environment permits. It takes the RC tag, stable
tag, accepted record SHA-256, and a qualification naming the reviewer, date,
hosts, machines and findings. It verifies a successful candidate workflow,
requires both tags and the checkout to resolve to the recorded commit, rechecks
the record plus every artifact byte, and then creates the stable GitHub Release
from those files. It does not compile or sign. If a later proof or website step
failed after the stable release was created, a rerun resumes only after
downloading that release and proving its entire asset inventory is byte-for-byte
identical; it never overwrites a differing asset. The `release` environment
supplies only the `WEBSITE_TOKEN` needed to prepare the website pull request.

Promotion resolves each public GitHub Release URL only through GitHub's official
release-asset host and compares its size and SHA-256 with the qualified record.
It then opens a website pull request for logical product `SwankyAmp`, retaining
the archived 1.4.0 fields while publishing version 2 downloads under the
`swanky-amp-2` identity. The website's own checks and operator review control
that merge.
`just promote-check CANDIDATE_TAG TAG RECORD_SHA256 DIRECTORY` runs the local,
read-only identity and byte checks from the stable tag checkout.

## Source and licences

Swanky Amp is licensed under GPLv3 or later; see [LICENSE](LICENSE). The model authority is the exact Free 1.4.0 C++ wrapper and generated Faust headers preserved in `verification/reference/released` from the `juce-1.4.0` tag. The Rust port retains the released control mappings, detuning, fitted constants, stage behavior, calibration tables, old cubic knee, and old tone mapping. Small equation and filter primitives were selectively adapted from the separately implemented Pro code only where comparison proved that they express the released Free equations.

This repository contains no Pro parameter grids, cabinet impulse responses, pedals, gate, reverb, licensing logic, Blender sources, artwork production sources, or shared private DSP dependency.

Three framework patches were copied from the corresponding vendored upstream sources in the Swanky Amp Pro checkout because the plugin exercises their public behavior:

- `vendor/baseview-truce`: frame delivery and host keyboard/modifier fixes.
- `vendor/truce-iced`: iced input, focus, redraw, and clipboard fixes.
- `vendor/truce-clap`: host state notification required by clap-validator.

The source-only `vendor/cargo-truce` copy is the published 6.3.0 build tool with
one Azure `ExcludeCredentials` patch copied from the Pro release chain. Its
unchanged upstream Truce License 1.0, `LICENSE-MIT` and `LICENSE-APACHE` files
and a precise source and patch record are included in that directory. The Truce
Framework Rider's Section 2.2 explicitly lists audio plug-ins and suites among
the uses that are not Covered Framework Offerings; covered commercial framework
products and services remain subject to the Rider. Cargo-truce is a build tool
and is not linked into the plugin.

Each directory carries its unchanged upstream licence files, original manifest, source reference, and a focused `UPSTREAM.md` description of the local changes. Everything else resolves from the pinned Cargo lockfile.
