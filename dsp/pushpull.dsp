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
import("triode.dsp");
import("tetrode.dsp");
import("tonestack.dsp");
import("cabinet.dsp");

// API conventions:
//
// The `nentry` function is used by faust to construct a UI. But in this case 
// it is used to track which parameters should be exposed to the plugin.
// Variables aassigned from `nentry` get setters in the standalone header file.
//
// Assume the parameters will be given in the range (-1, +1), and scale them
// here to the appropriate value.

pushpull = pushpull
with {
    pre_drive = nentry("pre_drive", 0, -1, +1, .1) <: ba.if(_ <= -1, 1e-1, uscale(log(1e0), log(1e2)) : exp);
    power_drive = nentry("power_drive", 0, -1, +1, .1) : uscale(log(1e-1), log(1e2)) : exp;
    gain_stages = nentry("gain_stages", 0, -1, +1, .1);
    gain_slope = nentry("gain_slope", 0, -1, +1, .1) : uscale(0.7, 1.3);
    cab_mix = nentry("cab_mix", 0, -1, +1, .1);

    // effective range of the triode, amplitudes beyond this will be compressed
    triode_range = (triode_plate.bias - triode_plate.clip) / 2.0;
    // likewise for the tetrode, but this is per side of the waveform as it clips
    // in both sides (so no factor of 2)
    tetrode_range = tetrode_plate.clip;

    // remove signal scaling from the pre-amp section, but if the signal was scaled
    // beyond the triode range, then it won't output anything more so just remove
    // that constant factor
    pre_unscale = 1 / min(triode_range, pre_drive);

    // likewise for the power-amp section, but in this case after the compression
    // starts to reduce the loudness much later
    power_uuscale = 1 / min(tetrode_range / 6, power_drive);

    // how much of stage 2 to include in the mix
    stage_2_mix = max(0, min(2, gain_stages) - 1);
    // ...
    stage_3_mix = max(0, min(3, gain_stages) - 2);
    stage_4_mix = max(0, min(4, gain_stages) - 3);

    gain_stage = _
        : *(pre_drive)
        : triode_grid 
        : triode_plate.full
        : *(pre_unscale)
        : _;

    gain_stage_simplified = _
        : *(pre_drive)
        : triode_plate.simplified
        : *(pre_unscale)
        : _;

    power_stage = _
        : *(power_drive)
        <: _, -1 * _ 
        : tetrode_grid, tetrode_grid 
        : tetrode_plate.full, tetrode_plate.full
        : _ + -1 * _
        : *(power_uuscale)
        : _;

    pushpull = _
        // with no grain staging there is a single stage leading to vintage
        // sounding asymmetric tube distortion
        : gain_stage

        // add gain stages in pairs so that the phase is correct when interpolating
        // and so that there is symmetric clipping at higher gains
        <: stage_2_mix, (*(gain_slope^1) : gain_stage : gain_stage : *(gain_slope^-1)), _ : mix_wet_dry
        <: stage_3_mix, (*(gain_slope^2) : gain_stage_simplified : gain_stage_simplified : *(gain_slope^-2)), _ : mix_wet_dry
        <: stage_4_mix, (*(gain_slope^3) : gain_stage_simplified : gain_stage_simplified : *(gain_slope^-3)), _ : mix_wet_dry

        : tone_stack

        : power_stage

        <: cab_mix, cab, _ : mix_wet_dry

        // gain stages seem to add to loudness
        : *(ba.db2linear(-gain_stages * 3))

        : _;
};