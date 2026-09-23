# Swanky Amp

Swanky Amp is Resonant DSP's free guitar amplifier. Version 2 is a Rust rebuild of the released Free 1.4.0 amplifier model, with its tone stack corrected, an iced editor, a standalone app, and CLAP and VST3 formats. It accepts mono and stereo host layouts and processes stereo channels through independent amplifier paths.

The released JUCE 1.4.0 source is preserved at the `juce-1.4.0` tag. Version 2 deliberately uses a new host and installation identity, `Swanky Amp 2` / `com.resonantdsp.swanky-amp-2`, so it installs beside the released `Swanky Amp` and does not take over old sessions.

## Development

Install Rust through [rustup](https://rustup.rs/) and install [just](https://github.com/casey/just). The repository pins its Rust toolchain. Run the complete per-change gate with:

```sh
just
```

The gate checks formatting, lints with and without the plugin-format features, runs the behavioral tests, verifies the [released reference renderer](verification/reference/README.md), compares the Rust amplifier's legacy path against all ten released factory presets at 44.1 kHz and 1x processing, proves the committed [tone-stack refit](verification/tone-stack/refit-report.md) is current, and proves the committed level calibration reproduces.

Render one preset and its internal comparison seams with:

```sh
just render-model "high gain" /tmp/high-gain.wav
```

`just model-check` runs the ten-preset comparison by itself. It checks every active triode plus the tone stack, power amp, cabinet, and final output. The fixed acceptance bounds are 0.2% relative waveform RMS, 0.65% relative peak error, and 0.02 dB in each low, mid, and high band. The peak bound covers the measured 0.627% level-11 power-stage difference from a noncontracting C++ build; RMS and band bounds remain unchanged and retain the timing, polarity, state, and voicing checks.

The shipping path applies Auto oversampling to the nonlinear tube stages while the cabinet remains at the host rate. Auto uses 2x at 44.1 and 48 kHz and 1x at 88.2 kHz and above; fixed 1x, 2x, and 4x choices are capped below 193.92 kHz internally. The header button cycles Auto, 1x, 2x and 4x and shows the factor the engine is running once audio has been prepared, such as "Auto 2×"; it is lit whenever the tube stages oversample or Auto is still choosing. The host receives the measured FIR delay: 32 samples at 2x and 48 samples at 4x. CLAP and VST3 changes request the host's deactivate/activate sequence; the standalone stops and rebuilds its output stream on the existing worker. An active CLAP reset clears processing history at the current factor with a bounded, allocation-free equilibrium calculation. Activation applies the pending factor off the audio thread. Choices that resolve to the active factor keep their state without a restart. The plate low-pass stays at 20 kHz as the tube rate changes and reproduces the released coefficients at 44.1 kHz.

Regenerate the public factor, latency, seam-level, and aliasing measurements with:

```sh
just dsp-report
```

The report's seam and aliasing measurements keep the released knee, tone mapping and level compensation in the corrected path (`render-model --model corrected --tone-mapping released --knee released --tables released`) so they isolate oversampling and the plate filter, use the explicit legacy renderer for the baseline, and measure the shipping path's active-reset equilibrium across all ten factory presets, control extremes, and supported rates. It does not establish factory-preset acceptance for the corrected sound.

### Tone stack

Swanky Amp 1.4.0 discretised its tone stack with the bilinear constant `SR`
instead of the standard `2·SR`, which placed every tone-stack feature an octave
above the circuit. Version 2 ships the standard mapping. The legacy path, which
`just model-check` compares with the frozen 1.4.0 renders, keeps the released
mapping so that comparison still proves the port. Anyone who wants the old
voicing exactly can keep Swanky Amp 1.4.0 installed beside version 2.

The factory presets were voiced on the octave-high stack, so their Low, Mid
and High, and Power Drive where the level into the power stage needed it, are
refitted to sound roughly as they did on a generated pluck, measured through the shipping path including the unit-slope knee below. The fit balances
spectral shape and level into the power stage and deliberately stops short of
an exact match, which would push the controls to their limits; the report
records each preset's residuals. Regenerate the version 2 bank and its report
with:

```sh
just refit
```

`just refit-check`, part of `just`, fails if `presets/factory-2.0.xml` or
`verification/tone-stack/` differ from what the code produces. The plugin
embeds that file as its factory bank at build time.

The refit is accepted by ear, so a blind listening kit renders every factory
preset both ways:

```sh
just listening-kit /path/outside/the/repository
```

For the single-coil DI and the refit's pluck it writes a pair of 24-bit
44.1 kHz WAVs per preset: Swanky Amp 1.4.0 from the C++ reference renderer
with the released bank, and the version 2 shipping path with Auto
oversampling and the refitted bank, both from a settled amplifier and aligned
for the oversampler's latency. Version 2 is trimmed to the released RMS so
loudness does not identify it, and a pair shares one headroom trim if either
would peak above -1.1 dBFS. Each pair's files are named `X` and `Y` in a
seeded random order; `KEY.txt` says which is which and lists the trims, which
are the remaining output level differences, and `pairs.md` adds the controls
the refit moved. The kit is review material and is never committed.

The three treble sections are first-order circuits, but 1.4.0 discretised
them as biquads with the second-order terms set to zero. That multiplies
numerator and denominator by `1 + z⁻¹`, leaving a pole on the unit circle at
Nyquist that only exact arithmetic cancels. Rounded to f32 the pole can sit a
few parts in 10⁹ outside the circle, for example the Marshall treble at
88.2 kHz (+3.9e-9) and the Fender treble at 176.4 kHz (+1.2e-8) and in the
released mapping at 44.1 kHz (+2.0e-8). Rounding noise at Nyquist then grows
exponentially until, after hours of continuous play, it swamps the signal and
drives the power stage into cutoff. Keeping f32 coefficients and making the
state f64 still fails, and in f64 the pole sits exactly on the circle, so
precision alone does not fix it. The shipping mapping discretises the treble
sections as true first-order filters, which removes the pole; the response is
unchanged. The legacy path keeps the released form, so the model gate stays
bit-identical and it still carries the defect.

### Presets

The header's preset field shows the current preset's name between `‹` and
`›`, which step through the factory presets and then the user's own. A press
on the name opens the menu: Init, the ten factory presets, the user presets,
then Save (a changed user preset), Save as…, Remove (user presets only),
Import 1.x presets and Open folder. Init restores every preset control to its
default; there is no Reset button. Choosing a preset sets its controls
through the host, so automation and undo see the change, and the selected
preset is part of the plugin state, so a reopened session shows its name
again. A dot after the name marks a preset changed since it was chosen.

As in 1.4.0, Input and the cabinet switch belong to the session: a preset
stores them, but choosing one leaves them as they are and changing them does
not mark the preset changed. Oversampling is not part of a preset.

User presets live in:

| Platform | Version 2 | Swanky Amp 1.4.0 |
|---|---|---|
| macOS | `~/Library/Audio/Presets/Resonant DSP/Swanky Amp 2` | `~/Library/Audio/Presets/Resonant DSP/Swanky Amp` |
| Windows | `%APPDATA%\Resonant DSP\Swanky Amp 2` | `%APPDATA%\Resonant DSP\Swanky Amp` |
| Linux | `$XDG_DATA_HOME/Resonant DSP/Swanky Amp 2` (default `~/.local/share`) | `~/.config/Resonant DSP/Swanky Amp` |

The version 2 folder is created on the first save or import. Each preset is
one `<name>.xml` file in the 1.x schema, an `APVTSSwankyAmp` element listing
`<PARAM id value/>` entries under the 1.x parameter ids, so 1.x and 2.0 presets
stay one format: version 2 reads 1.4.0 files, including the version
migrations 1.4.0 applied to presets from earlier releases, and 1.4.0 can load
a version 2 file. A file that is not well-formed or is not a Swanky Amp preset
is left out of the menu and named in the footer.

The first time version 2 runs without a preset folder, and on Import 1.x
presets, it copies the user's presets from the 1.4.0 folder, which it never
modifies. Each imported preset keeps its name and every control except Low,
Mid, High and Power Drive, which are refitted by the same objective as the
factory set above: rendered on the released octave-high tone stack and fitted
on the corrected one to match its spectral shape and level into the power
stage, with Power Drive moving at most 0.15 and only when the level would
otherwise change by more than 0.5 dB. The result is an approximation, closest
on moderate tone settings and furthest where a preset relied on extreme
Low, Mid or High; the file records `importedFrom` and `refit` attributes. A
name already taken in the version 2 folder is kept as it is, and unchanged
copies of the 1.4.0 factory presets, which 1.4.0 wrote into its folder, are not
copied because the refitted factory set already carries them.

### Soft-clip knee

The triode soft clips (grid, bias, plate and compression) use a unit-slope knee. The released Faust model scaled its cubic clip input by 1/3.4, so the curve left each knee with slope 4/3.4 against the linear side's 1, a corner at every clip. Scaling by 1/4 joins the knee smoothly at the cost of slightly less gain between knee and ceiling. Because all five preamp stages compress, the loss compounds, so each triode carries a fixed output makeup gain (+0.13, +0.05, +0.13, +0.15 and +0.10 dB for stages 1 to 5), fitted as the mean seam residual over the ten factory presets at 0 dB input. Correcting each stage at its own output drives the next one as hard as 1.4.0 did. The tetrode's push-pull clips keep the released curve: their corners are wider than the signal's distance to the knee, so ordinary playing sits inside the cubic and the knee span sets the power stage's bias and gain instead of shaping a knee. The unit span moved the power seam by -0.4 to -3.0 dB depending on power drive, which no single makeup gain can undo.

Regenerate the knee measurements with:

```sh
just knee-report
```

It renders every factory preset at 44.1 kHz and 1x with the DI scaled by -12, -6, 0 and +6 dB, through the corrected path with the released tone mapping and level compensation and the released and the unit knee, and records each seam's RMS ratio and crest-factor change in `verification/dsp/knee.json`. At 0 dB input it requires every triode seam within 0.6 dB of the released level, the tone stack within 1.05 dB, and the power amp, cabinet and output within 0.5 dB. The widest preamp residuals come from presets whose stages move in opposite directions (pre drive +0.43 dB and level 11 -0.60 dB after the fifth triode), which one gain per stage cannot separate; the power stage compresses them.

### Level calibration

As in 1.4.0, the amplifier levels itself with two tables and fixed scales. The preamp table normalises the last active triode's output against Drive, the tone-stack scale normalises the stack's gain at the factory defaults, the power table normalises the power amp's output against Power Drive, and the cabinet keeps its own fixed scale. Grit and Stages stay uncompensated, which is part of how the amplifier plays. The legacy path keeps the released values.

Oversampling, the unit-slope knee and the standard tone-stack mapping change the level reaching each of these, so the shipping path's values are measured against the released path, which `just model-check` holds to the frozen 1.4.0 renders. `calibrate` renders the single-coil DI at 44.1 kHz with Auto oversampling from a settled amplifier, every control but the swept one at its default, and multiplies each released value by the RMS ratio of the released seam to the shipping seam: Drive over the eleven table points at the last active triode, then the tone-stack scale on the power stage input at the defaults, then Power Drive over its eleven points at the power amp, each with the values found so far in place. Every table point therefore lands on the released level, and Drive and Power Drive move loudness as 1.4.0 did. The preamp table moves by -0.32 to +0.27 dB and the power table by -0.13 to +0.66 dB. The tone-stack scale is the one fixed value that moves, by +2.14 dB: the standard mapping's stack is quieter at its default settings on the DI, which no Drive table can correct.

At the factory defaults the power stage input lands on 1.4.0's level and the output with the cabinet off within 0.1 dB, which a test holds. With the cabinet on the default output is 1.26 dB quieter, because the cabinet responds to the default tone controls' changed voicing. The cabinet scale stays as released: the refitted factory presets keep the released stack's shape, and raising it would make each of them louder than 1.4.0. Across the ten factory presets the output moves from 0.08 to 2.49 dB below 1.4.0 before calibration to within 1.0 dB after, and the mean distance from 0.97 to 0.46 dB.

Regenerate the values in `src/dsp/calibration_data.rs` with:

```sh
just calibrate
```

`just calibrate-check`, part of `just`, fails if a fresh measurement moves any committed value by more than 0.05 dB.

### Soak

Issue #34 reported that 1.2 started sounding like a tremolo after hours of running. The soak is rerun on each release candidate:

```sh
just soak 4        # hours of audio per run, started in the background
just soak-check    # verdict so far, or the final one
```

`just soak` builds the `soak` tool in release mode and starts four detached processes at 44.1 kHz with Auto oversampling (2x): the shipping path, built exactly as the plugin engine builds it, for `clean`, `level 11` (the highest-gain factory preset) and Init, plus `level 11` on the legacy released path for comparison. Shipping runs read `presets/factory-2.0.xml`; the legacy run reads the released bank. Each writes `target/soak/<path>-<preset>.csv`, with its console output in the matching `.log`, its process ID in the `.pid`, and the commit it was built from in `target/soak/commit`. `SOAK_DIR` and `SOAK_RUNS` (see `scripts/soak.sh`) choose another directory and set of runs, including fixed oversampling. Each run renders two independent channels, as a stereo host would: stationary white noise at -40 dBFS RMS, and the same floor with a decaying 110 Hz pluck peaking at -20 dBFS every two seconds, so the drift and compression envelopes charge and release throughout. Every 10 seconds of audio a CSV row records output RMS and peak, the RMS at each active triode, the tone stack, power amp, cabinet and output seams, non-finite and subnormal sample counts, the processing time, and the tremolo-band modulation of the 100 Hz RMS envelope between 0.5 and 15 Hz, both as an equivalent sinusoidal depth over the whole band and as the strongest single frequency.

A shipping-path run passes when no sample is non-finite, its output RMS over the last 30 minutes is within 0.1 dB of the first 30 minutes, and its band modulation never exceeds the largest value of the first 10 minutes by more than 25% plus 0.005. Stationary noise alone reads about 0.06 through the estimator, so the margin covers its scatter while a coherent tremolo of about 0.4 dB depth still fails. The legacy run is reported for context and is not gated. `soak-check` also reports first-to-last-hour and per-seam drift and the slowest window against the median. On an Apple M-series core four hours of audio take about 25 minutes per run.

The first four-hour soak, [`verification/soak/2026-09-22-summary.txt`](verification/soak/2026-09-22-summary.txt), reproduced issue #34 on the legacy path. On `level 11`, after about 3.7 hours (13,290 to 13,640 s) the tone-stack seam rose by 23 to 26 dB while the power amp, cabinet and output fell by 15 to 26 dB, with modulation indices of 9 to 17 against a baseline under 0.7. Every triode seam stayed within 0.002 dB, which places the instability in the released tone stack at 44.1 kHz rather than in the stages' drift and compression envelopes. The shipping path of that commit, which already ran the tube stages and tone stack at 2x, passed four hours on all three presets with at most 0.005 dB of drift, modulation at its baseline and no non-finite samples.

The 12-hour soak of the shipping path at commit 318c8b5 found the same
failure there: `level 11` at Auto (2x) collapsed after about ten hours of noise
(tone-stack seam +43 dB, output -131 dB), while `level 11` at 1x and Init at 1x
and 2x held within 0.002 dB. The cause was the tone stack's spurious Nyquist
pole described under Tone stack, which also accounts for the legacy failure
above. Because that growth is a few parts in 10⁹ per sample, a pre-release
check drives the shipping tone stack alone for 24 hours of samples in minutes:

```sh
just tone-stack-soak
```

It runs level 11 and each stack model with Low, Mid, High and Presence at both
extremes, at 44.1, 88.2 and 176.4 kHz, with white noise at the level the stack
sees at level 11 (9.7 RMS), and fails if any hour's level moves more than
0.01 dB from the first or its mean exceeds 10⁻⁴ of its RMS. It takes about
eight minutes on an Apple M-series machine. Before the fix it failed within the
first hours at 176.4 kHz and at about eight hours at 88.2 kHz; after it, the
worst hourly drift over all 21 cases is 0.005 dB. `just` includes a short test
that the stack falls silent after its input stops at each of those rates,
which the Nyquist pole prevents.

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
The cabinet's on/off is a two-position vertical switch: a brushed aluminium
disc in a V track baked into the faceplate, exactly one disc wide and two
tall, the disc in the top half when on and the bottom half when off. The disc
is a baked sprite the compositor places from the parameter. Knob markers are
Pro's glossy black divots at the same proportions. Export the exact resolved
geometry (layout manifest schema 4, which gives each section its outline
radius and describes the switch track) or capture
the editor at 1x and 2x with:

```sh
just export-layout /tmp/swanky-layout
just capture /tmp/swanky-capture
```

`just capture-preset "high gain" /tmp/swanky-capture` draws the editor with
that factory preset applied and named in the header. `capture` needs a
working GPU adapter. The layout export remains available when
the artwork package is missing or stale so a new bake can be produced from
changed widget geometry.

The four live meter columns, captioned L and R, are local to each plugin
instance. The blue input pair observes the signal after the Input control on
the released -26 to +8 dB scale; the output pair, in the accent, observes the
final signal after the optional cabinet and Output control on a -30 to 0 dB
scale. Cells light from the bottom up. A mono instance mirrors its reading into
L and R. Immediate attack and a half-second release settle to exact darkness,
after which the editor has no meter change to redraw; the meters also go dark
while the editor window has lost focus and the pointer is elsewhere.

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

Swanky Amp is licensed under GPLv3 or later; see [LICENSE](LICENSE). The model authority is the exact Free 1.4.0 C++ wrapper and generated Faust headers preserved in `verification/reference/released` from the `juce-1.4.0` tag. The public legacy renderer retains the released control mappings, detuning, fitted constants, stage behavior, calibration tables, cubic knee, fixed digital plate filter, and old tone mapping. The shipping path adds tube-only oversampling, a rate-tracked 20 kHz plate filter, a unit-slope triode knee, the standard tone-stack mapping with refitted factory presets and level compensation recalibrated against the released path; later corrected-model work remains subject to measurement and player audition. Small equation and filter primitives were selectively adapted from the separately implemented Pro code only where comparison proved that they express the released Free equations.

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
