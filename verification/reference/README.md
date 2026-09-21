# Released-tone reference renderer

This directory freezes the Swanky Amp 1.4.0 tone at Git commit
`5c32004862e5dcce8a453e1310da926dc9712464`, tagged `juce-1.4.0`. The
renderer compiles the released generated Faust headers and `PushPullAmp` chain
directly. It does not link JUCE and contains no Swanky Amp Pro DSP.

`./render.sh /path/to/output` builds the renderer and writes all ten released
factory presets at 44.1, 48, and 96 kHz. `./check.sh` rebuilds those 30 cases in
a temporary directory and compares them with `frozen/`. Both commands need only
a C++20 compiler and Python 3's standard library. The C++ executable itself also
accepts any sample rate from 8 to 384 kHz and either the released preset bank or
a single current-format `APVTSSwankyAmp` preset:

```sh
c++ -std=c++20 -O2 renderer.cpp -o reference-renderer
./reference-renderer \
  --input input/single-coil.wav \
  --presets released/Resources/presets.xml \
  --preset clean --sample-rate 88200 \
  --output clean-88200.wav --report clean-88200.json
```

On macOS `render.sh` selects the full Xcode toolchain when it is installed. This
avoids an incompatible Command Line Tools SDK while preserving the same source
and compiler options.

## What is frozen

`released/` is a byte-for-byte extraction of the model headers, mapping source,
factory bank, and GPLv3 licence from the released commit. `frozen/manifest.json`
records a SHA-256 digest for every extracted file, the renderer, the DI, every
WAV, and every seam report.

The mono DI is Garrin McGoldrick's versioned single-coil performance, copied
from `code/SwankyAmpPro/verification/calibration/single-coil.wav`. That location
is provenance only; no Pro processing is used. It is 48 kHz mono 24-bit PCM and
is fed at 0 dB. This is an explicit fresh-session fixture: Input Level `0.0`
maps to 0 dB and the cabinet starts enabled. Factory selection preserves both
live session controls; it does not restore Input from the preset, and it ignores
the XML's cabinet-switch value. The renderer uses deterministic linear
interpolation for the frozen 44.1 and 96 kHz inputs and records that choice in
the manifest.

The output WAVs are mono 32-bit IEEE float. This matches the released mono path.
The released stereo contract is two independent model instances for left and
right; mono-to-stereo runs one instance and copies it. The frozen mono DI does
not exercise inter-channel state.

## Seam convention

Each JSON report separates `startup` (samples 0 through 1023) from `post_mute`
(sample 1024 onward). Raw seam measurements include the cold-start samples.
Rendered WAVs apply the plugin's exact 1,024-sample startup mute, so their
startup level is silence. `post_mute` deliberately does not claim the nonlinear
state has settled; the legacy plugin began exposing output at that boundary.

The seam locations are:

- `triode_N`: after each active triode and before the shared `triodeScale`;
  inactive stages have zero samples in that preset's report.
- `tone_stack`: after tone-stack processing and before
  `toneStackScale * preAmpScale * preAmpTarget`.
- `power_amp`: after the tetrode grid and plate, before division by
  `preAmpTarget`.
- `cabinet`: after the optional cabinet, before cabinet, power-drive-table, and
  output compensation.
- `raw_output`: after all compensation, immediately before the startup mute.

For every render the executable also processes the same blocks through the
untouched released `PushPullAmp::process`. The seam path must match its final
float bits exactly under that compiler. This detects an instrumentation error
without using a plugin binary or private Pro pipeline.

## Accuracy and portability

The frozen macOS/libc++ detune table includes all eight released five-stage
families: high-pass, grid time, grid clip, plate bias, plate clip, drift level,
drift time, and compression level. `std::minstd_rand` has a specified sequence,
but `std::uniform_real_distribution<float>` does not specify an identical value
mapping across C++ libraries. The manifest therefore records the complete
libc++ freeze fingerprint and the complete observed libstdc++ fingerprint. The
check accepts only an exact match to one of them, including all eight families
and all five values per family.

Floating-point contraction changes the nonlinear sample trajectory: on Linux,
all 30 WAVs differed from the Apple arm64 freeze even though the instrumented
and untouched paths remained bit identical in each process. Compiling the same
source on the freeze machine with contraction disabled reproduced that drift.
The Linux matrix observed a worst sample error of `0.00185403`, RMS error of
`0.000399044`, seam-level drift of `0.026258 dB`, and six-band output-level
drift of `0.00162867 dB`. Raw sample and RMS errors remain diagnostics. The
portable gate checks every seam within `0.03 dB` and six output bands split at
120, 400, 1,200, 3,500, and 8,000 Hz within `0.002 dB`.

The exact freeze environment is identified by its OS/platform, arm64
architecture, compiler driver and Apple Clang version, and `-std=c++20 -O2`
flags; it must reproduce all 30 WAVs byte for byte. Every environment must
preserve bit identity between the untouched and instrumented paths, match a
strict detune fingerprint, and pass the seam and band-level gates.

`render.sh` refuses to overwrite `frozen/` by default. The explicit
`--replace-frozen` option is accepted only on the canonical macOS arm64 Apple
Clang/libc++ environment; its changes still require review of the manifest and
render hashes.

The renderer preserves the released octave-high tone-stack discretisation,
soft-clip knee, two sweep tables, block-constant static gains, and seeded
detuning. It is a 1.4.0 baseline, not the corrected version 2 signal path.
