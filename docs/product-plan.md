# Swanky Amp 2.0

What version 2 of the free, GPLv3 Swanky Amp is, the decisions behind its sound, how it is verified and released, and what remains before the [launch](../../../company/work/RD-135.md). The implementation is the public repository `resonantdsp/SwankyAmp` (`code/SwankyAmp`): its [README](../README.md) holds the commands, the decisions and how to operate it, and its [changelog](../CHANGELOG.md) the player-facing feature list. The design detail lives beside what it describes: in the code's comments, the [voicing report](../verification/tone-stack/refit-report.md) and the [reference renderer's README](../verification/reference/README.md). The [DSP compatibility policy](../../../company/engineering/rust-dsp-plan.md) is the rule it applies; [Swanky Amp Pro 2.0](../../SwankyAmpPro/docs/product-plan.md) is its sibling, and the [convergence plan](../../../company/engineering/pro-free-convergence.md) keeps the code both products share identical. Work is tracked under [RD-240](../../../company/work/RD-240.md).

The [editor robustness review](../../SwankyAmpPro/docs/editor-robustness.md) records how the editor both products share runs inside a host, the decisions behind it, the exposure it keeps and where Swanky Amp differs ([RD-1157](../../../company/work/RD-1157.md)).

## The product

Version 2 brings the free amplifier to Pro 2.0's stack and visual standard and removes the last C++, Faust and JUCE from the catalogue. It is not a port of Pro.

- **Same product.** The controls of 1.4.0: Input and Output, the preamp's Drive, Tight and Grit, Stages, Overhead, Low Cut, the power amp's Drive, Tight and Sag, Low, Mid, High, Presence and the continuous tone-stack blend, the cabinet's switch, Bright, Distance and Dynamic, the preset bar and the input and output meters. No pedals, reverb, gate, stereo spread, impulse responses, scope, tuner or metronome.
- **Same character.** Its modelling stays its own: the 1.4.0 knob mappings, compression on all five preamp stages, its power-drive and sag curves and its parametric cabinet. None of old Pro's voicing changes are adopted; the numerical fixes below are.
- **Decoupled from Pro.** The licences differ, so the two products share no crates and no repository; code is copied, never linked. Where both products do the same job the copy is kept whole and identical to Pro's, so a fix ports as a plain patch; where they differ, including all of Free's DSP, Free's code stays its own and nothing copied may change its tone or model ([convergence plan](../../../company/engineering/pro-free-convergence.md)). Garrin-owned code may be published under GPLv3; third-party code keeps its licence and notices.
- **Minimal public surface.** The public repository holds the GPLv3-or-later plugin source, public artwork packing and validation, and the finished artwork package under CC BY 4.0. Free's private production companion, `SwankyAmp-production`, holds its trimmed Blender tooling. Licensing, Pro-only DSP and bake scripts never enter the public repository. The [artwork architecture](../../../company/engineering/product-artwork-pipeline.md) defines the boundary.
- **A new plugin identity, installed beside 1.4.0.** Version 2 is `Swanky Amp 2` / `com.resonantdsp.swanky-amp-2` / `SwA2`; 1.4.0 is bundle `com.ResonantDSP.SwankyAmp`, manufacturer `Manu`, code `ccwf`. Old sessions keep loading 1.4.0; presets come across through an importer.
- **Formats.** CLAP, VST3 and a standalone on macOS and Windows, and an Audio Unit v2 on macOS ([RD-1046](../../../company/work/RD-1046.md)). The Windows standalone plays through ASIO, built under the ASIO SDK's GPLv3 option. Whether a release ships a Linux download is declared in `Cargo.toml` (`[package.metadata.release]`, issue #40). 2.0 declares none and launches on macOS and Windows only: the Linux build has never run on a real machine, and its standalone's audio panel must be confirmed there before a release declares Linux again.
- **Around the amplifier.** An information panel from the header's cog: version, links, interface size 75 to 150 % on the 864 × 512 layout ([RD-1051](../../../company/work/RD-1051.md)), Copy diagnostics and third-party licence notices ([RD-1056](../../../company/work/RD-1056.md)). The release notice, the free plugin's first network code, turns the cog into a download arrow when the site reports a newer version; the README states exactly what is fetched ([RD-248](../../../company/work/RD-248.md), [RD-911](../../../company/work/RD-911.md)).

