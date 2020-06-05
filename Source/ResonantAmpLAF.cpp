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

#include "Utils.h"
#include "Components/RSlider.h"
#include "ResonantAmpLAF.h"

ResonantAmpLAF::ResonantAmpLAF()
{
	setColour(ResizableWindow::backgroundColourId, ResonantAmpLAF::getColourBackground());
	setColour(Label::textColourId, ResonantAmpLAF::getColourDark());
	setColour(Slider::textBoxTextColourId, ResonantAmpLAF::getColourDark());
}

const Font& ResonantAmpLAF::getDefaultFont() {
	const static Font font = Font(
		Typeface::createSystemTypefaceFor(
			BinaryData::PTSansRegular_ttf,
			BinaryData::PTSansRegular_ttfSize
		)
	);

	return font;
}

const Font& ResonantAmpLAF::getDefaultFontNarrow() {
	const static Font font = Font(
		Typeface::createSystemTypefaceFor(
			BinaryData::PTSansNarrowRegular_ttf,
			BinaryData::PTSansNarrowRegular_ttfSize
		)
	);

	return font;
}

const Font& ResonantAmpLAF::getDefaultFontBold() {
	const static Font font = Font(
		Typeface::createSystemTypefaceFor(
			BinaryData::PTSansBold_ttf,
			BinaryData::PTSansBold_ttfSize
		)
	);

	return font;
}

const Colour& ResonantAmpLAF::getColourDark() {
	const static Colour colour = Colour::fromHSV(0.0f, 0.0f, 0.25f, 1.0f);
	return colour;
}

const Colour& ResonantAmpLAF::getColourGrey() {
	const static Colour colour = Colour::fromHSV(0.0f, 0.0f, 0.75f, 1.0f);
	return colour;
}

const Colour& ResonantAmpLAF::getColourBackground() {
	const static Colour colour = Colour::fromHSV(0.0f, 0.0f, 1.0f, 1.0f);
	return colour;
}

const Colour& ResonantAmpLAF::getColourHighlight() {
	const static Colour colour = Colour::fromHSV(0.98f, 0.6f, 0.75f, 1.0f);
	return colour;
}

Slider::SliderLayout ResonantAmpLAF::getSliderLayout(Slider& slider)
{
    if (!slider.isRotary() && slider.getTextBoxPosition() != Slider::TextBoxBelow)
        return LookAndFeel_V4::getSliderLayout(slider);

    auto localBounds = slider.getLocalBounds();

    Slider::SliderLayout layout;
	layout.textBoxBounds = localBounds;
    layout.sliderBounds = localBounds;

    return layout;
}

