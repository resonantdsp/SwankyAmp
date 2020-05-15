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

#pragma once

#include <JuceHeader.h>
#include "LevelMeter.h"

LevelMeter::LevelMeter(int refreshRateHz, float decayTau, float dbLow, float dbHigh) :
	dbLow(dbLow),
	dbHigh(dbHigh),
	// want factor^refreshes = 0.5, where refreshes in the number of refreshes 
	// to reach the decay tau, i.e. in decayRate the value drops by 0.5
	decayFactor(std::powf(0.5, 1.0f / (decayTau * (float)refreshRateHz)))
{
	startTimerHz(refreshRateHz);
}

float LevelMeter::dbToLevel(float db) const
{
	return jmax(db - dbLow, 0.0f) / (dbHigh - dbLow);
}

void LevelMeter::paint(Graphics& g)
{
	g.fillAll(Colours::transparentBlack);

	const float singleCoilLevel = dbToLevel(-16.5);
	const float humbuckerLevel = dbToLevel(-2.5);

	const auto bounds = g.getClipBounds();

	const auto area_bar = Rectangle<float>(
		(float)(bounds.getX() + 10),
		(float)(bounds.getY()),
		(float)(bounds.getWidth() - 10),
		(float)(bounds.getHeight())
	);
	g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));
	g.fillRoundedRectangle(area_bar, 2.0);

	g.setColour(Colours::white);
	const auto singleBox = Rectangle<float>(
		0.0f,
		(1.0f - singleCoilLevel) * (float)bounds.getHeight() - 10.0f / 2.0f,
		8.0f,
		10.0f
	);
	g.drawText("S", singleBox, Justification::centredRight);
	const auto humbuckerBox = Rectangle<float>(
		0.0f,
		(1.0f - humbuckerLevel) * (float)bounds.getHeight() - 10.0f / 2.0f,
		8.0f,
		10.0f
	);
	g.drawText("H", humbuckerBox, Justification::centredRight);

	const auto unfilledHeight = bounds.getHeight() * (1.0 - level);
	g.reduceClipRegion(
		bounds.getX(),
		bounds.getY(),
		bounds.getWidth(),
		(int) unfilledHeight
	);
	g.setColour(getLookAndFeel().findColour(Slider::trackColourId));
	g.fillRoundedRectangle(area_bar, 2.0);

	g.restoreState();
	g.setColour(getLookAndFeel().findColour(Slider::trackColourId));

	const auto singleLine = Rectangle<float>(
		(float)bounds.getX() + 10.0f,
		(1.0f - singleCoilLevel) * (float)bounds.getHeight() + (float)bounds.getY() - 1.0f,
		10.0f,
		2.0f
	);
	g.fillRect(singleLine);

	const auto humbuckerLine = Rectangle<float>(
		(float)bounds.getX() + 10.0f,
		(1.0f - humbuckerLevel) * (float)bounds.getHeight() + (float)bounds.getY() - 1.0f,
		10.0f,
		2.0f
	);
	g.fillRect(humbuckerLine);
}

//==============================================================================
// Called from the audio thread.
void LevelMeter::update(float db)
{
	// We don't care if maxLevel gets set to zero (in timerCallback) between the
	// load and the assignment.
	maxLevel = jmax(maxLevel.load(), dbToLevel(db));
}

void LevelMeter::timerCallback()
{
	auto callbackLevel = maxLevel.exchange(0.0);

	if (callbackLevel > level)
		level = callbackLevel;
	else if (level > 1e-3)
		level *= decayFactor;
	else
		level = 0;

	repaint();
}
