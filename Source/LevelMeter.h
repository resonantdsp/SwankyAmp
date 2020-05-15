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

class LevelMeter : public Component, private Timer
{
public:
	LevelMeter(int, float, float, float);

	void paint(Graphics& g) override;
	void resized() override {}
	void update(float db);

	struct Listener
	{
		virtual ~Listener() {}
		virtual void handleNewValue(int, float) = 0;
	};

private:
	//==============================================================================
	void timerCallback() override;
	float dbToLevel(float db) const;

	std::atomic<float> maxLevel {0.0};
	float level = 0;
	const float dbLow;
	const float dbHigh;
	const float decayFactor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeter)
};
