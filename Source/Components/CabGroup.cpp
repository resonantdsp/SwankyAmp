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
#include "CabGroup.h"

CabGroup::CabGroup() :
	ParameterGroup("CABINET")
{
	addAndMakeVisible(buttonCabOnOff);
}

void CabGroup::setHeight(int height) {
	setSize(height, height);

	const int spacing = 12;
	const int innerHeight = getBorderBounds().getHeight() - 2 * spacing;

	buttonCabOnOff.setBounds(BorderSize<int>((int)(1.5f * (float)spacing)).subtractedFrom(getBorderBounds()));
}

