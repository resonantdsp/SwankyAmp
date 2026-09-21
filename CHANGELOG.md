# Changelog

`Cargo.toml` is the version authority. Candidate tags add `-rc.N`; stable tags
equal the crate version. Every stable version has a section here before any
signed build starts.

## Unreleased

## 2.0.0 — in development

Swanky Amp 2 preserves the released Free amplifier and cabinet sound in a new
Rust host identity that will install beside Swanky Amp 1.4.0. The interface,
factory preset bank and signed candidate qualification are still in progress.

- Ported the released amplifier and cabinet processing into mono and stereo
  paths under the `SwankyAmp2` / `com.resonantdsp.swanky-amp-2` / `SwA2`
  identity.
- Added frozen reference data and a model renderer covering ten released preset
  cases.
- Added automation to build, sign and qualify macOS and Windows candidates,
  attempt a qualified Linux bundle, and promote only the accepted candidate
  bytes.
