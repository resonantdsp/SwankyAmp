# Swanky Amp

Swanky Amp is Resonant DSP's free guitar amplifier. Version 2 is a Rust rebuild of the released Swanky Amp 1.4.0 amplifier model with its tone stack corrected, an iced editor, CLAP and VST3 plug-ins, an Audio Unit on macOS, and a standalone app. It accepts mono, stereo and mono-in, stereo-out host layouts, runs each stereo channel through its own amplifier path, and plays a mono input on both sides of a stereo output.

Version 2 has its own host and installation identity, `Swanky Amp 2` / `com.resonantdsp.swanky-amp-2`, so it installs beside the released `Swanky Amp` and does not take over old sessions. The JUCE 1.4.0 source is kept at the `juce-1.4.0` tag.

## Building and checking

Install Rust through [rustup](https://rustup.rs/) and [just](https://github.com/casey/just); the repository pins its Rust toolchain. The per-change gate is:

```sh
just
```

It checks formatting, runs clippy and runs the crate's tests. CI runs the rest on every pull request, as `.github/workflows/check.yml` defines. Run a part of it locally only when a change touches that area:

- `just release-tests`: the release scripts' tests;
- `just reference-check`: the [released reference renderer](verification/reference/README.md) still reproduces its frozen 1.4.0 renders;
- `just model-check`: the legacy path still matches the released 1.4.0 chain on the ten factory presets;
- `just validate-assets`: an artwork package matches its receipt and the layers it was packed from;
- `just clippy-all` and `just test-all`: the vendored host, the format adapters and the standalone.

The offline tools in `src/bin` build only with the `tools` feature, which keeps them out of the format builds; the recipes that run them turn it on.

### Bundles and the standalone

```sh
just setup      # once: pinned cargo-truce, validators and, on Windows, the ASIO SDK
just validate   # build, install and validate the plug-in bundles
just run        # open the standalone
```

`setup` builds the pinned cargo-truce inside this checkout and downloads checksum-verified pluginval and clap-validator, and on Windows the ASIO SDK. `validate` builds and installs the CLAP and VST3 bundles, and on macOS the Audio Unit, and runs the validators over them, auval among them on macOS.

The standalone opens with its input on, since an amplifier with its input off is silent, but only when the input is a device the player chose, from the Settings menu or with `--input`, and it is connected. The system default input is often a built-in microphone beside the built-in speakers, so on a first launch, or when the chosen interface is unplugged, the input starts off and the footer says how to turn it on; `--input-enabled on` or `off` overrides that for one launch, except that on Windows a launch whose ASIO interface will not open falls back to Windows audio with the input off. Its Settings menu chooses the input, the input channels, the output and the buffer size (128 samples unless chosen) and remembers them on the machine; `--input`, `--output` and `--buffer` override them for one launch (`cargo run --release -- --help` lists every option). Choosing an audio interface as the input takes the output to it too, unless an output has been chosen, and the input is kept within about one buffer of the output.

On Windows the standalone plays through ASIO when an ASIO driver is installed, and its Settings menu chooses between ASIO and Windows (WASAPI); `--driver asio` or `--driver wasapi` overrides that for one launch. On ASIO the interface is one device for input and output. The Windows recipes build the standalone with the Cargo feature `asio`, which compiles the ASIO SDK that `just setup` fetches into `tools/` and needs libclang; no other build compiles it.

## Signal path

The shipping path is the 1.4.0 model with tube-only oversampling, a plate filter whose cutoff holds as the oversampled rate changes, a smooth triode knee, a capped Grit mapping, the standard tone-stack mapping, and level compensation recalibrated against 1.4.0. The legacy path keeps every released mapping so that `just model-check` can prove the port against the frozen 1.4.0 renders.

Oversampling is set in the editor's header: Auto picks the tube stages' factor from the host's sample rate, or the player fixes one. The plug-in reports the oversampling filter's latency to the host, so changing the factor restarts processing for the host to take up the new latency.

These tools render, measure and stress the paths:

```sh
just render-model "high gain" /tmp/high-gain.wav   # one released preset through the legacy path, with its internal seams
just dsp-report        # oversampling and the plate filter against the legacy path; also checks the real-time reset
just knee-report       # the smooth knee against the released one at every seam, per preset and input level
just tone-stack-soak   # 24 hours of samples through the shipping tone stack; fails on any drift (minutes)
```

`dsp-report` and `knee-report` write their measurements under `target/dsp/`, and `knee-report` fails if a seam leaves the released level by more than `verification/dsp/knee.py` allows.

Version 2 ships the standard bilinear tone-stack mapping; 1.4.0's placed every tone-stack feature an octave above the circuit. Anyone who wants the old voicing exactly can keep 1.4.0 installed beside version 2.

### Level calibration

```sh
just calibrate   # rewrite src/dsp/calibration_data.rs, printing every point
```

`calibrate` measures the level compensation on the [guitar recordings](verification/reference/input/README.md), against 1.4.0. It keeps the level into the power stage where 1.4.0 had it at every Drive setting, and holds Init's loudness as Drive, Power Drive and Grit move. `just` tests the result on the same recordings: Drive, Power Drive and Grit at their extremes keep Init's loudness, at default tone each stack feeds the power stage as 1.4.0 did, and the factory defaults play as loud as 1.4.0. The factory voicing uses these levels, so rerun `just refit` after a calibration change and listen to the result.

## Presets

### Factory bank

```sh
just refit
```

rewrites `presets/factory-2.0.xml` and its [voicing report](verification/tone-stack/refit-report.md) from the 1.4.0 presets on the guitar recordings. Low, Mid, High and Presence move on half marks to bring each preset's tonal balance as close to 1.4.0's as the corrected stack allows; Power Drive keeps the level 1.4.0 fed the power stage, and Output brings each preset to Init's strike level on the humbucker. It takes minutes in a release build. The plug-in embeds the bank at build time.

Accepted limits of the corrected stack against 1.4.0:

- 1.4.0's scoop sat an octave higher than any setting of the corrected stack can place it, and the corrected Low acts only at the very bottom. The voiced presets therefore keep the low mids under 1.4.0 and the region around 1.3 kHz over it; the [voicing report](verification/tone-stack/refit-report.md)'s Remaining balance table gives the figures.
- Init is the corrected stack at its defaults and is not revoiced: against 1.4.0 it has 3 to 6.3 dB less between 100 and 400 Hz and 3.8 to 4.7 dB more between 0.8 and 1.6 kHz.
- 1.4.0's level fell with Drive and Power Drive, differently on each pickup. Version 2 holds Init's level averaged over the pickups, so high Drive and Power Drive play louder against Init than they did in 1.4.0, and each pickup lands up to about 3 dB either side of Init.
- On the single coil the driven presets come out louder than Init, because a clean amp follows the pickup where a driven one does not. 1.4.0's factory presets were not balanced at all.

These are measured at 44.1 kHz with Auto oversampling on the three tone stacks, not on blends between them.

### Presets on the player's machine

| Platform | Version 2 | Swanky Amp 1.4.0 |
|---|---|---|
| macOS | `~/Library/Audio/Presets/Resonant DSP/Swanky Amp 2` | `~/Library/Audio/Presets/Resonant DSP/Swanky Amp` |
| Windows | `%APPDATA%\Resonant DSP\Swanky Amp 2` | `%APPDATA%\Resonant DSP\Swanky Amp` |
| Linux | `$XDG_DATA_HOME/Resonant DSP/Swanky Amp 2` (default `~/.local/share`) | `~/.config/Resonant DSP/Swanky Amp` |

The version 2 folder is created when first needed: by a save, by Open folder, or by an import. Each preset is one `<name>.xml` file in the 1.x schema, so version 2 reads 1.4.0 files and 1.4.0 can load a version 2 file. A file that is not a Swanky Amp preset is left out of the menu and named in the footer. Saving never overwrites another preset unless the system dialog asked first, and a save never leaves a preset half written.

As in 1.4.0, Input and the cabinet switch belong to the session: a preset stores them, but choosing one leaves them as they are. The selected preset is part of the plug-in state, so a reopened session shows its name.

The first time version 2 runs without a preset folder, and on Import 1.x presets, it copies the player's presets from the 1.4.0 folder, which it never modifies, and skips names already taken and unchanged copies of 1.4.0's factory presets. An imported preset keeps every control except Low, Mid, High and Power Drive, which a quick fit in the plug-in converts for the corrected stack. That fit judges the stack on a generated pluck rather than the output on a guitar, so imported presets can sound boxier and less scooped than their originals, most where a preset relied on extreme Low, Mid or High.

## Editor

The six signal-flow groups (Levels, Cabinet, Preamp, Staging, Power Amp and Tone) sit on graphite with 1.4's rose as the accent. The bundled CC BY 4.0 artwork package provides the graphite, brushed metal, shadows and lighting; the text is native. The input meter keeps 1.4.0's scale, so the player stages the guitar with Input by eye as before.

### Information panel

The cog left of the preset bar opens the product name and version, Interface size, links to the product page, the manual and support, Copy diagnostics and Third-party licences. In the Windows standalone it also shows the ASIO Compatible logo and Steinberg's trademark line.

Interface size draws the editor at 75, 100, 125 or 150 %. It belongs to the computer: it is saved in `Swanky Amp 2 interface.json`, in `~/Library/Resonant DSP` on macOS, `%APPDATA%\Resonant DSP` on Windows and `$XDG_CONFIG_HOME/Resonant DSP` on Linux, never in presets or host state.

Copy diagnostics puts a short block on the clipboard for a support request: product, version and build commit, operating system and architecture, host and plug-in format, the sample rate and buffer audio last ran at, and the licence. Nothing is sent anywhere.

### Release notice

Opening an editor starts a background check of `https://resonantdsp.com/release-notices/swanky-amp.json`:

```json
{"schemaVersion":1,"productId":"SwankyAmp","currentVersion":"2.0.1"}
```

The website generates it from the promoted release catalogue and emits `"currentVersion":null` until `SwankyAmp` has verified downloads for that version. The plug-in rejects a document over 4 KiB and ignores fields it does not know, so the website can add to the document, within that size, without silencing installed versions. When the version is a strictly newer stable release, the cog turns into a download arrow and the panel announces it with a Download link to the product page, opened only on an explicit press; the document cannot choose a link. Any failure is silent, and every attempt, successful or not, waits 24 hours before the next. The last answer is kept in `Swanky Amp 2 release notice.json` beside the interface size.

The request is a bodyless `GET`. So the website can count monthly unique installs without an identifier, it adds `?first=ever` when this computer has no previous successful check, `?first=month` when the previous successful check was in an earlier calendar month (UTC), and no query otherwise. It sends no custom User-Agent, running version, product key, machine identifier or telemetry. As with any HTTPS request, the website or its delivery provider receives the public IP address and the ordinary connection, TLS, header and timing information needed to serve it.

### Captures and layout export

Captures are review tools for visual work, compared by eye against the accepted references; they are not a check.

```sh
just export-layout /tmp/swanky-layout
just capture /tmp/swanky-capture
just capture-preset "high gain" /tmp/swanky-capture
just capture-live /tmp/swanky-capture
just capture-information /tmp/swanky-capture 2.0.1
just capture-menu "A long preset name of the player's own" /tmp/swanky-capture
```

`export-layout` writes the resolved geometry an artwork bake follows; it works when the artwork package is missing or stale. `capture` draws the editor at every interface size and needs a working GPU adapter; the other capture recipes apply a factory preset, light the meters, open the information panel (announcing the named release, if given) or open the preset menu.

### Artwork

The repository carries the artwork as `assets/artwork.pack` with its `receipt.json` and `ARTWORK-LICENSE.txt` in `assets/artwork`. The editable layers are not committed; they come from the package. To change them, unpack to EXRs and edit in a standard HDR image tool, saving as ZIP-compressed float32 RGB with no alpha (the packer refuses anything else, and many tools default to half float or add alpha); then refresh the receipt, repack and validate:

```sh
just unpack-artwork assets/artwork.pack /tmp/swanky-artwork
just refresh-artwork /tmp/swanky-artwork
just pack-artwork /tmp/swanky-artwork /tmp/swanky-artwork.pack
just validate-assets /tmp/swanky-artwork.pack /tmp/swanky-artwork
```

Packing the unpacked layers unedited reproduces the package byte for byte. To propose an edit, unpack into `assets/artwork` (the EXRs there are ignored by git) and commit the repacked package and refreshed receipt. Replacement artwork needs neither Blender nor the original production sources.

## Long-run soak

The soak is a diagnostic for a suspected long-run defect, such as the tremolo-like drift issue #34 reported in 1.2. It is not a release step.

```sh
just soak 4        # hours of audio per run, started in the background
just soak-check    # verdict so far, or the final one
```

`just soak` runs clean, level 11 and Init on the shipping path and one on the legacy path for comparison, on low-level noise and plucks, and writes its results under `target/soak`; `scripts/soak.sh` says how to choose other runs. The verdict fails on non-finite output, level drift or tremolo. Four hours of audio take about 25 minutes per run on an Apple M-series core.

## Releasing

A release goes candidate tag → candidate workflow → qualification → stable tag → promote workflow. The crate version in `Cargo.toml` is the version authority, and `CHANGELOG.md` must have the matching section. That section's heading carries the planned release date, such as `## 2.0.1 — 2026-11-02`, never "in development": the tagged source is public, and every candidate must be releasable as it stands. `just version` dates a new section; an existing one, such as an "in development" heading, is dated by hand before the first candidate is cut. The website catalogue's date is the day the GitHub Release is published and may differ from the heading; a moved date is never a reason for a new candidate. `[package.metadata.release]` in `Cargo.toml` states whether the release ships a Linux download.

Prepare the version on a branch and land it through a pull request like any change:

```sh
just version 2.0.1      # updates Cargo.toml, Cargo.lock and CHANGELOG.md; never stages or commits
```

Then, on the merged master commit, which CI has checked:

```sh
just tone-stack-soak    # must pass before a candidate
just tag-candidate      # creates the next v2.0.1-rc.N locally
git push origin v2.0.1-rc.1
```

`tag-candidate` fetches first. It refuses changes in tracked files, a checkout other than `origin/master`, a commit that would fail the stable release check (version and dated heading), and a version whose stable tag `origin` already has. It numbers the candidate past every candidate tag held locally or on `origin`. The tag helpers push nothing.

### Candidate workflow

Only `vX.Y.Z-rc.N` tags start `.github/workflows/candidate.yml`, and its first job refuses a tag whose commit is not on master; stable `vX.Y.Z` tags never build. A manual run is a rehearsal, accepted only from an administrator-owned `rehearsal/*` branch; its artifacts use the commit hash and it creates no GitHub Release.

The workflow validates the committed artwork and writes the third-party notices before packaging. It builds a universal macOS package signed with the Resonant DSP Developer ID identities, notarized and stapled, and a Windows x64 installer signed through the Free-specific Azure identity and the shared Resonant DSP publisher profile. Both installers offer an install for all users or the current user; both are installed silently for all users on clean runners, pluginval and clap-validator inspect what was installed, and the workflow verifies the publisher identities and that every packaged binary carries the notices. When the release declares a Linux download, the workflow packages it on Linux, installs and validates the tarball, and records no candidate unless that passes; a release that declares none builds none.

The final job writes `release-record.json` with the tag, commit, version, toolchain, cargo-truce version, lockfile and artwork hashes, shipping identities, and each artifact's size and SHA-256, and creates a draft GitHub Release once. The workflow refuses an RC tag that already has a release, before any signing and again at the end, so new bytes need a new RC number. A run that failed partway resumes with "Re-run failed jobs", unless it failed after creating the draft, which needs a new RC; re-running all jobs is refused once the draft exists.

### Qualification and promotion

A person qualifies the candidate's exact installers in real hosts, checks installation, the interface and audio, and records the SHA-256 printed for `release-record.json`. Acceptance is a release decision; workflow success does not make it one. Besides that, these can only be confirmed on a real machine:

- On Windows, Website, Manual and Support in the information panel, and Download when an update is announced, open the default browser at their page.
- On Windows, a host that unloads the plug-in while the update check, a save dialog or a preset import is running does not crash.
- On Windows, saving a preset while another program holds its file reports an error in the footer and leaves the old preset intact.
- On macOS, opening the Audio Unit in GarageBand twice writes the update check's record beside the interface setting.
- On each platform, Save as… in a system dialog pointed at another folder never replaces a preset in the preset folder.

After acceptance, create the stable tag on the same commit:

```sh
just tag-release v2.0.1-rc.3   # tags the commit origin's v2.0.1-rc.3 names as v2.0.1
git push origin v2.0.1
```

`tag-release` reads the candidate tag from `origin`, never the checkout or a local tag, and checks the version and the dated changelog heading as committed there. It notes when `origin` holds a higher candidate than the one named.

Then dispatch the protected `promote` workflow from `master` (`gh workflow run promote.yml --ref master ...` or the equivalent UI choice), the only branch its `release` environment permits. It takes the RC tag, stable tag, accepted record SHA-256, and a qualification naming the reviewer, date, hosts, machines and findings. It refuses malformed tags before checking anything out, checks out `refs/tags/<tag>` without leaving the token in the tree, and runs the release-script tests from it. It verifies a successful candidate workflow, requires both tags and the checkout to resolve to the recorded commit, rechecks the record and every artifact byte, and creates the stable GitHub Release from those files; it does not compile or sign. A rerun after a later failure resumes only once the existing release's assets prove byte-for-byte identical; it never overwrites a differing asset.

Promotion resolves each public release URL only through GitHub's release-asset host and compares size and SHA-256 with the record, then opens a website pull request for logical product `SwankyAmp` that keeps the 1.4.0 legacy release and publishes version 2 downloads under the `swanky-amp-2` identity. The release date it catalogues is the day the stable GitHub Release was published, so a rerun on a later day changes nothing. The website's own checks and review control that merge. The `release` environment supplies only the `WEBSITE_TOKEN` for that pull request.

`just promote-check CANDIDATE_TAG TAG RECORD_SHA256 DIRECTORY` runs the same identity and byte checks locally and read-only from the stable tag checkout.

### Signing setup

Rulesets let only administrators create, update or delete `v*` tags and `rehearsal/*` branches. The protected `signing` environment allows only `v*-rc.*` tags and `rehearsal/*` branches, so fork and pull-request runs cannot reach it. It holds the Apple material as `APPLE_CERTIFICATES_P12`, `APPLE_CERTIFICATES_PASSWORD`, `APPLE_API_KEY_P8`, `APPLE_API_KEY_ID` and `APPLE_API_ISSUER_ID`.

Windows signing uses a Free-specific Azure application and service principal with a federated identity scoped to this repository's `signing` environment, and a signer-only role on the shared Public Trust profile for the Resonant DSP publisher; it has no access to Pro source or resources. These nonsecret repository variables configure it:

- `AZURE_TENANT_ID`, `AZURE_CLIENT_ID` and `AZURE_SUBSCRIPTION_ID`
- `TRUCE_AZURE_ACCOUNT`, `TRUCE_AZURE_PROFILE` and `TRUCE_AZURE_ENDPOINT`
- `WINDOWS_SIGNER_SUBJECT`, the exact subject expected on the installer, CLAP, VST3 and standalone signatures

The workflow logs in through GitHub OIDC and signs with the token that login gives; no client secret or signing key exists.

## Source and licences

Swanky Amp is licensed under GPLv3 or later; see [LICENSE](LICENSE). The Windows standalone links Steinberg's ASIO SDK 2.3.4, which Steinberg offers under its proprietary agreement or under GPLv3; Swanky Amp takes the GPLv3 option, so that build is distributed under GPLv3. The SDK is fetched at build time, pinned by checksum and never committed. The third-party notices carry its dual-licence text and the BSD licence of its host helpers from `assets/asio-sdk`, the GPLv3 text, and the exact Steinberg package as its source. ASIO is a registered trademark of Steinberg Media Technologies GmbH; GPLv3 does not cover the name or logo, so their use follows Steinberg's usage guidelines for SDK 2.3.4, which ask for the ASIO Compatible logo in the About panel of an application that runs on ASIO by default. The information panel shows it; `assets/asio-compatible.svg` is Steinberg's artwork, unchanged.

The model authority is the Swanky Amp 1.4.0 C++ wrapper and generated Faust headers preserved in `verification/reference/released` from the `juce-1.4.0` tag. Small equation and filter primitives were adapted from the separately implemented Pro code only where comparison proved they express the released equations. This repository contains no Pro parameter grids, cabinet impulse responses, pedals, gate, reverb, licensing logic, Blender sources, artwork production sources or shared private DSP.

The artwork in `assets/artwork.pack`, and the layers unpacked from it, is licensed under CC BY 4.0; see `assets/artwork/ARTWORK-LICENSE.txt`. The editor uses PT Sans under the SIL Open Font License, in `assets/fonts/PTSans-OFL.txt`.

The information panel's Third-party licences link opens the notices the plug-in embeds: the font's licence, every crate the shipped formats link, grouped by licence, the ASIO SDK's licences and source, and the Truce License. `just notices` writes them to `THIRD-PARTY-NOTICES.txt` with a pinned cargo-about from `about.toml` and `about.hbs`. The candidate workflow runs it before packaging and names the file in `THIRD_PARTY_NOTICES`, which `build.rs` embeds; a build without that variable embeds a one-line placeholder, so local builds never generate the notices. Every licence `about.toml` accepts is compatible with GPLv3.

### Vendored crates

Narrow patches of the published Truce sources and of baseview, each directory carrying its unchanged upstream licences, original manifest, source reference and an `UPSTREAM.md` describing the local changes:

- `vendor/baseview-truce`: frame delivery and host keyboard and modifier fixes.
- `vendor/truce-iced`: iced input, focus, redraw and clipboard fixes.
- `vendor/truce-clap`: host state notification required by clap-validator, dynamic-latency restart and active reset handling.
- `vendor/truce-standalone`: dynamic-latency restart on the output worker, an input kept within about one buffer of the output, a Buffer Size menu, remembered devices, input channels and buffer size, an input that starts live only on a chosen device with a line saying why it is off, and ASIO on Windows.
- `vendor/truce-core`, `vendor/truce-plugin`, `vendor/truce-loader` and `vendor/truce`: a real-time reset lifecycle hook and its forwarding bridge.
- `vendor/truce-au`: a latency change reaches the Audio Unit host's property listeners.
- `vendor/cargo-truce`: the source-only build tool with the Azure `ExcludeCredentials` patch, the Audio Unit Info.plist patch and the scoped Windows installer name. It is a build tool, not linked into the plug-in. The Truce Framework Rider's Section 2.2 lists audio plug-ins and suites among the uses that are not Covered Framework Offerings.

Everything else resolves from the pinned Cargo lockfile.
