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
#include "../ResonantAmpLAF.h"
#include "RSliderLabel.h"

RSliderLabel::RSliderLabel()
{
	addAndMakeVisible(slider);
	addAndMakeVisible(label);
	label.setJustificationType(Justification::centredTop);
	label.setColour(Label::textColourId, ResonantAmpLAF::getColourDark());
}

RSliderLabel::~RSliderLabel()
{
}

void RSliderLabel::setLabel(const String& text) {
	label.setText(text, NotificationType::dontSendNotification);
}

void RSliderLabel::setFont(float size) {
	label.setFont(size);
}

void RSliderLabel::setFont(const Font& font) {
	label.setFont(font);
}

void RSliderLabel::setWidth(int width) {
	slider.setSize(width, width);
	const auto dims = slider.calculateDims();
	slider.setSize(width, (int)(dims.innerBounds.getHeight() + 0.5));
	label.setSize(width, label.getHeight());
	setSize(slider.getWidth(), slider.getHeight() + label.getHeight());
}

void RSliderLabel::setHeight(int height) {
	// TODO: needs review, e.g. method `getWidthForHeight`
	const int sliderHeight = height - label.getHeight();
	slider.setSize(sliderHeight, sliderHeight);
	const auto dims = slider.calculateDims();
	const int width = (int)(dims.innerBounds.getAspectRatio() * sliderHeight);
	setWidth(width);
}

void RSliderLabel::setLabelHeight(int height) {
	label.setSize(label.getWidth(), height);
	setHeight(getHeight());
}

void RSliderLabel::resized()
{
	label.setTopLeftPosition(slider.getBounds().getBottomLeft());
}
