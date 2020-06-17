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
#include "PluginProcessor.h"

#include "PluginEditor.h"

ResonantAmpAudioProcessorEditor::ResonantAmpAudioProcessorEditor(
	ResonantAmpAudioProcessor& p,
	AudioProcessorValueTreeState& vts)
	:
	AudioProcessorEditor(&p),
	processor(p),
	valueTreeState(vts)
{
	setLookAndFeel(&resonantAmpLAF);

	LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypeface(
		resonantAmpLAF.getDefaultFont().getTypeface()
	);

	processor.meterListenersIn[0] = ampGroup.levelsGroup.getLevelMeterListenerInL();
	processor.meterListenersIn[1] = ampGroup.levelsGroup.getLevelMeterListenerInR();
	processor.meterListenersOut[0] = ampGroup.levelsGroup.getLevelMeterListenerOutL();
	processor.meterListenersOut[1] = ampGroup.levelsGroup.getLevelMeterListenerOutR();

	ampGroup.attachVTS(vts);

	logoSvg = Drawable::createFromSVG(*XmlDocument::parse(BinaryData::logo_svg));

	addAndMakeVisible(ampGroup);

	setSize(800, 600);
}

#undef ATTACH_SLIDER

ResonantAmpAudioProcessorEditor::~ResonantAmpAudioProcessorEditor()
{
	// the LAF can be called from ... who knows where, after the Editor goes out
	// of scope
	setLookAndFeel(nullptr);
	// ensure the processor doesn't used cache pointers that were freed
	processor.meterListenersIn[0] = nullptr;
	processor.meterListenersIn[1] = nullptr;
	processor.meterListenersOut[0] = nullptr;
	processor.meterListenersOut[1] = nullptr;
}

void ResonantAmpAudioProcessorEditor::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	g.drawImage(bgNoise, getLocalBounds().toFloat());

	const float logoHeight = 24.0f;
	const float logoPadding = 16.0f;

	const float logoRatio = (float)logoSvg->getWidth() / (float)logoSvg->getHeight();
	const float logoWidth = logoRatio * logoHeight;
	const float logoX = getBounds().getRight() - logoPadding - logoWidth;
	const float logoY = getBounds().getY() + logoPadding;
	logoSvg->setTransformToFit(Rectangle<float>(logoX, logoY, logoWidth, logoHeight), RectanglePlacement::centred);
	logoSvg->draw(g, 1.0f);

	g.setColour(Colour::fromHSV(0.0f, 0.0f, 0.0f, 0.05f));
	g.fillPath(bgPattern);
	g.setColour(Colour::fromHSV(0.0f, 0.0f, 0.0f, 0.1f));
	g.strokePath(bgPattern, PathStrokeType(1.0f));
}

#undef GROUP_DROP_SHADOW

void ResonantAmpAudioProcessorEditor::buildBgPattern()
{
	bgPattern.clear();

	rng.setSeed(3);

	const float patternScale = 24.0f;
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

void ResonantAmpAudioProcessorEditor::resized()
{
	// build noise to texture background
	rng.setSeed(1234);
	bgNoise = buildImageNoise(getWidth(), getHeight(), rng, 0.05f);

	// rebuild on re-size to track bottom right corner, could be built once then
	// translated, but in future might want to re-scale as well
	buildBgPattern();

	ampGroup.setGroupsHeight(128);
	const int marginX = jmax(0, getWidth() - ampGroup.getWidth());
	const int marginY = jmax(0, getHeight() - ampGroup.getHeight());

	ampGroup.setTopLeftPosition(marginX / 2, marginY / 2);
}

