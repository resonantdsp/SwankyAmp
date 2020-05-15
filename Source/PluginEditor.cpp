/*
 *  Resonant Amp tube amplifier simulation
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


#include "PluginProcessor.h"
#include "PluginEditor.h"

// initialize the editor members related to a VTS parameter and connect them
#define INIT_PARAMETER(n, l) \
slide##n.setSliderStyle(Slider::RotaryHorizontalVerticalDrag); \
slide##n.setTextBoxStyle(Slider::NoTextBox, true, 0, 0); \
addAndMakeVisible(slide##n); \
label##n.setText(l, dontSendNotification); \
label##n.setJustificationType(Justification::centred); \
addAndMakeVisible(label##n); \
att##n.reset(new SliderAttachment(valueTreeState, "id"#n, slide##n));

//==============================================================================
ResonantAmpAudioProcessorEditor::ResonantAmpAudioProcessorEditor(
	ResonantAmpAudioProcessor& p,
	AudioProcessorValueTreeState& vts) :
	AudioProcessorEditor(&p),
	processor(p),
	valueTreeState(vts),
	meter(30, 0.5f, -26.0f, +8.0f)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize (600, 500);

	INIT_PARAMETER(InputLevel, "Input Level")
	INIT_PARAMETER(OutputLevel, "Output Level")
	INIT_PARAMETER(PreDrive, "Pre Drive")
	INIT_PARAMETER(PowerDrive, "Power Drive")

	INIT_PARAMETER(TsLow, "Low")
	INIT_PARAMETER(TsMid, "Mid")
	INIT_PARAMETER(TsHigh, "High")

	INIT_PARAMETER(GainStages, "Gain Stages")
	INIT_PARAMETER(GainSlope, "Gain Slope")

	INIT_PARAMETER(LowCut, "Contour")
	INIT_PARAMETER(CabMix, "Cab Mix")

	INIT_PARAMETER(TriodeDynamic, "Pre Dyn.")
	INIT_PARAMETER(TriodeDistort, "Pre Dist.")

	INIT_PARAMETER(TetrodeDynamic, "Power Dyn.")
	INIT_PARAMETER(TetrodeDistort, "Power Dist.")

	processor.addMeterListener(*this);

	resized();
}

#undef INIT_PARAMETER

ResonantAmpAudioProcessorEditor::~ResonantAmpAudioProcessorEditor()
{
	processor.removeMeterListener(*this);
}

//==============================================================================
void ResonantAmpAudioProcessorEditor::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	g.setColour(Colours::white);
	g.setFont(15.0f);
}

void ResonantAmpAudioProcessorEditor::handleNewValue(int channel, float value)
{
	if (channel == 0) meter.update(value);
}

#define LAYOUT_GRID(n, c, r) \
slide##n.setBounds(inset + c * (knobSize + knobPad), inset + r * (knobSize + labelSize + knobPad), knobSize, knobSize); \
label##n.setBounds(inset + c * (knobSize + knobPad), inset + r * (knobSize + labelSize + knobPad) + knobSize, knobSize, labelSize);

void ResonantAmpAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	const float inset = 20;
	const float spacing = 20;
	const float knobSize = 80;
	const float textHeight = 15;
	const float knobPad = 10;
	const float labelSize = labelInputLevel.getFont().getHeight();

	meter.setBounds(inset + knobSize + knobPad - 20, inset + knobPad, 20, knobSize - 2 * knobPad);
	addAndMakeVisible(meter);

	LAYOUT_GRID(InputLevel, 1, 0)
	LAYOUT_GRID(OutputLevel, 2, 0)
	LAYOUT_GRID(PreDrive, 3, 0)
	LAYOUT_GRID(PowerDrive, 4, 0)

	LAYOUT_GRID(TsLow, 0, 1)
	LAYOUT_GRID(TsMid, 1, 1)
	LAYOUT_GRID(TsHigh, 2, 1)

	LAYOUT_GRID(GainStages, 0, 2)
	LAYOUT_GRID(GainSlope, 1, 2)

	LAYOUT_GRID(LowCut, 2, 2)
	LAYOUT_GRID(CabMix, 3, 2)

	LAYOUT_GRID(TriodeDynamic, 0, 3)
	LAYOUT_GRID(TriodeDistort, 1, 3)

	LAYOUT_GRID(TetrodeDynamic, 2, 3)
	LAYOUT_GRID(TetrodeDistort, 3, 3)
}

#undef LAYOUT_GRID
