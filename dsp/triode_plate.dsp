//  Swanky Amp tube amplifier simulation
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
import("common.dsp");

// API conventions:
//
// The `nentry` function is used by faust to construct a UI. But in this case 
// it is used to track which parameters should be exposed to the plugin.
// Variables aassigned from `nentry` get setters in the standalone header file.
//
// Assume the parameters will be given in the range (-1, +1), and scale them
// here to the appropriate value.

triode_plate = environment {
    bias = nentry("triode_plate_bias", 0, -1, +1, .1) : uscale(-100, +100);
    bias_corner = nentry("triode_plate_bias_corner", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+3)) : exp;

    scale = nentry("triode_plate_scale", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+1)) : exp;

    clip = nentry("triode_plate_clip", 0, -1, +1, .1) : uscale(-100, +100);
    corner = nentry("triode_plate_corner", 0, -1, +1, .1) : uscale(log(1e-2), log(1e+2)) : exp;

    drift_level = nentry("triode_plate_drift_level", 0, -1, +1, .1) : uscale(-100, +100);
    drift_tau = nentry("triode_plate_drift_tau", 0, -1, +1, .1) : uscale(log(1e-3), log(1e+0)) : exp;
    drift_depth = nentry("triode_plate_drift_depth", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+1)) : exp;

    comp_level = nentry("triode_plate_comp_level", 0, -1, +1, .1) : uscale(-100, +100);
    comp_tau = nentry("triode_plate_comp_tau", 0, -1, +1, .1) : uscale(log(1e-3), log(1e+0)) : exp;
    comp_ratio = nentry("triode_plate_comp_ratio", 0, -1, +1, .1) : uscale(log(1e0), log(1e+1)) : exp;
    comp_depth = nentry("triode_plate_comp_depth", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+1)) : exp;
    
    comp_tau1 = comp_tau : 1.0 / (ba.sec2samp(_) + 1);
    comp_tau2 = comp_tau * comp_ratio : 1.0 / (ba.sec2samp(_) + 1);

    comp_corner = nentry("triode_plate_comp_corner", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+2)) : exp;
    comp_offset = nentry("triode_plate_comp_offset", 0, -1, +1, .1) : uscale(-100, +100);

    nyquist = 1.0 / (2.0 * ba.samp2sec(1));
    lp_freq = nentry("triode_lp_freq", 0, -1, +1, .1) : uscale(log(5e3), log(15e3)) : exp : min(nyquist);

    full = _ 
        // found the fit works better with just a scale and a clip instead of
        // the full 1.5 power law treatement
        : *(scale)
        : soft_clip_down(bias_corner, -bias)

        // wave form is inverted on plate, easier to set defaults this way
        : *(-1)

        : soft_clip_down(corner, clip)

        <: _, max(drift_level) - drift_level
        : _, si.smooth(ba.tau2pole(drift_tau)) * drift_depth
        : -

        <: max(comp_level) - comp_level, _
        : calc_charge(comp_tau1, comp_tau2) * comp_depth + comp_offset, _
        // NOTE: the clip level is relative to zero
        : soft_clip_up(comp_corner)

        : fi.lowpass(1, lp_freq)

        : _;
};