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
import("triode_grid.dsp");
import("triode_plate.dsp");
import("tetrode_grid.dsp");
import("tetrode_plate.dsp");
import("tone_stack.dsp");
import("cabinet.dsp");

push_pull = push_pull
with {
    pre_drive_unit = nentry("pre_drive", 0, -1, +1, .1);
    pre_drive = pre_drive_unit : uscale(log(1e0), log(2e3)) : exp;
    // Measured the loudness change as a function of the pre drive, this looks
    // up the correction for any drive
    unscale_pre = ba.listInterp((+1.37e+01,+7.11e+00,+5.36e-01,-6.01e+00,-1.26e+01,-1.76e+01,-2.04e+01,-2.17e+01,-2.21e+01,-2.24e+01,-2.28e+01), (pre_drive_unit + 1.0) / 2.0 * 10) : ba.db2linear;

    power_drive_unit = nentry("power_drive", 0, -1, +1, .1);
    power_drive = power_drive_unit : uscale(log(5e-1), log(5e2)) : exp;
    unscale_power = ba.listInterp((+5.27e+00,-3.19e-01,-5.60e+00,-1.10e+01,-1.64e+01,-1.96e+01,-2.07e+01,-2.09e+01,-2.08e+01,-2.08e+01,-2.07e+01), (power_drive_unit + 1.0) / 2.0 * 10) : ba.db2linear;

    gain_stages = nentry("gain_stages", 0, -1, +1, .1);
    gain_slope = nentry("gain_slope", 0, -1, +1, .1) : uscale(0.5, 1.5);
    cab_on_off = nentry("cab_on_off", 0, -1, +1, .1);

    // when stages is between 1 and 3, turn that into a mix from 0 to 1
    stage_2_mix = max(0, min(3, gain_stages) - 1) / 2.0;
    // likewise for the range 3 to 5
    stage_3_mix = max(0, min(5, gain_stages) - 3) / 2.0;
    // likewise for the range 5 to 7
    stage_4_mix = max(0, min(7, gain_stages) - 5) / 2.0;

    rvalues = (1.08, 0.81, 0.99, 1.08, 0.86, 0.89, 0.89, 0.96, 1.28, 1.02, 0.86, 0.92, 0.99, 0.94, 0.89, 0.96, 0.98, 0.94, 1.09, 0.95, 1.11, 0.96, 0.97, 1.00, 0.89, 0.95, 1.13, 1.17, 0.88, 0.88, 1.18, 0.91);
    rvalue(i) = rvalues : ba.selectn(32, i % 32);

    triode_grid_1 = triode_grid[
        hp_freq = triode_grid.hp_freq * rvalue(0);
        grid_tau = triode_grid.grid_tau * rvalue(1);
        grid_ratio = triode_grid.grid_ratio * rvalue(2);
        grid_smooth = triode_grid.grid_smooth * rvalue(3);
        grid_level = triode_grid.grid_level * rvalue(4);
        grid_clip = triode_grid.grid_clip * rvalue(5);
    ].full;

    triode_grid_2 = triode_grid[
        hp_freq = triode_grid.hp_freq * rvalue(10);
        grid_tau = triode_grid.grid_tau * rvalue(11);
        grid_ratio = triode_grid.grid_ratio * rvalue(12);
        grid_smooth = triode_grid.grid_smooth * rvalue(13);
        grid_level = triode_grid.grid_level * rvalue(14);
        grid_clip = triode_grid.grid_clip * rvalue(15);
    ].full;

    triode_grid_3 = triode_grid[
        hp_freq = triode_grid.hp_freq * rvalue(20);
        grid_tau = triode_grid.grid_tau * rvalue(21);
        grid_ratio = triode_grid.grid_ratio * rvalue(22);
        grid_smooth = triode_grid.grid_smooth * rvalue(23);
        grid_level = triode_grid.grid_level * rvalue(24);
        grid_clip = triode_grid.grid_clip * rvalue(25);
    ].full;

    triode_plate_1 = triode_plate[
        bias = triode_plate.bias * rvalue(0);
        scale = triode_plate.scale * rvalue(1);
        clip = triode_plate.clip * rvalue(2);
        drift_level = triode_plate.drift_level * rvalue(3);
        drift_tau = triode_plate.drift_tau * rvalue(4);
        comp_level = triode_plate.comp_level * rvalue(5);
        comp_tau = triode_plate.comp_tau * rvalue(6);
        comp_ratio = triode_plate.comp_ratio * rvalue(7);
    ].full;

    triode_plate_2 = triode_plate[
        bias = triode_plate.bias * rvalue(10);
        scale = triode_plate.scale * rvalue(11);
        clip = triode_plate.clip * rvalue(12);
        drift_level = triode_plate.drift_level * rvalue(13);
        drift_tau = triode_plate.drift_tau * rvalue(14);
        comp_level = triode_plate.comp_level * rvalue(15);
        comp_tau = triode_plate.comp_tau * rvalue(16);
        comp_ratio = triode_plate.comp_ratio * rvalue(17);
    ].full;

    triode_plate_3 = triode_plate[
        bias = triode_plate.bias * rvalue(20);
        scale = triode_plate.scale * rvalue(21);
        clip = triode_plate.clip * rvalue(22);
        drift_level = triode_plate.drift_level * rvalue(23);
        drift_tau = triode_plate.drift_tau * rvalue(24);
        comp_level = triode_plate.comp_level * rvalue(25);
        comp_tau = triode_plate.comp_tau * rvalue(26);
        comp_ratio = triode_plate.comp_ratio * rvalue(27);
    ].full;
    
    gain_stage_1 = _
        : triode_grid_1
        : triode_plate_1
        : /(triode_plate.scale)
        : _;

    gain_stage_2 = _
        : triode_grid_2
        : triode_plate_2
        : /(triode_plate.scale)
        : _;

    gain_stage_3 = _
        : triode_grid_3
        : triode_plate_3
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
        : gain_stage_1

        // Add gain stages in pairs so that the phase is correct when interpolating
        // and so that there is symmetric clipping at higher gains
        <: stage_2_mix, (*(gain_slope^1) : gain_stage_2 : gain_stage_3 : *(gain_slope^-1)), _ : mix_wet_dry
        <: stage_3_mix, (*(gain_slope^2) : gain_stage_1 : gain_stage_2 : *(gain_slope^-2)), _ : mix_wet_dry
        <: stage_4_mix, (*(gain_slope^3) : gain_stage_3 : gain_stage_1 : *(gain_slope^-3)), _ : mix_wet_dry

        : tone_stack

        : *(unscale_pre)

        : *(power_drive)
        : power_stage

        <: ba.if(cab_on_off > 0, cab, _)

        : *(unscale_power)

        : _;
};