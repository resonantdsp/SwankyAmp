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

#include "Utils.h"

float angleModulo(float angle)
{
	const float modulo = fmodf(angle, MathConstants<float>::twoPi);
	if (modulo > MathConstants<float>::pi)
		return modulo - MathConstants<float>::twoPi;
	else
		return modulo;
}

void fillImageNoise(Image& image, Random& rng, float alpha)
{
	if (image.getFormat() != Image::PixelFormat::ARGB)
		image.convertedToFormat(Image::PixelFormat::ARGB);
	for (int i = 0; i < image.getWidth(); i++)
		for (int j = 0; j < image.getHeight(); j++)
			image.setPixelAt(
				i, j,
				Colour::fromHSV(0.0f, 0.0f, 0.0f, rng.nextFloat() * alpha)
			);
}

Image buildImageNoise(int width, int height, Random& rng, float alpha)
{
	Image noise(Image::PixelFormat::ARGB, width, height, false);
	fillImageNoise(noise, rng, alpha);
	return noise;
}
