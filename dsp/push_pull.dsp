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
import("triode_grid.dsp");
import("triode_plate.dsp");
import("tetrode_grid.dsp");
import("tetrode_plate.dsp");
import("tonestack.dsp");
import("cabinet.dsp");

push_pull = push_pull
with {
    pre_drive_unit = nentry("pre_drive", 0, -1, +1, .1);
    pre_drive = pre_drive_unit : uscale(log(5e-1), log(5e2)) : exp;
    // Measured the loudness change as a function of the pre drive, this looks
    // up the correction for any drive
    unscale_pre = ba.listInterp((+4.85e+00,-1.17e+00,-7.12e+00,-1.27e+01,-1.75e+01,-2.02e+01,-2.15e+01,-2.21e+01,-2.26e+01,-2.29e+01,-2.31e+01), (pre_drive_unit + 1.0) / 2.0 * 10) : ba.db2linear; 

    power_drive_unit = nentry("power_drive", 0, -1, +1, .1);
    power_drive = power_drive_unit : uscale(log(1e-1), log(2e2)) : exp;
    unscale_power = ba.listInterp((+1.90e+01,+1.24e+01,+5.85e+00,-1.58e-01,-5.41e+00,-8.99e+00,-1.04e+01,-1.06e+01,-1.06e+01,-1.05e+01,-1.04e+01), (power_drive_unit + 1.0) / 2.0 * 10) : ba.db2linear;

    gain_stages = nentry("gain_stages", 0, -1, +1, .1);
    gain_slope = nentry("gain_slope", 0, -1, +1, .1) : uscale(0.5, 1.5);
    cab_on_off = nentry("cab_on_off", 0, -1, +1, .1);

    // How much of stages 2/3 to include in the mix
    stage_2_mix = max(0, min(2, gain_stages) - 1);
    // How much of stages 4/5 to include in the mix
    stage_3_mix = max(0, min(3, gain_stages) - 2);

    gain_stage = _
        : triode_grid 
        : triode_plate.full
        // The model fit to the signal includes the scale imparted by the amp
        // circuitry. But want only to keep the distortion, not the scaling.
        : /(triode_plate.scale)
        : _;

    power_stage = _
        // The incoming signal is unscaled, bring it up to the scale expected
        // as the input to the power amp
        : *(triode_plate.scale)

        : tetrode_grid.full
        : tetrode_plate.full

        // Bring the signal back to the same scale as the input
        : /(triode_plate.scale)
        // NOTE: the power amp leaves the signal at 0 bias and more or less
        // unscaled, so no need to correct further

        : _;

    push_pull = _
        // Drive the pre-map stage with this factor
        : *(pre_drive)

        // With no grain staging there is a single stage leading to vintage
        // sounding asymmetric tube distortion
        : gain_stage

        // Add gain stages in pairs so that the phase is correct when interpolating
        // and so that there is symmetric clipping at higher gains
        <: stage_2_mix, (*(gain_slope^1) : gain_stage : gain_stage : *(gain_slope^-1)), _ : mix_wet_dry
        <: stage_3_mix, (*(gain_slope^2) : gain_stage : gain_stage : *(gain_slope^-2)), _ : mix_wet_dry

        // Correct for the loudness resulting from the pre-drive
        : *(unscale_pre)

        : tone_stack

        : *(power_drive)
        : power_stage
        : *(unscale_power)

        <: ba.if(cab_on_off > 0, cab, _)

        : _;
};