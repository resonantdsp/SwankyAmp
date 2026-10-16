# Input and output levels

How Swanky Amp 2.0 stages a guitar's level on the way in and on the way out: the facts behind the input meter, the Input and Drive controls and the fixed output cut. This is an engineering reference. It does not own the calibration method or the acceptance; those are in the [README](../README.md#level-calibration), the [product plan](product-plan.md#level-calibration) and the module comment of `src/dsp/calibration.rs`.

Each figure says where it comes from:

- **code**: a constant or formula in the source at this commit;
- **measured**: computed or rendered from the code or data, with where and on what;
- **recorded**: stated in a pull request or record, with no measurement anyone can repeat.

The measurements here were made on October 16, 2026 on master `b03ac27`, whose DSP is the same as `v2.0.0` (`8338751`): `git diff v2.0.0 b03ac27 -- src/dsp src/engine.rs src/render.rs` is empty.

## The input chain in volts

**In short.** The first triode's model takes its input in volts, the voltage of the circuit simulation it was fitted to. A sample of value *s* at the plug-in's input reaches that first triode as

> *v* = *s* × Input gain × Drive gain, in volts peak.

At Init (Input 0, Drive 3) a full-scale sample is **6.16 V**, so the input meter's midpoint, −9 dBFS, is **2.2 V** at the first tube, a single coil staged by the meter about **1.1 V** and a humbucker about **3.6 V**. That is the one conversion point. Everything after the first stage is scaled by calibration, not carried through in circuit volts.

### The steps

1. **Input** (code, `src/dsp/mapping.rs`). A gain of −35 to +35 dB, 0 dB at the centre of the knob.
2. **The input meter** (code, `src/engine.rs`, `src/meters.rs`). It reads each block's sample peak after Input and before anything else, on 1.4.0's scale, −26 to +8 dBFS, linear in dB, so its midpoint is −9 dBFS. 1.4.0 marked it S at −16.5 and H at −2.5 dBFS (code, `Source/Components/LevelsGroup.cpp` at tag `juce-1.4.0`; why those levels was not recorded); version 2 removed the marks.
3. **Oversampling** (code, `src/dsp/oversample.rs`). Half-band filters that change the rate, not the level.
4. **Drive** (code, `src/dsp/mapping.rs`). `PREAMP_DRIVE`, a logarithmic range from 0.1 to 2,000 over Drive's shaped value, floored at 0.5. This is the gain straight into the first triode; the level compensation for Drive comes after the tone stack. Volts at the first triode per full-scale sample (measured, by evaluating `AmpVoicing::from_controls` at each setting in a throwaway test):

   | Drive on the panel | 0 to 1 | 2 | **3 (Init)** | 4 | 5 | 6 | 8 | 10 |
   | --- | --- | --- | --- | --- | --- | --- | --- | --- |
   | V peak per full-scale sample | 0.50 | 1.94 | **6.16** | 16.8 | 40.7 | 91.5 | 285 | 2,000 |

5. **The first triode** (code, `src/dsp/stage.rs`). Its input divided by Overhead's gain, which is fixed at 1 for the first stage, goes straight into the grid model.

### Why the first triode's input is in volts

The 1.x triode was fitted to an LTspice simulation (recorded and checked: the fitting scripts are in the private `SwankyAmp-dsp` repository, the netlist in the local `ampsim` checkout, `spice/ab_push_pull/run.net`, SHA-256 `116d59e20f1b0e7e…`). The first stage is a 12AT7 (the `NH12AT7` model) in common cathode: a 22 nF coupling capacitor and 470 kΩ grid leak, a 100 kΩ plate load, 820 Ω and 680 nF at the cathode. The source driving it played 440 Hz sines of 0.1, 1, 3, 5, 7, 10 and 50 V peak and pulses of 0.1 to 10 V. `fit-triode-grid.py` fits the model from the source voltage to the grid voltage, and `fit-triode-plate.py` from the grid to the plate, both in unscaled volts with each signal's starting value subtracted, at 96 kHz. The fitted constants in `stage.rs` are written in a unit space, but the signal they act on is in volts.

