# Guitar recordings

Direct recordings of a real guitar: the input for the level calibration, the
factory voicing and the level tests.

| File | Pickup | Length | Peak | Level while sounding |
| --- | --- | --- | --- | --- |
| `single-coil-plucks-strum-chord.wav` | single coil | 12.1 s | −16.7 dBFS | −34.4 dBFS RMS |
| `humbucker-plucks-strum-chord.wav` | humbucker | 12.2 s | −6.7 dBFS | −25.5 dBFS RMS |
| `single-coil.wav` | single coil | 1.4 s | −15.6 dBFS | |

The two longer files are mono, 48 kHz, 24-bit, recorded direct with the same
settings, and play the same three things: each open string plucked from low E
to high E, the open strings strummed, then a soft chord at the fifth fret held
until it decays. The chord is each file's peak. The files are exactly as
recorded, with no gain applied; the humbucker is 10 dB hotter at its peak.
Keep that difference, never raise the two to the same level.

Half their energy lies below 263 Hz (single coil) and 392 Hz (humbucker). A
synthetic pluck puts half its energy above 1 kHz, and measured through the
tone stack and the power stage it gives answers a player does not hear.

## Staging

The recordings are staged by the released 1.x input meter, which Swanky Amp 2
keeps: it reads the block's sample peak after Input, and at Input 0 a light
strum peaks about one third of the way up with a single coil, −16.5 dBFS, and
about two thirds with a humbucker, −2.5 dBFS. As recorded, the chords peak at
−16.7 and −6.7 dBFS. Every measurement plays both files 2 dB louder,
`RECORDING_GAIN_DB` in `src/dsp/calibration.rs`, which puts them at −14.7 and
−4.7 dBFS: 1.8 dB over the single coil's level and 2.2 dB under the
humbucker's. One gain for both keeps the player's own gap between the pickups
rather than forcing each onto its level; it is chosen so the two chords miss
their levels by about the same amount in opposite directions.

## Recording a new take

Record both pickups direct at the same interface settings, play the same three
parts, and commit the files as recorded under the names above. Set
`RECORDING_GAIN_DB` by the staging rule, then regenerate the level tables and
the factory bank and listen to the result:

```sh
just calibrate
just refit
```

`single-coil.wav` is a separate, shorter take and never changes: it is the
input of the frozen 1.4.0 renders in `../frozen`, whose manifest records its
digest, and of the model comparison; see [the reference README](../README.md).
