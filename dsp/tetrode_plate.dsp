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
import("common.dsp");

tetrode_plate = environment {
    // See `triode_plate.dsp` for more info on common functionality

    power = nentry("tetrode_plate_power", 0, -1, +1, 1) : uscale(1.0, 2.0);
    bias = nentry("tetrode_plate_bias", 0, -1, +1, 1) : uscale(-10, +10);

    scale = nentry("tetrode_plate_scale", 0, -1, +1, 1) : uscale(log(1e-2), log(1e2)) : exp;
    // The working point
    point = nentry("tetrode_plate_point", 0, -1, +1, 1) : uscale(0, 20);

    drift_level = nentry("tetrode_plate_drift_level", 0, -1, +1, .1) : uscale(-10, 10) : exp;
    drift_tau = nentry("tetrode_plate_drift_tau", 0, -1, +1, .1) : uscale(log(1e-3), log(1e+0)) : exp;
    drift_depth = nentry("tetrode_plate_drift_depth", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+1)) : exp;

    clip = nentry("tetrode_plate_clip", 0, -1, +1, 1) : uscale(10, 50);
    clip_corner = nentry("tetrode_plate_clip_corner", 0, -1, +1, 1) : uscale(log(1e-1), log(1e2)) : exp;
    
    comp_level = nentry("tetrode_plate_comp_level", 0, -1, +1, .1) : uscale(-100, +100);
    comp_tau = nentry("tetrode_plate_comp_tau", 0, -1, +1, .1) : uscale(log(1e-3), log(1e+0)) : exp;
    comp_ratio = nentry("tetrode_plate_comp_ratio", 0, -1, +1, .1) : uscale(log(1e0), log(1e+1)) : exp;
    comp_depth = nentry("tetrode_plate_comp_depth", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+1)) : exp;
    comp_tau1 = comp_tau : 1.0 / (ba.sec2samp(_) + 1);
    comp_tau2 = comp_tau * comp_ratio : 1.0 / (ba.sec2samp(_) + 1);

    cross_corner = nentry("tetrode_plate_cross_corner", 0, -1, +1, 1) : uscale(log(1e-1), log(1e+2)) : exp;

    // This is the common process for both sides of the signal
    side = _ 
        // NOTE: power clip is correct here, but the results aren't impacted 
        // strongly but it, so omitted for simplicity

        // Bias drifting causing cross over distortion
        <: _, max(drift_level) - drift_level
        : _, si.smooth(ba.tau2pole(drift_tau)) * drift_depth
        : -

        // Clipping at the top of the waveform with a variable level
        <: max(comp_level) - comp_level, _
        : calc_charge(comp_tau1, comp_tau2) * -1 * comp_depth + clip, _
        : soft_clip_up(clip_corner)

        // Soften the cross over distortion edge
        : soft_clip_down(cross_corner, 0)

        : _;
    
    // Combine both sides in push-pull fashion
    full = _
        : *(scale)
        <: *(-1), _
        : side, side
        : *(-1), _
        : +
        : _;
};