Two measurements confirm it (measured, from the simulation results in `SwankyAmp-dsp/data/sim`, which Git does not track: `sine_1e-01.npy` SHA-256 `bc7ebae3e876bf3f…`, `sine_1e+00.npy` `1a530e214fb4ab03…`, `sine_5e+00.npy` `f95a8b04820f5e7d…`):

- The simulated stage's small-signal gain is 35.1, and `TRIODE_SCALE` in `src/dsp/amp.rs`, the stage gain 1.x's calibration removes between stages, is 35.01.
- Driven with the same sines, the shipping first stage at Init's settings follows the simulated stage's gain (fundamental out over fundamental in; the model in a throwaway test at 96 kHz with the shipping knee, measured over the second half of one second; the simulation over its last 20 ms):

  | Peak at the first triode | 0.1 V | 1 V | 3 V | 5 V | 7 V | 10 V | 50 V |
  | --- | --- | --- | --- | --- | --- | --- | --- |
  | Simulated stage | 35.1 | 35.1 | 32.5 | 27.5 | 20.7 | 14.3 | 2.2 |
  | Shipping model, first stage | 31.4 | 31.7 | 29.6 | 26.2 | 21.1 | 15.3 | 2.9 |

  The model runs about 1 dB under the simulation at small signals and within 0.6 dB from 5 to 10 V. The first stage carries 1.x's per-stage detuning, so it is not exactly the fitted stage; whether that explains the 1 dB is not established. In the simulation the stage is linear to about 1 V, 0.7 dB compressed at 3 V and 2.1 dB at 5 V.

### Volts at Init

