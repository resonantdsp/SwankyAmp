/*
 *  Swanky Amp tube amplifier simulation
 *  Copyright (C) 2020  Garrin McGoldrick
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include <unordered_map>

#include <JuceHeader.h>

#include "PluginEditor.h"

#include "PluginProcessor.h"

// add parameter to the VTS with default range -1 to +1
#define MAKE_PARAMETER_UNIT(n)                                                 \
  std::make_unique<AudioParameterFloat>(                                       \
      "id" #n, #n, NormalisableRange<float>(-1.0f, 1.0f, 2.0f / 1e3f), 0.0f)
// add parameter to the VTS with custom range
#define MAKE_PARAMETER(n, l, h, d)                                             \
  std::make_unique<AudioParameterFloat>(                                       \
      "id" #n, #n, NormalisableRange<float>(l, h, fabs(h - l) / 1e3f), 0.0f)
// assign a VTS parameter to an object member of the same name
#define ASSIGN_PARAMETER(n) par##n = parameters.getRawParameterValue("id" #n);

SwankyAmpAudioProcessor::SwankyAmpAudioProcessor()
    :
#ifndef JucePlugin_PreferredChannelConfigurations
      AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
                     ),
#endif
      parameters(*this, nullptr, Identifier("APVTSSwankyAmp"),
                 {
                     MAKE_PARAMETER_UNIT(InputLevel),
                     MAKE_PARAMETER_UNIT(OutputLevel),

                     MAKE_PARAMETER_UNIT(TsLow),
                     MAKE_PARAMETER_UNIT(TsMid),
                     MAKE_PARAMETER_UNIT(TsHigh),
                     MAKE_PARAMETER_UNIT(TsPresence),

                     MAKE_PARAMETER(GainStages, 1.0f, 7.0f, 2.0f),
                     MAKE_PARAMETER_UNIT(GainSlope),
                     MAKE_PARAMETER(LowCut, -1.0f, 1.0f, 0.4f),

                     std::make_unique<AudioParameterBool>("idCabOnOff",
                                                          "CabOnOff", true),
                     MAKE_PARAMETER_UNIT(CabBrightness),
                     MAKE_PARAMETER(CabDistance, 0.0f, 1.0f, 0.0f),

                     MAKE_PARAMETER_UNIT(PreAmpDrive),
                     MAKE_PARAMETER_UNIT(PreAmpTight),
                     MAKE_PARAMETER_UNIT(PreAmpGrit),

                     MAKE_PARAMETER_UNIT(PowerAmpDrive),
                     MAKE_PARAMETER_UNIT(PowerAmpTight),
                     MAKE_PARAMETER_UNIT(PowerAmpGrit),

                     MAKE_PARAMETER(PowerAmpSag, -1.0f, 1.0f, -0.6f),
                     MAKE_PARAMETER_UNIT(PowerAmpSagRatio),
                     MAKE_PARAMETER(PowerAmpSagSlope, -1.0f, 1.0f, -0.25f),
                 }) {
  ASSIGN_PARAMETER(InputLevel)
  ASSIGN_PARAMETER(OutputLevel)

  ASSIGN_PARAMETER(TsLow)
  ASSIGN_PARAMETER(TsMid)
  ASSIGN_PARAMETER(TsHigh)
  ASSIGN_PARAMETER(TsPresence)

  ASSIGN_PARAMETER(GainStages)
  ASSIGN_PARAMETER(GainSlope)
  ASSIGN_PARAMETER(LowCut)

  ASSIGN_PARAMETER(CabOnOff)
  ASSIGN_PARAMETER(CabBrightness)
  ASSIGN_PARAMETER(CabDistance)

  ASSIGN_PARAMETER(PreAmpDrive)
  ASSIGN_PARAMETER(PreAmpTight)
  ASSIGN_PARAMETER(PreAmpGrit)

  ASSIGN_PARAMETER(PowerAmpDrive)
  ASSIGN_PARAMETER(PowerAmpTight)
  ASSIGN_PARAMETER(PowerAmpGrit)
  ASSIGN_PARAMETER(PowerAmpSag)

  ASSIGN_PARAMETER(PowerAmpSag)
  ASSIGN_PARAMETER(PowerAmpSagRatio)
  ASSIGN_PARAMETER(PowerAmpSagSlope)
}

#undef MAKE_PARAMETER_UNIT
#undef MAKE_PARAMETER
#undef ASSIGN_PARAMETER

SwankyAmpAudioProcessor::~SwankyAmpAudioProcessor() {}

float remap_sided(float unit, float to_low, float to_high) {
  if (unit >= 0) {
    return unit * to_high;
  } else {
    return -unit * to_low;
  }
}

float remap_range(float unit, float to_low, float to_high) {
  return (unit + 1.0f) / 2.0f * (to_high - to_low) + to_low;
}

float remap_xy(float x, float x1, float x2, float y1, float y2) {
  x = jmax(x1, jmin(x2, x));
  x = (x - x1) / (x2 - x1);
  float y = x * (y2 - y1) + y1;
  return y;
}

/** Remap a value in the range (-1, +1) to the same range, but apply log
 * scaling to it such that the latter part of the range is more compressed.
 * The output value will change with `slope1` at x = -1, and change with
 * `slope2` at x = +1.
 */
