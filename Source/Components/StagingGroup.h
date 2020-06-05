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
#include "ParameterGroup.h"
#include "RSliderLabel.h"

#include "LevelMeter.h"

class StagingGroup : public ParameterGroup
{
public:
	StagingGroup();
	~StagingGroup() {}

	void setHeight(int height);

	RSliderLabel sliderStages;
	RSliderLabel sliderSlope;
	RSliderLabel sliderFilter;

private:
	int height = 0;

	// disable setting the width
	using Component::setSize;
	using Component::setBounds;
	using Component::setBoundsRelative;
	using Component::setBoundsInset;
	using Component::setBoundsToFit;
	using Component::centreWithSize;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StagingGroup)
};