Input 0, Drive 3, 6.16 V per full-scale sample (measured: the peaks are from the [guitar recordings' README](../verification/reference/input/README.md) and reproduce with ffmpeg, −16.65 and −6.72 dBFS):

| Level at the input meter | dBFS peak | V peak at the first triode |
| --- | --- | --- |
| Meter foot | −26 | 0.31 |
| Single coil chord, as recorded | −16.7 | 0.90 |
| 1.4.0's S mark | −16.5 | 0.92 |
| Single coil chord, as calibration plays it | −14.7 | 1.13 |
| **Meter midpoint** | **−9** | **2.19** |
| Humbucker chord, as recorded | −6.7 | 2.85 |
| Humbucker chord, as calibration plays it | −4.7 | 3.59 |
| 1.4.0's H mark | −2.5 | 4.62 |
| Full scale | 0 | 6.16 |
| Meter top | +8 | 15.5 |

Calibration plays both recordings 2 dB louder than recorded (`RECORDING_GAIN_DB`). So at Init a single coil staged by the meter plays the first stage in its linear range, and a humbucker reaches the start of its compression.

### What the chain does not say

- **The meter does not include Drive.** A meter reading converts to volts only at a given Drive: multiply by that Drive's figure in the table above. At Drive 5 the staged single coil reaches 7.5 V and the humbucker 23.7 V.
- **The fitted range ends at 50 V.** From about Drive 6 a staged humbucker drives the first stage past the largest amplitude it was fitted at (53 V at Drive 6); there the model is extrapolated.
- **It is not the guitar's own voltage.** How many volts at the guitar jack make a given dBFS depends on the audio interface's input gain, which the plug-in never sees, and the recordings' interface settings were not recorded. The honest statement is that the amplifier treats a level on its meter, at a given Drive, as a voltage at its first tube.
- **Only the first stage is in circuit volts.** Each later triode receives the previous stage's output divided by `TRIODE_SCALE` and by Overhead's gain (0.1 to 10, 1 at the centre), as if an interstage divider took off exactly the stage's gain. The power stage was fitted the same way from the phase inverter's output, but what reaches it is set by the level tables (`TONE_STACK_SCALE`, `PREAMP_SWEEP`, `PREAMP_TARGET`) and Power Drive's gain (30 to 30,000), calibrated against 1.4.0 rather than carried through a circuit.

## Output staging

**The cut** (code). `OUTPUT_HEADROOM_DB = -2` in `src/engine.rs` takes 2 dB off the final output, after the amplifier, the cabinet and Output, before the output meter. It landed in [#148](https://github.com/resonantdsp/SwankyAmp/pull/148) (October 13, 2026) and is in rc.8, promoted as 2.0.0. Calibration, the refit and the level tests run the amplifier model directly, so they measure without it; the output meter reads after it.

**Its recorded basis** (recorded, #148): "On a hard strum with a hot humbucker, Init peaked at −4.1 dB true peak (−13.6 LUFS). Reference amp sims sit around −6 dB. Pro takes 4 dB off for the same reason (SwankyAmpPro #193)." The README and product plan repeat it as "Init on a hard humbucker strum peaks near −6 dB true peak rather than −4". Two tester reports in the same week said 2.0 was louder than 1.4 ([RD-1192](../../../company/work/RD-1192.md)).

**Measured on the committed recordings.** Init through the shipping engine (`swanky-amp-2 render init`, 48 kHz, stereo output), read with ffmpeg 9.0.2's `ebur128` (true peak, integrated loudness) and `astats`. The output carries the same signal on both channels, which reads 3 dB louder in LUFS than the same signal measured as mono, as calibration measures it.

| Recording | Played | True peak | Integrated | RMS over the file |
| --- | --- | --- | --- | --- |
| Humbucker | as recorded | −6.8 dBTP | −18.3 LUFS | −22.0 dBFS |
| Humbucker | +2 dB, as calibration plays it | −6.4 dBTP | −17.8 LUFS | −21.4 dBFS |
| Single coil | as recorded | −8.0 dBTP | −22.7 LUFS | −26.3 dBFS |
| Single coil | +2 dB, as calibration plays it | −7.4 dBTP | −20.9 LUFS | −24.5 dBFS |

Before the cut the humbucker as recorded peaked at −4.84 dBFS, as #148's proof records.

**Where the records and the recollection part.**

- The −4.1 dBTP and −13.6 LUFS in #148 have no recorded source: no take, host, player or loudness reading is named. They are not the committed humbucker recording, which before the cut peaked at −4.84 dBFS and read −16.3 LUFS integrated on the stereo output, so they describe a harder strum or a different reading. RD-1192 also records Garrin reaching 0 dBFS at Init with a hot humbucker before rc.8, which fits neither figure; it does not say on which take.
- "Reference amp sims sit around −6 dB" is not backed by any measurement of another amplifier simulation in this repository, in Pro's or in the company records.
- No record states a guitar reference of about −18 dBFS RMS peaking near −6 dBFS. The closest figures are the measurement above: Init on the humbucker recording as recorded plays −18.3 LUFS integrated and peaks at −6.8 dBTP, but its RMS is −22.0 dBFS, and that measurement was not the basis of the cut.

## The calibration procedure

The [guitar recordings' README](../verification/reference/input/README.md) owns the recordings and the staging rule; the [README](../README.md#level-calibration) owns the command and what the tests prove; the [product plan](product-plan.md#level-calibration) owns the decisions. In short:

- Two direct recordings, a single coil and a humbucker played the same way at the same interface settings, kept 10 dB apart as played and both raised by `RECORDING_GAIN_DB`, 2 dB, so their chords miss 1.4.0's S and H levels by about the same amount either side.
- `just calibrate` first sets the level into the power stage to 1.4.0's at every Drive on every tone stack, then holds the loudness of the level reference, 1.4.0's default settings, as Drive, Power Drive and Grit move, through gains after the cabinet that change level and nothing else.
- `just refit` then brings each factory preset to the reference's strike level on the humbucker with Output.
- The 2 dB output cut sits outside all of it.
