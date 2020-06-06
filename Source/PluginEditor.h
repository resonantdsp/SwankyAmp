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
#include "ResonantAmpLAF.h"
#include "Components/ParameterGroup.h"
#include "Components/LevelsGroup.h"
#include "Components/PreAmpGroup.h"
#include "Components/PowerAmpGroup.h"
#include "Components/StagingGroup.h"
#include "Components/ToneStackGroup.h"
#include "Components/CabGroup.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

class ResonantAmpAudioProcessorEditor : public AudioProcessorEditor
{
public:
	ResonantAmpAudioProcessorEditor(ResonantAmpAudioProcessor&, AudioProcessorValueTreeState&);
	~ResonantAmpAudioProcessorEditor();

	void paint (Graphics&) override;
	void resized() override;

private:
	ResonantAmpLAF resonantAmpLAF;
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	ResonantAmpAudioProcessor& processor;
	AudioProcessorValueTreeState& valueTreeState;

	std::unique_ptr<Drawable> logoSvg;

	LevelsGroup levelsGroup;
	std::unique_ptr<SliderAttachment> attInputLevel;
	std::unique_ptr<SliderAttachment> attOutputLevel;

	PreAmpGroup preAmpGroup;
	std::unique_ptr<SliderAttachment> attPreAmpDrive;
	std::unique_ptr<SliderAttachment> attPreAmpTouch;
	std::unique_ptr<SliderAttachment> attPreAmpGrit;

	PowerAmpGroup powerAmpGroup;
	std::unique_ptr<SliderAttachment> attPowerAmpDrive;
	std::unique_ptr<SliderAttachment> attPowerAmpTouch;

	StagingGroup stagingGroup;
	std::unique_ptr<SliderAttachment> attGainStages;
	std::unique_ptr<SliderAttachment> attGainSlope;
	std::unique_ptr<SliderAttachment> attLowCut;

	ToneStackGroup toneStackGroup;
	std::unique_ptr<SliderAttachment> attTsLow;
	std::unique_ptr<SliderAttachment> attTsMid;
	std::unique_ptr<SliderAttachment> attTsHigh;

	CabGroup cabGroup;
	std::unique_ptr<ButtonAttachment> attCabOnOff;

	Image bgNoise;
	Path bgPattern;
	Random rng;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ResonantAmpAudioProcessorEditor)
};

#undef INSERT_PARAMETER
