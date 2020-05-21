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

tetrode_grid = environment {
    // See `triode_grid.dsp` for info on common functionality

    hp_freq = nentry("tetrode_hp_freq", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+2)) : exp;

    // The highpass applies to the signal with some DC offset, leading to some
    // dynamics as the DC offset is being subtracted, want to preserve those
    // early dyanamics
    offset1 = nentry("tetrode_grid_offset1", 0, -1, +1, 1) : uscale(0, 500);

    // This offset affects how much signal is being accumulated into the 
    // smoothing
    offset2 = nentry("tetrode_grid_offset2", 0, -1, +1, 1) : uscale(0, 500);

    // Smoothing time constant
    taus = nentry("tetrode_grid_taus", 0, -1, +1, 1) : uscale(log(1e-4), log(1e0)) : exp;

    level = nentry("tetrode_grid_level", 0, -1, +1, .1) : uscale(-100, +100);
    tau = nentry("tetrode_grid_tau", 0, -1, +1, .1) : uscale(log(1e-4), log(1e+0)) : exp;
    ratio = nentry("tetrode_grid_ratio", 0, -1, +1, .1) : uscale(log(1e-2), log(1e+2)) : exp;

    tau1 = tau : 1.0 / (ba.sec2samp(_) + 1);
    tau2 = tau * ratio : 1.0 / (ba.sec2samp(_) + 1);

    full = _ 
        : -(offset1)
        : fi.highpass(1, hp_freq) 

        // The difference between the grid input and output looks like an
        // exponentially smoothed version of the signal, subtracting this
        // then recovers the correct result, seems relted to the drift on
        // the screen
        : -(offset2)
        <: _, si.smooth(ba.tau2pole(taus)) : -

        // Same effect observed with the triode grid signal
        : cap_comp(level, tau1, tau2, 1.0)

        : _;
};
