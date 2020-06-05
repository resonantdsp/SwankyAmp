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
#include "ToneStackGroup.h"

ToneStackGroup::ToneStackGroup() :
	ParameterGroup("TONE STACK")
{

	addAndMakeVisible(sliderLow);
	sliderLow.setLabel("LOW");
	sliderLow.slider.setPosMapLow(0.0f);
	sliderLow.slider.setPosMapHigh(10.0f);
	sliderLow.slider.setPosMapFmt("%02.0f");

	addAndMakeVisible(sliderMid);
	sliderMid.setLabel("MID");
	sliderMid.slider.setPosMapLow(0.0f);
	sliderMid.slider.setPosMapHigh(10.0f);
	sliderMid.slider.setPosMapFmt("%02.0f");

	addAndMakeVisible(sliderHigh);
	sliderHigh.setLabel("HIGH");
	sliderHigh.slider.setPosMapLow(0.0f);
	sliderHigh.slider.setPosMapHigh(10.0f);
	sliderHigh.slider.setPosMapFmt("%02.0f");
}

void ToneStackGroup::setHeight(int height) {
	setSize(0, height);

	const int labelSize = 16;
	const int spacing = 12;
	const int innerHeight = getBorderBounds().getHeight() - 2 * spacing;

	Point<int> corner = getBorderBounds().getTopLeft() + Point<int>(spacing, spacing);

	sliderLow.setTopLeftPosition(corner);
	sliderLow.setLabelHeight(labelSize);
	sliderLow.slider.setGap(2.0f);
	sliderLow.slider.setMargin(0.15 * innerHeight);
	sliderLow.setLabelHeight(16.0f);
	sliderLow.setFont(16.0f);
	sliderLow.setHeight(innerHeight);

	corner = sliderLow.getBounds().getTopRight() + Point<int>(spacing, 0);

	sliderMid.setTopLeftPosition(corner);
	sliderMid.setLabelHeight(labelSize);
	sliderMid.slider.setGap(2.0f);
	sliderMid.slider.setMargin(0.15 * innerHeight);
	sliderMid.setLabelHeight(16.0f);
	sliderMid.setFont(16.0f);
	sliderMid.setHeight(innerHeight);

	corner = sliderMid.getBounds().getTopRight() + Point<int>(spacing, 0);

	sliderHigh.setTopLeftPosition(corner);
	sliderHigh.setLabelHeight(labelSize);
	sliderHigh.slider.setGap(2.0f);
	sliderHigh.slider.setMargin(0.15 * innerHeight);
	sliderHigh.setLabelHeight(16.0f);
	sliderHigh.setFont(16.0f);
	sliderHigh.setHeight(innerHeight);

	corner = sliderHigh.getBounds().getTopRight() + Point<int>(spacing, 0);

	setSize(corner.getX() - getBounds().getX() + spacing, height);
}

