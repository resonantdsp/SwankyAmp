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

#include "StagingGroup.h"

StagingGroup::StagingGroup() :
	ParameterGroup("STAGING")
{

	addAndMakeVisible(sliderStages);
	sliderStages.setLabel("STAGES");
	sliderStages.slider.setPosMapLow(1.0f);
	sliderStages.slider.setPosMapHigh(5.0f);

	addAndMakeVisible(sliderSlope);
	sliderSlope.setLabel("SLOPE");

	addAndMakeVisible(sliderFilter);
	sliderFilter.setLabel("FILTER");
}


void StagingGroup::attachVTS(AudioProcessorValueTreeState& vts)
{
	attStages.reset(new SliderAttachment(vts, "idGainStages", sliderStages.slider));
	attSlope.reset(new SliderAttachment(vts, "idGainSlope", sliderSlope.slider));
	attFilter.reset(new SliderAttachment(vts, "idLowCut", sliderFilter.slider));
}

void StagingGroup::resized()
{
	const int prevInnerHeight = getBorderBounds().getHeight() - 2 * spacing;
	const Point<int> prevCorner = getBorderBounds().getTopLeft() + Point<int>(spacing, spacing);

	ParameterGroup::resized();

	const int innerHeight = getBorderBounds().getHeight() - 2 * spacing;
	Point<int> corner = getBorderBounds().getTopLeft() + Point<int>(spacing, spacing);

	// only re-set the positions when the height or position changes
	if (prevInnerHeight == innerHeight && prevCorner == corner) return;

	sliderStages.setTopLeftPosition(corner);
	sliderStages.slider.setMargin(0.15f * (float)innerHeight);
	sliderStages.setHeight(innerHeight);

	corner = sliderStages.getBounds().getTopRight() + Point<int>(spacing, 0);

	sliderSlope.setTopLeftPosition(corner);
	sliderSlope.slider.setMargin(0.15f * (float)innerHeight);
	sliderSlope.setHeight(innerHeight);

	corner = sliderSlope.getBounds().getTopRight() + Point<int>(spacing, 0);

	sliderFilter.setTopLeftPosition(corner);
	sliderFilter.slider.setMargin(0.15f * (float)innerHeight);
	sliderFilter.setHeight(innerHeight);

	corner = sliderFilter.getBounds().getTopRight() + Point<int>(spacing, 0);

	// can now determine the width and set it, this will re-call `resized` but
	// since the height is the same it won't re-do the calculation
	setSize(corner.getX() - getBounds().getX(), getHeight());
}

