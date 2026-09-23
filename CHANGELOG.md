# Changelog

`Cargo.toml` is the version authority. Candidate tags add `-rc.N`; stable tags
equal the crate version. Every stable version has a section here before any
signed build starts.

## Unreleased

## 2.0.0 — in development

Swanky Amp 2 preserves the released Free amplifier and cabinet sound, with the
tone stack corrected, in a new Rust host identity that will install beside
Swanky Amp 1.4.0. The interface,
factory preset bank and signed candidate qualification are still in progress.

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
- Added automation to build, sign and qualify macOS and Windows candidates,
  attempt a qualified Linux bundle, and promote only the accepted candidate
  bytes.
- Added a bounded, cached release notice: a header action that turns into a
  highlighted download arrow when a newer stable release is published and opens the
  fixed catalogue page on an explicit press. The website's static
  current-release document remains a release prerequisite.
- Regrouped the editor after 1.4: six separate rounded boxes, each traced by a
  V groove, with Pro's outlined header controls and uncluttered ten-cell
  meters. 1.4's rose highlight is the accent for lit rings, lit outlines, the
  edition tag and the output meter.
- Aligned the six groups into two columns with shared edges, set the wordmark
  as Pro's one-line "SWANKY AMP FREE 2.0", and replaced the static
  oversampling label with Pro's button: it cycles Auto, 1x, 2x and 4x and
  names the factor the engine resolved.
- Replaced the cabinet toggle with a vertical two-position switch in its own
  column of the Cabinet row: Pro's slider slot and brushed cap stood on end,
  with the ON label lit in the accent.
