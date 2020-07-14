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

    drift_level = nentry("tetrode_plate_drift_level", 0, -1, +1, .1) : uscale(-100, 100);
    drift_tau = nentry("tetrode_plate_drift_tau", 0, -1, +1, .1) : uscale(log(1e-3), log(1e+0)) : exp;
    drift_depth = nentry("tetrode_plate_drift_depth", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+1)) : exp;

    drift2_level = nentry("tetrode_plate_drift2_level", 0, -1, +1, .1) : uscale(-50, 50);
    drift2_depth = nentry("tetrode_plate_drift2_depth", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+1)) : exp;

    clip = nentry("tetrode_plate_clip", 0, -1, +1, 1) : uscale(10, 50);
    clip_corner = nentry("tetrode_plate_clip_corner", 0, -1, +1, 1) : uscale(log(1e-1), log(1e2)) : exp;
    
    comp_tau = nentry("tetrode_plate_comp_tau", 0, -1, +1, .1) : uscale(log(1e-3), log(1e+0)) : exp;
    comp_depth = nentry("tetrode_plate_comp_depth", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+1)) : exp;

    cross_corner = nentry("tetrode_plate_cross_corner", 0, -1, +1, 1) : uscale(log(1e-1), log(1e+2)) : exp;

    sag_toggle = nentry("tetrode_plate_sag_toggle", 0, -1, +1, .1) : uscale(0, 1);
    sag_depth = nentry("tetrode_plate_sag_depth", 0, -1, +1, .1) : uscale(log(1e-1), log(1e1)) : exp;
    sag_tau = nentry("tetrode_plate_sag_tau", 0, -1, +1, .1) : uscale(log(1e-2), log(5e-1)) : exp;
    sag_ratio = nentry("tetrode_plate_sag_ratio", 0, -1, +1, .1) : uscale(log(1e0), log(1e1)) : exp;
    sag_onset = nentry("tetrode_plate_sag_onset", 0, -1, +1, .1) : uscale(log(1e-1), log(1e1)) : exp;

    sag_tau1 = sag_tau : 1.0 / (ba.sec2samp(_) + 1.0);
    sag_tau2 = sag_tau * sag_ratio : 1.0 / (ba.sec2samp(_) + 1.0);

    nyquist = 1.0 / (2.0 * ba.samp2sec(1));
    hp_freq = nentry("tetrode_hp_freq", 0, -1, +1, .1) : uscale(log(1e1), log(1e2)) : exp : min(nyquist);
    lp_freq = nentry("tetrode_lp_freq", 0, -1, +1, .1) : uscale(log(5e3), log(15e3)) : exp : min(nyquist);

    // calculation of the power draw sag induced overhead reduction
    calc_comp_clip = _
        : /(clip)
        : abs
        : min(1.0)
        : si.smooth(ba.tau2pole(comp_tau))
        : clip * 1.0 / (1.0 + _ * comp_depth)
        : _;

    // This is the common process for both sides of the signal
    side = _ 
        // NOTE: power clip is correct here, but the results aren't impacted 
        // strongly but it, so omitted for simplicity

        // Bias drifting causing cross over distortion
        <: _, max(drift_level) - drift_level
        : _, si.smooth(ba.tau2pole(drift_tau)) * drift_depth
        : -

        // Clipping at the top of the waveform with a variable level
        <: calc_comp_clip, _
        : soft_clip_up(clip_corner)

        // Soften the cross over distortion edge
        : soft_clip_down(cross_corner, 0)

        : _;
    
    calc_sag_comp = _
        : /(clip)
        : abs
        <: min(1.0), max(1.0) - 1.0
        : sag_onset * _ + _
        : calc_charge(sag_tau1, sag_tau2)
        : 1.0 / (1.0  +  _ * sag_depth * sag_toggle)
        : _;
    
    // Combine both sides in push-pull fashion
    full = _
        : *(scale)
        <: _, _

        : _, (_ <: *(-1), _)
        : _, side, side
        : _, *(-1), _
        : _, +

        : calc_sag_comp, _
        : *
        : *(1.0 + sag_depth * sag_toggle)

        : fi.bandpass(1, hp_freq, lp_freq)

        // TODO: this is really only needed for fitting
        <: _, abs
        : _, max(drift2_level) - drift2_level
        : _, si.smooth(ba.tau2pole(drift_tau)) * drift2_depth * -1
        : -

        : _;
};