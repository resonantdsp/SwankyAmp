# Guitar recordings

Direct recordings of a real guitar, the input every level measurement and
the factory voicing use.

| File | Pickup | Length | Peak | Level while sounding |
| --- | --- | --- | --- | --- |
| `single-coil-plucks-strum-chord-2.wav` | single coil | 12.1 s | −16.7 dBFS | −34.4 dBFS RMS |
| `humbucker-plucks-strum-chord-2.wav` | humbucker | 12.3 s | −6.7 dBFS | −25.5 dBFS RMS |
| `single-coil.wav` | single coil | 1.4 s | −15.6 dBFS | |

The two longer files are mono, 48 kHz, 24-bit, recorded direct with the same
settings, and play the same three things: each open string plucked from low E
to high E, the open strings strummed, then a soft chord at the fifth fret held
until it decays. The chord is each file's peak. The files are exactly as
recorded, with no gain applied; the humbucker is 10 dB hotter at its peak.
Keep that difference, never raise the two to the same level.

A take is staged by the released 1.x input meter, which reads the block's
sample peak plus Input: a light strum from a single coil should peak at its S
notch, −16.5 dBFS, and one from a humbucker at its H notch, −2.5 dBFS, at
Input 0. These chords peak at −16.7 and −6.7 dBFS, 0.2 dB under S and 4.2 dB
under H. The level measurements play both files 2 dB louder,
`RECORDING_GAIN_DB` in `src/dsp/calibration.rs`, which puts the chords at
−14.7 and −4.7 dBFS, 1.8 dB over S and 2.2 dB under H, and keeps the player's
own gap between the pickups rather than forcing each onto its notch.

`just calibrate` and `just refit` measure through them, as do the level tests.
Half their energy lies below 263 Hz (single coil) and 392 Hz (humbucker); a
synthetic pluck puts half its energy above 1 kHz, and measured through the tone
stack and the power stage it gives answers a player does not hear.

`single-coil.wav` is a shorter, hotter take, the input of the frozen 1.4.0
renders in `../frozen`; see `../README.md`. The files here are never changed:
a new take gets a new name, and the takes it replaces leave the repository.
