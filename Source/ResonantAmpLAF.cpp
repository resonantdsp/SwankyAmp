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
#include "Components/ParameterGroup.h"
#include "Components/RSlider.h"
#include "Components/LevelMeter.h"
#include "Components/RButton.h"

#include "ResonantAmpLAF.h"

const Colour ResonantAmpLAF::colourDark = Colour::fromHSV(0.0f, 0.0f, 0.25f, 1.0f);
const Colour ResonantAmpLAF::colourGrey = Colour::fromHSV(0.0f, 0.0f, 0.75f, 1.0f);
const Colour ResonantAmpLAF::colourBackground = Colour::fromHSV(0.0f, 0.0f, 1.0f, 1.0f);
const Colour ResonantAmpLAF::colourHighlight = Colour::fromHSV(0.98f, 0.6f, 0.75f, 1.0f);
const Colour ResonantAmpLAF::colourSteel = Colour::fromHSV(0.64f, 0.02f, 0.97f, 1.0f);

ResonantAmpLAF::ResonantAmpLAF()
{
	setColour(ResizableWindow::backgroundColourId, ResonantAmpLAF::colourBackground);
	setColour(Label::textColourId, ResonantAmpLAF::colourDark);
	setColour(Slider::textBoxTextColourId, ResonantAmpLAF::colourDark);

	setColour(ParameterGroup::borderColourId, ResonantAmpLAF::colourDark);
	setColour(ParameterGroup::steelColourId, ResonantAmpLAF::colourSteel);

	setColour(RSlider::dialColourId, ResonantAmpLAF::colourDark);
	setColour(RSlider::dialOutlineColourId, ResonantAmpLAF::colourGrey);
	setColour(RSlider::dialTextColourId, ResonantAmpLAF::colourGrey);
	setColour(RSlider::dialDotColourId, ResonantAmpLAF::colourHighlight);

	setColour(LevelMeter::outlineColourId, ResonantAmpLAF::colourDark);
	setColour(LevelMeter::backgroundColourId, ResonantAmpLAF::colourBackground);
	setColour(LevelMeter::meterColourId, ResonantAmpLAF::colourGrey);
	setColour(LevelMeter::textColourId, ResonantAmpLAF::colourDark);

	setColour(RButton::buttonColourId, ResonantAmpLAF::colourDark);
	setColour(RButton::textColourId, ResonantAmpLAF::colourGrey);
}

const Font& ResonantAmpLAF::getDefaultFont()
{
	const static Font font = Font(
		Typeface::createSystemTypefaceFor(
			BinaryData::PTSansRegular_ttf,
			BinaryData::PTSansRegular_ttfSize
		)
	);

	return font;
}

const Font& ResonantAmpLAF::getDefaultFontNarrow()
{
	const static Font font = Font(
		Typeface::createSystemTypefaceFor(
			BinaryData::PTSansNarrowRegular_ttf,
			BinaryData::PTSansNarrowRegular_ttfSize
		)
	);

	return font;
}

const Font& ResonantAmpLAF::getDefaultFontBold()
{
	const static Font font = Font(
		Typeface::createSystemTypefaceFor(
			BinaryData::PTSansBold_ttf,
			BinaryData::PTSansBold_ttfSize
		)
	);

	return font;
}