### Reference material

| Reference | Where it is |
| --- | --- |
| Released model | `code/SwankyAmp` at tag `juce-1.4.0` (commit `5c32004`). Branch `archive/free-pre-v2-experiments` (`f6f1ce5`) holds later experiments with recalibrated tables and unused pedal stages; it is not the released sound. |
| Model definition | Faust sources in `code/SwankyAmpFaust/dsp`, token-identical to the shipped headers. The knob mapping is `setAmpParameters` in `Source/PluginProcessor.cpp`; the chain, detuning and level tables are in `Source/dsp/PushPullAmp.h`. |
| Released sound | No 1.4.0 binary is available. The [reference renderer](../verification/reference/README.md), compiled from the released headers kept under `verification/reference/released/`, stands in for it with probes at every seam ([RD-241](../../../company/work/RD-241.md)). |
| Factory presets | Ten 1.4.0 presets, in [`products/swanky-amp/presets`](../../../company/products/swanky-amp/presets) and the repository's `Resources/presets.xml`. |
| Guitar recordings | A single coil and a humbucker played direct, in `verification/reference/input`: the input for calibration and voicing. |

## The audio model

### What the survey established

- The amplifier core is the same model as Pro's: 1.4.0's fitted triode constants match Pro's value for value apart from the cold clipper, and the tetrode and tone-stack sources are identical. That supports copying stage equations verified against Free's released model, not Pro's amplifier.
- Old Pro (JUCE 1.x) did not fix the numerical defects the [DSP review](../../../company/engineering/dsp-review-2026-09-11.md) found; the fixes come from the Rust rebuild.
- Free's controls are not a subset of Pro's: Overhead is its own knob, Low Cut has its own curve, sag time follows Power Tight, and a hidden `PowerAmpSagRatio` is live. The mapping is ported from 1.4.0.
- Free processes stereo input through independent left and right paths; Pro feeds its paths from mono, so Pro's channel routing is not copied.
- The free cabinet is a parametric equaliser chain with a level-dependent high end, ported from `Cabinet.dsp` with audio-rate coefficient updates. No impulse responses enter the public repository.
- 1.4.0's per-stage detuning comes from a seeded `std::minstd_rand` at run time; version 2 pins a table generated from that sequence.

### Fixes adopted

`just model-check` holds the legacy path to the released renders at every seam ([RD-243](../../../company/work/RD-243.md)); the shipping path adds these, each with its level tuning ([RD-244](../../../company/work/RD-244.md)):