float remap_log(float x, float slope1, float slope2) {
  const float x1 = 1.0f / slope1;
  const float x2 = 1.0f / slope2;
  const float y1 = logf(x1);
  const float y2 = logf(x2);
  const float y = logf(remap_range(x, x1, x2));
  return remap_xy(y, y1, y2, -1.0f, +1.0f);
}

// set the amp object user parameters from the VTS values
void SwankyAmpAudioProcessor::setAmpParameters() {
  for (int i = 0; i < 2; i++) {
    amp_channel[i].set_input_level(*parInputLevel);
    amp_channel[i].set_output_level(*parOutputLevel);
    amp_channel[i].set_pre_drive(*parPreAmpDrive);
    amp_channel[i].set_power_drive(*parPowerAmpDrive);

    amp_channel[i].set_ts_low(*parTsLow);
    amp_channel[i].set_ts_mid(*parTsMid);
    amp_channel[i].set_ts_high(*parTsHigh);
    amp_channel[i].set_ts_presence(*parTsPresence);

    amp_channel[i].set_gain_stages(*parGainStages);
    amp_channel[i].set_gain_slope(*parGainSlope);

    amp_channel[i].set_cab_on_off((*parCabOnOff > 0.5f) ? +1.0f : -1.0f);
    amp_channel[i].set_cab_brightness(
        remap_sided(*parCabBrightness, -0.6f, +0.6f));
    amp_channel[i].set_cab_distance(*parCabDistance);

    amp_channel[i].set_triode_hp_freq(remap_sided(*parLowCut, -1.0f, +0.75f));
    amp_channel[i].set_tetrode_hp_freq(remap_sided(*parLowCut, -1.0f, +0.75f));

    const float minPreAmpTight =
        remap_xy(*parPreAmpDrive, -0.5f, +1.0f, -1.0f, 0.0f);
    const float adjPreAmpTight =
        remap_range(*parPreAmpTight, minPreAmpTight, +1.0f);

    amp_channel[i].set_triode_grid_tau(
        remap_sided(adjPreAmpTight * -1.0f, -0.5f, +0.1f));
    amp_channel[i].set_triode_grid_ratio(
        remap_sided(adjPreAmpTight * -1.0f, -1.0f, +0.1f));
    amp_channel[i].set_triode_plate_bias(
        remap_sided(adjPreAmpTight, -1.0f, +0.5f));
    amp_channel[i].set_triode_plate_comp_ratio(
        remap_sided(adjPreAmpTight, -1.0f, +0.0f));

    amp_channel[i].set_triode_grid_level(
        remap_sided(*parPreAmpGrit * -1.0f, -0.2f, +3.0f));
    amp_channel[i].set_triode_grid_clip(
        remap_sided(*parPreAmpGrit * -1.0f, -1.0f, +4.0f));
    amp_channel[i].set_triode_plate_comp_level(
        remap_sided(*parPreAmpGrit * +1.0f, -0.0f, +1.0f));
    amp_channel[i].set_triode_plate_comp_offset(
        remap_sided(*parPreAmpGrit * -1.0f, -0.0f, +5.0f));

    amp_channel[i].set_tetrode_grid_tau(
        remap_sided(*parPowerAmpTight * -1.0f, -1.0f, +1.0f));
    amp_channel[i].set_tetrode_grid_ratio(
        remap_sided(*parPowerAmpTight * -1.0f, -1.0f, +0.1f));
    amp_channel[i].set_tetrode_plate_comp_depth(
        remap_sided(*parPowerAmpTight * -1.0f, -0.5f, +0.0f));
    amp_channel[i].set_tetrode_plate_sag_tau(
        remap_sided(*parPowerAmpTight * -1.0f, -1.0f, +1.0f));

    const float sagOffset = jmax(0.0f, 2.0f * (float)*parPowerAmpDrive) +
                            0.5f * jmax(0.0f, (float)*parPreAmpDrive);
    const float sagRange = 1.0f / (1.0f + sagOffset * 1.0f);

    amp_channel[i].set_tetrode_plate_sag_toggle(
        *parPowerAmpSag > -0.999f ? 1.0f : 0.0f);
    amp_channel[i].set_tetrode_plate_sag_depth(
        remap_xy(*parPowerAmpSag, -1.0f, 1.0f, -1.0f - sagOffset,
                 -1.0f - sagOffset + 1.0f * sagRange));
    amp_channel[i].set_tetrode_plate_sag_ratio(*parPowerAmpSagRatio);
    amp_channel[i].set_tetrode_plate_sag_onset(*parPowerAmpSagSlope);
  }
}

