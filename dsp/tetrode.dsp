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

// API conventions:
//
// The `nentry` function is used by faust to construct a UI. But in this case 
// it is used to track which parameters should be exposed to the plugin.
// Variables aassigned from `nentry` get setters in the standalone header file.
//
// Assume the parameters will be given in the range (-1, +1), and scale them
// here to the appropriate value.

tetrode_grid = tetrode_grid
with {
    hp_freq = nentry("tetrode_hp_freq", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+2)) : exp;

    // Observed some soft compression in the upper part of the wave form like
    // with the triode (see `triode.dsp` for more).
    grid_tau = nentry("tetrode_grid_tau", 0, -1, +1, .1) : uscale(log(1e-5), log(1e-1)) : exp;
    grid_ratio = nentry("tetrode_grid_ratio", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+4)) : exp;
    grid_level = nentry("tetrode_grid_level", 0, -1, +1, .1) : uscale(-100, +100);

    // NOTE: the tetrode arrangement removes the more drastic compression seen
    // in the triode

    // Convert to `cap_comp` parameters
    grid_tau1 = grid_tau : 1.0 / (ba.sec2samp(_) + 1);
    grid_tau2 = grid_tau * grid_ratio : 1.0 / (ba.sec2samp(_) + 1);
    grid_tau3 = 1;

    // NOTE: the parameters are fit with input signal level that occurs after
    // pre-amp. But here we keep the signal normalized, so introuce a scale of
    // 20 to compensate

    tetrode_grid = _ 
        : *(20.0)
        : fi.highpass(1, hp_freq) 
        : cap_comp(grid_level, grid_tau1, grid_tau2, grid_tau3)
        : /(20.0)
        : _;
};

tetrode_plate = environment {
    // See `triode.dsp::triode_plate` for details on the parameters

    corner = nentry("tetrode_plate_corner", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+3)) : exp;
    clip = nentry("tetrode_plate_clip", 0, -1, +1, .1) : uscale(0, 75);

    level = nentry("tetrode_plate_level", 0, -1, +1, .1) : uscale(-100, +100);
    tau = nentry("tetrode_plate_tau", 0, -1, +1, .1) : uscale(log(1e-4), log(1e+0)) : exp;
    ratio = nentry("tetrode_plate_ratio", 0, -1, +1, .1) : uscale(log(1e-2), log(1e+2)) : exp;

    smooth = nentry("tetrode_plate_smooth", 0, -1, +1, .1) : uscale(log(1e-1), log(1e1)) : exp;

    tau1 = tau : 1.0 / (ba.sec2samp(_) + 1);
    tau2 = tau * ratio : 1.0 / (ba.sec2samp(_) + 1);

    // NOTE: the bottom of the signal isn't processed since this is for a
    // push pull amp, so that part of the signal is coming from another tube
    // with polarity inverted

    full = _ 
        : *(20.0)

        // there is some clipping the top of the waveform
        : soft_clip_up(corner, clip)

        // keep only the upper part of the signal
        : max(0)

        // accumulate drift from signal above level
        <: _, max(0, _ - level) 
        : _, calc_charge(tau1, tau2)
        // the drit biases the signal
        : -

        // effectively there is clipping at 0 since the waveform switches
        // over to the other tube, so smoothen that (this is the cross over
        // distortion)
        : soft_clip_down(smooth, 0)

        : /(20.0)
        : _;
};