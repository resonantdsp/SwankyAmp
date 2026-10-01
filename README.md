# Swanky Amp

Swanky Amp is Resonant DSP's free guitar amplifier. Version 2 is a Rust rebuild of the released Swanky Amp 1.4.0 amplifier model with its tone stack corrected, an iced editor, CLAP and VST3 plug-ins, an Audio Unit on macOS, and a standalone app. It accepts mono, stereo and mono-in, stereo-out host layouts, runs each stereo channel through its own amplifier path, and plays a mono input on both sides of a stereo output.

Version 2 has its own host and installation identity, `Swanky Amp 2` / `com.resonantdsp.swanky-amp-2`, so it installs beside the released `Swanky Amp` and does not take over old sessions. The JUCE 1.4.0 source is kept at the `juce-1.4.0` tag.

## Building and checking

Install Rust through [rustup](https://rustup.rs/) and [just](https://github.com/casey/just); the repository pins its Rust toolchain. The per-change gate is:

```sh
just
```

It checks formatting, lints every target with the default features (the plug-in formats and the standalone) and the tools, and runs the crate's tests without the default features. It compiles the format adapters and the standalone but does not run their tests.

CI runs `just ci-checks` on every pull request and every push to master, except for changes to Markdown alone. Beyond the gate it lints without the default features, runs the format adapters' and the vendored standalone host's tests, runs the release-script tests, verifies the [released reference renderer](verification/reference/README.md), compares the legacy path against the ten released factory presets, proves the committed level calibration reproduces, and validates the artwork package. Once those pass, it builds the standalone and runs the bundle validation on macOS and Windows, without signing or secrets.

Run a part of it locally only when a change touches that area:

- `just release-tests` for the release scripts;
- `just reference-check`, `just model-check` and `just calibrate-check` for the DSP;
- `just validate-assets` for artwork or layout;
- `just clippy-all` and `just test-all` for the vendored host, a format adapter or the standalone.

The offline tools in `src/bin` build only with the `tools` feature, which keeps them out of the format builds; the recipes that run them turn it on.

### Bundles and the standalone

```sh
just setup      # once: pinned cargo-truce, validators and, on Windows, the ASIO SDK
just validate   # build, install and validate the plug-in bundles
just run        # open the standalone
```

`setup` builds the source-pinned cargo-truce 6.3.0 inside this checkout and downloads checksum-verified pluginval and clap-validator, and on Windows the checksum-verified ASIO SDK. `validate` builds and installs the CLAP and VST3 bundles, and on macOS the Audio Unit, and runs the validators over them, auval among them on macOS.

The standalone opens with its input on, since an amplifier with its input off is silent; `--input-enabled off` opts out. Its Settings menu chooses the input, the output and the buffer size (128 samples unless chosen) and remembers them on the machine; `--input`, `--output` and `--buffer` override them for one launch (`cargo run --release -- --help` lists every option). Choosing an audio interface as the input takes the output to it too, unless an output has been chosen, and the input is kept within about one buffer of the output.

On Windows the standalone plays through ASIO when an ASIO driver is installed, and its Settings menu chooses between ASIO and Windows (WASAPI); `--driver asio` or `--driver wasapi` overrides that for one launch. On ASIO the interface is one device for input and output. The Windows recipes build the standalone with the Cargo feature `asio`, which compiles the ASIO SDK that `just setup` fetches into `tools/` and needs libclang; no other build compiles it.

## Signal path

The shipping path is the 1.4.0 model with tube-only oversampling, a rate-tracked plate filter, a unit-slope triode knee, a capped Grit mapping, the standard tone-stack mapping, and level compensation recalibrated against the released path. The legacy path keeps every released mapping so that `just model-check` still proves the port against the frozen 1.4.0 renders.

### Model comparison

```sh
just model-check
just render-model "high gain" /tmp/high-gain.wav
```

`model-check` renders the ten released factory presets through the legacy path at 44.1 kHz and 1x and compares every active triode, the tone stack, power amp, cabinet and final output with the released chain. The bounds are 0.2 % relative waveform RMS, 0.65 % relative peak error and 0.02 dB in each of a low, mid and high band; the peak bound covers a 0.627 % level-11 power-stage difference measured against a C++ build without floating-point contraction. `render-model` renders one preset and writes its internal seams beside it.

The frozen corpus captures the released cold start, including its 1,024-sample output mute. The Rust path settles its nonlinear state for one second before audio begins, and stages re-enter warm when the Stages control brings them back into the signal path, so the comparison applies the same one-second silent pre-roll to the released chain and excludes it from the measured WAVs.

### Oversampling

Auto oversampling applies to the nonlinear tube stages; the cabinet stays at the host rate. Auto uses 2x at 44.1 and 48 kHz and 1x at 88.2 kHz and above; the fixed 1x, 2x and 4x choices are capped below 193.92 kHz internally. The header button cycles Auto, 1x, 2x and 4x and shows the factor running once audio is prepared, such as "Auto 2×"; it is lit whenever the tube stages oversample or Auto is still choosing. Oversampling is not part of a preset.

The host receives the FIR delay: 32 samples at 2x and 48 at 4x. A factor change requests the host's deactivate/activate sequence in CLAP and VST3; an Audio Unit host is told the new latency and the factor takes effect at its next reset; the standalone rebuilds its output stream on the existing worker. Activation applies the pending factor off the audio thread, and a choice that resolves to the active factor keeps its state without a restart. An active CLAP reset clears processing history at the current factor with a bounded, allocation-free equilibrium calculation. The plate low-pass stays at 20 kHz as the tube rate changes and reproduces the released coefficients at 44.1 kHz.

```sh
just dsp-report
```

regenerates the factor, latency, seam-level and aliasing measurements in `verification/dsp/oversampling-plate.json`. It keeps the released knee, tone mapping and level tables in the corrected path so it isolates oversampling and the plate filter, and it checks the active-reset equilibrium across the factory presets, control extremes and supported rates. It says nothing about how the corrected factory presets sound.

### Tone stack

Swanky Amp 1.4.0 discretised its tone stack with the bilinear constant `SR` instead of the standard `2·SR`, which placed every tone-stack feature an octave above the circuit. Version 2 ships the standard mapping. Anyone who wants the old voicing exactly can keep 1.4.0 installed beside version 2.

The three treble sections are first-order circuits, which 1.4.0 discretised as biquads with the second-order terms set to zero. That leaves a pole on the unit circle at Nyquist that only exact arithmetic cancels; rounded to f32 it can sit a few parts in 10⁹ outside the circle (the Marshall treble at 88.2 kHz, the Fender treble at 176.4 kHz and, in the released mapping, at 44.1 kHz), and rounding noise at Nyquist then grows until, after hours of play, it drives the power stage into cutoff. Higher precision alone does not fix it: in f64 the pole sits exactly on the circle. The shipping mapping discretises the treble sections as true first-order filters, which removes the pole without changing the response. The legacy path keeps the released form, and the defect, so the model gate stays bit-identical.

`just` includes a test that the stack falls silent after its input stops at each affected rate. Before a candidate,

```sh
just tone-stack-soak
```

drives the shipping tone stack alone for 24 hours of samples at 44.1, 88.2 and 176.4 kHz, level 11 and each stack model with Low, Mid, High and Presence at both extremes, on white noise at the level the stack sees at level 11. It fails if any hour's level moves more than 0.01 dB from the first or its mean exceeds 10⁻⁴ of its RMS, and takes about eight minutes on an Apple M-series machine.

### Soft-clip knee

The triode soft clips (grid, bias, plate and compression) use a unit-slope knee. The released model scaled its cubic clip input by 1/3.4, leaving a corner at every knee; scaling by 1/4 joins the knee smoothly at the cost of slightly less gain between knee and ceiling. Because all five preamp stages compress, the loss compounds, so each triode carries a fixed makeup gain (+0.13, +0.05, +0.13, +0.15 and +0.10 dB for stages 1 to 5), the mean seam residual over the ten factory presets at 0 dB input, which drives each next stage as hard as 1.4.0 did. The tetrode's push-pull clips keep the released curve: ordinary playing sits inside their cubic, where the knee span sets the power stage's bias and gain rather than shaping a knee.

```sh
just knee-report
```

renders every factory preset at 44.1 kHz and 1x with the DI at -12, -6, 0 and +6 dB through the released and the unit knee and writes each seam's RMS ratio and crest-factor change to `verification/dsp/knee.json`. At 0 dB input it requires every triode seam within 0.6 dB of the released level, the tone stack within 1.05 dB, and the power amp, cabinet and output within 0.5 dB.

### Grit

Grit lowers each triode's grid clip and raises the threshold of its plate compressor. In 1.4.0 the threshold rose by up to 100 of its units; above about 72 the third stage's compressor never charges and the stage clips everything to a constant, which cost 1.4.0 52 dB at full Grit, at every input level. The shipping path stops the threshold at 70, which Grit reaches at 8.5 on its 0 to 10 scale. Below that nothing changes, and the raised threshold had barely begun to reach the signal, so no grit is lost. The lower grid clip still costs 12 dB on the DI at full Grit, which the Grit output gain restores; Grit below its centre does not change the level. The legacy path keeps the released mapping.

### Level calibration

The level compensation is measured by `calibrate` on the [guitar recordings](verification/reference/input/README.md), staged as that README describes, played at Input 0 and averaged over the two pickups, at 44.1 kHz with Auto oversampling from a settled amplifier, every control but the swept one at its default. The reference is the released path.

The first stage sets how hard the power stage is driven, keeping 1.4.0's structure. The level into the power stage is measured on both paths at each of Drive's eleven table points for each tone stack; the tone-stack scale takes the mean gap and the preamp table each Drive point's departure from it, so real playing drives the power stage as 1.4.0 did. One scale serves all three stacks, so each sits up to half their spread from 1.4.0, and the corrected Fender stack passes more of a humbucker's upper mids than 1.4.0's, so the two pickups land either side of the average. The power table normalises the power amp's output against Power Drive; the cabinet keeps its own fixed scale.

The second stage holds loudness: ITU-R BS.1770-4 gated integrated loudness, averaged in LUFS over the recordings, with the factory defaults' loudness as the target so Init keeps its level. The power table is rescaled point by point to that target, then Drive and Grit each get an output gain table solved the same way. All three gains follow the cabinet, so they change level and nothing else. Stages stays uncompensated, as released.

```sh
just calibrate          # rewrite src/dsp/calibration_data.rs, printing every point
just calibrate-check    # fail if a fresh measurement moves a value by more than 0.05 dB
```

The factory voicing uses these levels, so rerun `just refit` after a calibration change and listen to the result.

## Presets

### Factory bank

The 1.4.0 factory presets were voiced on the octave-high stack, so each is revoiced for the corrected one on the guitar recordings, judged at the output where the player strikes (the loudest 40 % of each recording's momentary-loudness blocks). Low, Mid, High and Presence move on a grid of half marks, between 1 and 9, to bring the balance between sixth-octave bands from 80 Hz to 16 kHz as close to 1.4.0's as the grid allows. Power Drive is set so each preset feeds the power stage as 1.4.0 did, to the nearest half mark, and Output so each strikes as loud as Init on the humbucker. The strike level is the 95th percentile of momentary loudness over the whole recording; integrated loudness would average over the ring-out, where a driven amp sustains and a clean one decays. A clean amp follows the pickup where a driven one does not, so on the single coil the driven presets come out louder than Init. 1.4.0's factory presets were not balanced.

```sh
just refit
```

rewrites `presets/factory-2.0.xml` and its [voicing report](verification/tone-stack/refit-report.md), which lists each preset's settings, balance, power-stage feed and levels against 1.4.0 and Init. It takes minutes in a release build. The plug-in embeds the bank at build time.

Accepted limits of the corrected stack against 1.4.0:

- 1.4.0's scoop sat an octave higher than any setting of the corrected stack can place it, and the corrected Low acts only below about 125 Hz. The voiced presets keep 150 to 400 Hz up to 1.1 dB under 1.4.0 (level 11 up to 2.7 dB) and around 1.3 kHz 0.5 to 2.5 dB over.
- Init is the corrected stack at its defaults and is not revoiced: against 1.4.0 it has 3 to 6.3 dB less between 100 and 400 Hz and 3.8 to 4.7 dB more between 0.8 and 1.6 kHz.
- 1.4.0's level fell with Drive and Power Drive, differently on each pickup. Version 2 holds Init's level averaged over the pickups, so high Drive and Power Drive play louder against Init than they did in 1.4.0, and each pickup lands up to about 3 dB either side of Init.

These are measured at 44.1 kHz with Auto oversampling on the three tone stacks, not on blends between them.

### The preset bar

The header's preset field shows the current preset's name between `‹` and `›`, which step through the factory presets and then the user's own; a name too long for the field ends in an ellipsis, and hovering the field shows the whole name in the footer. Pressing the name opens the menu: Init, the ten factory presets, the user presets, then Save (a changed user preset), Save as…, Remove (user presets only), Import 1.x presets and Open folder. The menu widens to fit its longest name, up to the window's width, and moves left where it would run past the header's edge; only a name wider than the window ends in an ellipsis there. Remove's first press turns the item into "Remove <name>?" and keeps the menu open; a second press deletes the file, and closing the menu cancels. Init restores every preset control to its default; there is no Reset button.

Choosing a preset sets its controls through the host, so automation and undo see the change, and the selected preset is part of the plug-in state, so a reopened session shows its name. A dot after the name marks a preset changed since it was chosen. The menu capitalises the factory presets like Init; the bank, the saved state and tools such as `just capture-preset` name them in lower case, as 1.4.0 did. As in 1.4.0, Input and the cabinet switch belong to the session: a preset stores them, but choosing one leaves them as they are and changing them does not mark the preset changed.

### User presets

| Platform | Version 2 | Swanky Amp 1.4.0 |
|---|---|---|
| macOS | `~/Library/Audio/Presets/Resonant DSP/Swanky Amp 2` | `~/Library/Audio/Presets/Resonant DSP/Swanky Amp` |
| Windows | `%APPDATA%\Resonant DSP\Swanky Amp 2` | `%APPDATA%\Resonant DSP\Swanky Amp` |
| Linux | `$XDG_DATA_HOME/Resonant DSP/Swanky Amp 2` (default `~/.local/share`) | `~/.config/Resonant DSP/Swanky Amp` |

The version 2 folder is created when first needed: by a save, by Open folder, or by an import, even one that copies nothing. Each preset is one `<name>.xml` file in the 1.x schema, an `APVTSSwankyAmp` element of `<PARAM id value/>` entries under the 1.x parameter ids, so version 2 reads 1.4.0 files, including the migrations 1.4.0 applied to earlier presets, and 1.4.0 can load a version 2 file. A file that is not well-formed or not a Swanky Amp preset is left out of the menu and named in the footer.

The first time version 2 runs without a preset folder, and on Import 1.x presets, it copies the user's presets from the 1.4.0 folder, which it never modifies. Each imported preset keeps its name and every control except Low, Mid, High and Power Drive. Those are converted by a faster fit than the factory voicing, one the plug-in runs itself: the preset is rendered on the released stack and fitted on the corrected one to match the stack's own output on a generated pluck, with Power Drive moving at most 0.15 and only when the level into the power stage would otherwise change by more than 0.5 dB. Because it judges the stack rather than the output, and a pluck rather than a guitar, imported presets can sound boxier and less scooped than their originals, most where a preset relied on extreme Low, Mid or High. Imported presets keep their Output as it was. The file records `importedFrom` and `refit` attributes. A name already taken in the version 2 folder is kept as it is, and unchanged copies of the 1.4.0 factory presets, which 1.4.0 wrote into its folder, are not copied.

## Editor

The editor is 864 by 512 interface pixels and uses one iced widget tree for the live controls and the artwork layout contract. The six signal-flow groups (Levels, Cabinet, Preamp, Staging, Power Amp and Tone) are separate rounded boxes on the graphite, each outlined by its own V groove, with 1.4's rose as the accent on the lit rings, the selected outlines and the output meter. The bundled CC BY 4.0 artwork package provides the graphite, brushed metal, shadows and response lighting. Knob markers are glossy black divots. Readouts show whole units at rest and tenths while a knob is dragged.

The cabinet's on/off is a two-position vertical switch: a brushed aluminium disc in a V track baked into the faceplate, the disc in the top half when on and the bottom half when off. While the cabinet is off, its three knobs, labels and readouts are dimmed and stay adjustable.

### Meters

The four meter columns, captioned L and R, are local to each plug-in instance. The blue input pair reads the signal after the Input control; the output pair, in the accent, reads the final signal after the optional cabinet and Output. Cells light from the bottom up. The input meter keeps 1.4.0's scale, -26 to +8 dBFS, without marks, and the player stages the guitar with Input by eye: a light strum peaks about one third of the way up with a single coil, about two thirds with a humbucker. The output meter spans -60 to 0 dBFS, one cell per 6 dB. A mono instance mirrors its reading into L and R. Levels rise immediately and fall to 1/e in 0.3 s, settling to exact darkness, after which the editor has nothing to redraw; the meters also go dark while the window has lost focus and the pointer is elsewhere.

### Information panel

A small outlined cog button left of the preset bar opens the information panel over the dimmed editor: the product name and running version, such as "Swanky Amp Free 2.0.0"; Interface size; links to the product page, the manual and support, each tagged `utm_source=swanky-amp-2&utm_medium=plugin&utm_campaign=information`; Copy diagnostics; and Third-party licences. In the Windows standalone it also shows the ASIO Compatible logo and Steinberg's trademark line. Escape, the button again or a press outside closes it.

Interface size draws the whole editor at 75, 100, 125 or 150 %. The layout never changes: the widget tree lays out at 864 by 512, the window is that times the size, and native text, knob rings, markers and meters render at the window's real resolution. The editor resizes its own window and asks the host to follow in CLAP, VST3, the Audio Unit and the standalone; it stays fixed-size to hosts, so none offers a drag handle. The size belongs to the computer: it is saved once per installation in `Swanky Amp 2 interface.json`, in `~/Library/Resonant DSP` on macOS, `%APPDATA%\Resonant DSP` on Windows and `$XDG_CONFIG_HOME/Resonant DSP` on Linux, never in presets or host state.

Copy diagnostics puts a short block on the clipboard for a support request: product and version, operating system and architecture, host application and plug-in format, the sample rate and buffer audio last ran at, and the licence. Nothing is sent anywhere.

### Release notice

Opening an editor starts a background check of `https://resonantdsp.com/release-notices/swanky-amp.json`, a document of at most 4 KiB:

```json
{"schemaVersion":1,"productId":"SwankyAmp","currentVersion":"2.0.1"}
```

The website generates it from the promoted release catalogue and emits `"currentVersion":null` until `SwankyAmp` has verified downloads for that version. The plug-in accepts only a strict stable `major.minor.patch` version and compares it numerically with the running one. When it is strictly newer, the cog turns into a highlighted download arrow and the panel announces the version with a Download link to the fixed URL `https://resonantdsp.com/products/swanky-amp/?utm_source=swanky-amp-2&utm_medium=plugin&utm_campaign=release-notice`, opened only on an explicit press; the document cannot choose a link. A missing endpoint, an offline computer, an invalid document and a timeout are all silent.

The check has a three-second total timeout and follows no redirects. It keeps its last valid answer, last attempt and last successful check in the process and, when writable, in `Resonant DSP/Swanky Amp 2/release-notice.json` under the operating system's cache directory. Successful and failed attempts both wait 24 hours before another request, even when the cache cannot be written; invalid or future cache timestamps trigger a check. All filesystem and network work stays on the notice worker, outside audio processing.

The request is a bodyless `GET`. So the website can count monthly unique installs without an identifier, it adds `?first=ever` when this computer has no previous successful check, `?first=month` when the previous successful check was in an earlier calendar month (UTC), and no query otherwise; a failed check leaves that record untouched. It sends no custom User-Agent, running version, product key, machine identifier or telemetry. As with any HTTPS request, the website or its delivery provider receives the public IP address and the ordinary connection, TLS, header and timing information needed to serve it.

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

`export-layout` writes the resolved geometry (layout manifest schema 4, with each section's outline radius and the switch track); it works when the artwork package is missing or stale, so a new bake can follow changed geometry. `capture` draws the editor at every interface size at 1x and 2x (`amp-1x.png` and `amp-2x.png` at 100 %, `amp-150-2x.png` and so on), whatever size this machine has chosen, and needs a working GPU adapter. `capture-preset` applies a factory preset and names it in the header, `capture-live` lights the meters with a deterministic stereo note, and `capture-information` opens the information panel, announcing the named release if one is given. `capture-menu` lists the named preset as the player's own, chooses it and opens the preset menu, with the pointer over the field so the footer names it.

### Artwork

The repository carries the artwork as `assets/artwork.pack` with its `receipt.json` and `ARTWORK-LICENSE.txt` in `assets/artwork`. The editable layers are not committed, since each rebake would add some 30 MB of EXRs; they come from the package. Contributors can make a reproducible round trip without the production renderer: unpack the deterministic RGB9E5 package to ZIP float32 RGB EXRs, edit them in a standard HDR image tool, refresh the receipt, then repack and validate:

```sh
just unpack-artwork assets/artwork.pack /tmp/swanky-artwork
just refresh-artwork /tmp/swanky-artwork
just pack-artwork /tmp/swanky-artwork /tmp/swanky-artwork.pack
just validate-assets /tmp/swanky-artwork.pack /tmp/swanky-artwork
```

Packing the unpacked layers unedited reproduces the package byte for byte. To propose an edit, unpack into `assets/artwork` (the EXRs there are ignored by git) and commit the repacked package and refreshed receipt. The base and shadow layers are two texels per interface pixel, exact at 100 % on a Retina display; the package stores every layer as deflated RGB9E5 and adds two box-filtered halvings of the base, shadow and disc sprite, averaged in linear light, for smaller interface sizes. The receipt records the radiance and shadow semantics, dimensions, hashes and public layout provenance; producer metadata is descriptive, so replacement CC artwork needs neither Blender nor the original production sources. `just validate-assets` checks that the package matches its committed receipt and, when layers are present in `assets/artwork` or a given folder, that it is the deterministic result of packing them.

## Long-run soak

The soak is a diagnostic for a suspected long-run defect, such as the tremolo-like drift issue #34 reported in 1.2. It is not a release step.

```sh
just soak 4        # hours of audio per run, started in the background
just soak-check    # verdict so far, or the final one
```

`just soak` builds the `soak` tool in release mode and starts four detached runs at 44.1 kHz with Auto oversampling: the shipping path, built as the plug-in engine builds it, for `clean`, `level 11` and Init, plus `level 11` on the legacy path for comparison. Each writes `target/soak/<path>-<preset>.csv` with a `.log`, a `.pid` and the commit it was built from in `target/soak/commit`; `SOAK_DIR` and `SOAK_RUNS` (see `scripts/soak.sh`) choose another directory and set of runs. Each run renders two independent channels: white noise at -40 dBFS RMS, and the same floor with a decaying 110 Hz pluck peaking at -20 dBFS every two seconds. Every 10 seconds of audio a row records output RMS and peak, each seam's RMS, non-finite and subnormal counts, processing time, and the 0.5 to 15 Hz modulation of the RMS envelope.

A shipping-path run passes when no sample is non-finite, its output RMS over the last 30 minutes is within 0.1 dB of the first 30, and its band modulation never exceeds the first 10 minutes' largest value by more than 25 % plus 0.005; a coherent tremolo of about 0.4 dB depth fails. The legacy run is reported, not gated. Four hours of audio take about 25 minutes per run on an Apple M-series core. The soak found the tone-stack Nyquist pole on both paths; the [12-hour runs after the fix](verification/soak/2026-09-23-summary.txt) pass.

## Releasing

A release goes candidate tag → candidate workflow → qualification → stable tag → promote workflow. The crate version in `Cargo.toml` is the version authority, and `CHANGELOG.md` must have the matching section. That section's heading carries the planned release date, such as `## 2.0.1 — 2026-11-02`, never "in development": the tagged source is public, and every candidate must be releasable as it stands. `just version` dates a new section; an existing one, such as an "in development" heading, is dated by hand before the first candidate is cut. The website catalogue's date is the day the GitHub Release is published and may differ from the heading; a moved date is never a reason for a new candidate. `[package.metadata.release]` in `Cargo.toml` states whether the release ships a Linux download.

Prepare the version on a branch and land it through a pull request like any change:

```sh
just version 2.0.1      # updates Cargo.toml, Cargo.lock and CHANGELOG.md; never stages or commits
```

Then, on the merged master commit, which CI has checked:

```sh
just tone-stack-soak
just tag-candidate      # creates the next v2.0.1-rc.N locally
git push origin v2.0.1-rc.1
```

`tag-candidate` fetches first. It refuses changes in tracked files, a checkout other than `origin/master`, a commit that would fail the stable release check (version and dated heading), and a version whose stable tag `origin` already has. It numbers the candidate past every candidate tag held locally or on `origin`. The tag helpers push nothing.

### Candidate workflow

Only `vX.Y.Z-rc.N` tags start `.github/workflows/candidate.yml`, and its first job refuses a tag whose commit is not on master; stable `vX.Y.Z` tags never build. A manual run is a rehearsal, accepted only from an administrator-owned `rehearsal/*` branch; its artifacts use the commit hash and it creates no GitHub Release.

The workflow validates the committed artwork and writes the third-party notices before packaging. It builds a universal macOS package signed with the Resonant DSP Developer ID identities, notarized and stapled, and a Windows x64 installer signed through the Free-specific Azure identity and the shared Resonant DSP publisher profile. Both installers offer an install for all users or the current user; both are installed silently for all users on clean runners, pluginval and clap-validator inspect what was installed, and the workflow verifies the publisher identities and that every packaged binary carries the notices. When the release declares a Linux download, the workflow packages it on Ubuntu 22.04, installs and validates the tarball, and records no candidate unless that passes; a release that declares none builds none.

The final job writes `release-record.json` with the tag, commit, version, toolchain, cargo-truce version, lockfile and artwork hashes, shipping identities, and each artifact's size and SHA-256, and creates a draft GitHub Release once. The workflow refuses an RC tag that already has a release, before any signing and again at the end, so new bytes need a new RC number. A run that failed partway resumes with "Re-run failed jobs", unless it failed after creating the draft, which needs a new RC; re-running all jobs is refused once the draft exists.

### Qualification and promotion

A person qualifies the candidate's exact installers in real hosts, checks installation, the interface and audio, and records the SHA-256 printed for `release-record.json`. Acceptance is a release decision; workflow success does not make it one. After acceptance, create the stable tag on the same commit:

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

The workflow downloads Trusted Signing Client 1.0.95, logs in through GitHub OIDC and takes a signing token while the federated assertion is valid. The vendored cargo-truce writes `ExcludeCredentials` so the signing library uses that Azure CLI token instead of hanging in the runner's managed-identity probe. No client secret or signing key exists.

## Source and licences

Swanky Amp is licensed under GPLv3 or later; see [LICENSE](LICENSE). The Windows standalone links Steinberg's ASIO SDK 2.3.4, which Steinberg offers under its proprietary agreement or under GPLv3; Swanky Amp takes the GPLv3 option, so that build is distributed under GPLv3. The SDK is fetched at build time, pinned by checksum and never committed. The third-party notices carry its dual-licence text and the BSD licence of its host helpers from `assets/asio-sdk`, the GPLv3 text, and the exact Steinberg package as its source. ASIO is a registered trademark of Steinberg Media Technologies GmbH; GPLv3 does not cover the name or logo, so their use follows Steinberg's usage guidelines for SDK 2.3.4, which ask for the ASIO Compatible logo in the About panel of an application that runs on ASIO by default. The information panel shows it; `assets/asio-compatible.svg` is Steinberg's artwork, unchanged.

The model authority is the Swanky Amp 1.4.0 C++ wrapper and generated Faust headers preserved in `verification/reference/released` from the `juce-1.4.0` tag. Small equation and filter primitives were adapted from the separately implemented Pro code only where comparison proved they express the released equations. This repository contains no Pro parameter grids, cabinet impulse responses, pedals, gate, reverb, licensing logic, Blender sources, artwork production sources or shared private DSP.

The artwork in `assets/artwork.pack`, and the layers unpacked from it, is licensed under CC BY 4.0; see `assets/artwork/ARTWORK-LICENSE.txt`. The editor uses PT Sans under the SIL Open Font License, in `assets/fonts/PTSans-OFL.txt`.

The information panel's Third-party licences link opens the notices the plug-in embeds: the font's licence, every crate the shipped formats link, grouped by licence, the ASIO SDK's licences and source, and the Truce License. `just notices` writes them to `THIRD-PARTY-NOTICES.txt` with a pinned cargo-about from `about.toml` and `about.hbs`. The candidate workflow runs it before packaging and names the file in `THIRD_PARTY_NOTICES`, which `build.rs` embeds; a build without that variable embeds a one-line placeholder, so local builds never generate the notices. Every licence `about.toml` accepts is compatible with GPLv3.

### Vendored crates

Narrow patches of the published Truce 6.3.0 sources and of baseview, each directory carrying its unchanged upstream licences, original manifest, source reference and an `UPSTREAM.md` describing the local changes:

- `vendor/baseview-truce`: frame delivery and host keyboard and modifier fixes.
- `vendor/truce-iced`: iced input, focus, redraw and clipboard fixes.
- `vendor/truce-clap`: host state notification required by clap-validator, dynamic-latency restart and active reset handling.
- `vendor/truce-standalone`: dynamic-latency restart on the output worker, an input kept within about one buffer of the output, a Buffer Size menu, remembered devices and buffer size, and ASIO on Windows.
- `vendor/truce-core`, `vendor/truce-plugin`, `vendor/truce-loader` and `vendor/truce`: a real-time reset lifecycle hook and its forwarding bridge.
- `vendor/truce-au`: a latency change reaches the Audio Unit host's property listeners.
- `vendor/cargo-truce`: the source-only 6.3.0 build tool with the Azure `ExcludeCredentials` patch, the Audio Unit Info.plist patch and the scoped Windows installer name. It is a build tool, not linked into the plug-in. The Truce Framework Rider's Section 2.2 lists audio plug-ins and suites among the uses that are not Covered Framework Offerings.

Everything else resolves from the pinned Cargo lockfile.