const String SwankyAmpAudioProcessor::getName() const {
  return JucePlugin_Name;
}

bool SwankyAmpAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool SwankyAmpAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool SwankyAmpAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double SwankyAmpAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int SwankyAmpAudioProcessor::getNumPrograms() { return 1; }

int SwankyAmpAudioProcessor::getCurrentProgram() { return 0; }

void SwankyAmpAudioProcessor::setCurrentProgram(int index) {
  ignoreUnused(index);
}

const String SwankyAmpAudioProcessor::getProgramName(int index) {
  ignoreUnused(index);
  return {};
}

void SwankyAmpAudioProcessor::changeProgramName(int index,
                                                const String &newName) {
  ignoreUnused(index, newName);
}

void SwankyAmpAudioProcessor::prepareToPlay(double sampleRate,
                                            int samplesPerBlock) {
  ignoreUnused(samplesPerBlock);

  // Use this method as the place to do any pre-playback
  // initialisation that you need..
  for (int i = 0; i < 2; i++)
    amp_channel[i].init(jmax(1, (int)sampleRate));
  setAmpParameters();
}

void SwankyAmpAudioProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
  for (int i = 0; i < 2; i++)
    amp_channel[i].instanceClear();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SwankyAmpAudioProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
  ignoreUnused(layouts);
  return true;

#else
  // outputs must be mono or stereo
  if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
    return false;
  // inputs must be mono or stereo
  if (layouts.getMainInputChannelSet() != AudioChannelSet::mono() &&
      layouts.getMainInputChannelSet() != AudioChannelSet::stereo())
    return false;
  // if input is stereo, output must be stereo
  if (layouts.getMainInputChannelSet() == AudioChannelSet::stereo() &&
      layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
    return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}
#endif

void SwankyAmpAudioProcessor::processBlock(AudioBuffer<float> &buffer,
                                           MidiBuffer &midiMessages) {
  ignoreUnused(midiMessages);

  ScopedNoDenormals noDenormals;
  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  // copy plugin parameter values into the amp object
  setAmpParameters();

  // In case we have more outputs than inputs, this code clears any output
  // channels that didn't contain input data, (because these aren't
  // guaranteed to be empty - they may contain garbage).
  // This is here to avoid people getting screaming feedback
  // when they first compile a plugin, but obviously you don't need to keep
  // this code if your algorithm always overwrites all the output channels.
  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

  const auto numSamples = buffer.getNumSamples();

  for (int ichannel = 0; ichannel < jmin(totalNumInputChannels, 2);
       ichannel++) {
    auto inLevel = buffer.getMagnitude(ichannel, 0, numSamples);
    // convert to decibels and add the input level which ranges from -35 to +35
    inLevel = 20 * log10f(inLevel) + (*parInputLevel * 35);
    if (meterListenersIn[ichannel] != nullptr)
      meterListenersIn[ichannel]->update(inLevel);
    if (ichannel == 0 && totalNumInputChannels < 2 &&
        meterListenersIn[1] != nullptr)
      meterListenersIn[1]->update(inLevel);
  }

  // mono to mono: run the amp once
  if (totalNumInputChannels == 1 && totalNumOutputChannels == 1) {
    float *amp_buffer = buffer.getWritePointer(0);
    amp_channel[0].compute(buffer.getNumSamples(), &amp_buffer, &amp_buffer);
  }
  // mono to stereo: run the amp once, copy the result
  else if (totalNumInputChannels == 1 && totalNumOutputChannels == 2) {
    float *amp_buffer = buffer.getWritePointer(0);
    amp_channel[0].compute(buffer.getNumSamples(), &amp_buffer, &amp_buffer);
    float *amp_buffer_other = buffer.getWritePointer(1);
    std::memcpy((void *)amp_buffer_other, (void *)amp_buffer,
                numSamples * sizeof(float));
  }
  // stereo to stereo: run the amp twice
  else if (totalNumInputChannels == 2 && totalNumOutputChannels == 2) {
    for (int i = 0; i < 2; i++) {
      float *amp_buffer = buffer.getWritePointer(i);
      amp_channel[i].compute(buffer.getNumSamples(), &amp_buffer, &amp_buffer);
    }
  }

  for (int ichannel = 0; ichannel < jmin(totalNumOutputChannels, 2);
       ichannel++) {
    auto outLevel = buffer.getMagnitude(ichannel, 0, numSamples);
    // note: the output level parameter is already factored into the buffer
    outLevel = 20 * log10f(outLevel);
    if (meterListenersOut[ichannel] != nullptr)
      meterListenersOut[ichannel]->update(outLevel);
    if (ichannel == 0 && totalNumOutputChannels < 2 &&
        meterListenersOut[1] != nullptr)
      meterListenersOut[1]->update(outLevel);
  }
}

