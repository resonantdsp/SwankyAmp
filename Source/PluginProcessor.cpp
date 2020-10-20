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
#include <cmath>
#include <unordered_map>

#include <JuceHeader.h>

#include "PluginEditor.h"

#include "PluginProcessor.h"

// add parameter to the VTS with default range -1 to +1
#define MAKE_PARAMETER_UNIT(n) \
  std::make_unique<AudioParameterFloat>( \
      "id" #n, #n, NormalisableRange<float>(-1.0f, 1.0f, 2.0f / 1e3f), 0.0f)
// add parameter to the VTS with custom range
#define MAKE_PARAMETER(n, l, h, d) \
  std::make_unique<AudioParameterFloat>( \
      "id" #n, #n, NormalisableRange<float>(l, h, fabs(h - l) / 1e3f), d)
// assign a VTS parameter to an object member of the same name
#define ASSIGN_PARAMETER(n) par##n = parameters.getRawParameterValue("id" #n);

SwankyAmpAudioProcessor::SwankyAmpAudioProcessor() :
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
    parameters(
        *this,
        nullptr,
        Identifier("APVTSSwankyAmp"),
        {
            MAKE_PARAMETER_UNIT(InputLevel),
            MAKE_PARAMETER_UNIT(OutputLevel),

            MAKE_PARAMETER_UNIT(TsLow),
            MAKE_PARAMETER_UNIT(TsMid),
            MAKE_PARAMETER_UNIT(TsHigh),
            MAKE_PARAMETER_UNIT(TsPresence),
            MAKE_PARAMETER(TsSelection, 0.0f, 2.0f, 0.0f),

            std::make_unique<AudioParameterInt>(
                "idGainStages", "GainStages", 1, 5, 3),
            MAKE_PARAMETER_UNIT(GainOverhead),
            MAKE_PARAMETER(LowCut, -1.0f, 1.0f, 0.4f),

            std::make_unique<AudioParameterBool>(
                "idCabOnOff", "CabOnOff", true),
            MAKE_PARAMETER_UNIT(CabBrightness),
            MAKE_PARAMETER(CabDistance, 0.0f, 1.0f, 0.5f),
            MAKE_PARAMETER(CabDynamic, -1.0f, 1.0f, -0.3f),

            MAKE_PARAMETER(PreAmpDrive, -1.0f, 1.0f, -0.4f),
            MAKE_PARAMETER_UNIT(PreAmpTight),
            MAKE_PARAMETER_UNIT(PreAmpGrit),

            MAKE_PARAMETER(PowerAmpDrive, -1.0f, 1.0f, -0.2f),
            MAKE_PARAMETER_UNIT(PowerAmpTight),
            MAKE_PARAMETER_UNIT(PowerAmpGrit),

            MAKE_PARAMETER(PowerAmpSag, -1.0f, 1.0f, -0.6f),
            MAKE_PARAMETER_UNIT(PowerAmpSagRatio),
        })
{
  ASSIGN_PARAMETER(InputLevel)
  ASSIGN_PARAMETER(OutputLevel)

  ASSIGN_PARAMETER(TsLow)
  ASSIGN_PARAMETER(TsMid)
  ASSIGN_PARAMETER(TsHigh)
  ASSIGN_PARAMETER(TsPresence)
  ASSIGN_PARAMETER(TsSelection)

  ASSIGN_PARAMETER(GainStages)
  ASSIGN_PARAMETER(GainOverhead)
  ASSIGN_PARAMETER(LowCut)

  ASSIGN_PARAMETER(CabOnOff)
  ASSIGN_PARAMETER(CabBrightness)
  ASSIGN_PARAMETER(CabDistance)
  ASSIGN_PARAMETER(CabDynamic)

  ASSIGN_PARAMETER(PreAmpDrive)
  ASSIGN_PARAMETER(PreAmpTight)
  ASSIGN_PARAMETER(PreAmpGrit)

  ASSIGN_PARAMETER(PowerAmpDrive)
  ASSIGN_PARAMETER(PowerAmpTight)
  ASSIGN_PARAMETER(PowerAmpGrit)
  ASSIGN_PARAMETER(PowerAmpSag)

  ASSIGN_PARAMETER(PowerAmpSag)
  ASSIGN_PARAMETER(PowerAmpSagRatio)
}

#undef MAKE_PARAMETER_UNIT
#undef MAKE_PARAMETER
#undef ASSIGN_PARAMETER

SwankyAmpAudioProcessor::~SwankyAmpAudioProcessor() {}

/**
 * @brief Remap a float value to a positive and negative range.
 *
 * Remap the range [-1, 0) to [`to_low`, 0) and the range (0, 1] to
 * (0, `to_high`]. Note that the values below zero can be scaled differently
 * from those above zero.
 *
 * @param unit value to remap, usually in the unit scale [-1, +1]
 * @param to_low scale values above zero by this amount
 * @param to_high  scale values below zero by this amount
 * @return remapped value
 */
float remap_sided(float unit, float to_low, float to_high)
{
  if (unit >= 0) { return unit * to_high; }
  else
  {
    return -unit * to_low;
  }
}

/**
 * @brief Remap a float value to a new range.
 *
 * Remap the range [-1, +1] to [`to_low`, `to_high`]. Unlike `remap_sided`, the
 * same scaling is applied to all input values. An input value of `0` will map
 * to the mean of `to_low` and `to_high`.
 *
 * @param unit value to remap, usually in the unit scale [-1, +1]
 * @param to_low value to reach when `unit` is at `-1`
 * @param to_high value to reach when `unit` is at `+1`
 * @return remapped value
 */
float remap_range(float unit, float to_low, float to_high)
{
  return (unit + 1.0f) / 2.0f * (to_high - to_low) + to_low;
}

/**
 * @brief Remap a given range of floats to a new range.
 *
 * Remap the range [`x1`, `x2`] to the range [`y1`, `y2`]. Clips the input `x`
 * to the range [`x1`, `x2`].
 *
 * @param x value to remap
 * @param x1 lower value in the range to map from
 * @param x2 upper value in the range to map from
 * @param y1 lower value in the range to map to
 * @param y2 upper value in the range to map to
 * @return remapped value
 */
float remap_xy(float x, float x1, float x2, float y1, float y2)
{
  x = jmax(x1, jmin(x2, x));
  x = (x - x1) / (x2 - x1);
  float y = x * (y2 - y1) + y1;
  return y;
}

/**
 * @brief Remap a value from the range (-1, +1) to the same range, but with a
 * new metric such that dy/dx(x) follows a sinh curve.
 *
 * In other words, for an input x near the eges -1 or 1, a small change in x
 * will result in a bigger change in y. For input values near 0, a small
 * change in x will result in a smaller change in y.
 *
 * The calulating uses exponential values in the intermediate steps. This can
 * probably be fixed later, but for now scales should stay below 100.
 *
 * @param x the value to remap
 * @param x0 the point in the range (-1, 1) where y changes most slowly
 * @param scale larger values will create a bigger difference
 * @return remaped value
 */
float remapSinh(float x, float x0, float scale)
{
  // the value mapped by sinh
  const float mapped = sinh((x - x0) * scale);
  // y(x) at the bounds -1 and 1
  const float lower = sinh((-1.0f - x0) * scale);
  const float upper = sinh((+1.0f - x0) * scale);
  return (mapped - lower) / (upper - lower) * 2.0f - 1.0f;
}

float invertRemapSinh(float x, float x0, float scale)
{
  const float lower = sinh((-1.0f - x0) * scale);
  const float upper = sinh((+1.0f - x0) * scale);
  const float unscaled = (x + 1.0f) / 2.0f * (upper - lower) + lower;
  return asinh(unscaled) / scale + x0;
}

// set the amp object user parameters from the VTS values
void SwankyAmpAudioProcessor::setAmpParameters()
{
  for (int i = 0; i < 2; i++)
  {
    const float preAmpDriveMap = *parPreAmpDrive;
    const float powerAmpDriveMap = remapSinh(*parPowerAmpDrive, -0.2f, 1.0f);
    const float powerAmpSagMap = remapSinh(*parPowerAmpSag, 0.0f, 1.0f);

    amp_channel[i].set_input_level(*parInputLevel);
    amp_channel[i].set_output_level(
        *parOutputLevel
        + (10.0f + remap_xy(preAmpDriveMap, 0.0f, 1.0f, 0.0f, -3.0f)) / 35.0f);
    amp_channel[i].set_triode_drive(preAmpDriveMap);
    amp_channel[i].set_tetrode_drive(powerAmpDriveMap);

    amp_channel[i].set_tonestack_bass(*parTsLow);
    amp_channel[i].set_tonestack_mids(*parTsMid);
    amp_channel[i].set_tonestack_treble(*parTsHigh);
    amp_channel[i].set_tonestack_presence(*parTsPresence);
    amp_channel[i].set_tonestack_selection(*parTsSelection);

    amp_channel[i].set_triode_num_stages((int)(*parGainStages));
    amp_channel[i].set_triode_overhead(*parGainOverhead);

    amp_channel[i].set_cabinet_on((*parCabOnOff > 0.5f) ? true : false);
    amp_channel[i].set_cabinet_brightness(
        remap_sided(*parCabBrightness, -0.6f, +0.6f));
    amp_channel[i].set_cabinet_distance(*parCabDistance);
    // full dynamic when knob is at 0.0
    amp_channel[i].set_cabinet_dynamic(
        remap_xy(*parCabDynamic, -1.0f, 0.0f, -1.0f, +1.0f));
    // move the dynamic level down over the dynamic knob range
    amp_channel[i].set_cabinet_dynamic_level(-1.0f * *parCabDynamic);

    amp_channel[i].set_triode_hp_freq(remap_sided(*parLowCut, -1.0f, +0.75f));
    amp_channel[i].set_tetrode_hp_freq(remap_sided(*parLowCut, -1.0f, +0.75f));

    const float minPreAmpTight =
        remap_xy(preAmpDriveMap, -0.5f, +1.0f, -1.0f, 0.0f);
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

    amp_channel[i].set_tetrode_plate_sag_depth(
        powerAmpSagMap +
        // shift the depth higher at low drive to get some audible effect when
        // not much of signal is over clip, and lower at high drive to avoid
        // just hacking away the signal with a constant db offset
        remap_xy(powerAmpDriveMap, -1.0f, 1.0f, 1.0f, -1.0f));
    amp_channel[i].set_tetrode_plate_sag_ratio(*parPowerAmpSagRatio);
    amp_channel[i].set_tetrode_plate_sag_onset(powerAmpSagMap);
    amp_channel[i].set_tetrode_plate_sag_factor(
        amp_channel[i].get_tetrode_drive());
    amp_channel[i].set_tetrode_plate_sag_toggle(
        powerAmpSagMap < -0.99f ? -1.0f : 1.0f);
  }
}

const String SwankyAmpAudioProcessor::getName() const
{
  return JucePlugin_Name;
}

bool SwankyAmpAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool SwankyAmpAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool SwankyAmpAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double SwankyAmpAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int SwankyAmpAudioProcessor::getNumPrograms() { return 1; }

int SwankyAmpAudioProcessor::getCurrentProgram() { return 0; }

void SwankyAmpAudioProcessor::setCurrentProgram(int index)
{
  ignoreUnused(index);
}

const String SwankyAmpAudioProcessor::getProgramName(int index)
{
  ignoreUnused(index);
  return {};
}

void SwankyAmpAudioProcessor::changeProgramName(
    int index, const String& newName)
{
  ignoreUnused(index, newName);
}

void SwankyAmpAudioProcessor::prepareToPlay(
    double sampleRate, int samplesPerBlock)
{
  ignoreUnused(samplesPerBlock);

  // Use this method as the place to do any pre-playback
  // initialisation that you need..
  for (int i = 0; i < 2; i++) amp_channel[i].prepare(jmax(1, (int)sampleRate));
  setAmpParameters();
}

void SwankyAmpAudioProcessor::releaseResources()
{
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
  for (int i = 0; i < 2; i++) amp_channel[i].reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SwankyAmpAudioProcessor::isBusesLayoutSupported(
    const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
  ignoreUnused(layouts);
  return true;

#else
  // outputs must be mono or stereo
  if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
      && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
    return false;
  // inputs must be mono or stereo
  if (layouts.getMainInputChannelSet() != AudioChannelSet::mono()
      && layouts.getMainInputChannelSet() != AudioChannelSet::stereo())
    return false;
  // if input is stereo, output must be stereo
  if (layouts.getMainInputChannelSet() == AudioChannelSet::stereo()
      && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void SwankyAmpAudioProcessor::processBlock(
    AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
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

  for (int ichannel = 0; ichannel < jmin(totalNumInputChannels, 2); ichannel++)
  {
    auto inLevel = buffer.getMagnitude(ichannel, 0, numSamples);
    // convert to decibels and add the input level which ranges from -35 to +35
    inLevel = 20 * log10f(inLevel) + (*parInputLevel * 35);
    if (meterListenersIn[ichannel] != nullptr)
      meterListenersIn[ichannel]->update(inLevel);
    if (ichannel == 0 && totalNumInputChannels < 2
        && meterListenersIn[1] != nullptr)
      meterListenersIn[1]->update(inLevel);
  }

  // mono to mono: run the amp once
  if (totalNumInputChannels == 1 && totalNumOutputChannels == 1)
  {
    float* amp_buffer = buffer.getWritePointer(0);
    amp_channel[0].process(buffer.getNumSamples(), &amp_buffer);
  }
  // mono to stereo: run the amp once, copy the result
  else if (totalNumInputChannels == 1 && totalNumOutputChannels == 2)
  {
    float* amp_buffer = buffer.getWritePointer(0);
    amp_channel[0].process(buffer.getNumSamples(), &amp_buffer);
    float* amp_buffer_other = buffer.getWritePointer(1);
    std::memcpy(
        (void*)amp_buffer_other, (void*)amp_buffer, numSamples * sizeof(float));
  }
  // stereo to stereo: run the amp twice
  else if (totalNumInputChannels == 2 && totalNumOutputChannels == 2)
  {
    for (int i = 0; i < 2; i++)
    {
      float* amp_buffer = buffer.getWritePointer(i);
      amp_channel[i].process(buffer.getNumSamples(), &amp_buffer);
    }
  }

  for (int ichannel = 0; ichannel < jmin(totalNumOutputChannels, 2); ichannel++)
  {
    auto outLevel = buffer.getMagnitude(ichannel, 0, numSamples);
    // note: the output level parameter is already factored into the buffer
    outLevel = 20 * log10f(outLevel);
    if (meterListenersOut[ichannel] != nullptr)
      meterListenersOut[ichannel]->update(outLevel);
    if (ichannel == 0 && totalNumOutputChannels < 2
        && meterListenersOut[1] != nullptr)
      meterListenersOut[1]->update(outLevel);
  }
}

bool SwankyAmpAudioProcessor::hasEditor() const
{
  return true;  // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SwankyAmpAudioProcessor::createEditor()
{
  return new SwankyAmpAudioProcessorEditor(*this, parameters);
}

void SwankyAmpAudioProcessor::setPresetText(const String& text)
{
  storedPresetText = text;
}

const String& SwankyAmpAudioProcessor::getPresetText() const
{
  return storedPresetText;
}

void SwankyAmpAudioProcessor::getStateInformation(MemoryBlock& destData)
{
  auto state = parameters.copyState();
  std::unique_ptr<XmlElement> xml(state.createXml());
  const String presetText = getPresetText();
  if (presetText.isNotEmpty()) { xml->setAttribute("presetName", presetText); }
  copyXmlToBinary(*xml, destData);
}

void SwankyAmpAudioProcessor::setStateInformation(
    const void* data, int sizeInBytes)
{
  std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
  if (xmlState.get() != nullptr)
  {
    if (xmlState->hasTagName(parameters.state.getType()))
    {
      if (xmlState->hasAttribute("presetName"))
      {
        setStateInformation(
            xmlState, xmlState->getStringAttribute("presetName"), true);
      }
      else
      {
        setStateInformation(xmlState, "", true);
      }
    }
  }
}

/**
 * @brief Build map of serialized state parameter names to values.
 * @param state serialized state
 * @return map of parameter names to values
 */
std::unordered_map<String, double>
mapParameterValues(const SerializedState& state)
{
  std::unordered_map<String, double> values;

  XmlElement* element = state->getFirstChildElement();

  while (element != nullptr)
  {
    if (element->getTagName() == "PARAM" && element->hasAttribute("id")
        && element->hasAttribute("value"))
    {
      const String& id = element->getStringAttribute("id");
      const double value = element->getDoubleAttribute("value");
      values[id] = value;
    }

    element = element->getNextElement();
  }

  return values;
}

double transformUnitScale(
    double value,
    double lower,
    double upper,
    double lowerPost,
    double upperPost)
{
  const double post = 2.0 / (upperPost - lowerPost)
          * ((value + 1.0) / 2.0 * (upper - lower) + lower - lowerPost)
      - 1.0;
  return jmin(1.0, jmax(-1.0, post));
}

struct VersionNumber
{
  int major = -1;
  int minor = -1;
  int patch = -1;

  VersionNumber() {}

  VersionNumber(int major, int minor, int patch) :
      major(major), minor(minor), patch(patch)
  {
  }

  bool operator==(const VersionNumber& other) const
  {
    return this->major == other.major && this->minor == other.minor
        && this->patch == other.patch;
  }

  bool operator<(const VersionNumber& other) const
  {
    if (this->major < other.major) return true;
    if (this->major == other.major && this->minor < other.minor) return true;
    if (this->major == other.major && this->minor == other.minor
        && this->patch < other.patch)
      return true;
    return false;
  }

  bool operator>(const VersionNumber& other) const
  {
    return !(*this == other) && !(*this < other);
  }

  bool operator!=(const VersionNumber& other) const
  {
    return !(*this == other);
  }
};

VersionNumber parseVersionString(const String& versionString)
{
  int section = 0;
  VersionNumber versionNumber;
  String buff;
  for (const auto c : versionString)
  {
    if (c == '.')
    {
      if (buff.isNotEmpty())
      {
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

  if (buff.isNotEmpty())
  {
    if (section == 0)
      versionNumber.major = buff.getIntValue();
    else if (section == 1)
      versionNumber.minor = buff.getIntValue();
    else if (section == 2)
      versionNumber.patch = buff.getIntValue();
  }

  return versionNumber;
}

void SwankyAmpAudioProcessor::setStateInformation(
    const std::unique_ptr<XmlElement>& state,
    const String& presetText,
    bool useAll)
{
  setPresetText(presetText);

  std::unordered_map<String, double> values;
  if (state != nullptr) values = mapParameterValues(state);

  // TODO: move to a function

  // range changes from 0.6 to 0.7
  if (state != nullptr && state->hasAttribute("pluginVersion")
      && parseVersionString(state->getStringAttribute("pluginVersion"))
          < VersionNumber(0, 7, 0))
  {
    if (values.find("idPowerAmpDrive") != values.end())
    {
      const double value = values["idPowerAmpDrive"];
      const double post =
          transformUnitScale(value, log(1.0), log(1e3), log(0.5), log(5e2));
      values["idPowerAmpDrive"] = post;
    }
    if (values.find("idPowerAmpSag") != values.end())
    {
      const double value = values["idPowerAmpSag"];
      const double post = transformUnitScale(value, 0.0, 1.0, 0.0, 0.5);
      values["idPowerAmpSag"] = post;
    }
  }

  // from 1.1 to 1.2
  if (state != nullptr && state->hasAttribute("pluginVersion")
      && parseVersionString(state->getStringAttribute("pluginVersion"))
          < VersionNumber(1, 2, 0))
  {
    if (values.find("idPreAmpDrive") != values.end())
    {
      const double value = values["idPreAmpDrive"];
      const float post = remap_xy((float)value, -1.0f, 1.0f, -0.67f, 0.86f);
      values["idPreAmpDrive"] = (double)post;
    }
    if (values.find("idPowerAmpDrive") != values.end())
    {
      const double value = values["idPowerAmpDrive"];
      const float post = invertRemapSinh(
          remap_xy((float)value, -1.0f, 1.0f, -0.85f, 1.14f), -0.2f, 1.0f);
      values["idPowerAmpDrive"] = (double)post;
    }
    if (values.find("idPowerAmpSag") != values.end())
    {
      const double value = values["idPowerAmpSag"];
      const float post = remapSinh((float)value, 0.0f, 1.0f);
      values["idPowerAmpSag"] = (double)post;
    }
  }

  setStateMutex.enter();

  if (presetText.isNotEmpty())
  {
    SwankyAmpAudioProcessorEditor* editor =
        dynamic_cast<SwankyAmpAudioProcessorEditor*>(getActiveEditor());
    if (editor != nullptr) { editor->setPresetTextDontNotify(presetText); }
  }

  for (const auto& id : parameterIds)
  {
    if (!useAll && (id == "idInputLevel" || id == "idCabOnOff")) continue;

    auto parameter = parameters.getParameter(id);
    if (parameter == nullptr) continue;

    if (values.find(id) == values.end())
      parameter->setValueNotifyingHost(parameter->getDefaultValue());
    else
      parameter->setValueNotifyingHost(
          parameter->convertTo0to1((float)values[id]));
  }

  // clear the amp state so that buffered values don't decay too slowly with new
  // parameters
  for (int i = 0; i < 2; i++) amp_channel[i].reset();

  setStateMutex.exit();
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new SwankyAmpAudioProcessor();
}
