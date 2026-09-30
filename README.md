# Swanky Amp

Swanky Amp is Resonant DSP's free guitar amplifier. Version 2 is a Rust rebuild of the released Free 1.4.0 amplifier model, with its tone stack corrected, an iced editor, a standalone app, and CLAP, VST3 and, on macOS, Audio Unit formats. It accepts mono, stereo and mono-in, stereo-out host layouts, processes stereo channels through independent amplifier paths, and plays a mono input on both sides of a stereo output.

The released JUCE 1.4.0 source is preserved at the `juce-1.4.0` tag. Version 2 deliberately uses a new host and installation identity, `Swanky Amp 2` / `com.resonantdsp.swanky-amp-2`, so it installs beside the released `Swanky Amp` and does not take over old sessions.

## Development

Install Rust through [rustup](https://rustup.rs/) and install [just](https://github.com/casey/just). The repository pins its Rust toolchain. Run the per-change gate with:

```sh
just
```

The gate checks formatting, lints every target of the crate with the default features (the plug-in formats and the standalone) and the tools, and runs the crate's behavioral tests without the default features. It therefore compiles the format adapters and the standalone binary but does not run their tests.

CI runs the full set, `just ci-checks`, on every pull request and every push to master. Beyond the gate it lints without the default features, runs the format adapters' tests and the vendored standalone host's tests, runs the release-script tests, verifies the [released reference renderer](verification/reference/README.md), compares the Rust amplifier's legacy path against all ten released factory presets at 44.1 kHz and 1x processing, proves the committed level calibration reproduces, and validates the artwork package.

Run a part of it locally only when the change touches that area:

- `just release-tests` for the release scripts;
- `just reference-check`, `just model-check` and `just calibrate-check` for the DSP;
- `just validate-assets` for artwork or layout;
- `just clippy-all` and `just test-all` for the vendored host, a format adapter or the standalone.

The offline tools in `src/bin` build only with the `tools` feature, which keeps them out of the plug-in format builds; the recipes that run them turn it on.

Render one preset and its internal comparison seams with:

```sh
just render-model "high gain" /tmp/high-gain.wav
```

`just model-check` runs the ten-preset comparison by itself. It checks every active triode plus the tone stack, power amp, cabinet, and final output. The fixed acceptance bounds are 0.2% relative waveform RMS, 0.65% relative peak error, and 0.02 dB in each low, mid, and high band. The peak bound covers the measured 0.627% level-11 power-stage difference from a noncontracting C++ build; RMS and band bounds remain unchanged and retain the timing, polarity, state, and voicing checks.

The versioned reference corpus captures the released cold startup, including its 1024-sample output mute. The Rust path settles its configured nonlinear state for one second before audio begins, and stages re-enter warm when the continuous stage-count control brings them back into the signal path. Model comparison therefore applies the same one-second silent pre-roll to the released chain and excludes it from the measured WAVs. The cold corpus and warmed comparison remain separate so the startup difference is explicit.

The shipping path applies Auto oversampling to the nonlinear tube stages while the cabinet remains at the host rate. Auto uses 2x at 44.1 and 48 kHz and 1x at 88.2 kHz and above; fixed 1x, 2x, and 4x choices are capped below 193.92 kHz internally. The header button cycles Auto, 1x, 2x and 4x and shows the factor the engine is running once audio has been prepared, such as "Auto 2×"; it is lit whenever the tube stages oversample or Auto is still choosing. The host receives the measured FIR delay: 32 samples at 2x and 48 samples at 4x. CLAP and VST3 changes request the host's deactivate/activate sequence; an Audio Unit host is told the new latency and the factor takes effect at its next reset; the standalone stops and rebuilds its output stream on the existing worker. An active CLAP reset clears processing history at the current factor with a bounded, allocation-free equilibrium calculation. Activation applies the pending factor off the audio thread. Choices that resolve to the active factor keep their state without a restart. The plate low-pass stays at 20 kHz as the tube rate changes and reproduces the released coefficients at 44.1 kHz.

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

The factory presets were voiced on the octave-high stack, so each is voiced
again for the corrected one on the guitar recordings in
`verification/reference/input`, judged at the output. Low, Mid, High and
Presence are searched so the balance between third-octave bands from 80 Hz to
8 kHz is as close to 1.4.0's as a light cost on moving each control allows,
with the controls kept between 1 and 9, and Power Drive follows so each preset
drives the power stage as 1.4.0 did. Once a bank is accepted by ear, `just
refit` keeps its Low, Mid, High and Presence and sets only Power Drive and
Output again: moving the tone controls bought a few tenths of a dB of balance,
less than the ear or the recordings resolve. It searches only a preset the
bank lacks. Regenerate the version 2 bank and its report, which records each
preset's settings, balance and power-stage level against 1.4.0, with:

```sh
just refit
```

It takes a few minutes in a release build, so it is not part of `just`. The
plugin embeds `presets/factory-2.0.xml` as its factory bank at build time.

Known limits of the corrected stack against 1.4.0:

- 1.4.0's scoop sat an octave higher than any setting of the corrected stack
  can place it, and the corrected Low acts only below about 125 Hz. The
  voiced presets keep 150 to 400 Hz 1 to 2 dB under 1.4.0 and 1 to 1.6 kHz
  about 1 dB over; the [voicing report](verification/tone-stack/refit-report.md)
  lists the remainder per preset.
- Init is the corrected stack at its default settings and is not revoiced:
  against 1.4.0 it has 3.5 to 7 dB less between 100 and 400 Hz and 4 to
  5.6 dB more between 0.8 and 1.6 kHz.
- At playing level 1.4.0 got several dB louder as Drive and Power Drive rose
  towards 10, by how much depending on the pickup. Version 2 holds Init's
  level across both, so high Drive and Power Drive settings play quieter than
  they did in 1.4.0.

These levels are measured at 44.1 kHz with Auto oversampling and on the three
tone stacks themselves, not on blends between them.

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
`›`, which step through the factory presets and then the user's own. A name
too long for the field ends in an ellipsis short of the arrows. A press
on the name opens the menu: Init, the ten factory presets, the user presets,
then Save (a changed user preset), Save as…, Remove (user presets only),
Import 1.x presets and Open folder. Remove deletes the preset's file, so its
first press only turns the item into "Remove <name>?" and keeps the menu open;
a second press deletes it, and closing the menu cancels. Init restores every preset control to its
default; there is no Reset button. Choosing a preset sets its controls
through the host, so automation and undo see the change, and the selected
preset is part of the plugin state, so a reopened session shows its name
again. A dot after the name marks a preset changed since it was chosen. The
menu capitalises the factory presets like Init; the bank, the saved state and
the tools such as `just capture-preset` name them in lower case, as 1.4.0 did.

Version 2's factory presets are balanced to strike as loud as Init: each
one's Output is set so that its strike level on the humbucker recording
matches Init's. The strike level is the 95th percentile of momentary
loudness (K-weighted 400 ms blocks at a 100 ms hop, those above -70 LUFS)
over the whole recording. Integrated loudness, the measure the level
calibration below holds, averages over the ring-out, where a driven amp
sustains and a clean one decays; a driven preset level with Init on it
strikes several dB softer. A clean amp also follows the pickup where a
driven one does not, so on the single coil the driven presets come out
louder than Init. Swanky Amp 1.4.0's factory presets were not balanced, and
imported 1.x presets keep their Output as it was. `just refit` measures the
balance and applies it when it writes the bank, and the [voicing
report](verification/tone-stack/refit-report.md) lists each preset's Output
change and its levels against Init on each pickup.

As in 1.4.0, Input and the cabinet switch belong to the session: a preset
stores them, but choosing one leaves them as they are and changing them does
not mark the preset changed. Oversampling is not part of a preset.

User presets live in:

| Platform | Version 2 | Swanky Amp 1.4.0 |
|---|---|---|
| macOS | `~/Library/Audio/Presets/Resonant DSP/Swanky Amp 2` | `~/Library/Audio/Presets/Resonant DSP/Swanky Amp` |
| Windows | `%APPDATA%\Resonant DSP\Swanky Amp 2` | `%APPDATA%\Resonant DSP\Swanky Amp` |
| Linux | `$XDG_DATA_HOME/Resonant DSP/Swanky Amp 2` (default `~/.local/share`) | `~/.config/Resonant DSP/Swanky Amp` |

The version 2 folder is created when first needed: by a save, by Open folder,
or by an import, even one that copies nothing. Each preset is one
`<name>.xml` file in the 1.x schema, an `APVTSSwankyAmp` element listing
`<PARAM id value/>` entries under the 1.x parameter ids, so 1.x and 2.0
presets stay one format: version 2 reads 1.4.0 files, including the version
migrations 1.4.0 applied to presets from earlier releases, and 1.4.0 can load
a version 2 file. A file that is not well-formed or is not a Swanky Amp preset
is left out of the menu and named in the footer.

The first time version 2 runs without a preset folder, and on Import 1.x
presets, it copies the user's presets from the 1.4.0 folder, which it never
modifies. Each imported preset keeps its name and every control except Low,
Mid, High and Power Drive, which are converted by a faster fit than the factory
voicing, one the plugin can run itself: rendered on the released octave-high
tone stack and fitted on the corrected one to match the stack's own output on
a generated pluck, with Power Drive moving at most 0.15 and only when the
level into the power stage would otherwise change by more than 0.5 dB. That
fit judges the stack rather than the output and a pluck rather than a guitar,
so imported presets can sound boxier and less scooped than their originals,
most where a preset relied on extreme Low, Mid or High; the file records
`importedFrom` and `refit` attributes. A name already taken in the version 2
folder is kept as it is, and unchanged copies of the 1.4.0 factory presets,
which 1.4.0 wrote into its folder, are not copied because the voiced factory
set already carries them.

### Soft-clip knee

The triode soft clips (grid, bias, plate and compression) use a unit-slope knee. The released Faust model scaled its cubic clip input by 1/3.4, so the curve left each knee with slope 4/3.4 against the linear side's 1, a corner at every clip. Scaling by 1/4 joins the knee smoothly at the cost of slightly less gain between knee and ceiling. Because all five preamp stages compress, the loss compounds, so each triode carries a fixed output makeup gain (+0.13, +0.05, +0.13, +0.15 and +0.10 dB for stages 1 to 5), fitted as the mean seam residual over the ten factory presets at 0 dB input. Correcting each stage at its own output drives the next one as hard as 1.4.0 did. The tetrode's push-pull clips keep the released curve: their corners are wider than the signal's distance to the knee, so ordinary playing sits inside the cubic and the knee span sets the power stage's bias and gain instead of shaping a knee. The unit span moved the power seam by -0.4 to -3.0 dB depending on power drive, which no single makeup gain can undo.

Regenerate the knee measurements with:

```sh
just knee-report
```

It renders every factory preset at 44.1 kHz and 1x with the DI scaled by -12, -6, 0 and +6 dB, through the corrected path with the released tone mapping and level compensation and the released and the unit knee, and records each seam's RMS ratio and crest-factor change in `verification/dsp/knee.json`. At 0 dB input it requires every triode seam within 0.6 dB of the released level, the tone stack within 1.05 dB, and the power amp, cabinet and output within 0.5 dB. The widest preamp residuals come from presets whose stages move in opposite directions (pre drive +0.43 dB and level 11 -0.60 dB after the fifth triode), which one gain per stage cannot separate; the power stage compresses them.

### Grit

Grit lowers each triode's grid clip and raises the threshold of its plate compressor. In 1.4.0 the threshold rose by up to 100 of its units, and above about 72 the threshold of the third stage, which its detuning places highest, sits above the stage's own plate signal. The compressor then never charges, its ceiling falls to the zero offset Grit leaves it, and the stage clips everything to a constant. 1.4.0 lost 52 dB at full Grit this way, and the unit-slope knee's flatter clip took the shipping path to 100 dB. The collapse sets in at the same threshold at every input level from -30 to +12 dB, so it is the mapping driving the compressor past the range the fitted stage supports, not a level effect. The shipping path stops the threshold at 70, just short of the collapse, which Grit reaches at 8.5 on its 0 to 10 scale. Below that nothing changes, and until the collapse the raised threshold had barely begun to reach the signal, so removing it loses no grit. The lower grid clip alone still costs 12 dB on the DI at full Grit, which the Grit output gain below restores. Grit below its centre has no effect on level. The legacy path keeps the released mapping, so the model gate stays bit-identical and it still carries the defect.

### Level calibration

The level compensation has two stages, both measured by `calibrate` on the
guitar recordings in `verification/reference/input`, played at Input 0 with
`RECORDING_GAIN_DB` (2 dB) applied to both and averaged over the two pickups,
at 44.1 kHz with Auto oversampling from a settled amplifier, every control but
the swept one at its default. The reference is the released path, which `just
model-check` holds to the frozen 1.4.0 renders.

The first stage keeps 1.4.0's structure and sets how hard the power stage is
driven. With the tone controls at their defaults, the level into the power
stage is measured on both paths at each of Drive's eleven table points for
each tone stack. The tone-stack scale takes the mean gap and the preamp table
each Drive point's departure from it, so real playing drives the power stage
as 1.4.0 did at every Drive. One scale serves all three stacks, so each sits
up to half their spread from 1.4.0. The corrected Fender stack also passes
more of a humbucker's upper mids than 1.4.0's did, so the two pickups land
either side of the average; one gain cannot serve both. The power table then
normalises the power amp's output against Power Drive by the ratio of the
released seam to the shipping one, and the cabinet keeps its own fixed scale.
`calibrate` prints every measured point.

The second stage keeps loudness. Loudness here is ITU-R BS.1770-4 gated
integrated loudness, computed in the tool and averaged in LUFS over the
recordings. The target is the factory defaults' loudness from the first stage,
so Init keeps its level. The power table is rescaled point by point to that
target, and then Drive and Grit each get an output gain table solved the same
way. The two Drive points either side of the default absorb the default's own
few tenths of a dB, so Init lands exactly. All three gains follow the cabinet,
so they change level and nothing else. Stages stays uncompensated, as
released.

Regenerate the values in `src/dsp/calibration_data.rs` with:

```sh
just calibrate
```

`just calibrate-check`, part of CI's checks, fails if a fresh measurement moves any committed value by more than 0.05 dB. The factory voicing and balance use the same levels, so rerun `just refit` after a calibration change and listen to the result.

### Soak

Issue #34 reported that 1.2 started sounding like a tremolo after hours of running. The soak is a diagnostic, run on demand when a long-run defect is suspected; it is not a step in releasing a candidate. The pre-release checks are `just ci-checks` and `just tone-stack-soak`, described below.

```sh
just soak 4        # hours of audio per run, started in the background
just soak-check    # verdict so far, or the final one
```

`just soak` builds the `soak` tool in release mode and starts four detached processes at 44.1 kHz with Auto oversampling (2x): the shipping path, built exactly as the plugin engine builds it, for `clean`, `level 11` (the highest-gain factory preset) and Init, plus `level 11` on the legacy released path for comparison. Shipping runs read `presets/factory-2.0.xml`; the legacy run reads the released bank. Each writes `target/soak/<path>-<preset>.csv`, with its console output in the matching `.log`, its process ID in the `.pid`, and the commit it was built from in `target/soak/commit`. `SOAK_DIR` and `SOAK_RUNS` (see `scripts/soak.sh`) choose another directory and set of runs, including fixed oversampling. Each run renders two independent channels, as a stereo host would: stationary white noise at -40 dBFS RMS, and the same floor with a decaying 110 Hz pluck peaking at -20 dBFS every two seconds, so the drift and compression envelopes charge and release throughout. Every 10 seconds of audio a CSV row records output RMS and peak, the RMS at each active triode, the tone stack, power amp, cabinet and output seams, non-finite and subnormal sample counts, the processing time, and the tremolo-band modulation of the 100 Hz RMS envelope between 0.5 and 15 Hz, both as an equivalent sinusoidal depth over the whole band and as the strongest single frequency.

A shipping-path run passes when no sample is non-finite, its output RMS over the last 30 minutes is within 0.1 dB of the first 30 minutes, and its band modulation never exceeds the largest value of the first 10 minutes by more than 25% plus 0.005. Stationary noise alone reads about 0.06 through the estimator, so the margin covers its scatter while a coherent tremolo of about 0.4 dB depth still fails. The legacy run is reported for context and is not gated. `soak-check` also reports first-to-last-hour and per-seam drift and the slowest window against the median. On an Apple M-series core four hours of audio take about 25 minutes per run.

The soak reproduced issue #34 on the legacy path: on `level 11`, after about
3.7 hours the tone-stack seam rose by 23 to 26 dB while every later seam fell,
and every triode seam held within 0.002 dB
([`verification/soak/2026-09-22-summary.txt`](verification/soak/2026-09-22-summary.txt)).
A 12-hour run found the same collapse on the shipping path after about ten
hours at 2x. Both were the tone stack's spurious Nyquist pole described under
Tone stack; after the fix, 12-hour runs of Init at 2x and `level 11` at 2x and
4x passed
([`verification/soak/2026-09-23-summary.txt`](verification/soak/2026-09-23-summary.txt)).
Because that growth is a few parts in 10⁹ per sample, the pre-release check
drives the shipping tone stack alone for 24 hours of samples in minutes:

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

### Standalone

After `just setup`, open the standalone shell with:

```sh
just run
```

The standalone opens with its input on, since an amplifier with its input off
is silent; `--input-enabled off` opts out. Its Settings menu chooses the input,
the output and the buffer size (128 samples unless chosen), and remembers them
on the machine; the `--input`, `--output` and `--buffer` flags override them for one launch
(`cargo run --release -- --help` lists every option). Choosing an audio
interface as the input takes the output to it too, unless an output has been
chosen, and the input is kept within about one buffer of the output.
On Windows it plays through ASIO when an ASIO driver is installed, and its
Settings menu chooses between ASIO and Windows (WASAPI); the `--driver` flag,
`asio` or `wasapi`, overrides that for one launch. On ASIO the interface is one
device for input and output. The Windows recipes build the standalone with the
Cargo feature `asio`, which compiles the ASIO SDK that `just setup` fetches
into `tools/` and needs libclang; no other build compiles it.

### Editor

The editor is 864 by 512 interface pixels and uses one iced widget tree for
the live controls and the artwork layout contract. As in 1.4, the six Free signal-flow groups (Levels, Cabinet,
Preamp, Staging, Power Amp and Tone) are separate rounded boxes with graphite
between them, each outlined by its own V groove. Pro's material language
carries over with 1.4's rose highlight as Free's accent on the lit rings,
the selected outlines and the output meter. The bundled CC BY 4.0 artwork
package provides the graphite, brushed metal, shadows, and response lighting.
The cabinet's on/off is a two-position vertical switch: a brushed aluminium
disc in a V track baked into the faceplate, exactly one disc wide and two
tall, the disc in the top half when on and the bottom half when off. The disc
is a baked sprite the compositor places from the parameter. Knob markers are
Pro's glossy black divots at the same proportions. While the cabinet is off, its
three knobs, their labels and readouts are dimmed as Pro dims a bypassed
section, and stay adjustable. Readouts show whole units at rest and tenths
while a knob is dragged.

The information panel's Interface size draws the whole editor at 75, 100, 125
or 150 %. The layout never changes: the widget tree always lays out at 864 by
512, the window is that times the size, and native text, the knob rings,
markers and meters render at the window's real resolution, so they stay sharp
at every size. The editor resizes its own window and asks the host to follow,
in CLAP, VST3, the Audio Unit and the standalone; it stays fixed-size to hosts,
so none offers a drag handle. The size belongs to the computer, not to a sound:
it is saved once per installation in `Swanky Amp 2 interface.json`, in
`~/Library/Resonant DSP` on macOS, `%APPDATA%\Resonant DSP` on Windows and
`$XDG_CONFIG_HOME/Resonant DSP` on Linux, and never in presets or host state.
The baked faceplate is two texels per interface pixel, exact at 100 % on a
Retina display, and the package stores box-filtered levels that smaller
drawings read.

Export the exact resolved geometry (layout manifest schema 4, which gives each
section its outline radius and describes the switch track) or capture the
editor at every interface size, at 1x and 2x, with:

```sh
just export-layout /tmp/swanky-layout
just capture /tmp/swanky-capture
```

The 100 % captures are `amp-1x.png` and `amp-2x.png`; the other sizes add
theirs, as in `amp-150-2x.png`. A capture always draws at the size it names,
whatever size this machine has chosen.
`just capture-preset "high gain" /tmp/swanky-capture` draws the editor with
that factory preset applied and named in the header, and
`just capture-information /tmp/swanky-capture` with the information panel
open; `just capture-information /tmp/swanky-capture 2.0.1` also announces
that release in it. `capture` needs a working GPU adapter. The layout export
remains available when the artwork package is missing or stale so a new bake
can be produced from changed widget geometry.

The four live meter columns, captioned L and R, are local to each plugin
instance. The blue input pair observes the signal after the Input control; the
output pair, in the accent, observes the final signal after the optional
cabinet and Output control. Cells light from the bottom up. The input meter
keeps 1.4.0's scale, -26 to +8 dBFS, and the player stages the guitar with
Input by eye: a light strum peaks about one third of the way up the input
meter with a single coil, about two thirds with a humbucker. The output meter
spans -60 to 0 dBFS, one cell per 6 dB. A mono instance mirrors its reading
into L and R. Levels rise immediately and fall to 1/e in 0.3 s, settling to
exact darkness, after which the editor has no meter change to redraw; the
meters also go dark while the editor window has lost focus and the pointer is
elsewhere.

The repository carries the artwork as `assets/artwork.pack` with its
`receipt.json` and `ARTWORK-LICENSE.txt` in `assets/artwork`; the editable
layers are not committed, since each rebake would add some 30 MB of EXRs to
the history. They come from the package itself. Artwork contributors can make a
public, reproducible round trip without the production renderer: unpack the
deterministic RGB9E5 package to editable ZIP float32 RGB EXRs, edit them in a
standard HDR image tool, refresh the receipt, then repack and validate:

```sh
just unpack-artwork assets/artwork.pack /tmp/swanky-artwork
just refresh-artwork /tmp/swanky-artwork
just pack-artwork /tmp/swanky-artwork /tmp/swanky-artwork.pack
just validate-assets /tmp/swanky-artwork.pack /tmp/swanky-artwork
```

Packing the unpacked layers unedited reproduces the package byte for byte.
To propose an edit, unpack into `assets/artwork` (the EXRs there are ignored by
git) and commit the repacked package and refreshed receipt.
The base and shadow layers are twice the editor's size in each direction. The
package stores every layer as deflated RGB9E5 and adds two box-filtered
halvings of the base, shadow and disc sprite, averaged in linear light, for
interface sizes that draw them smaller than their texels.
The receipt records the scene-linear radiance and display-linear shadow
semantics, dimensions, hashes, and public layout provenance. Producer metadata
is descriptive, so replacement CC artwork does not depend on Blender or the
original production sources. `just validate-assets`, part of CI's checks, validates that the checked-in package
describes its committed receipt and, when the layers are present in
`assets/artwork` or a folder given to `validate-assets`, that it is the
deterministic result of packing them.

### Bundle validation

Bundle validation is a separate platform check:

```sh
just setup
just validate
```

`setup` builds the repository's source-pinned cargo-truce 6.3.0 inside this
checkout and downloads checksum-verified builds of pluginval and clap-validator,
and on Windows the checksum-verified ASIO SDK.
`validate` builds and installs the CLAP and VST3 bundles, and on macOS the
Audio Unit, and runs the validators over them, auval among them on macOS.
GitHub Actions builds the standalone and runs the same bundle validation on
macOS and Windows without signing or repository secrets, once the checks pass.

## Releasing

The crate version in `Cargo.toml` is the version authority. `CHANGELOG.md` must
have the matching section. The local helpers do not push anything:

```sh
just version 2.0.1
just ci-checks
git add Cargo.toml Cargo.lock CHANGELOG.md
git commit -m "Release version 2.0.1"
just tag-candidate       # creates the next v2.0.1-rc.N locally
git push origin v2.0.1-rc.1
```

`just version` preflights the changelog and prepares only those three version
files. It never stages or commits them. The tag helpers require a clean tracked
working tree so each tag describes the committed version that passed `just ci-checks`.

Only `vX.Y.Z-rc.N` tags start `.github/workflows/candidate.yml`. A manual run is
a rehearsal and is accepted only from an administrator-owned `rehearsal/*`
branch; its artifacts use the commit hash and it creates no GitHub Release.
Stable `vX.Y.Z` tags never build.

The candidate workflow validates the committed artwork before packaging. It
builds a universal macOS package signed with the existing Resonant DSP Developer
ID identities, notarizes and staples it, and builds a Windows x64 installer
signed through the Free-specific Azure CI identity and shared Resonant DSP
publisher profile. Both installers offer an install for all users or for the
current user, and both are installed silently for all users on clean runners;
pluginval and clap-validator inspect what was installed, and the workflows
verify the publisher identities. Linux packaging is attempted on Ubuntu 22.04.
Its tarball is included only if installing and validating it succeeds; a Linux
failure does not discard qualified macOS and Windows candidates and does not
create an unqualified Linux download.

The final job writes `release-record.json` with the RC tag, commit, version,
toolchain, patched cargo-truce version, Cargo lockfile and artwork hashes,
shipping identities, and each artifact's size and SHA-256. An RC tag creates a
draft GitHub Release once. The workflow refuses an RC tag that already has a
release at its start, before any signing, and the final job refuses again
rather than replace one, so any new bytes require a new RC number and a fresh
review. A run that failed partway resumes with "Re-run failed jobs", unless it
failed after creating the draft, which needs a new RC; re-running all jobs is
refused once the draft exists. Workflow artifacts are also retained
for rehearsals and inspection.

### Signing setup

The repository's release-tag `v*` and `rehearsal/*` branch rules allow only
administrators to create, update or delete those refs. The protected `signing`
environment allows only `v*-rc.*` tags and `rehearsal/*` branches. Fork and
pull-request runs have no path to it. `signing` holds the existing Apple
material as `APPLE_CERTIFICATES_P12`, `APPLE_CERTIFICATES_PASSWORD`,
`APPLE_API_KEY_P8`, `APPLE_API_KEY_ID`, and `APPLE_API_ISSUER_ID`.

Windows signing uses a Free-specific Azure application and service principal
with a federated identity scoped to this repository's `signing` environment.
Its signer-only role uses the existing Public Trust profile for the same
Resonant DSP publisher; Free needs no second certificate profile and no access
to Pro source or runtime resources. These nonsecret repository variables
configure it:

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
hosts, machines and findings. Before checking anything out it refuses a stable
tag other than `vX.Y.Z` or a candidate tag other than `vX.Y.Z-rc.N`, so no
branch's code runs in the release environment. It then checks out
`refs/tags/<tag>` without leaving the repository token in the tree and runs the
release-script tests from it; tokens reach only the steps that call GitHub or
the website, and the tree those steps run comes from an administrator-only tag. It verifies a successful candidate workflow, requires both tags
and the checkout to resolve to the recorded commit, rechecks
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

## Information panel and release notices

The header carries a small outlined button with Pro's settings cog to the left
of the preset bar. A press opens the information panel over the dimmed editor:
the product name and running version, such as "Swanky Amp Free 2.0.0", and
links to the website's product page, the manual and support, each tagged
`utm_source=swanky-amp-2&utm_medium=plugin&utm_campaign=information`. Below
them, Interface size offers 75, 100, 125 and 150 %; a press resizes the editor
at once and is remembered for every later editor on the computer (see
[Editor](#editor)). Escape, the button again or a press outside the panel
closes it.

Copy diagnostics, beside the links, puts a short block on the clipboard for a
support request: product and version, operating system and architecture, the
host application and plug-in format, the sample rate and buffer audio last ran
at, and the licence. Nothing is sent anywhere; the player pastes it. The
Third-party licences link and, in the Windows standalone, the ASIO Compatible
logo are described under [Source and licences](#source-and-licences).

Opening an editor starts a background check for the static current-release
document at
`https://resonantdsp.com/release-notices/swanky-amp.json`. The document is at
most 4 KiB and has this schema:

```json
{"schemaVersion":1,"productId":"SwankyAmp","currentVersion":"2.0.1"}
```

The website generates it from the promoted release catalogue and emits
`"currentVersion":null` until `SwankyAmp` is available and has verified
downloads for that same version. A missing endpoint, an offline computer, an
invalid document and a timeout are all silent.

The plugin accepts only a strict stable `major.minor.patch` version and
compares it numerically, component by component, with the running version.
When the document names a strictly newer version, the cog button turns
into a highlighted download arrow and the panel adds a line announcing that
version with a Download link to the fixed tagged catalogue URL
`https://resonantdsp.com/products/swanky-amp/?utm_source=swanky-amp-2&utm_medium=plugin&utm_campaign=release-notice`,
opened in the default browser only on an explicit press; the downloaded
document cannot choose a link.

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

Swanky Amp is licensed under GPLv3 or later; see [LICENSE](LICENSE). The model authority is the exact Free 1.4.0 C++ wrapper and generated Faust headers preserved in `verification/reference/released` from the `juce-1.4.0` tag. The public legacy renderer retains the released control mappings, detuning, fitted constants, stage behavior, calibration tables, cubic knee, fixed digital plate filter, and old tone mapping. The shipping path adds tube-only oversampling, a rate-tracked 20 kHz plate filter, a unit-slope triode knee, the standard tone-stack mapping with refitted factory presets and level compensation recalibrated against the released path. Small equation and filter primitives were selectively adapted from the separately implemented Pro code only where comparison proved that they express the released Free equations.

The artwork in `assets/artwork.pack`, and the layers unpacked from it, is
licensed under CC BY 4.0; see `assets/artwork/ARTWORK-LICENSE.txt`. The editor typography uses PT Sans under the SIL Open
Font License in `assets/fonts/PTSans-OFL.txt`.

The information panel's Third-party licences link opens the third-party
notices the plug-in embeds: the font's licence, every crate the shipped
formats link, grouped by licence, and the ASIO SDK's licences and source.
`just notices` writes them
to `THIRD-PARTY-NOTICES.txt` with a pinned cargo-about from `about.toml` and
`about.hbs`. The candidate workflow runs it before packaging and names the file
in `THIRD_PARTY_NOTICES`, which `build.rs` embeds; a build without that
variable embeds a one-line placeholder, so local builds and checks never
generate the notices. Every licence `about.toml` accepts is compatible with
GPLv3.

This repository contains no Pro parameter grids, cabinet impulse responses, pedals, gate, reverb, licensing logic, Blender sources, artwork production sources, or shared private DSP dependency.

Three existing framework patches were copied from the corresponding vendored upstream sources in the Swanky Amp Pro checkout because the plugin exercises their public behavior:

- `vendor/baseview-truce`: frame delivery and host keyboard/modifier fixes.
- `vendor/truce-iced`: iced input, focus, redraw, and clipboard fixes.
- `vendor/truce-clap`: host state notification required by clap-validator.

The source-only `vendor/cargo-truce` copy is the published 6.3.0 build tool with
the patches its `UPSTREAM.md` records: the Azure `ExcludeCredentials` patch
and the Audio Unit Info.plist patch shared with the Pro release chain, and the
scoped Windows installer name. Its
unchanged upstream Truce License 1.0, `LICENSE-MIT` and `LICENSE-APACHE` files
and a precise source and patch record are included in that directory. The Truce
Framework Rider's Section 2.2 explicitly lists audio plug-ins and suites among
the uses that are not Covered Framework Offerings; covered commercial framework
products and services remain subject to the Rider. Cargo-truce is a build tool
and is not linked into the plugin.

The dynamic-latency work adds narrow copies from the exact published Truce 6.3.0 sources:

- `vendor/truce-clap`: dynamic-latency restart and active reset handling, extending the existing state-notification copy.
- `vendor/truce-standalone`: dynamic-latency restart on the output worker, and, as in Pro, an input kept within about one buffer of the output, a Buffer Size menu, remembered devices and buffer size, and the Windows standalone on ASIO.
- `vendor/truce-core`, `vendor/truce-plugin`, `vendor/truce-loader`, and `vendor/truce`: the narrow real-time reset lifecycle hook and its forwarding bridge.
- `vendor/truce-au`: a latency change reaches the Audio Unit host's property listeners.

The Windows standalone is built with Steinberg's ASIO SDK 2.3.4, which
Steinberg licenses either under its proprietary agreement or under the GNU
General Public License, version 3; Swanky Amp uses it under GPLv3. The SDK is
fetched at build time, pinned by checksum, and not committed; the third-party
notices carry its licence texts, from `assets/asio-sdk`, and name that package
as its source. ASIO is a registered trademark of Steinberg Media Technologies
GmbH. GPLv3 does not cover the name or logo, so their use follows Steinberg's
usage guidelines for SDK 2.3.4, which put the ASIO Compatible logo in the About
panel of an application that runs on ASIO by default, as this one does, so its
information panel shows it; `assets/asio-compatible.svg` is Steinberg's
artwork, unchanged.

Each Truce directory carries the unchanged governing Truce licence and MIT and Apache texts, original manifest, source reference, and a focused `UPSTREAM.md` description of the local changes. `vendor/baseview-truce` carries its own MIT and Apache licence texts and provenance. Everything else resolves from the pinned Cargo lockfile.
