# Resonant Amp

Resonant Amp is a tube amplifier simulation DSP plugin which aims to capture the details in the dynamics of tube amplifiers.

The software is currently in alpha and is distributed only as a VST3 for 64-bit Windows systems. You can find the installer here:

<https://drive.google.com/open?id=1aOKUJyCAkUSvM0FRaJP6nhsQv2_noSLS>

## The model

The model was developed by running finite element method simulations (spice), storing the outputs, developing empirical models using a mix of python and C++, and then fitting the simulation results to those models. That code is very experimental and outside the scope of this repository.

## Building

The DSP is primarily written in [FAUST](https://faust.grame.fr/), whereas the UI is written in C++ using the [JUCE](https://www.juce.com) tooklit.

This repository includes code to:

* Build the VST3 or AAX using Visual Studio 2019
* Build the AU using Xcode
* Create the windows installer using [Inno Setup](https://jrsoftware.org/isinfo.php)
* Compile the FAUST code into a standalone C++ class

### For Windows

The project is configured assuming the VST3 SDK is found at: `C:\SDKs\VST_SDK\VST3_SDK\`. This can be changed in the VS solution files.

* Open the VS solution file at: `Builds/VisualStudio2019/ResonantAmp.sln`
* Change the target in VS to the x64 Release.
* Build the VST3 target.
* Move the VST3 to your VST3 system directory (usually `C:\Program Files\Common Files\VST3`)

### For Mac

This hasn't yet been attempted, but in theory it is possible.

### Installer

* Move into the `package` directory
* Open the Inno Setup script `setup.iss`
* Compile the installer, it should be created at `package/ResonantAmp-win64.exe`

### FAUST code

This isn't entirely stable and might require some code tweaking to get it working on your platform. Unfortunately the method chosen to get the FAUST code into a standalone format is very much a hack job which will need to be revisited at some later time.

This process generates `Source/AmpMono.h` artifact. However this file is tracked in the repository, so there is no need to re-generate it unless you are modifying the FAUT DSP files.

* Move into the `dsp` directory
* Run `python buildamp.py`

However this might not work for versions of FAUST other than `2.14.4` in which case you will need to dig around `dsp/builddsp.py` and fix any issues arising from that script.
