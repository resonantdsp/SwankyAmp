/*
 *  Resonant Amp tube amplifier simulation
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

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LevelMeter.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

// add a slider and label member for a VTS parameter
#define INSERT_PARAMETER(name) \
Slider slide##name; \
Label label##name; \
std::unique_ptr<SliderAttachment> att##name;

//==============================================================================
/**
*/
class ResonantAmpAudioProcessorEditor : public AudioProcessorEditor, private LevelMeter::Listener
{
public:
	ResonantAmpAudioProcessorEditor(ResonantAmpAudioProcessor&, AudioProcessorValueTreeState&);
	~ResonantAmpAudioProcessorEditor();

	//==============================================================================
	void paint (Graphics&) override;
	void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	ResonantAmpAudioProcessor& processor;
	AudioProcessorValueTreeState& valueTreeState;

	void handleNewValue(int, float) override;
	LevelMeter meter;

	INSERT_PARAMETER(InputLevel)
	INSERT_PARAMETER(OutputLevel)
	INSERT_PARAMETER(PreDrive)
	INSERT_PARAMETER(PowerDrive);

	INSERT_PARAMETER(TsLow)
	INSERT_PARAMETER(TsMid)
	INSERT_PARAMETER(TsHigh)

	INSERT_PARAMETER(GainStages)
	INSERT_PARAMETER(GainSlope)

	INSERT_PARAMETER(LowCut)
	INSERT_PARAMETER(CabMix)

	INSERT_PARAMETER(TriodeDynamic)
	INSERT_PARAMETER(TriodeDistort)

	INSERT_PARAMETER(TetrodeDynamic)
	INSERT_PARAMETER(TetrodeDistort)

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ResonantAmpAudioProcessorEditor)
};

#undef INSERT_PARAMETER
