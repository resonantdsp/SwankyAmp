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
#include "ParameterGroup.h"

#include "../ResonantAmpLAF.h"

ParameterGroup::ParameterGroup() :
	ParameterGroup("")
{
}

ParameterGroup::ParameterGroup(const String& pLabel)
{
	setLabel(pLabel);
	label.setJustificationType(Justification::topLeft);
	label.setFont(ResonantAmpLAF::getDefaultFont().withHeight(24.0f));
	label.setColour(Label::textColourId, ResonantAmpLAF::getColourDark());

	addAndMakeVisible(label);
}

void ParameterGroup::setLabel(const String& pLabel) {
	label.setText(pLabel, dontSendNotification);
}

void ParameterGroup::setLineThickness(float thickness) {
	lineThickness = thickness;
}

void ParameterGroup::paint(Graphics& g)
{
	auto gradient = ColourGradient();
	gradient.addColour(0.0f, Colour::fromHSV(0.64f, 0.01f, 0.95f, 1.0f));
	gradient.addColour(0.5f, Colour::fromHSV(0.64f, 0.0f, 1.0f, 1.0f));
	gradient.addColour(1.0f, Colour::fromHSV(0.64f, 0.01f, 0.95f, 1.0f));
	gradient.point1 = getBorderBounds().getCentre().toFloat().translated(-0.5f * (float)getHeight(), 0.0f);
	gradient.point2 = getBorderBounds().getCentre().toFloat().translated(+0.5f * (float)getHeight(), 0.0f);

	g.setGradientFill(gradient);
	g.fillRoundedRectangle(getBorderBounds().toFloat(), 2.0f* lineThickness);

	g.drawImage(bgNoise, getBorderBounds().toFloat(), RectanglePlacement::stretchToFit);

	g.setColour(ResonantAmpLAF::getColourDark());
	g.drawRoundedRectangle(getBorderBounds().toFloat(), 2.0f * lineThickness, lineThickness);

	g.setColour(Colour::fromHSV(0.0f, 0.0f, 1.0f, 0.5f));
	g.drawRoundedRectangle(
		getBorderBounds().toFloat().translated(-lineThickness / 4.0f, -lineThickness / 4.0f),
		2.0f * lineThickness,
		lineThickness / 2.0f
	);
}

void ParameterGroup::resized()
{
	label.setBounds(getLocalBounds());

	auto noise = Image(
		Image::PixelFormat::ARGB,
		jmax(1, getBorderBounds().getWidth() / 20),
		getBorderBounds().getHeight(),
		false
	);
	for (int i = 0; i < noise.getWidth(); i++)
		for (int j = 0; j < noise.getHeight(); j++)
			noise.setPixelAt(
				i, j,
				Colour::fromHSV(0.0f, 0.0f, 0.0f, rng.nextFloat() * 0.03f)
			);

	bgNoise = noise;
}

Rectangle<int> ParameterGroup::getBorderBounds() const {
	Rectangle<float> bounds = getLocalBounds().toFloat();
	bounds.setTop(label.getFont().getHeight());
	BorderSize<float>(lineThickness / 2.0f).subtractFrom(bounds);
	return bounds.toNearestInt();
}

