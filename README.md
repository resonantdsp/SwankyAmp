# Swanky Amp

Swanky Amp is Resonant DSP's free guitar amplifier. Version 2 is a Rust rebuild of the released Swanky Amp 1.4.0 amplifier model with its tone stack corrected, an iced editor, CLAP and VST3 plug-ins, an Audio Unit on macOS, and a standalone app. It accepts mono, stereo and mono-in, stereo-out host layouts, runs each stereo channel through its own amplifier path, and plays a mono input on both sides of a stereo output.

Version 2 has its own host and installation identity, `Swanky Amp 2` / `com.resonantdsp.swanky-amp-2`, so it installs beside the released `Swanky Amp` and does not take over old sessions. The JUCE 1.4.0 source is kept at the `juce-1.4.0` tag.

## Building and checking

Install Rust through [rustup](https://rustup.rs/) and [just](https://github.com/casey/just); the repository pins its Rust toolchain. The per-change gate is:

```sh
just
```

It checks formatting, runs clippy and runs the crate's tests. On every pull request and every push to master that changes more than prose CI runs `just ci-checks` on Linux (every clippy set, every test in one optimised profile, the release scripts' tests and the reference and model comparisons) and, on Windows, clippy, where the ASIO host compiles, and a test that builds every editor pipeline through Direct3D 12, whose shader compiler rejects programs Metal accepts. Only a push to master also builds the bundles on macOS and Windows and runs the format validators, so a change to the bundles or the formats is worth `just validate` locally before it lands. `.github/workflows/check.yml` defines both tiers. Run a part of the Linux checks locally only when a change touches that area:

- `just release-tests`: the release scripts' tests;
- `just reference-check`: the [released reference renderer](verification/reference/README.md) still reproduces its frozen 1.4.0 renders;
- `just model-check`: the legacy path still matches the released 1.4.0 chain on the ten factory presets;
- `just validate-assets`: an artwork package matches its receipt and the layers it was packed from (CI's tests check the committed package);
- `just clippy-all` and `just test-all`: the vendored host, the format adapters and the standalone.

The offline tools in `src/bin` build only with the `tools` feature, which keeps them out of the format builds; the recipes that run them turn it on.

### Bundles and the standalone

```sh
just setup      # once: pinned cargo-truce, validators and, on Windows, the ASIO SDK
just validate   # build, install and validate the plug-in bundles
just run        # open the standalone
```

`setup` builds the pinned cargo-truce inside this checkout and downloads checksum-verified pluginval and clap-validator, and on Windows the ASIO SDK. `validate` builds and installs the CLAP and VST3 bundles, and on macOS the Audio Unit, and runs the validators over them, auval among them on macOS.

The standalone opens with its input on, since an amplifier with its input off is silent, but only when the input is a device the player chose, from the information panel, the Settings menu or with `--input`, and it is connected. The system default input is often a built-in microphone beside the built-in speakers, so on a first launch, or when the chosen interface is unplugged, the input starts off and the information panel opens to say why. The computer's own microphone is never remembered: chosen from the panel or the menu it plays for that session, and the next launch asks for an input again; named with `--input` it is the player's explicit choice and starts live. Changing the audio driver on Windows turns the input off, since the new driver may open a device the player never chose; `--input-enabled on` or `off` overrides the launch rule for one launch, except that on Windows a launch whose ASIO interface will not open falls back to Windows audio with the input off. Its Settings menu chooses the input, the input channels, the output and the buffer size (128 samples unless chosen) and remembers them on the machine; `--input`, `--output` and `--buffer` override them for one launch (`cargo run --release -- --help` lists every option). Choosing an audio interface as the input takes the output to it too, unless an output has been chosen, and the input is kept within about one buffer of the output.

On Windows the standalone plays through ASIO when an ASIO driver is installed, and its Settings menu chooses between ASIO and Windows (WASAPI); `--driver asio` or `--driver wasapi` overrides that for one launch. On ASIO the interface is one device for input and output. The Windows recipes build the standalone with the Cargo feature `asio`, which compiles the ASIO SDK that `just setup` fetches into `tools/` and needs libclang; no other build compiles it.

The [product plan](docs/product-plan.md) owns design decisions, sound acceptance
and release qualification. The [editor review](../SwankyAmpPro/docs/editor-robustness.md)
records how the editor both products share runs inside a host, the decisions behind it and the exposure it keeps.

## Signal path

The shipping path is the 1.4.0 model with tube-only oversampling, plate and power-stage low-passes matched at every rate to their response at 96 kHz where 1.4.0 used its 44.1 kHz design, a smooth triode knee, a capped Grit mapping, the standard tone-stack mapping, a cabinet that keeps its 48 kHz response at the other common sample rates, and level compensation recalibrated against 1.4.0. The legacy path keeps every released mapping and the released cabinet design at every rate so that `just model-check` can prove the port against the frozen 1.4.0 renders.

Oversampling is set in the editor's header: Auto picks the tube stages' factor from the host's sample rate, or the player fixes one. The tube stages' fixed low-passes keep the response they have at 96 kHz, the rate Auto runs them at from 48 kHz, so up to 10 kHz the factor changes aliasing and not tone; above it 4x plays up to about 1 dB brighter at 16 kHz. The plug-in reports the oversampling filter's latency to the host, always that of the factor the audio is running: a new factor takes effect at the next block, and the latency reported changes with it, except in CLAP, which keeps an active plug-in's latency fixed, so there the factor waits for the restart the plug-in asks the host for.

To hear the plug-in itself offline, `cargo run --release -- render <preset> in.wav out.wav [id=value ...]` plays the input's first channel through the shipping engine with a preset (`init`, `factory:<name>` or `user:<file>`) and writes the stereo 32-bit float output the plug-in gives a mono track, the same length as the input and not shifted by the reported latency.

These tools render, measure and stress the paths:

```sh
just render-model "high gain" /tmp/high-gain.wav   # one released preset through the legacy path, with its internal seams
just dsp-report        # oversampling and the tube filters against the legacy path; also checks the real-time reset
just knee-report       # the smooth knee against the released one at every seam, per preset and input level
just tone-stack-soak   # 24 hours of samples through the shipping tone stack; fails on any drift (minutes)
just fit-cabinet       # refit the cabinet sections for the common rates and rewrite src/dsp/cabinet_data.rs
```

`dsp-report` and `knee-report` write their measurements under `target/dsp/`, and `knee-report` fails if a seam leaves the released level by more than `verification/dsp/knee.py` allows.

Version 2 ships the standard bilinear tone-stack mapping; 1.4.0's placed every tone-stack feature an octave above the circuit. Anyone who wants the old voicing exactly can keep 1.4.0 installed beside version 2.

### Level calibration

```sh
just calibrate   # rewrite src/dsp/calibration_data.rs, printing every point
```

`calibrate` measures the level compensation on the [guitar recordings](verification/reference/input/README.md), against 1.4.0. Its level reference is `LEVEL_REFERENCE` in `src/dsp/calibration.rs`, 1.4.0's default settings, fixed so that a change to Init moves neither the levels nor the factory presets; Init differs from it only in starting the tone stack at 2. It keeps the level into the power stage where 1.4.0 had it at every Drive setting, and holds the reference's loudness as Drive, Power Drive and Grit move. `just` tests the result on the same recordings: Drive, Power Drive and Grit at their extremes keep the reference's loudness, at default tone each stack feeds the power stage as 1.4.0 did, and 1.4.0's default settings play as loud as 1.4.0. The factory voicing uses these levels, so rerun `just refit` after a calibration change and listen to the result.

## Presets

### Factory bank

```sh
just refit
```

rewrites `presets/factory-2.0.xml` and its [voicing report](verification/tone-stack/refit-report.md) from the 1.4.0 presets on the guitar recordings. Low, Mid, High and Presence move on half marks to bring each preset's tonal balance as close to 1.4.0's as the corrected stack allows; Power Drive keeps the level 1.4.0 fed the power stage, and Output brings each preset to the level reference's strike level on the humbucker. It takes minutes in a release build. The plug-in embeds the bank at build time.

Accepted limits of the corrected stack against 1.4.0:

- 1.4.0's scoop sat an octave higher than any setting of the corrected stack can place it, and the corrected Low acts only at the very bottom. The voiced presets therefore keep the low mids under 1.4.0 and the region around 1.3 kHz over it; the [voicing report](verification/tone-stack/refit-report.md)'s Remaining balance table gives the figures.
- 1.4.0's default settings are not revoiced: on the corrected stack they have 3 to 6.3 dB less than 1.4.0 between 100 and 400 Hz and 3.8 to 4.7 dB more between 0.8 and 1.6 kHz. Init starts the tone stack at 2 rather than 0 for more mids.
- 1.4.0's level fell with Drive and Power Drive, differently on each pickup. Version 2 holds the level reference's level averaged over the pickups, so high Drive and Power Drive play louder against it than they did in 1.4.0, and each pickup lands up to about 3 dB either side of it.
- On the single coil the driven presets come out louder than the level reference, because a clean amp follows the pickup where a driven one does not. 1.4.0's factory presets were not balanced at all.

These are measured at 44.1 kHz with Auto oversampling on the three tone stacks, not on blends between them.

### Presets on the player's machine

| Platform | Version 2 | Swanky Amp 1.4.0 |
|---|---|---|
| macOS | `~/Library/Audio/Presets/Resonant DSP/Swanky Amp 2` | `~/Library/Audio/Presets/Resonant DSP/Swanky Amp` |
| Windows | `%APPDATA%\Resonant DSP\Swanky Amp 2` | `%APPDATA%\Resonant DSP\Swanky Amp` |
| Linux | `$XDG_DATA_HOME/Resonant DSP/Swanky Amp 2` (default `~/.local/share`) | `~/.config/Resonant DSP/Swanky Amp` |

The version 2 folder is created when first needed: by a save, by Open folder, or by an import. Each preset is one `<name>.xml` file in the 1.x schema, and 1.4.0 can load a version 2 file. A file that is not a Swanky Amp preset is left out of the menu and named in the footer. So is a 1.x file put in the version 2 folder by hand, one stamped with a 1.x `pluginVersion` or none, since it would play unconverted: the footer asks for it to go in the 1.4.0 folder and through Import 1.x presets. Saving never overwrites another preset unless the system dialog asked first, and a save never leaves a preset half written.

As in 1.4.0, Input and the cabinet switch belong to the session: a preset stores them, but choosing one leaves them as they are. The selected preset is part of the plug-in state, so a reopened session shows its name.

The first time version 2 runs without a preset folder, and on Import 1.x presets, it copies the player's presets from the 1.4.0 folder, which it never modifies, and skips names already taken and unchanged copies of 1.4.0's factory presets. An imported preset keeps every control except Low, Mid, High and Presence, which move by the average the factory voicing moved the ten 1.4.0 presets (`convert_1x` in `src/presets.rs`): Low −0.15, Mid −0.28, High −0.71 and Presence +0.22 in stored units, about −¾, −1½, −3½ and +1 mark on the panel. It is an approximation: imported presets land near their originals' balance as the factory presets do, not on it, and Output is not rebalanced.

## Editor

The six signal-flow groups (Levels, Cabinet, Preamp, Staging, Power Amp and Tone) sit on graphite with 1.4's rose as the accent. The bundled CC BY 4.0 artwork package provides the graphite, brushed metal, shadows and lighting; the text is native. The input meter keeps 1.4.0's scale, so the player stages the guitar with Input by eye as before.

The meters run at no more than 60 frames a second, and a frame for them alone redraws only the meters over the kept editor. The editor keeps the keys it uses, a focused knob's arrows, Home and End, and Escape while the information panel or the preset menu is open; every other key reaches the host, so Space and host shortcuts work after a knob is touched.

### Information panel

The cog left of the preset bar opens the product name, version and build number, as in `Swanky Amp Free 2.0.0 (build 212)`, Interface size, links to the product page, the manual and support, Copy diagnostics and Third-party licences. The build number counts the commits behind the one built, so on the squash-merged, linear master each commit has a larger number than the last and a promoted release is the same build as its candidate; a build made without git is build 0. In the Windows standalone it also shows the ASIO Compatible logo and Steinberg's trademark line.

In the standalone the panel also offers Input, Output and, for an input with more than one channel, Input channels: the Settings menu's choices, remembered the same way. Choosing an input turns it on; Off turns it off for the session. The panel opens by itself at launch only when no input was ever chosen, a remembered device is missing, the ASIO interface would not open, or the output would not start, in which case the app opens without sound until another output is chosen; the box that needs the player is outlined in the accent, and every message sits in one block below the choices. An input that is the computer's own microphone carries a warning that it feeds back through the speakers. macOS identifies that microphone exactly; Windows recognises a microphone on the onboard HD Audio chip, built in or plugged into its jack, and not one behind another driver such as Intel Smart Sound; Linux and ASIO do not say, so no warning shows there. While the input is off, the Input knob's readout says OFF and a press on the knob opens the panel instead of turning it; the footer says the input is off, and a press on that line opens the panel too.

Interface size draws the editor at 75, 100, 125 or 150 %. It belongs to the computer: it is saved in `Swanky Amp 2 interface.json`, in `~/Library/Resonant DSP` on macOS, `%APPDATA%\Resonant DSP` on Windows and `$XDG_CONFIG_HOME/Resonant DSP` on Linux, never in presets or host state.

Copy diagnostics puts a short block on the clipboard for a support request: product, version, build number and short commit, as in `Swanky Amp Free 2.0.0 (build 212, d6904d3)`, operating system and architecture, host and plug-in format, the sample rate and buffer audio last ran at, the licence, the graphics adapter and driver, where the editor log is and the last 50 warnings and errors it recorded in this process. Nothing is sent anywhere.

### Editor log

One file per computer account, shared by every format, at `~/Library/Logs/Resonant DSP/Swanky Amp 2.log` on macOS and `%LOCALAPPDATA%\Resonant DSP\Swanky Amp 2\Logs\editor.log` on Windows and `$XDG_STATE_HOME/Resonant DSP/Swanky Amp 2.log` (by default under `~/.local/state`) on Linux. Each process that writes to it starts with a header (product, version, commit, format, host, operating system, architecture, pid); then each editor open and close stage with its duration and the graphics adapter and driver, device losses and rebuilds, and every warning and error from the plug-in, the editor framework and wgpu, panics the editor catches among them, up to 2,000 a process. Nothing is logged per frame or from the audio thread, the home folder is written as `~`, repeated lines are counted, and past 1 MB the file becomes `… (previous).log`, so two are kept. A sandboxed host that refuses the write loses only the file. When the editor's graphics cannot start, the window shows one line naming the log and support@resonantdsp.com instead of staying blank. On Windows, compiled shaders are kept beside the log in `ShaderCache`, so later editors open faster.

### Release notice

Opening an editor starts a background check of `https://resonantdsp.com/release-notices/swanky-amp.json`:

```json
{"schemaVersion":1,"productId":"SwankyAmp","currentVersion":"2.0.1","currentBuild":215}
```

The website generates it from the promoted release catalogue and emits `"currentVersion":null` until `SwankyAmp` has verified downloads for that version. The plug-in rejects a document over 4 KiB and ignores fields it does not know, so the website can add to the document, within that size, without silencing installed versions. `currentBuild`, optional, is the release's build number. When the version is a strictly newer stable release, or the same version with a `currentBuild` greater than this build's (a tester on an earlier release candidate once the release is out), the cog turns into a download arrow and the panel announces it with a Download link to the product page, opened only on an explicit press; the document cannot choose a link. Any failure is silent, and every attempt, successful or not, waits 24 hours before the next. The last answer is kept in `Swanky Amp 2 release notice.json` beside the interface size.

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
just capture-audio missing-input /tmp/swanky-capture
```

`export-layout` writes the resolved geometry an artwork bake follows; it works when the artwork package is missing or stale. `capture` draws the editor at every interface size and needs a working GPU adapter, and fails if a frame that draws only the meters over the kept editor differs from a full frame; the other capture recipes apply a factory preset, light the meters, open the information panel (announcing the named release, if given), show the standalone's audio choices in one of the states `capture-audio` lists, or open the preset menu.

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

A release goes candidate tag → candidate workflow → qualification → release tag → promote workflow. The crate version in `Cargo.toml` is the only version, and a release is a git tag equal to it. `CHANGELOG.md` keeps an `## Unreleased` section, which `just version` turns into the version's section dated today; set that date to the planned release date by hand, and never let the heading say "in development", and a moved date is never a reason for a new candidate. The website's date is the day the GitHub release is published.

A candidate tag is for a build we would ship. A signed build for anything else, such as trying a change on a real machine, comes from a `rehearsal/*` branch.

```sh
just version 2.0.1    # edits Cargo.toml, Cargo.lock and CHANGELOG.md; commits nothing
                      # land that through a pull request, then on origin/master:
just tone-stack-soak  # must pass before a candidate
just tag-candidate    # v2.0.1-rc.1, or the next candidate for this version
git push origin v2.0.1-rc.1
```

Neither tag recipe pushes; pushing a tag is the operator's act, and only administrators can create `v*` tags and `rehearsal/*` branches. `tag-candidate` fetches first and refuses changes in tracked files, a checkout other than `origin/master` and a version `origin` has already released, and numbers the candidate past every candidate tag held locally or on `origin`.

### Candidate

A tag `vX.Y.Z-rc.N` starts `.github/workflows/candidate.yml`; a release tag never builds. The workflow refuses a tag whose commit is not on master, whose version is not the crate version, or whose changelog section is missing or says it is in development (`just release-check candidate <tag>` checks the last two locally).

It builds a universal macOS `.pkg` (CLAP, VST3, Audio Unit and the standalone), notarized and stapled, and an x64 Windows `.exe` (CLAP, VST3 and the standalone), signed from the `signing` environment, with the third-party notices embedded. It installs each on a clean runner, runs the format validators over what was installed, and checks every shipped file's signature against the exact publisher. `[package.metadata.release]` in `Cargo.toml` states whether a release ships Linux; when it does, the workflow also packages, installs and validates the Linux tarball. 2.0 ships none.

`release-record.json` names the candidate, commit, build number, version, toolchain, vendored cargo-truce version, the lockfile and artwork hashes, the plug-in's identity, and each download's kind, size and SHA-256; `release-record.sha256` beside it lets `sha256sum -c` check it in place. The downloads, record and checksum go to the public downloads bucket at `https://downloads.resonantdsp.com/swankyamp/candidates/<tag>/` and to a GitHub pre-release named after the tag. A candidate is written once: the workflow refuses a tag whose record is already stored, so new bytes need a new candidate tag. A run that failed partway resumes with "Re-run failed jobs".

A dispatch on a `rehearsal/*` branch (`gh workflow run candidate.yml --ref rehearsal/<name>`) builds, signs and validates the same way, names its run artifacts after the short commit, and publishes nothing.

### Qualify

A person qualifies the candidate's exact installers in real hosts and by ear; [verification](verification/README.md#open-limits) lists what only a real machine confirms. Qualifying accepts the SHA-256 of the candidate's `release-record.json`. Then tag the release on the candidate's commit:

```sh
just tag-release v2.0.1-rc.3   # v2.0.1, on the commit origin's v2.0.1-rc.3 names
git push origin v2.0.1
```

`tag-release` reads the candidate tag from `origin`, never the checkout, and refuses unless the version's changelog heading there carries a date.

### Promote

`.github/workflows/promote.yml` is dispatched from `master`, the only branch its `release` environment admits, and builds nothing:

```sh
gh workflow run promote.yml --ref master -f candidate_tag=v2.0.1-rc.3 \
  -f tag=v2.0.1 -f record_sha256=<hash> -f qualification='...'
```

`qualification` says who qualified the candidate, in which hosts, on which machines, when and what they found; an empty one fails the run. The run checks out the release tag, requires a successful candidate run for the candidate tag, fetches the candidate from the bucket and checks it: both tags and the checkout are one commit, the record is the accepted one and agrees with the tagged tree, and every download matches it. It then copies the candidate and `qualification.md` to `swankyamp/<version>/` in the same bucket, fetches the public URLs back and compares them, publishes the GitHub release with the downloads, record, checksum and `qualification.md`, and opens a website pull request cataloguing the downloads with the build number and the release's publication date. The website's checks and the operator's review merge it.

`just promote-check <candidate tag> <tag> <record sha256> <directory>` runs the same fetch and checks locally from a checkout of the release tag. A rerun after a late failure goes on only when an existing release holds exactly the candidate's files, so it takes the same qualification text.

### Settings

Rulesets let only administrators create, update or delete `v*` tags and `rehearsal/*` branches. The `signing` environment admits only `v*-rc.*` tags and `rehearsal/*` branches, so fork and pull-request runs cannot reach it; it holds the Apple material (`APPLE_CERTIFICATES_P12`, `APPLE_CERTIFICATES_PASSWORD`, `APPLE_API_KEY_P8`, `APPLE_API_KEY_ID`, `APPLE_API_ISSUER_ID`) and the credential that writes the downloads bucket (`AWS_ACCESS_KEY_ID`, `AWS_SECRET_ACCESS_KEY`, `R2_ACCOUNT_ID`). The `release` environment admits only `master` and holds a credential that writes the bucket and the `WEBSITE_TOKEN` for the catalogue pull request. The repository variables `PUBLIC_DOWNLOAD_BUCKET` and `PUBLIC_DOWNLOAD_BASE_URL` name the bucket and where it is served.

Windows signing uses a Free-specific Azure application and service principal with a federated identity scoped to this repository's `signing` environment, and a signer-only role on the shared Public Trust profile for the Resonant DSP publisher; it has no access to Pro source or resources. These repository variables, none of them secret, configure it:

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

Narrow patches of the published Truce sources, of baseview, of iced_wgpu and of wgpu-hal, each directory carrying its unchanged upstream licences, original manifest, source reference and an `UPSTREAM.md` describing the local changes:

- `vendor/baseview-truce`: frame delivery paced by the display, host keyboard and modifier fixes, keys the editor does not use handed back to the host, no process-wide DPI change and no drag-and-drop, and a window kept alive until a detached GPU thread releases it.
- `vendor/truce-iced`: iced input, focus, redraw and clipboard fixes, a GPU thread whose setup is bounded and final, frames built only when they can be shown, live-display frames capped at 60 a second and drawn alone over the kept editor, a low-power GPU request and an sRGB surface, the editor's lifecycle records and a native note when its graphics cannot start.
- `vendor/wgpu-hal`: on Windows the shader compiler loads from System32, compiled shaders are cached on disk, and only the GPU Windows would choose (the player's per-program setting, otherwise low power) gets a device.
- `vendor/iced_wgpu`: multisampled meshes drawn over their own region rather than the whole frame.
- `vendor/truce-clap`: host state notification required by clap-validator, dynamic-latency restart with the latency held until it, and active reset handling.
- `vendor/truce-standalone`: dynamic-latency restart on the output worker, an input kept within about one buffer of the output, a Buffer Size menu, remembered devices, input channels and buffer size, an input that starts live only on a chosen device, is off after a driver switch and never remembers the computer's own microphone, the audio choices and what needs the player offered to the plug-in's editor, a window that opens without sound when the output will not start, streams faded out and stopped on close, no Ctrl+I, Ctrl+O, Ctrl+S or Ctrl+Shift+S shortcuts, and ASIO on Windows.
- `vendor/truce-core`, `vendor/truce-plugin`, `vendor/truce-loader` and `vendor/truce`: a real-time reset lifecycle hook and its forwarding bridge. `truce-core` and `truce-loader` also carry an activation flag saying the format holds latency until the next reset.
- `vendor/truce-au`: editor window resizing, and a latency change reaches the Audio Unit host's property listeners.
- `vendor/cargo-truce`: the source-only build tool with the Azure `ExcludeCredentials` patch, the Audio Unit Info.plist patch and Windows installers for all users only. It is a build tool, not linked into the plug-in. The Truce Framework Rider's Section 2.2 lists audio plug-ins and suites among the uses that are not Covered Framework Offerings.

Everything else resolves from the pinned Cargo lockfile.
