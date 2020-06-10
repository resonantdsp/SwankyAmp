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

#include "PowerAmpGroup.h"

PowerAmpGroup::PowerAmpGroup() :
	ParameterGroup("POWER AMP")
{
	addAndMakeVisible(sliderDrive);
	sliderDrive.setLabel("DRIVE");

	addAndMakeVisible(sliderTouch);
	sliderTouch.setLabel("TOUCH");
}

void PowerAmpGroup::attachVTS(AudioProcessorValueTreeState& vts)
{
	attDrive.reset(new SliderAttachment(vts, "idPowerAmpDrive", sliderDrive.slider));
	attTouch.reset(new SliderAttachment(vts, "idPowerAmpTouch", sliderTouch.slider));
}

void PowerAmpGroup::resized()
{
	const int prevInnerHeight = getBorderBounds().getHeight() - 2 * spacing;
	const Point<int> prevCorner = getBorderBounds().getTopLeft() + Point<int>(spacing, spacing);

	ParameterGroup::resized();

	const int innerHeight = getBorderBounds().getHeight() - 2 * spacing;
	Point<int> corner = getBorderBounds().getTopLeft() + Point<int>(spacing, spacing);

	// only re-set the positions when the height or position changes
	if (prevInnerHeight == innerHeight && prevCorner == corner) return;

	sliderDrive.setTopLeftPosition(corner);
	sliderDrive.slider.setMargin(0.15f * (float)innerHeight);
	sliderDrive.setHeight(innerHeight);

	corner = sliderDrive.getBounds().getTopRight() + Point<int>(spacing, 0);

	sliderTouch.setTopLeftPosition(corner);
	sliderTouch.slider.setMargin(0.15f * (float)innerHeight);
	sliderTouch.setHeight(innerHeight);

	corner = sliderTouch.getBounds().getTopRight() + Point<int>(spacing, 0);

	// can now determine the width and set it, this will re-call `resized` but
	// since the height is the same it won't re-do the calculation
	setSize(corner.getX() - getBounds().getX(), getHeight());
}
