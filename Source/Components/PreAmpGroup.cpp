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
#include "PreAmpGroup.h"

PreAmpGroup::PreAmpGroup() :
	ParameterGroup("PRE AMP")
{

	addAndMakeVisible(sliderDrive);
	sliderDrive.setLabel("DRIVE");
	sliderDrive.slider.setPosMapLow(0.0f);
	sliderDrive.slider.setPosMapHigh(10.0f);
	sliderDrive.slider.setPosMapFmt("%02.0f");

	addAndMakeVisible(sliderTouch);
	sliderTouch.setLabel("TOUCH");
	sliderTouch.slider.setPosMapLow(0.0f);
	sliderTouch.slider.setPosMapHigh(10.0f);
	sliderTouch.slider.setPosMapFmt("%02.0f");
}

void PreAmpGroup::setHeight(int height) {
	setSize(0, height);

	const int labelSize = 16;
	const int spacing = 12;
	const int innerHeight = getBorderBounds().getHeight() - 2 * spacing;

	Point<int> corner = getBorderBounds().getTopLeft() + Point<int>(spacing, spacing);

	sliderDrive.setTopLeftPosition(corner);
	sliderDrive.setLabelHeight(labelSize);
	sliderDrive.slider.setGap(2.0f);
	sliderDrive.slider.setMargin(0.15 * innerHeight);
	sliderDrive.setLabelHeight(16.0f);
	sliderDrive.setFont(16.0f);
	sliderDrive.setHeight(innerHeight);

	corner = sliderDrive.getBounds().getTopRight() + Point<int>(spacing, 0);

	sliderTouch.setTopLeftPosition(corner);
	sliderTouch.setLabelHeight(labelSize);
	sliderTouch.slider.setGap(2.0f);
	sliderTouch.slider.setMargin(0.15 * innerHeight);
	sliderTouch.setLabelHeight(16.0f);
	sliderTouch.setFont(16.0f);
	sliderTouch.setHeight(innerHeight);

	corner = sliderTouch.getBounds().getTopRight() + Point<int>(spacing, 0);

	setSize(corner.getX() - getBounds().getX() + spacing, height);
}

