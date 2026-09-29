# Guitar recordings

Direct recordings of a real guitar, the input every level measurement and
the factory voicing use.

| File | Pickup | Length | Peak | Level while sounding |
| --- | --- | --- | --- | --- |
| `single-coil-plucks-strum-chord.wav` | single coil | 11.9 s | −23.2 dBFS | −40.8 dBFS RMS |
| `humbucker-plucks-strum-chord.wav` | humbucker | 12.2 s | −14.5 dBFS | −34.3 dBFS RMS |
| `single-coil.wav` | single coil | 1.4 s | −15.6 dBFS | |

The two longer files are mono, 48 kHz, 24-bit, recorded direct with the same
settings, and play the same three things: each open string plucked from low E
to high E, the open strings strummed, then a chord at the fifth fret held
until it decays. They are exactly as recorded, with no gain applied, and are
played at Input 0, the level Swanky Amp expects from a guitar. The humbucker
is 8.7 dB hotter at its peak; keep that difference, never raise the two to
the same level.

`just calibrate` and `just refit` measure through them, as do the level tests.
Half their energy lies below 263 Hz (single coil) and 440 Hz (humbucker); a
synthetic pluck puts half its energy above 1 kHz, and measured through the tone
stack and the power stage it gives answers a player does not hear.

`single-coil.wav` is a shorter, hotter take, the input of the frozen 1.4.0
renders in `../frozen`; see `../README.md`. The files here are never changed:
a new take gets a new name.
