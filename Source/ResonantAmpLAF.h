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

class ResonantAmpLAF : public LookAndFeel_V4
{
public:
	ResonantAmpLAF();

	// Font size conversions (for 96 dpi):
	// 12pt/16px
	// 14/18.667px
	// 16/21.333px
	// 18/24px
	// 22/29.333px
	// 24/32px

	static const Font& getDefaultFont();
	static const Font& getDefaultFontNarrow();
	static const Font& getDefaultFontBold();

	static const Colour colourDark;
	static const Colour colourGrey;
	static const Colour colourBackground;
	static const Colour colourHighlight;
	static const Colour colourSteel;

	static const DropShadow& getDropShadow();

	static Path getSaveIconPath(float d);
	static Path getRemoveIconPath(float d);

	Path getTickShape(float height) override;
	Slider::SliderLayout getSliderLayout(Slider& slider) override;

	void drawRotarySlider(
		Graphics& g,
		int x,
		int y,
		int width,
		int height,
		float sliderPos,
		const float rotaryStartAngle,
		const float rotaryEndAngle,
		Slider& slider
	) override;

	void drawToggleButton(
		Graphics& g,
		ToggleButton& button,
		bool shouldDrawButtonAsHighlighted,
		bool shouldDrawButtonAsDown
	) override;

	void drawComboBox(
		Graphics& g,
		int width,
		int height,
		bool, int, int, int, int,
		ComboBox& box
	) override;
};

