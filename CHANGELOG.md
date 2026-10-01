# Changelog

`Cargo.toml` is the version authority. Candidate tags add `-rc.N`; stable tags
equal the crate version. Every stable version has a section here before any
signed build starts. Its heading carries the planned release date, written by
hand before the first candidate is cut when the section already exists, since
`just version` dates only a new one. The website's date is the day the release
is published and may differ; a moved date is never a reason for a new
candidate.

## Unreleased

## 2.0.0 — 2026-10-30

Swanky Amp 2 preserves the released Free amplifier and cabinet sound, with the
tone stack and soft-clip knees corrected, in a new Rust host identity that
installs beside Swanky Amp 1.4.0.

- Ported the released amplifier and cabinet processing into mono and stereo
  paths under the `SwankyAmp2` / `com.resonantdsp.swanky-amp-2` / `SwA2`
  identity.
- Offered mono in, stereo out beside stereo and mono, so a mono guitar track
  can feed a stereo output, which plays the amplifier on both sides.
- Added an Audio Unit (version 2) for Logic Pro and GarageBand, which the
  macOS installer puts beside CLAP, VST3 and the standalone app. It tells a
  sandboxed host such as GarageBand that it checks for releases over the
  network and opens preset files outside the host, and it finds the user
  presets in the account's home folder there, as every other format does.
- Let the macOS and Windows installers install for all users or only the
  current user.
- Oversampled the tube stages: Auto runs them at 2x at 44.1 and 48 kHz and
  1x at 88.2 kHz and above, and the header's oversampling button cycles Auto,
  1x, 2x and 4x and names the factor the engine resolved.
- Corrected the tone stack's discretisation: 1.4.0 voiced every tone-stack
  feature an octave above the circuit. The ten factory presets are revoiced
  for it on real guitar recordings, judged by the balance between bands at the
  output, with Power Drive keeping each one's drive into the power stage to
  within about a dB, the nearest half mark on the panel; the
  results are in `verification/tone-stack/refit-report.md`, and Swanky Amp
  1.4.0 remains available for the original voicing. Imported 1.x user
  presets use a faster conversion and can sound boxier than their originals.
- Balanced the factory presets to Init's level, which 1.4.0's never were:
  each preset's Output moves so that all ten strike as loud as Init on a
  humbucker, so switching presets no longer jumps in level. On a single coil
  the driven presets play louder than Init, because their sustain holds up
  where a clean tone decays. Imported 1.x presets are not rebalanced.
