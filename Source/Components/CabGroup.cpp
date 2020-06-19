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
#include "CabGroup.h"

CabGroup::CabGroup() :
	ParameterGroup("CABINET")
{
	addAndMakeVisible(buttonCabOnOff);

	addAndMakeVisible(sliderBright);
	sliderBright.setLabel("BRIGHT");

	addAndMakeVisible(sliderDistance);
	sliderDistance.setLabel("DISTANCE");
}

void CabGroup::attachVTS(AudioProcessorValueTreeState& vts)
{
	attCabOnOff.reset(new ButtonAttachment(vts, "idCabOnOff", buttonCabOnOff));
	attCabBrightness.reset(new SliderAttachment(vts, "idCabBrightness", sliderBright.slider));
	attCabDistance.reset(new SliderAttachment(vts, "idCabDistance", sliderDistance.slider));
}

void CabGroup::resized()
{
	const int prevInnerHeight = getBorderBounds().getHeight() - 2 * spacing;
	const Point<int> prevCorner = getBorderBounds().getTopLeft() + Point<int>(spacing, spacing);

	ParameterGroup::resized();

	const int innerHeight = getBorderBounds().getHeight() - 2 * spacing;
	Point<int> corner = getBorderBounds().getTopLeft() + Point<int>(spacing, spacing);

	// only re-set the positions when the height or position changes
	if (prevInnerHeight == innerHeight && prevCorner == corner) return;

	buttonCabOnOff.setTopLeftPosition(corner + Point<int>(spacing, spacing) / 2);
	buttonCabOnOff.setSize(
		(int)(buttonCabOnOff.calcWidthForHeight((float)innerHeight - spacing)),
		(int)((float)innerHeight - spacing)
	);


	corner = buttonCabOnOff.getBounds().getTopRight() + Point<int>(spacing, 0);

	sliderBright.setTopLeftPosition(corner + Point<int>(spacing, -spacing) / 2);
	sliderBright.slider.setMargin(0.15f * (float)innerHeight);
	sliderBright.setHeight(innerHeight);

	corner = sliderBright.getBounds().getTopRight() + Point<int>(spacing, 0);

	sliderDistance.setTopLeftPosition(corner);
	sliderDistance.slider.setMargin(0.15f * (float)innerHeight);
	sliderDistance.setHeight(innerHeight);

	corner = sliderDistance.getBounds().getTopRight() + Point<int>(spacing, 0);

	// can now determine the width and set it, this will re-call `resized` but
	// since the height is the same it won't re-do the calculation
	setSize(corner.getX() - getBounds().getX(), getHeight());
}
