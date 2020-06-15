# Resonant Amp

Resonant Amp is a tube amplifier simulation DSP plugin which aims to capture the details in the dynamics of tube amplifiers.

The software is currently in alpha and is distributed only as a VST3 for 64-bit Windows systems. You can find the installer here:

<https://drive.google.com/open?id=1aOKUJyCAkUSvM0FRaJP6nhsQv2_noSLS>

If you prefer to download the VST3 file directly and move it into the appropriate folder (typically `C:\Program Files\Common Files\VST3`), you can get it here:

<https://drive.google.com/open?id=1BrrAsjQ0f8kNIKv2-GHh7Hjl1CVIRMka>

## Road map

* Preset management
* More modern high gain mode

## Usage

Load the plugin into your favorite VST host or DAW (into a mono or stereo track), and have fun!

* Set the levels (gain staging):
    * Set the `input` control such that a strummed open chord just reaches the `S` tick mark for a single coil pickeup, or `H` for a hummbucker.
    * Set the `output` control to get the desired volume. Generally the -15 dB range is typical.
    * Note: these are suggested values. You can safely increase the input level to mimick the use of a clean boost pedal, or if you know your pickups are hotter than typical.

* Generally speaking, you'll want to leave the `cabinet` control to `on`, unless you'd rather use your own cabinet plugin downstream of the amp.

* Set the pre amp section
  * Set the `drive` control (a.k.a. gain) to get the desired pre amp distortion.
  * Increase the `tight` control to get to tighten the tube dynamics. This is especially helpful at high drive. Lower values with less drive lead to more touch sensitivity, higher values lead to a more modern sound.
  * Tune the `grit` control to get different distortion tones. This effectively changes the overhead available in the pre amp tubes.
  * Note: the plugin will attempt to maintain an even perceived loudness when modyfing the drive. This way you can use the drive to set the desired distortion, and then use the output level to adjust... well the output level.

* Set the staging:
  * Set the `stages` control to determine the number of pre amp tubes the signal is routed to. Increase this for a more even high gain distortion.
  * Tune the `slope` control to determine how much harder each successive tube is pushed (smaller values can help even out the distortion).
  * Increase `filter` control to remove low end build up in the pre-amp stage. A lower value can lead to a fuller sound, but it can be less stable.

* Set the tone stack:
  * The `low` control affects the amount of bass in your sound. Increase it for a fatter sound. Too much and the sound can become more washed out, muddy, and loose precision.
  * The `mid` control affects the amount of mids in your sound. Increase it to help the guitar stand out in a mix, to add aggression to the sound, and also to increase the sustain. Too much and the guitar sounds like its being played through a telephone speaker.
  * The `high` control affects the amout of high frequencies in your sound. Increase it get a brighter tone with more chime. Too much and the guitar can sound thin and brittle.

* Set the power amp section:
  * See the notes on the pre amp section
  * The `drive` control here has the same effect on distortion as the volume knob of an amp, but the plugin maintains an even loudness.
  * The the `sag` control to adjust the amount of voltage sag. With large sag, when the signal is large, it will get compressed, and it will also have less overhead meaning the distortion will be heard earlier at lower levels. The distortion also responds more to how heavily the guitar is played. This control works closely in conjuction with the `tight` control.
  * Note that the power amp can act as a compressor: try setting the drive to the point where softly picked notes don't distort, but heavily picked ones do. You should notice the notes souding a bit fuller as the transiet hits the distortion ceiling, and then the note rings through as the bias point shifts.

* Set the cabinet:
  * Leave the cabinet on unless you are using a dedicated cabinet emulator downstream of this plugin, or if you want a really experimental sound.
  * The `bright` control affects the brightness of the cabinet speaker by decreasing the lows and mids, and bumping up the precense. Decreasing this will do the opposite, darkening the sound.
  * The `distance` control affects the distance of the microphone to the cabinet. Increase it to scoop out some lows as well as some high mids.

## The model

The model was developed by running finit-difference simulation methods (spice), storing the outputs, developing empirical models using a mix of python and C++, and then fitting the model paramters to the simulation results. That code is very experimental and outside the scope of this repository.