- Fixed a slow tone-stack instability that silenced high-gain presets after
  hours of continuous play (issue #34). The first-order treble sections were
  discretised as biquads with a spurious pole at Nyquist, which f32 rounding
  placed just outside the unit circle; they are now true first-order filters,
  with the response unchanged.
- Kept a bad sample from upstream from silencing the amplifier until the
  host prepares it again: a non-finite or absurdly large input sample plays
  as a one-sample dropout, and the host never receives a non-finite sample.
- Joined the triode soft clips' knees smoothly: the released cubic left each
  knee with slope 4/3.4, a corner at every grid, bias, plate and compression
  clip. Each triode stage carries a fixed makeup gain fitted against the
  released seam levels over the ten factory presets, keeping every seam at 0 dB
  input within 0.6 dB of 1.4.0 (tone stack 1.05 dB, output 0.5 dB). The
  tetrode keeps the released curve, which sets its bias and gain rather than a
  knee.
- Recalibrated the level compensation for the corrected amplifier on real
  guitar recordings, staged as 1.4.0's input meter asks and played at
  Input 0: with the tone controls at their
  defaults, playing drives the power stage within about 1 dB of 1.4.0 at every
  Drive on every tone stack.
- Drive, Power Drive and Grit change the sound without changing the volume.
  In 1.4.0 the level moved by several dB across Drive and Power Drive, most on
  a humbucker, and Grit silenced the amplifier at its top. Output gains
  measured by `just calibrate` hold the loudness, averaged over the
  recordings, close to Init's across each control.
- Fixed Grit silencing the amplifier near its top: it raised a triode
  compressor's threshold past the stage's plate signal, collapsing the
  stage's output to a constant, 52 dB down. The threshold now stops just
  short of that point.
- Input, Output and the level gains Drive and Power Drive derive now glide
  linearly across the block in which they change instead of stepping, so
  sweeping or automating them no longer clicks or zippers. The tube stages,
  tone stack and cabinet still step, and a setting held still sounds exactly
  as before.
- Made the header's preset field live: `‹` and `›` step through the refitted
  factory presets and the user's own, and the name opens a menu with Init,
  every preset, Save, Save as…, Remove, Import 1.x presets and Open folder.
  Presets apply through the host, the selection survives a session reload, and
  a dot marks a changed preset. Input and the cabinet switch stay with the
  session, as in 1.4.0. Save as… replaces a preset only when the system
  dialog returned that file, and every save is written whole or not at all. Remove
  asks in the menu before it deletes the file,
  and the factory presets are capitalised like Init. A name too long for the
  field ends in an ellipsis and reads whole in the footer while the pointer is
  over the field; the menu widens to fit its longest name, up to the window.
- Kept presets in the 1.x XML format, one file per preset under
  `Resonant DSP/Swanky Amp 2`, and applied 1.4.0's migrations for presets from
  earlier releases. Unreadable files are skipped and named.
- Imported 1.4.0 user presets on first run and on request, refitting each one's
  Low, Mid, High and Power Drive to the corrected tone stack like the factory
  set, without overwriting a version 2 preset or touching the 1.4.0 files.
- Regrouped the editor: six separate rounded boxes in two columns, each traced
  by a V groove, with Pro's outlined header controls, knob markers and
  uncluttered ten-cell meters, and the one-line "SWANKY AMP FREE" wordmark.
  1.4's rose highlight is the accent for lit rings, lit outlines, the
  edition tag and the output meter. The editor is 864 by 512 pixels.
- Replaced the cabinet toggle with a vertical two-position switch in its own
  column of the Cabinet row: a brushed aluminium disc that sits in either end
  of a V track two discs tall, with the ON label lit in the accent. The
  cabinet's Bright, Distance and Dynamic knobs, their labels and readouts dim
  while the cabinet is off, and stay adjustable.
- Lit the level meters from each instance's own signal, rising instantly and
  falling to 1/e in 0.3 s: input after the Input control on 1.4.0's -26 to
  +8 dBFS scale, where a light strum peaks about one third of the way up with
  a single coil, about two thirds with a humbucker, and output after the
  cabinet and Output control on -60 to 0 dBFS. Hosts that show plugin meters
  receive the same four levels.
- Added an information panel, opened from the header's cog button: it
  names the product and its version, links to the website, the manual and
  support, and closes with Escape, the button again or a press outside. Its
  Copy diagnostics link copies the version and build commit, system, host and
  format, sample rate and buffer for a support request, and its Third-party
  licences link opens the licences of the font and open-source code the
  product is built from, generated from its dependencies.
- Added an interface size to the information panel: the whole editor at 75,
  100, 125 or 150 %, with the same layout and native text drawn sharp at every
  size. The editor resizes its window and asks the host to follow in CLAP,
  VST3, the Audio Unit and the standalone. The size is remembered once per
  computer, never in presets or host state. The faceplate artwork is baked at
  two texels per interface pixel with filtered levels, so it is sharp at 100 %
  on Retina and at 150 %.
- Stopped committing the editable artwork layers: the repository keeps the
  artwork package with its receipt and licence, and `just unpack-artwork`
  recreates the EXR layers from the package, which pack back to it byte for
  byte.
- Added a bounded, cached release notice: the header's cog button turns into
  a highlighted download arrow when a newer stable release is published, and the
  panel announces it with a link to the fixed catalogue page. It ignores
  fields it does not know, so the published document can grow.
- Kept the plug-in loaded once its editor has opened, so a Windows host that
  unloads it cannot crash when the release check, the save dialog or a preset
  import outlives the last instance.
- Kept the standalone app's input from falling behind its output: a guitar
  played through it stays within about one buffer, where startup, a stall or
  separate input and output devices could leave up to a tenth of a second of
  delay for the session. The Settings menu gains a Buffer Size choice of 32 to
  1024 samples, 128 unless chosen, and the app remembers its input, output and
  buffer size between launches; `--input`, `--output` and `--buffer` override
  them for one launch. Choosing an audio interface as the input takes the
  output to it as well, unless an output has been chosen. On Windows, devices
  are listed by their full names, such as "Speakers (UMC202HD 192k)".
- Opened the standalone app with its input on, since an amplifier with its
  input off is silent; `--input-enabled off` opts out for one launch.
- The Windows standalone app plays through an audio interface's own ASIO®
  driver when one is installed, instead of the Windows shared audio path,
  which adds about 10 ms in each direction. The Settings menu gains an Audio
  Driver choice between ASIO and Windows (WASAPI), which the app remembers;
  `--driver asio` or `--driver wasapi` overrides it for one launch. On ASIO the
  interface is one device for input and output, chosen from either device
  menu, and a guitar played into it reaches the output in the same buffer.
  The information panel of the Windows standalone shows the ASIO Compatible
  logo. ASIO is a registered trademark of Steinberg Media Technologies GmbH.
