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

#include <JuceHeader.h>

#include "LevelMeter.h"
#include "ParameterGroup.h"
#include "StagingGroup.h"

StagingGroup::StagingGroup() :
	ParameterGroup("STAGING")
{

	addAndMakeVisible(sliderStages);
	sliderStages.setLabel("STAGES");
	sliderStages.slider.setPosMapLow(1.0f);
	sliderStages.slider.setPosMapHigh(5.0f);
	sliderStages.slider.setPosMapFmt("%02.0f");

	addAndMakeVisible(sliderSlope);
	sliderSlope.setLabel("SLOPE");
	sliderSlope.slider.setPosMapLow(0.0f);
	sliderSlope.slider.setPosMapHigh(10.0f);
	sliderSlope.slider.setPosMapFmt("%02.0f");

	addAndMakeVisible(sliderFilter);
	sliderFilter.setLabel("FILTER");
	sliderFilter.slider.setPosMapLow(0.0f);
	sliderFilter.slider.setPosMapHigh(10.0f);
	sliderFilter.slider.setPosMapFmt("%02.0f");
}

void StagingGroup::setHeight(int height) {
	setSize(0, height);

	const int labelSize = 16;
	const int spacing = 12;
	const int innerHeight = getBorderBounds().getHeight() - 2 * spacing;

	Point<int> corner = getBorderBounds().getTopLeft() + Point<int>(spacing, spacing);

	sliderStages.setTopLeftPosition(corner);
	sliderStages.setLabelHeight(labelSize);
	sliderStages.slider.setGap(2.0f);
	sliderStages.slider.setMargin(0.15 * innerHeight);
	sliderStages.setLabelHeight(16.0f);
	sliderStages.setFont(16.0f);
	sliderStages.setHeight(innerHeight);

	corner = sliderStages.getBounds().getTopRight() + Point<int>(spacing, 0);

	sliderSlope.setTopLeftPosition(corner);
	sliderSlope.setLabelHeight(labelSize);
	sliderSlope.slider.setGap(2.0f);
	sliderSlope.slider.setMargin(0.15 * innerHeight);
	sliderSlope.setLabelHeight(16.0f);
	sliderSlope.setFont(16.0f);
	sliderSlope.setHeight(innerHeight);

	corner = sliderSlope.getBounds().getTopRight() + Point<int>(spacing, 0);

	sliderFilter.setTopLeftPosition(corner);
	sliderFilter.setLabelHeight(labelSize);
	sliderFilter.slider.setGap(2.0f);
	sliderFilter.slider.setMargin(0.15 * innerHeight);
	sliderFilter.setLabelHeight(16.0f);
	sliderFilter.setFont(16.0f);
	sliderFilter.setHeight(innerHeight);

	corner = sliderFilter.getBounds().getTopRight() + Point<int>(spacing, 0);

	setSize(corner.getX() - getBounds().getX() + spacing, height);
}

