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

#include "LevelsGroup.h"
#include "ParameterGroup.h"
#include "LevelMeter.h"

LevelsGroup::LevelsGroup() :
	ParameterGroup("LEVELS"),
	meterInL(),
	meterInR(),
	meterOutL(),
	meterOutR()
{
	const auto inputTicks = MeterTicks{ {-16.5f, "S"}, {-2.5f, "H"} };

	meterInL.setRefreshRate(30);
	meterInL.setDecayTau(0.5f);
	meterInL.setDbLow(-26.0f);
	meterInL.setDbHigh(+8.0f);
	meterInL.setTicks(inputTicks);

	meterInR.setRefreshRate(30);
	meterInR.setDecayTau(0.5f);
	meterInR.setDbLow(-26.0f);
	meterInR.setDbHigh(+8.0f);
	meterInR.setTicks(inputTicks);
	meterInR.setLabelWidth(0);

	const auto outputTicks = MeterTicks{
		{-5.0f, "-5"},
		{-10.0f, ""},
		{-15.0f, "-15"},
		{-20.0f, ""},
		{-25.0f, "-25"},
	};

	meterOutL.setRefreshRate(30);
	meterOutL.setDecayTau(0.5f);
	meterOutL.setDbLow(-30.0f);
	meterOutL.setDbHigh(0.0f);
	meterOutL.setTicks(outputTicks);
	meterOutL.setLabelWidth(0);

	meterOutR.setRefreshRate(30);
	meterOutR.setDecayTau(0.5f);
	meterOutR.setDbLow(-30.0f);
	meterOutR.setDbHigh(0.0f);
	meterOutR.setTicks(outputTicks);
	meterOutR.setLabelsOnRight(true);

	addAndMakeVisible(meterInL);
	addAndMakeVisible(meterInR);

	addAndMakeVisible(meterOutL);
	addAndMakeVisible(meterOutR);

	addAndMakeVisible(sliderInputLevel);
	sliderInputLevel.setLabel("INPUT");
	sliderInputLevel.slider.setPosMapHigh(35.0f);
	sliderInputLevel.slider.setPosMapLow(-35.0f);
	sliderInputLevel.slider.setPosMapFmt("%+.0f dB");

	addAndMakeVisible(sliderOutputLevel);
	sliderOutputLevel.setLabel("OUTPUT");
	sliderOutputLevel.slider.setPosMapHigh(35.0f);
	sliderOutputLevel.slider.setPosMapLow(-35.0f);
	sliderOutputLevel.slider.setPosMapFmt("%+.0f dB");
}

LevelMeterListener* LevelsGroup::getLevelMeterListenerIn(int channel) {
	if (channel == 0) {
		return &meterInL;
	}
	else if (channel == 1) {
		return &meterInR;
	}
	else {
		return nullptr;
	}
}

LevelMeterListener* LevelsGroup::getLevelMeterListenerOut(int channel) {
	if (channel == 0) {
		return &meterOutL;
	}
	else if (channel == 1) {
		return &meterOutR;
	}
	else {
		return nullptr;
	}
}

void LevelsGroup::setHeight(int height) {
	setSize(0, height);

	const int labelSize = 16;
	const int meterWidth = 16;
	const int spacing = 12;
	const int labelGap = (int)(lineThickness + 0.5);
	const int innerHeight = getBorderBounds().getHeight() - 2 * spacing;

	Point<int> corner = getBorderBounds().getTopLeft() + Point<int>(spacing, spacing);

	meterInL.setLabelHeight((float)labelSize);
	meterInL.setLabelWidth(labelSize);
	meterInL.setLabelGap(labelGap);
	meterInL.setTopLeftPosition(corner);
	meterInL.setBarHeight(innerHeight);
	meterInL.setBarWidth(meterWidth);

	corner = meterInL.getBounds().getTopRight() + Point<int>(spacing, 0);

	meterInR.setLabelHeight((float)labelSize);
	meterInR.setTopLeftPosition(corner);
	meterInR.setBarHeight(innerHeight);
	meterInR.setBarWidth(meterWidth);

	corner = meterInR.getBounds().getTopRight() + Point<int>(spacing, 0);

	sliderInputLevel.setTopLeftPosition(corner);
	sliderInputLevel.setLabelHeight(labelSize);
	sliderInputLevel.slider.setGap(2.0f);
	sliderInputLevel.slider.setMargin(0.15 * innerHeight);
	sliderInputLevel.setLabelHeight(16.0f);
	sliderInputLevel.setFont(16.0f);
	sliderInputLevel.setHeight(innerHeight);

	corner = sliderInputLevel.getBounds().getTopRight() + Point<int>(spacing, 0);

	sliderOutputLevel.setTopLeftPosition(corner);
	sliderOutputLevel.setLabelHeight(labelSize);
	sliderOutputLevel.slider.setGap(2.0f);
	sliderOutputLevel.slider.setMargin(0.15 * innerHeight);
	sliderOutputLevel.setLabelHeight(16.0f);
	sliderOutputLevel.setFont(16.0f);
	sliderOutputLevel.setHeight(innerHeight);

	corner = sliderOutputLevel.getBounds().getTopRight() + Point<int>(spacing, 0);

	meterOutL.setTopLeftPosition(corner);
	meterOutL.setLabelHeight((float)labelSize);
	meterOutL.setBarHeight(innerHeight);
	meterOutL.setBarWidth(meterWidth);

	corner = meterOutL.getBounds().getTopRight() + Point<int>(spacing, 0);

	meterOutR.setLabelHeight((float)labelSize);
	meterOutR.setLabelWidth(labelSize);
	meterInL.setLabelGap(labelGap);
	meterOutR.setTopLeftPosition(corner);
	meterOutR.setBarHeight(innerHeight);
	meterOutR.setBarWidth(meterWidth);

	corner = meterOutR.getBounds().getTopRight() + Point<int>(spacing, 0);

	setSize(corner.getX() - getBounds().getX() + spacing, height);
}

void LevelsGroup::paint(Graphics& g)
{
	ParameterGroup::paint(g);
}


void LevelsGroup::resized()
{
	ParameterGroup::resized();
}