bool SwankyAmpAudioProcessor::hasEditor() const {
  return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor *SwankyAmpAudioProcessor::createEditor() {
  return new SwankyAmpAudioProcessorEditor(*this, parameters);
}

void SwankyAmpAudioProcessor::getStateInformation(MemoryBlock &destData) {
  auto state = parameters.copyState();
  std::unique_ptr<XmlElement> xml(state.createXml());
  copyXmlToBinary(*xml, destData);
}

void SwankyAmpAudioProcessor::setStateInformation(const void *data,
                                                  int sizeInBytes) {
  std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
  if (xmlState.get() != nullptr)
    if (xmlState->hasTagName(parameters.state.getType()))
      setStateInformation(xmlState, true);
}

std::unordered_map<String, double>
mapParameterValues(const SerializedState &state) {
  std::unordered_map<String, double> values;

  XmlElement *element = state->getFirstChildElement();

  while (element != nullptr) {
    if (element->getTagName() == "PARAM" && element->hasAttribute("id") &&
        element->hasAttribute("value")) {
      const String &id = element->getStringAttribute("id");
      const double value = element->getDoubleAttribute("value");
      values[id] = value;
    }

    element = element->getNextElement();
  }

  return values;
}

double transformUnitScale(double value, double lower, double upper,
                          double lowerPost, double upperPost) {
  const double post =
      2.0 / (upperPost - lowerPost) *
          ((value + 1.0) / 2.0 * (upper - lower) + lower - lowerPost) -
      1.0;
  return jmin(1.0, jmax(-1.0, post));
}

struct VersionNumber {
  int major = -1;
  int minor = -1;
  int patch = -1;

  VersionNumber() {}

  VersionNumber(int major, int minor, int patch)
      : major(major), minor(minor), patch(patch) {}

  bool VersionNumber::operator<(const VersionNumber &other) {
    if (this->major < other.major)
      return true;
    if (this->major == other.major && this->minor < other.minor)
      return true;
    if (this->major == other.major && this->minor == other.minor &&
        this->patch < other.patch)
      return true;
    return false;
  }
};

VersionNumber parseVersionString(const String &versionString) {
  int section = 0;
  VersionNumber versionNumber;
  String buff;
  for (const auto &c : versionString) {
    if (c == '.') {
      if (buff.isNotEmpty()) {
        if (section == 0)
          versionNumber.major = buff.getIntValue();
        else if (section == 1)
          versionNumber.minor = buff.getIntValue();
        else if (section == 2)
          versionNumber.patch = buff.getIntValue();
      }
      section += 1;
      buff.clear();
      continue;
    }
    buff += c;
  }
  return versionNumber;
}

void SwankyAmpAudioProcessor::setStateInformation(
    const std::unique_ptr<XmlElement> &state, bool useAll) {
  std::unordered_map<String, double> values;
  if (state != nullptr)
    values = mapParameterValues(state);

  // TODO: move to a function

  // range changes from 0.6 to 0.7
  if (state != nullptr && state->hasAttribute("pluginVersion") &&
      parseVersionString(state->getStringAttribute("pluginVersion")) <
          VersionNumber(0, 7, 0)) {
    if (values.find("idPowerAmpDrive") != values.end()) {
      const double value = values["idPowerAmpDrive"];
      const double post =
          transformUnitScale(value, log(1.0), log(1e3), log(0.5), log(5e2));
      values["idPowerAmpDrive"] = post;
    }
    if (values.find("idPowerAmpSag") != values.end()) {
      const double value = values["idPowerAmpSag"];
      const double post = transformUnitScale(value, 0.0, 1.0, 0.0, 0.5);
      values["idPowerAmpSag"] = post;
    }
  }

  // Not clear if multiple threads trying to set state could cause issues as
  // they would both trigger notirications to the host (the parameters changes
  // are atomic so that aspect should be ok). This is a precaution.
  setStateMutex.enter();

  for (const auto &id : parameterIds) {
    if (!useAll && (id == "idInputLevel" || id == "idCabOnOff"))
      continue;

    auto parameter = parameters.getParameter(id);
    if (parameter == nullptr)
      continue;

    if (values.find(id) == values.end())
      parameter->setValueNotifyingHost(parameter->getDefaultValue());
    else
      parameter->setValueNotifyingHost(
          parameter->convertTo0to1((float)values[id]));
  }

  // clear the amp state so that buffered values don't decay too slowly with new
  // parameters
  for (int i = 0; i < 2; i++)
    amp_channel[i].instanceClear();

  setStateMutex.exit();
}

AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new SwankyAmpAudioProcessor();
}
