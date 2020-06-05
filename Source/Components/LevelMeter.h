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

typedef std::pair<float, String> MeterTick;
typedef std::vector<MeterTick> MeterTicks;

struct LevelMeterListener {
	virtual ~LevelMeterListener() {}
	virtual void update(float) = 0;
};

class LevelMeter : public Component, public LevelMeterListener, private Timer
{
public:
	LevelMeter();

	void paint(Graphics& g) override;
	void update(float db) override;

	void setRefreshRate(int /*refreshRateHz*/);
	void setDbLow(float /*db*/);
	void setDbHigh(float /*db*/);
	void setDecayTau(float /*tau*/);
	void setTicks(const MeterTicks& /*ticks*/);

	void setBarWidth(int /*width*/);
	void setBarHeight(int /*height*/);
	void setLabelWidth(int /*width*/);
	void setLabelHeight(float /*height*/);
	void setLabelGap(int /*width*/);
	void setLabelsOnRight(bool);

	float getLabelHeight() const;
	int getLabelWidth() const;

private:
	void timerCallback() override;
	float dbToLevel(float db) const;

	std::atomic<float> maxLevel;
	float level;
	float dbLow;
	float dbHigh;
	float decayTau;
	MeterTicks ticks;

	int barWidth;
	int labelWidth;
	float labelHeight;
	int labelGap;
	bool labelsOnRight;

	// disable setting the width
	using Component::setSize;
	using Component::setBounds;
	using Component::setBoundsRelative;
	using Component::setBoundsInset;
	using Component::setBoundsToFit;
	using Component::centreWithSize;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeter)
};
