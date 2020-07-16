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
#include "LevelMeter.h"
#include "ParameterGroup.h"
#include "PresetGroup.h"

PresetGroup::PresetGroup() :
	buttonSave("presetGroupButtonSave", DrawableButton::ButtonStyle::ImageFitted),
	buttonRemove("presetGroupButtonRemove", DrawableButton::ButtonStyle::ImageFitted),
	buttonNext("presetGroupButtonNext", DrawableButton::ButtonStyle::ImageFitted),
	buttonPrev("presetGroupButtonPrev", DrawableButton::ButtonStyle::ImageFitted)
{
	presetSelector.setEditableText(true);
	addAndMakeVisible(presetSelector);

	saveIcon.setFill(Colours::transparentBlack);
	saveIcon.setStrokeFill(ResonantAmpLAF::colourDark);
	saveIconHighlight.setFill(Colours::transparentBlack);
	saveIconHighlight.setStrokeFill(ResonantAmpLAF::colourHighlight);
	addAndMakeVisible(buttonSave);

	removeIcon.setFill(Colours::transparentBlack);
	removeIcon.setStrokeFill(ResonantAmpLAF::colourDark);
	removeIconHighlight.setFill(Colours::transparentBlack);
	removeIconHighlight.setStrokeFill(ResonantAmpLAF::colourHighlight);
	addAndMakeVisible(buttonRemove);

	nextIcon.setFill(Colours::transparentBlack);
	nextIcon.setStrokeFill(ResonantAmpLAF::colourDark);
	nextIconHighlight.setFill(Colours::transparentBlack);
	nextIconHighlight.setStrokeFill(ResonantAmpLAF::colourHighlight);
	addAndMakeVisible(buttonNext);

	prevIcon.setFill(Colours::transparentBlack);
	prevIcon.setStrokeFill(ResonantAmpLAF::colourDark);
	prevIconHighlight.setFill(Colours::transparentBlack);
	prevIconHighlight.setStrokeFill(ResonantAmpLAF::colourHighlight);
	addAndMakeVisible(buttonPrev);
}

void PresetGroup::paint(Graphics& g)
{
	// skip the group paint to avoid drawing border
	Component::paint(g);
}

void PresetGroup::resized()
{
	ParameterGroup::resized();
	presetSelector.setTopLeftPosition(0, 0);
	presetSelector.setSize(getHeight() * 8, getHeight());

	saveIcon.setPath(ResonantAmpLAF::getSaveIconPath((float)getHeight()));
	saveIcon.setStrokeType(PathStrokeType(3.0f));
	saveIconHighlight.setStrokeType(PathStrokeType(3.0f));
	saveIconHighlight.setPath(ResonantAmpLAF::getSaveIconPath((float)getHeight()));
	buttonSave.setImages(&saveIcon, &saveIconHighlight);

	buttonSave.setSize(getHeight(), getHeight());
	buttonSave.setTopLeftPosition(presetSelector.getBounds().getTopRight() + Point<int>(spacing, 0));

	removeIcon.setPath(ResonantAmpLAF::getRemoveIconPath((float)getHeight()));
	removeIcon.setStrokeType(PathStrokeType(3.0f));
	removeIconHighlight.setStrokeType(PathStrokeType(3.0f));
	removeIconHighlight.setPath(ResonantAmpLAF::getRemoveIconPath((float)getHeight()));
	buttonRemove.setImages(&removeIcon, &removeIconHighlight);

	buttonRemove.setSize(getHeight(), getHeight());
	buttonRemove.setTopLeftPosition(buttonSave.getBounds().getTopRight() + Point<int>(jmax(1, spacing / 2), 0));

	prevIcon.setPath(ResonantAmpLAF::getPrevIconPath((float)getHeight()));
	prevIcon.setStrokeType(PathStrokeType(3.0f));
	prevIconHighlight.setStrokeType(PathStrokeType(3.0f));
	prevIconHighlight.setPath(ResonantAmpLAF::getPrevIconPath((float)getHeight()));
	buttonPrev.setImages(&prevIcon, &prevIconHighlight);

	buttonPrev.setSize(getHeight(), getHeight());
	buttonPrev.setTopLeftPosition(buttonRemove.getBounds().getTopRight() + Point<int>(jmax(1, spacing / 2), 0));

	nextIcon.setPath(ResonantAmpLAF::getNextIconPath((float)getHeight()));
	nextIcon.setStrokeType(PathStrokeType(3.0f));
	nextIconHighlight.setStrokeType(PathStrokeType(3.0f));
	nextIconHighlight.setPath(ResonantAmpLAF::getNextIconPath((float)getHeight()));
	buttonNext.setImages(&nextIcon, &nextIconHighlight);

	buttonNext.setSize(getHeight(), getHeight());
	buttonNext.setTopLeftPosition(buttonPrev.getBounds().getTopRight() + Point<int>(jmax(1, spacing / 2), 0));

	setSize(buttonNext.getRight(), getHeight());
}

