/*
 *  Swanky Amp tube amplifier simulation
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

float angleModulo(float angle);

Image buildImageNoise(int width, int height, Random &rng, float alpha);

// commonly used in parameter groups that need to handle the size (e.g. to
// maintain an aspect ratio)
#define DISABLE_COMPONENT_RESIZE()                                             \
  using Component::setSize;                                                    \
  using Component::setBounds;                                                  \
  using Component::setBoundsRelative;                                          \
  using Component::setBoundsInset;                                             \
  using Component::setBoundsToFit;                                             \
  using Component::centreWithSize;
