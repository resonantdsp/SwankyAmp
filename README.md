# Resonant Amp

Resonant Amp is a tube amplifier simulation DSP plugin which aims to capture the details in the dynamics of tube amplifiers.

The software is currently in alpha and is distributed only as a VST3 for 64-bit Windows systems. You can find the installer here:

<https://drive.google.com/open?id=1aOKUJyCAkUSvM0FRaJP6nhsQv2_noSLS>

If you prefer to download the VST3 file directly and move it into the appropriate folder (typically `C:\Program Files\Common Files\VST3`), you can get it here:

<https://drive.google.com/open?id=1BrrAsjQ0f8kNIKv2-GHh7Hjl1CVIRMka>

## Change log

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

## Road map

* Re-work the tone stack to give greater range
* Overhaul the UI
* Add the ability to save presets

## Usage

Load the plugin into your favorite VST host or DAW (into a mono or stereo track), and have fun!

The UI is a hot mess at the moment, but here's a rough overview of the functionality:

* Use the input level to gain stage appropriately. The level meter has a marking `S` indicating roughly where you want to gain stage a single coil pickup, and `H` for a humbucker pickup. Strum a chord and adjust the input level until the meter peaks at the appropriate level. This is just a guideline. If you play hard, through an overdrive, or just want a different sound, then you can safely ignore that guideline.

* The `Pre Drive` control allows you to adjust the amount of distortion arising from the pre-amp stage. This is also often called the "Gain".

* The `Power Drive` control allows you to adjust the amount of distortion arising from the power amp stage. This is often also called the "Volume".

* The plugin roughly compensates for the additional volume arising from increasing the drive. However, when you get to very high levels you will notice the volume increasing, and might have to adjust your output level accordingly.

* The `Low`, `Mid` and `High` controls adjust the tone stack as you might expect from a typical guitar amp.

* The `Gain Stages` control adjusts the number of pre-amp stages the signal goes through. Increase this for a more modern distorted sound. All the way to the left the signal goes through only one gain stage which is an unusual situation and can give rise to some interesting tones.

* The `Gain Slope` control adjusts how much harder each consecutive gain stage is working than the last. Increase this for an edgier distortion. The effect is most pronounced at higher gain stages.

* The `Contour` control adjusts a high pass which removes low end in the pre-amp stage. Increase it for a tighter sound, but too much and you'll notice you're losing lows. Decrease it for a dirty distortion sound as the low end builds up in the pre-amp section and constantly biases the signal into a distorted region.

* When the `Cabinet` parameter is active, the amplifier output is fed into a cabinet model. The model emulates a generic 4x12 cabinet with a condesner microphone. If you have a cabinet emulation plugin, it might be best to disable this parameter and feed the output of Resonant Amp into your cabinet emulator.

* The `Pre. ...` controls adjust parameters relating to the pre-amp distortion, while the `Power ...` controls adjust the same parameters but for the power amp.

* The `... Dyn.` controls adjust parameters that affect how dynamically the distortion responds to your playing. Reduce the controls for a more consistent distortion, increase them to get more slow moving bias shifts.

* The `... Dist.` controls adjust parameters that affect the sound or tone of the distortion.

* These parameters are changing this relating to the circuitry around the tube and even the tube geometry itself (e.g. think plate voltage, resistors, but also the power of the tube, its internal capacitance etc.). These controls allow you to tune into a particular distortion sound not related to any one particular amplifier model. Think of it as building your own amp.

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
