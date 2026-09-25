# Changelog

`Cargo.toml` is the version authority. Candidate tags add `-rc.N`; stable tags
equal the crate version. Every stable version has a section here before any
signed build starts.

## Unreleased

## 2.0.0 — in development

Swanky Amp 2 preserves the released Free amplifier and cabinet sound, with the
tone stack and soft-clip knees corrected, in a new Rust host identity that will
install beside Swanky Amp 1.4.0. Qualification of the signed candidate in real hosts is still in progress.

- Ported the released amplifier and cabinet processing into mono and stereo
  paths under the `SwankyAmp2` / `com.resonantdsp.swanky-amp-2` / `SwA2`
  identity.
- Added frozen reference data and a model renderer covering ten released preset
  cases.
- Corrected the tone stack's discretisation: 1.4.0 voiced every tone-stack
  feature an octave above the circuit. The ten factory presets are refitted to
  sound roughly as they did, with the residuals recorded in
  `verification/tone-stack/refit-report.md`; Swanky Amp 1.4.0 remains
  available for the original voicing.
- Balanced the factory presets to equal loudness, which 1.4.0's never were:
  each preset's Output moves by -6.4 to +2.7 dB so that all ten match Init's
  loudness averaged over the single-coil DI and a plucked test signal.
  Imported 1.x presets are not rebalanced.
- Fixed a slow tone-stack instability that silenced high-gain presets after
  hours of continuous play. The first-order treble sections were discretised
  as biquads with a spurious pole at Nyquist, which f32 rounding placed just
  outside the unit circle; they are now true first-order filters, with the
  response unchanged. `just tone-stack-soak` checks 24 hours of samples
  before a release.
- Joined the triode soft clips' knees smoothly: the released cubic left each
  knee with slope 4/3.4, a corner at every grid, bias, plate and compression
  clip. Each triode stage carries a fixed makeup gain fitted against the
  released seam levels over the ten factory presets, keeping every seam at 0 dB
  input within 0.6 dB of 1.4.0 (tone stack 1.05 dB, output 0.5 dB). The
  tetrode keeps the released curve, which sets its bias and gain rather than a
  knee. The preset refit is measured with the new knee.
- Recalibrated the level compensation for the corrected amplifier: the
  preamp and power tables and the tone-stack scale are measured against the
  released path by `just calibrate`, so Drive and Power Drive move loudness
  as 1.4.0 did and the factory defaults land on 1.4.0's level into the power
  stage and at the output with the cabinet off. The factory presets' output
  sat within 1.0 dB of 1.4.0, from up to 2.5 dB below, before the
  factory balance.
- Drive, Power Drive and Grit now change the sound without changing the
  volume. 1.4.0 got quieter as each rose: on plucked notes Power Drive cost
  9 dB from 0 to 10 (15 dB after the corrections), Drive 5 dB, and Grit
  silenced the amplifier at its top. Output gains measured by `just calibrate`
  hold the loudness, averaged over a played DI and a pluck, within 0.6 dB of
  Init across each control, and Init is unchanged.
- Input, Output and the level gains Drive and Power Drive derive now glide
  linearly across the block in which they change instead of stepping, so
  sweeping or automating them no longer clicks or zippers. The tube stages,
  tone stack and cabinet still step, and a setting held still sounds exactly
  as before.
- Fixed Grit silencing the amplifier near its top: it raised a triode
  compressor's threshold past the stage's plate signal, collapsing the
  stage's output to a constant (-52 dB in 1.4.0, -100 dB after the knee
  correction). The threshold now stops just short of that point.
- Added a multi-hour soak diagnostic (`just soak`, `just soak-check`) that
  checks level drift, tremolo-band modulation and non-finite output on
  low-level input. It reproduced the 1.2 report of a
  tremolo developing over hours (issue #34) on the legacy path after about 3.7
  hours, localized to the released tone stack; the shipping path passed four
  hours.
- Added automation to build, sign and qualify macOS and Windows candidates,
  attempt a qualified Linux bundle, and promote only the accepted candidate
  bytes.
- Added a bounded, cached release notice: a header action that turns into a
  highlighted download arrow when a newer stable release is published and opens the
  fixed catalogue page on an explicit press. At rest the information mark
  opens the product page. The website's static current-release document
  remains a release prerequisite.
- Regrouped the editor after 1.4: six separate rounded boxes, each traced by a
  V groove, with Pro's outlined header controls and uncluttered ten-cell
  meters. 1.4's rose highlight is the accent for lit rings, lit outlines, the
  edition tag and the output meter.
- Aligned the six groups into two columns with shared edges, set the wordmark
  as Pro's one-line "SWANKY AMP FREE 2.0", and replaced the static
  oversampling label with Pro's button: it cycles Auto, 1x, 2x and 4x and
  names the factor the engine resolved.
- Ended the footer's RESONANT DSP mark on the boxes' right margin, the line
  the header's last button already ends on, and started the wordmark and the
  footer's hint on the left margin. Footer text sits on the footer bar's
  centre line.
- Replaced the cabinet toggle with a vertical two-position switch in its own
  column of the Cabinet row: a brushed aluminium disc that sits in either end
  of a V track two discs tall, with the ON label lit in the accent.
- Set the knob markers to Pro's divot proportions, so both knob sizes match
  Pro's knobs.
- Lit the level meters from each instance's own signal: input after the Input
  control on the released -26 to +8 dB scale, output after the cabinet and
  Output control on -30 to 0 dB, with instant attack and a half-second
  release. Hosts that show plugin meters receive the same four levels.
- Made the header's preset field live: `‹` and `›` step through the refitted
  factory presets and the user's own, and the name opens a menu with Init,
  every preset, Save, Save as…, Remove, Import 1.x presets and Open folder.
  Presets apply through the host, the selection survives a session reload, and
  a dot marks a changed preset. Input and the cabinet switch stay with the
  session, as in 1.4.0. Remove asks in the menu before it deletes the file,
  and the factory presets are capitalised like Init.
- Kept presets in the 1.x XML format, one file per preset under
  `Resonant DSP/Swanky Amp 2`, and applied 1.4.0's migrations for presets from
  earlier releases. Unreadable files are skipped and named.
- Imported 1.4.0 user presets on first run and on request, refitting each one's
  Low, Mid, High and Power Drive to the corrected tone stack like the factory
  set, without overwriting a version 2 preset or touching the 1.4.0 files.
