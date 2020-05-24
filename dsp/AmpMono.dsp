//  Resonant Amp tube amplifier simulation
//  Copyright (C) 2020  Garrin McGoldrick
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.

import("stdfaust.lib");
import("push_pull.dsp");

// API conventions:
//
// The `nentry` function is used by faust to construct a UI. But in this case 
// it is used to track which parameters should be exposed to the plugin.
// Variables aassigned from `nentry` get setters in the standalone header file.
//
// Assume the parameters will be given in the range (-1, +1), and scale them
// here to the appropriate value.

// Unit scaling:
// * Assume single the peak voltage is around 150 mV for a single coil pickup,
//   and around 750 mV for a humbucker.
// * Thus, the peak dB FS for a strummed chord-like signal with peak voltage x:
//   20 * log10(x)
// * A single coild pickup should have a peak dB FS around -16.5
// * A humbucker should be around -2.5
// http://tomsguitarprojects.blogspot.com/2014/12/electric-guitar-output-voltage-levels.html

input_level = nentry("input_level", 0, -1, +1, .1) : uscale(-35, +35) : ba.db2linear;
output_level = nentry("output_level", 0, -1, +1, .1) : uscale(-35, +35) : ba.db2linear;

process = _
    : *(input_level)
    : push_pull
    : *(output_level)
    // Drive correction increases the volume, correct for that
    //: *(ba.db2linear(-6.0))
    : _;
