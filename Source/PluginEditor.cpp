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

#include "PluginProcessor.h"
#include "PluginEditor.h"

ResonantAmpAudioProcessorEditor::ResonantAmpAudioProcessorEditor(
	ResonantAmpAudioProcessor& p,
	AudioProcessorValueTreeState& vts) :
	AudioProcessorEditor(&p),
	processor(p),
	valueTreeState(vts)
{
	setLookAndFeel(&resonantAmpLAF);
	LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypeface(
		resonantAmpLAF.getDefaultFont().getTypeface()
	);

	addAndMakeVisible(levelsGroup);
	processor.setMeterListenerIn(levelsGroup.getLevelMeterListenerIn(0), 0);
	processor.setMeterListenerIn(levelsGroup.getLevelMeterListenerIn(1), 1);
	processor.setMeterListenerOut(levelsGroup.getLevelMeterListenerOut(0), 0);
	processor.setMeterListenerOut(levelsGroup.getLevelMeterListenerOut(1), 1);
	attInputLevel.reset(new SliderAttachment(
		valueTreeState,
		"idInputLevel",
		levelsGroup.sliderInputLevel.slider)
	);
	attOutputLevel.reset(new SliderAttachment(
		valueTreeState,
		"idOutputLevel",
		levelsGroup.sliderOutputLevel.slider)
	);

	addAndMakeVisible(preAmpGroup);
	attPreAmpDrive.reset(new SliderAttachment(
		valueTreeState,
		"idPreAmpDrive",
		preAmpGroup.sliderDrive.slider)
	);
	attPreAmpTouch.reset(new SliderAttachment(
		valueTreeState,
		"idPreAmpTouch",
		preAmpGroup.sliderTouch.slider)
	);

	addAndMakeVisible(powerAmpGroup);
	attPowerAmpDrive.reset(new SliderAttachment(
		valueTreeState,
		"idPowerAmpDrive",
		powerAmpGroup.sliderDrive.slider)
	);
	attPowerAmpTouch.reset(new SliderAttachment(
		valueTreeState,
		"idPowerAmpTouch",
		powerAmpGroup.sliderTouch.slider)
	);

	addAndMakeVisible(stagingGroup);
	attGainStages.reset(new SliderAttachment(
		valueTreeState,
		"idGainStages",
		stagingGroup.sliderStages.slider)
	);
	attGainSlope.reset(new SliderAttachment(
		valueTreeState,
		"idGainSlope",
		stagingGroup.sliderSlope.slider)
	);
	attLowCut.reset(new SliderAttachment(
		valueTreeState,
		"idLowCut",
		stagingGroup.sliderFilter.slider)
	);

	addAndMakeVisible(toneStackGroup);
	attTsLow.reset(new SliderAttachment(
		valueTreeState,
		"idTsLow",
		toneStackGroup.sliderLow.slider)
	);
	attTsMid.reset(new SliderAttachment(
		valueTreeState,
		"idTsMid",
		toneStackGroup.sliderMid.slider)
	);
	attTsHigh.reset(new SliderAttachment(
		valueTreeState,
		"idTsHigh",
		toneStackGroup.sliderHigh.slider)
	);

	addAndMakeVisible(cabGroup);
	attCabOnOff.reset(new ButtonAttachment(
		valueTreeState,
		"idCabOnOff",
		cabGroup.buttonCabOnOff)
	);

	logoSvg = Drawable::createFromSVG(*XmlDocument::parse(BinaryData::logo_svg));


	const int padding = 64;
	const int spacing = 32;
	setSize(5 * 93 + 7 * 8 + spacing + 2 * padding, 3 * 128 + 2 * spacing + 2 * padding);
}

ResonantAmpAudioProcessorEditor::~ResonantAmpAudioProcessorEditor()
{
	setLookAndFeel(nullptr);
	processor.setMeterListenerIn(nullptr, 0);
	processor.setMeterListenerIn(nullptr, 1);
	processor.setMeterListenerOut(nullptr, 0);
	processor.setMeterListenerOut(nullptr, 1);
}