## Building

The DSP is primarily written in [FAUST](https://faust.grame.fr/), whereas the UI is written in C++ using the [JUCE](https://www.juce.com) toolkit.

This repository includes code to:

* Build the VST3 or AAX using Visual Studio 2019
* Build the AU using Xcode
* Create the windows installer using [Inno Setup](https://jrsoftware.org/isinfo.php)
* Compile the FAUST code into a standalone C++ class

### For Windows

You will need the following softare to compile the plugin for windows:

* Visual Studio 2019
* The VST3 SDK
* The JUCE SDK

The project is configured assuming the VST3 SDK is found at: `C:\SDKs\VST_SDK\VST3_SDK\`, and that the JUCE SDK is found at `C:\JUCE\modules`. This can be changed in the VS solution files.

* Open the VS solution file at: `Builds\VisualStudio2019\ResonantAmp.sln`
* Change the target in VS to the x64 Release.
* Build the VST3 target.
* Move the VST3 to your VST3 system directory (usually `C:\Program Files\Common Files\VST3`)

### For Mac

This hasn't yet been attempted, but in theory it is possible.

### Installer

* Move into the `package` directory
* Open the Inno Setup script `setup.iss`
* Compile the installer, it should be created at `package\ResonantAmp-win64.exe`

### FAUST code

This isn't entirely stable and might require some code tweaking to get it working on your platform. Unfortunately the method chosen to get the FAUST code into a standalone format is very much a hack job which will need to be revisited at some later time.

This process generates `Source/AmpMono.h` artifact. However this file is tracked in the repository, so there is no need to re-generate it unless you are modifying the FAUT DSP files.

* Move into the `dsp` directory
* Run `python buildamp.py`

However this might not work for versions of FAUST other than `2.14.4` in which case you will need to dig around `dsp/builddsp.py` and fix any issues arising from that script.

## Change log

Version 0.4.0:

* Introduced voltage sag
* Small changes to the default power amp model to accomodate the voltage sag
* Overall the new power amp model is a better representation of the underlying amp

Version 0.3.0:

* New cabinet model is a more accurate depiction of a 4x12 cabinet into a dynamic mic.
* New cabinet controls to get more variation out of the final sound.
* Touch controls re-wired into tight controls.

Version 0.2.1:

* Added some texturing to the dials and buttons
* Technical changes to support further UI developement

Version 0.2.0:

* Add grit control to pre amp

Version 0.1.0:

* Built a proper UI
* Improved the parameter ranges, especially the drive
* Simplified the drive tone control
* Reduced the mids control slightly

Version 0.0.6:

* Rework the power amp again, capture slow dynamics
* In particular capturing bias drift contributing to distorted compression
* Improvements transfered over also to the pre amp section
* Some of the dsp code was streamlined to be more efficient

Version 0.0.5:

* Reworked tone stack to behave more like a normal amp
* Don't normalize tone stack levels (pushing up levels will increase distortion)

Version 0.0.4:

* Stability fixes
* Minor tweaks to power amp model
* Improvement to the pre amp model

Version 0.0.3:

* Added a parameter smooth cross over distortion
* Adjusted drive range for less spinal tap level 11
* Fixed issue with gain stage parameter not working as intended

Version 0.0.2:

* The power amplifier model is re-written and is a better representation of the simulation.
* The perceived volume of the plugin is more invariant to changes in the drive parameters.
* All model fits have been improved, default parameters should better ressemble the simulated circuits.
* Parameter ranges have been refined to give better control over the distortion sound.
* The cabinet mix has been made into a toggle for clarity.

## JUCE usage in code

* Following the JUCE guidelines loosely, with the notable change that the code uses tabs specifically to avoid visual indentation.
* Components should have sensible defaults so that a default conctructor can be provided, otherwise the no copy convention causes problems.
* The Look and Feel (LAF) contains defintions that can change on-the-fly (mainly colours). Default dimensions should be defined in component classes, as those don't need to be looked-up at each paint call.

