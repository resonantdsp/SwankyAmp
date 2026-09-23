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

The shipping path applies Auto oversampling to the nonlinear tube stages while the cabinet remains at the host rate. Auto uses 2x at 44.1 and 48 kHz and 1x at 88.2 kHz and above; fixed 1x, 2x, and 4x choices are capped below 193.92 kHz internally. The host receives the measured FIR delay: 32 samples at 2x and 48 samples at 4x. CLAP and VST3 changes request the host's deactivate/activate sequence; the standalone stops and rebuilds its output stream on the existing worker. An active CLAP reset clears processing history at the current factor with a bounded, allocation-free equilibrium calculation. Activation applies the pending factor off the audio thread. Choices that resolve to the active factor keep their state without a restart. The plate low-pass stays at 20 kHz as the tube rate changes and reproduces the released coefficients at 44.1 kHz.

Regenerate the public factor, latency, seam-level, and aliasing measurements with:

```sh
just dsp-report
```

The report keeps the released knee and tone mapping in both paths, uses the explicit legacy renderer for the baseline, and measures active-reset equilibrium across all ten factory presets, control extremes, and supported rates. It does not establish factory-preset acceptance for the corrected sound.

The versioned reference corpus captures the released cold startup, including its 1024-sample output mute. The Rust path settles its configured nonlinear state for one second before audio begins, and stages re-enter warm when the continuous stage-count control brings them back into the signal path. Model comparison therefore applies the same one-second silent pre-roll to the released chain and excludes it from the measured WAVs. The cold corpus and warmed comparison remain separate so the startup difference is explicit.

After `just setup`, open the standalone shell with:

```sh
just run
```

The editor uses one iced widget tree for the live controls and the artwork
layout contract. As in 1.4, the six Free signal-flow groups (Levels, Cabinet,
Preamp, Staging, Power Amp and Tone) are separate rounded boxes with graphite
between them, each outlined by its own V groove. Pro's material language
carries over with 1.4's rose highlight as Free's accent on the lit rings,
the selected outlines and the output meter. The bundled CC BY 4.0 material
layers provide the graphite, brushed metal, shadows, and response lighting.
Export the exact resolved geometry (layout manifest schema 2, which gives each
section its outline radius) or capture the editor at 1x and 2x with:

```sh
just export-layout /tmp/swanky-layout
just capture /tmp/swanky-capture
```

`capture` needs a working GPU adapter. The layout export remains available when
the artwork package is missing or stale so a new bake can be produced from
changed widget geometry.

Artwork contributors can make a public, reproducible round trip without the
production renderer. Unpack the deterministic RGB9E5 package to editable ZIP
float32 RGB EXRs, edit them in a standard HDR image tool, refresh the receipt,
then repack and validate:

```sh
just unpack-artwork assets/artwork.pack /tmp/swanky-artwork
just refresh-artwork /tmp/swanky-artwork
just pack-artwork /tmp/swanky-artwork /tmp/swanky-artwork.pack
just validate-assets /tmp/swanky-artwork.pack /tmp/swanky-artwork
```

The receipt records the scene-linear radiance and display-linear shadow
semantics, dimensions, hashes, and public layout provenance. Producer metadata
is descriptive, so replacement CC artwork does not depend on Blender or the
original production sources. `just` validates that the checked-in package is
the deterministic result of the editable layers.

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

## Release notices

Opening an editor starts a background check for the static current-release
document at
`https://resonantdsp.com/release-notices/swanky-amp.json`. The document is at
most 4 KiB and has this schema:

```json
{"schemaVersion":1,"productId":"SwankyAmp","currentVersion":"2.0.1"}
```

The website emits `"currentVersion":null` until `SwankyAmp` is available and
has verified downloads for that same version. The endpoint does not exist yet;
the website change that generates it from the promoted release catalogue is a
separate deployment. A missing endpoint, an offline computer, an invalid
document and a timeout are all silent.

The plugin accepts only a strict stable `major.minor.patch` version and
compares it numerically, component by component, with the running version.
The header carries a small outlined information action to the left of the
preset bar. When the document names a strictly newer version, that action
turns into a highlighted download arrow, and an explicit press on it opens the
fixed tagged catalogue URL
`https://resonantdsp.com/products/swanky-amp/?utm_source=swanky-amp-2&utm_medium=plugin&utm_campaign=release-notice`
in the default browser; the downloaded document cannot choose a link. At rest
the action does nothing when pressed.

The check has a three-second total timeout, follows no redirects and retains its
last valid answer and last attempt time in the process. It also stores them
under the operating system's cache directory in
`Resonant DSP/Swanky Amp 2/release-notice.json` when that location is writable.
Successful and failed attempts both wait 24 hours before another request, even
when the cache cannot be written. Invalid or future cache timestamps trigger a
check instead of suppressing one indefinitely. All filesystem and network work
stays on the notice worker, outside audio processing.

The request is a bodyless `GET` to the exact document URL above. It sends no query,
custom User-Agent, running version, product key, machine identifier or user
telemetry. As with any HTTPS request, the website or its delivery provider
receives the public IP address and ordinary connection, TLS, HTTP-header and
request-timing information needed to serve and operate the endpoint.

## Source and licences

Swanky Amp is licensed under GPLv3 or later; see [LICENSE](LICENSE). The model authority is the exact Free 1.4.0 C++ wrapper and generated Faust headers preserved in `verification/reference/released` from the `juce-1.4.0` tag. The public legacy renderer retains the released control mappings, detuning, fitted constants, stage behavior, calibration tables, cubic knee, fixed digital plate filter, and old tone mapping. The shipping path currently adds tube-only oversampling and a rate-tracked 20 kHz plate filter; later corrected-model work remains subject to measurement and player audition. Small equation and filter primitives were selectively adapted from the separately implemented Pro code only where comparison proved that they express the released Free equations.

The editable artwork in `assets/artwork` is licensed under CC BY 4.0; see its
`ARTWORK-LICENSE.txt`. The editor typography uses PT Sans under the SIL Open
Font License in `assets/fonts/PTSans-OFL.txt`.

This repository contains no Pro parameter grids, cabinet impulse responses, pedals, gate, reverb, licensing logic, Blender sources, artwork production sources, or shared private DSP dependency.

Three existing framework patches were copied from the corresponding vendored upstream sources in the Swanky Amp Pro checkout because the plugin exercises their public behavior:

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

The dynamic-latency work adds narrow copies from the exact published Truce 6.3.0 sources:

- `vendor/truce-clap`: dynamic-latency restart and active reset handling, extending the existing state-notification copy.
- `vendor/truce-standalone`: dynamic-latency restart on the output worker.
- `vendor/truce-core`, `vendor/truce-plugin`, `vendor/truce-loader`, and `vendor/truce`: the narrow real-time reset lifecycle hook and its forwarding bridge.

Each Truce directory carries the unchanged governing Truce licence and MIT and Apache texts, original manifest, source reference, and a focused `UPSTREAM.md` description of the local changes. `vendor/baseview-truce` carries its own MIT and Apache licence texts and provenance. Everything else resolves from the pinned Cargo lockfile.