| Change | Level treatment |
| --- | --- |
| Engine-owned parameters, settling at preparation in place of the 1,024-sample mute, warm stage re-entry, reciprocal multiplies, proper mono handling | Tone-neutral. All five stages advance continuously, so changing Stages cannot restore stale state. |
| Pro's tube-stage oversampling with its listening-tested Auto default | The fewest doublings that reach 88.2 kHz: 2× at 44.1 and 48 kHz, 1× at 88.2 kHz and above. The header cycles Auto, 1×, 2× and 4× and shows the resolved factor. 1× disables oversampling; it does not restore 1.4.0, which stays installed beside 2.0 for that. |
| Plate and power-stage low-passes matched to their 96 kHz response at every tube rate | Required with oversampling, or the tone follows the factor. Up to 10 kHz the factor changes aliasing, not tone; 4× is up to about 1 dB brighter at 16 kHz. The 48 kHz sound at Auto is the voiced reference ([Free #122](https://github.com/resonantdsp/SwankyAmp/pull/122)). |
| Tone stack's bass and mid section as two first-order sections above a 96 kHz tube rate | Tone-neutral: the single-precision biquad was up to 0.78 dB off there; the split form is exact. Up to 96 kHz the biquad runs untouched. |
| Cabinet held to its 48 kHz response at every common rate, in double precision | At ten standard rates from 32 to 384 kHz the low-pass and shelf are six sections from a generated table (`just fit-cabinet`), within 0.01 dB of 48 kHz; other rates keep the plain design. Double precision removed the sections' round-off hiss; 48 kHz renders differ only at that old noise floor, nulls of −70 to −76 dB ([Free #121](https://github.com/resonantdsp/SwankyAmp/pull/121)). |
| Unit-slope soft-clip knee on the five triodes | Free compresses on all five stages, so the gain change compounds; each stage carries a makeup gain fitted at its seam. The tetrode keeps the released curve: its clip corners are wider than the signal and no single makeup corrected the power seam. |
| Grit's compressor threshold capped | Above about Grit 8.5 the threshold rose past the plate signal and the stage clipped to a constant, silencing the amp (1.4.0 had the same defect at −52 dB). The cap acts only there and keeps the grid-clip loss as character. |
| Level tables regenerated by `calibrate` | See below. |

### Changing the oversampling factor

The host is told the oversampler's delay, 32 samples at 2× and 48 at 4×, so a factor change is a latency change, and the latency reported is always that of the factor the audio is running. A choice that resolves to the factor already running keeps the amplifier's state. How each format gets there:

- **VST3, Audio Unit and the standalone.** The new factor takes effect at the next block and the reported latency changes with it; a click at the switch is expected. The VST3 adapter asks the host to restart the component for the latency change, the vendored Audio Unit adapter tells the host's latency listeners, and the vendored standalone's output worker reopens the same device.
- **CLAP.** CLAP keeps an active plug-in's latency fixed, so the factor waits for the restart the adapter asks the host for, and the new latency is published at the next activation. The engine learns this through the activation flag `latency_held_while_active`, carried by the vendored `truce-core`, `truce-loader` and `truce-clap`. An active CLAP reset clears the processing history at the current factor, settling the stages without allocating.

The vendored crates' `UPSTREAM.md` files record each change against truce 6.3.0, and the tests in `src/lib.rs` hold the reported latency against the audio, the CLAP and standalone transitions, and the unchanged state for a choice that resolves to the same factor.

### Level calibration

`calibrate` measures on the two guitar recordings at Input 0, averaged over the pickups, both played 2.0 dB louder than recorded (`RECORDING_GAIN_DB`) the way a player stages Input by the meter, as Pro's calibration does. The first stage feeds the power stage the level 1.4.0 fed it at every Drive on every stack with the tone controls at their defaults; the second holds loudness, BS.1770-4 on the recordings, with a fixed level reference, 1.4.0's default settings, anchored exactly, through a rescaled `POWER_SWEEP` and post-cabinet `DRIVE_GAIN` and `GRIT_GAIN` tables. Stages stays uncompensated, as released. A test holds that reference on the two recordings within 0.5 dB of 1.4.0's level with the cabinet off and within 2 dB with it on. The README's [Level calibration](../README.md#level-calibration) section holds the command and what the tests prove; the method is the module comment of `src/dsp/calibration.rs`.

1.4.0's loudness was never level under drive: on the recordings it played several dB under its defaults at full Drive and full Power Drive, most on a humbucker. Version 2 holds the reference's level averaged over the two pickups, so a pickup can land up to about 3 dB either side of it at the extremes. Garrin accepted this level behaviour by ear.

### The tone stack

The released stack discretises its circuits with `c = SR` instead of the standard bilinear `2·SR`, placing its features an octave above the circuit. Free uses the corrected stack, as Pro does: Free should attract guitarists with a convincing amplifier sound, and it answers the direction of issue #16's complaint about a scooped, bright sound in a mix ([RD-245](../../../company/work/RD-245.md)). The choice is settled.

The released stack also ran its three first-order treble sections through the second-order form, leaving a pole at Nyquist that f32 coefficients put just outside the unit circle; it grew over hours and is the likely cause of issue #34's tremolo. The shipping path discretises those sections as true first-order filters with identical response; the legacy path stays bit-identical. `just tone-stack-soak` drives 24 hours of samples through 21 extreme cases in about eight minutes and is a pre-release check. Multi-hour soaks are not part of releasing; `just soak` stays an on-demand diagnostic.

### Presets

The ten factory presets keep their character within reason rather than exactly, because the corrected stack cannot place 1.4.0's scoop an octave up. Each is voiced from its 1.4.0 settings on the guitar recordings, judged at the strikes, every fitted knob on a half mark; Power Drive keeps its drive into the power stage within about 1.2 dB; Output makes every preset strike at the level reference's level on a humbucker. Init is the corrected stack at 1.4.0's defaults except the tone stack, which starts at 2 for more mids than the bright first stack; the reference stays at 0, so the bank does not follow Init. Garrin accepted the bank by ear on September 30, 2026 ([RD-246](../../../company/work/RD-246.md)). `just refit` regenerates it and its [voicing report](https://github.com/resonantdsp/SwankyAmp/blob/master/verification/tone-stack/refit-report.md); the accepted limits are a light 150 to 400 Hz, a little more around 1.3 kHz and up to 2.5 dB missing above 8 kHz.

Users' 1.x presets import on first run and on request, without touching the 1.x files. The import shifts Low, Mid, High and Presence by the average move the factory voicing made to the 1.4.0 presets ([RD-1068](../../../company/work/RD-1068.md)), which lands them in the right range rather than on their original balance; a 1.x file placed in the 2.0 preset folder any other way is refused with a pointer to the import.

## The interface

One view in Pro's material language: graphite surfaces, the large and small knob families, V grooves, native text and the diffused meter cells. Six rounded, groove-outlined boxes keep 1.4.0's grouping, with the same controls in roughly the same places. 1.4.0's highlight colour, `SwankyAmpLAF::colourHighlight` (HSV 0.98/0.60/0.75, a muted rose), is the accent on lit rings, outlines, the FREE 2.0 tag, the release-notice arrow and the output meter; the input meter keeps Pro's blue. The header takes Pro's outlined buttons, one-line wordmark and single cycling oversampling button. The cabinet switch is a brushed disc in a V-slot track. The input meter keeps 1.4.0's −26 to +8 dBFS scale without its S and H marks; the output meter spans −60 to 0 dBFS.

Rust and iced own the interface definition. `export-layout` drives the private producer, which returns image layers and provenance; the public packer assembles the committed package, and the loader checks its geometry and payload without private sources ([RD-250](../../../company/work/RD-250.md)). Pro-only widgets (the spread gesture, cabinet diagrams, IR previews, licensing) are not copied. Visual completion is judged against the accepted Pro references; Garrin's acceptance of the interface and his open notes are [RD-247](../../../company/work/RD-247.md).

## Verification

- **Every change.** `just` runs format, clippy and the tests locally. Each pull request runs `checks (linux)`: format, clippy, all tests including artwork validation in one optimised profile, the release-script tests, `just reference-check` and `just model-check`. Alongside it, `checks (windows)` runs clippy on Windows and builds every editor pipeline through Direct3D 12, so a shader Direct3D's compiler rejects fails with its message. Each push to `master` also builds, installs and validates the bundles on macOS and Windows (Free #124).
- **Pre-release.** `just tone-stack-soak`.
- **Listening.** Garrin accepted the factory bank and the level behaviour under drive by ear against 1.4.0; listening in real hosts is part of qualification.

### Host qualification of the frozen candidate

Garrin qualifies the frozen candidate's installers beside 1.4.0, following the session and dates owned by [RD-249](../../../company/work/RD-249.md). What 2.0 adds to the ordinary load, play, automate, save and reopen:

- The Audio Unit in Logic Pro and GarageBand.
- Every interface size in each format, and Windows display scaling at 150 % and 200 % combined with it.
- The Windows standalone on ASIO with a real interface.
- An oversampling change while playing: in an Audio Unit and a VST3 host it applies at once with a click, in a CLAP host after the restart ([Free #122](https://github.com/resonantdsp/SwankyAmp/pull/122)).
- The first-run import on a real 1.4.0 preset folder ran end to end in the October 7 smoke test on both systems; the sitting repeats it only if the import changes.
- The Copy diagnostics line pasting correctly on both systems.
- Installation for all users and for the current user on macOS, and for all users on Windows.
- Every check in the [verification record's open limits](../verification/README.md#open-limits), which keeps that list; it covers what only a real machine can confirm.

## Build and release

Swanky Amp and Swanky Amp Pro share one release chain: the same contract script, record, workflows and recipes, differing only where the products do. Candidates build only on `vX.Y.Z-rc.N` tags, which are for builds we would ship; a `rehearsal/*` branch builds, signs and validates a test build and publishes nothing. A candidate is published once, to the public downloads bucket under `swankyamp/candidates/<tag>/` and as a GitHub pre-release; that record and pre-release are the candidate's evidence. Promotion is dispatched from `master` with the candidate tag, the release tag on the same commit, the accepted record's SHA-256 and the qualification statement; it copies the candidate's own bytes to `swankyamp/<version>/`, publishes the GitHub release and opens the website catalogue pull request. Release tags never build. `signing` admits only administrator-created candidate tags and `rehearsal/*` branches, and `release` only `master`; fork pull requests receive no secrets. Signing uses the shared publisher identities through a separate Free Windows CI identity ([signing record](../../../company/operations/signing.md#free-ci-identity)). The macOS installer lets the player install for all users or only themselves; the Windows installer installs for all users, because Ableton Live 10 and a default Reaper never scan the per-user VST3 folder. The README's [Releasing](../README.md#releasing) section is the procedure; [RD-249](../../../company/work/RD-249.md) tracks the release.

## Where it stands

The frozen candidate is `v2.0.0-rc.6` ([RD-1176](../../../company/work/RD-1176.md)): commit `af56d4e4ed9ffdd7bbe9642ce39ebca19f6ca217`, build 342, `release-record.json` SHA-256 `a74fb79bf5bb6eb6114d778bc7a938fd5327f7023d482fc8b646f5275411fc53`, [candidate run](https://github.com/resonantdsp/SwankyAmp/actions/runs/37651870539). It carries every launch feature, including the 1.x preset import ([RD-1068](../../../company/work/RD-1068.md)), and is a published [pre-release](https://github.com/resonantdsp/SwankyAmp/releases/tag/v2.0.0-rc.6) whose installers and record are public under `https://downloads.resonantdsp.com/swankyamp/candidates/v2.0.0-rc.6/`. Earlier October candidates are superseded, including rc.5 (`70ea023`, build 341), replaced the same day by the product-name fix (#137) before anyone used it; its pre-release was deleted on October 7 with the other superseded ones. Its qualification and promotion are owned by [RD-249](../../../company/work/RD-249.md) and remain open; the earlier build below records verified output and source evidence for RC1, not for rc.6.

### Retained build evidence

`v2.0.0-rc.1` is built at `7d9e1e7270bf6ddf358702ac0f8322e85ab2709e`. All jobs in its [candidate workflow](https://github.com/resonantdsp/SwankyAmp/actions/runs/37220277995) passed: the signed, notarized universal macOS package, signed Windows x64 installer, installed-format validators, publisher checks and licence notices. The installers downloaded from its draft release matched its release record, whose SHA-256 is `595d2d4828ff598f30fa61119ae32af1ff5d401f74110d956de232bcafae42ed`, and a local macOS check confirmed signatures, notarization and universal formats.

The pre-release tone-stack soak passed all 21 cases representing 24 hours of samples per case: maximum drift **0.00500 dB** against the **0.01 dB** limit and maximum offset/RMS **3.82 × 10⁻⁵** against **10⁻⁴**. Host qualification and stable promotion remain open. The [candidate history](../../../company/engineering/evidence/release-candidates-2026-09/README.md) lists the removed September candidates.

The private `resonantdsp-bakes/swankyamp/candidates/v2.0.0-rc.1/` prefix was deleted on October 7, 2026 with the other superseded candidates ([RD-1190](../../../company/work/RD-1190.md)). Only the pinned ASIO SDK source zip survives, at `resonantdsp-bakes/swankyamp/retained/`, so the source of the GPLv3 build stays available ([RD-249](../../../company/work/RD-249.md)).

A Windows linkage check proved that the SDK's COM classes and DLL helpers are absent from the shipping RC1 standalone: its executable code section was byte-identical to the map-audited build from exact RC1 source. CLAP and VST3 do not enable the standalone ASIO dependency. This does not replace qualification on a real Windows interface.

Remaining, in the order of the [release calendar](../../../company/calendar.md):

1. Garrin's open interface notes ([RD-247](../../../company/work/RD-247.md)); fixing any of them means a new candidate.
2. Host qualification, as above, with the schedule and current results in [RD-249](../../../company/work/RD-249.md).
3. The stable tag and exact-byte promotion, website catalogue pull request and release-notice check ([RD-249](../../../company/work/RD-249.md)); the public launch follows [RD-135](../../../company/work/RD-135.md).

The audio faults 2.0 launches with are fixed after launch or recorded as accepted ([RD-1153](../../../company/work/RD-1153.md)).