const DropShadow& ResonantAmpLAF::getDropShadow()
{
	const static DropShadow dropShadow(
		Colour::fromHSV(0.0f, 0.0f, 0.0f, 0.5),
		4,
		Point<int>(1, 1)
	);
	return dropShadow;
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
	Slider& slider)
{
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

	const RSliderDims dims = rslider->calcDims();

	const auto sliderAngle = angleModulo(
		rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle)
	);
	
	// dial

	auto dialBounds = Rectangle<float>();
	dialBounds.setSize(dims.radius * 2.0f, dims.radius * 2.0f);
	dialBounds.setX(dims.centre.getX() - dims.radius);
	dialBounds.setY(dims.centre.getY() - dims.radius);

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

	ResonantAmpLAF::getDropShadow().drawForPath(g, dialPath);

	g.setColour(findColour(RSlider::dialColourId));
	g.fillPath(dialPath);

	// texture the dial

	ColourGradient gradient;
	gradient.addColour(0.0f, Colour::fromHSV(0.0f, 0.0f, 1.0f, 0.1f));
	gradient.addColour(0.75f, Colour::fromHSV(0.0f, 0.0f, 1.0f, 0.0f));
	gradient.point1 = dialBounds.getTopLeft();
	gradient.point2 = dialBounds.getBottomLeft();
	g.setGradientFill(gradient);
	g.fillPath(dialPath);

	g.saveState();
	g.reduceClipRegion(dialPath);
	g.drawImage(rslider->getBgNoise(), slider.getLocalBounds().toFloat());
	g.restoreState();

	// dial outline

	g.setColour(findColour(RSlider::dialOutlineColourId));

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

	// label text

	const String labelText = rslider->fmtSliderPos(sliderPos);
	g.setFont(ResonantAmpLAF::getDefaultFontNarrow().withHeight(dims.radius / 1.5f));
	g.setColour(findColour(RSlider::dialTextColourId));
	g.drawText(labelText, dialBounds, Justification::centred, true);

	// tick
 
	Path pointerPath;
	auto pointerLength = dims.radius * 0.33f;
	auto lineThickness = 2.0f;
	pointerPath.addRoundedRectangle(
		-lineThickness * 2.0f * 0.5f,
		-dims.radius,
		lineThickness * 2.0f,
		pointerLength,
		lineThickness
	);
	pointerPath.applyTransform(AffineTransform::rotation(sliderAngle).translated(dialBounds.getCentre()));
	g.setColour(findColour(RSlider::dialOutlineColourId));
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

	g.setColour(findColour(RSlider::dialOutlineColourId));

	for (int iangle = 1; iangle < 10; iangle++) {
		const float angle = dims.theta - iangle * dims.theta / 5.0f;
		const auto dotCenter = 
			dialBounds.getCentre() 
			- (dims.radius + dims.margin / 2.0f) 
			* Point<float>(sinf(angle), cosf(angle));
		auto dotBounds = Rectangle<float>();
		dotBounds.setCentre(dotCenter);
		dotBounds.translate(-dotSize / 2.0f, -dotSize / 2.0f);
		dotBounds.setSize(dotSize, dotSize);
		g.fillEllipse(dotBounds);
	}

	g.setColour(findColour(RSlider::dialDotColourId));
	g.saveState();
	g.reduceClipRegion(dotClipPath);

	for (int iangle = 1; iangle < 10; iangle++) {
		const float angle = dims.theta - iangle * dims.theta / 5.0f;
		const auto dotCenter = 
			dialBounds.getCentre() 
			- (dims.radius + dims.margin / 2.0f) 
			* Point<float>(sinf(angle), cosf(angle));
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
	RButton* rbutton = dynamic_cast<RButton*>(&button);

	if (!rbutton)
		return LookAndFeel_V4::drawToggleButton(
			g,
			button,
			shouldDrawButtonAsHighlighted,
			shouldDrawButtonAsDown
		);

	ignoreUnused(shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

	const float lineWidth = 2.0f;

	const float radiusForHeight = (float)g.getClipBounds().getHeight() / 4.0f - lineWidth;
	const float radiusForWidth = (float)g.getClipBounds().getWidth() / 2.0f - lineWidth;

	const float radius = jmin(radiusForHeight, radiusForWidth);

	Rectangle<float> outer;
	outer.setSize(2.0f * radius, 4.0f * radius);
	outer.setPosition(
		g.getClipBounds().getCentreX() - radius,
		g.getClipBounds().getCentreY() - 2.0f * radius
	);

	// draw the circle

	Rectangle<float> circleBounds;
	circleBounds.setSize(2.0f * radius, 2.0f * radius);
	if (button.getToggleState())
		circleBounds.setPosition(outer.getTopLeft());
	else
		circleBounds.setPosition(outer.getTopLeft().translated(0.0f, 2.0f * radius));

	Path circlePath;
	circlePath.addEllipse(circleBounds);

	g.setColour(findColour(RButton::buttonColourId));
	g.fillPath(circlePath);

	// texture the circle

	ColourGradient gradient;
	gradient.addColour(0.0f, Colour::fromHSV(0.0f, 0.0f, 1.0f, 0.1f));
	gradient.addColour(0.75f, Colour::fromHSV(0.0f, 0.0f, 1.0f, 0.0f));
	gradient.point1 = circleBounds.getTopLeft();
	gradient.point2 = circleBounds.getBottomLeft();
	g.setGradientFill(gradient);
	g.fillPath(circlePath);

	g.saveState();
	g.reduceClipRegion(circlePath);
	g.drawImage(rbutton->getBgNoise(), button.getLocalBounds().toFloat());
	g.restoreState();

	// draw the text

	g.setColour(findColour(RButton::textColourId));
	g.setFont(ResonantAmpLAF::getDefaultFontNarrow().withHeight(radius));
	g.drawText(
		button.getToggleState() ? "ON" : "OFF",
		circleBounds,
		Justification::centred,
		true
	);

	g.setColour(findColour(RButton::buttonColourId));
	g.drawRoundedRectangle(outer, radius, lineWidth);
}