void ResonantAmpLAF::drawRotarySlider(
	Graphics& g,
	int x,
	int y,
	int width,
	int height,
	float sliderPos,
	const float rotaryStartAngle,
	const float rotaryEndAngle,
	Slider& slider
) {
	RSlider* rslider = dynamic_cast<RSlider*>(&slider);

	if (!rslider)
		return LookAndFeel_V4::drawRotarySlider(
			g,
			x,
			y,
			width,
			height,
			sliderPos,
			rotaryStartAngle,
			rotaryEndAngle,
			slider
		);

	const auto bounds = g.getClipBounds();

	const RSliderDims dims = rslider->calculateDims();

    const auto sliderAngle = angleModulo(rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle));
	
	// dial

	Path dialPath;
	dialPath.addCentredArc(
		dims.centre.getX(),
		dims.centre.getY(),
		dims.radius,
		dims.radius,
		0.0f,
		-dims.theta,
		dims.theta,
		true
	);
	dialPath.closeSubPath();

	auto dialShadow = DropShadow(
		Colour::fromHSV(0.0f, 0.0f, 0.0f, 0.5f),
		(int)(0.333f * dims.margin + 0.5f),
		Point<int>(1, 1)
	);
	dialShadow.drawForPath(g, dialPath);

	g.setColour(ResonantAmpLAF::getColourDark());
	g.fillPath(dialPath);

	// dial outline

	g.setColour(ResonantAmpLAF::getColourGrey());

	Path dialOutlinePath;
	//dialOutlinePath.startNewSubPath(dims.start + Point<float>(1.5f, 0));
	dialOutlinePath.addCentredArc(
		dims.centre.getX(),
		dims.centre.getY(),
		dims.radius - 1.5f,
		dims.radius - 1.5f,
		0.0f,
		-dims.theta,
		dims.theta,
		true
	);
	dialOutlinePath.closeSubPath();
	g.strokePath(dialOutlinePath, PathStrokeType(1.0f));

	auto dialBounds = Rectangle<float>();
	dialBounds.setSize(dims.radius * 2.0f, dims.radius * 2.0f);
	dialBounds.setX(dims.centre.getX() - dims.radius);
	dialBounds.setY(dims.centre.getY() - dims.radius);

	// label text

	const String labelText = rslider->fmtSliderPos(sliderPos);
	g.setFont(ResonantAmpLAF::getDefaultFontNarrow().withHeight(20.0f));
	g.setColour(ResonantAmpLAF::getColourGrey());
	g.drawText(labelText, dialBounds, Justification::centred, true);

	// tick
 
	Path pointerPath;
	auto pointerLength = dims.radius * 0.33f;
	auto lineThickness = 2.0f;
	pointerPath.addRoundedRectangle(-lineThickness * 2.0f * 0.5f, -dims.radius, lineThickness * 2.0f, pointerLength, lineThickness);
	pointerPath.applyTransform(AffineTransform::rotation(sliderAngle).translated(dialBounds.getCentre()));
	g.setColour(ResonantAmpLAF::getColourGrey());
	g.fillPath(pointerPath);

	// dots

	const float dotSize = dims.margin - 2.0f * dims.gap;

	auto dotClipPath = Path();
	dotClipPath.startNewSubPath(dialBounds.getCentre());
	dotClipPath.addCentredArc(
		dialBounds.getCentreX(),
		dialBounds.getCentreY(),
		dims.radius + dims.margin,
		dims.radius + dims.margin,
		0.0f,
		-dims.theta,
		sliderAngle
	);
	dotClipPath.closeSubPath();

	g.setColour(ResonantAmpLAF::getColourGrey());

	for (int iangle = 1; iangle < 10; iangle++) {
		const float angle = dims.theta - iangle * dims.theta / 5.0f;
		const auto dotCenter = dialBounds.getCentre() - (dims.radius + dims.margin / 2.0f) * Point<float>(sinf(angle), cosf(angle));
		auto dotBounds = Rectangle<float>();
		dotBounds.setCentre(dotCenter);
		dotBounds.translate(-dotSize / 2.0f, -dotSize / 2.0f);
		dotBounds.setSize(dotSize, dotSize);
		g.fillEllipse(dotBounds);
	}

	g.setColour(ResonantAmpLAF::getColourHighlight());
	g.saveState();
	g.reduceClipRegion(dotClipPath);

	for (int iangle = 1; iangle < 10; iangle++) {
		const float angle = dims.theta - iangle * dims.theta / 5.0f;
		const auto dotCenter = dialBounds.getCentre() - (dims.radius + dims.margin / 2.0f) * Point<float>(sinf(angle), cosf(angle));
		auto dotBounds = Rectangle<float>();
		dotBounds.setCentre(dotCenter);
		dotBounds.translate(-dotSize / 2.0f, -dotSize / 2.0f);
		dotBounds.setSize(dotSize, dotSize);
		g.fillEllipse(dotBounds);
	}

	g.restoreState();
}

void ResonantAmpLAF::drawToggleButton(
	Graphics& g,
	ToggleButton& button,
	bool shouldDrawButtonAsHighlighted,
	bool shouldDrawButtonAsDown)
{
	const float lineWidth = 2.0f;

	const float radiusForHeight = (float)g.getClipBounds().getHeight() / 4.0f - lineWidth;
	const float radiusForWidth = (float)g.getClipBounds().getHeight() / 2.0f - lineWidth;

	const float radius = jmin(radiusForHeight, radiusForWidth);

	Rectangle<float> outer;
	outer.setSize(2.0f * radius, 4.0f * radius);
	outer.setPosition(
		g.getClipBounds().getCentreX() - radius,
		g.getClipBounds().getCentreY() - 2.0f * radius
	);

	Rectangle<float> circle;
	circle.setSize(2.0f * radius, 2.0f * radius);
	if (button.getToggleState())
		circle.setPosition(outer.getTopLeft());
	else
		circle.setPosition(outer.getTopLeft().translated(0.0f, 2.0f * radius));

	g.setColour(ResonantAmpLAF::getColourDark());
	g.fillEllipse(circle);

	g.setColour(ResonantAmpLAF::getColourGrey());
	g.setFont(ResonantAmpLAF::getDefaultFontNarrow().withHeight(radius));
	g.drawText(
		button.getToggleState() ? "ON" : "OFF",
		circle,
		Justification::centred,
		true
	);

	g.setColour(ResonantAmpLAF::getColourDark());
	g.drawRoundedRectangle(outer, radius, lineWidth);
}