#define GROUP_DROP_SHADOW(n) \
auto n##ShadowPath = Path(); \
n##ShadowPath.addRoundedRectangle(n##Group.getBorderBounds(), 4.0f); \
n##ShadowPath.applyTransform(AffineTransform::translation( \
	(float)n##Group.getBounds().getTopLeft().getX(), \
	(float)n##Group.getBounds().getTopLeft().getY() \
)); \
auto n##Shadow = DropShadow(Colour::fromHSV(0.0f, 0.0f, 0.0f, 0.333f), 6, Point<int>(1, 1)); \
n##Shadow.drawForPath(g, n##ShadowPath); 

void ResonantAmpAudioProcessorEditor::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	g.drawImage(bgNoise, getLocalBounds().toFloat());

	const float height = 24.0f;
	const float padding = 16.0f;

	const float logoRatio = (float)logoSvg->getWidth() / (float)logoSvg->getHeight();
	const float logoWidth = logoRatio * height;
	const float logoX = getBounds().getRight() - padding - logoWidth;
	const float logoY = getBounds().getY() + padding;
	logoSvg->setTransformToFit(Rectangle<float>(logoX, logoY, logoWidth, height), RectanglePlacement::centred);
	logoSvg->draw(g, 1.0f);

	g.setColour(Colour::fromHSV(0.0f, 0.0f, 0.0f, 0.05f));
	g.fillPath(bgPattern);
	g.setColour(Colour::fromHSV(0.0f, 0.0f, 0.0f, 0.1f));
	g.strokePath(bgPattern, PathStrokeType(1.0f));

	GROUP_DROP_SHADOW(levels)
	GROUP_DROP_SHADOW(preAmp)
	GROUP_DROP_SHADOW(powerAmp)
	GROUP_DROP_SHADOW(staging)
	GROUP_DROP_SHADOW(toneStack)
}

void ResonantAmpAudioProcessorEditor::resized()
{
	const float lineThickness = 2.0f;

	int padding = 64;
	int spacing = 32;

	levelsGroup.setLineThickness(lineThickness);
	levelsGroup.setHeight(128);
	levelsGroup.setTopLeftPosition(padding, padding);

	cabGroup.setLineThickness(lineThickness);
	cabGroup.setHeight(128);
	cabGroup.setTopLeftPosition(spacing + levelsGroup.getRight(), padding);

	preAmpGroup.setLineThickness(lineThickness);
	preAmpGroup.setHeight(128);
	preAmpGroup.setTopLeftPosition(padding, spacing + levelsGroup.getBottom());

	powerAmpGroup.setLineThickness(lineThickness);
	powerAmpGroup.setHeight(128);
	powerAmpGroup.setTopLeftPosition(padding, spacing + preAmpGroup.getBottom());

	stagingGroup.setLineThickness(lineThickness);
	stagingGroup.setHeight(128);
	stagingGroup.setTopLeftPosition(preAmpGroup.getBounds().getTopRight() + Point<int>(spacing, 0));

	toneStackGroup.setLineThickness(lineThickness);
	toneStackGroup.setHeight(128);
	toneStackGroup.setTopLeftPosition(powerAmpGroup.getBounds().getTopRight() + Point<int>(spacing, 0));


	rng.setSeed(1234);

	auto noise = Image(
		Image::PixelFormat::ARGB,
		getWidth(),
		getHeight(),
		false
	);
	for (int i = 0; i < noise.getWidth(); i++)
		for (int j = 0; j < noise.getHeight(); j++)
			noise.setPixelAt(
				i, j,
				Colour::fromHSV(0.0f, 0.0f, 0.0f, rng.nextFloat() * 0.03f)
			);
	bgNoise = noise;

	rng.setSeed(3);

	const float patternScale = 24.0f;
	bgPattern.clear();
	Rectangle<float> element;
	element.setSize(patternScale * 0.8f, patternScale * 0.8f);
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			const float distance = 
				powf(((float)(i * i) + (float)(j * j)), 0.5f) 
				/ powf((float)(14*14 + 9*9), 0.5f);
			if (rng.nextFloat() < 0.3 + 0.7 * distance) continue;

			Point<float> corner(getLocalBounds().getBottomRight().toFloat());
			corner += Point<float>(-patternScale * (i + 0.5f), -patternScale * (j + 0.5f));
			corner += Point<float>(-patternScale / 2.0f, -patternScale / 2.0f);
			element.setPosition(corner);
			bgPattern.addRoundedRectangle(element, 2.0f);
		}
	}
}

#undef LAYOUT_GRID
