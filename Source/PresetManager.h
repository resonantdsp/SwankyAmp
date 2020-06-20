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

#pragma once

#include <JuceHeader.h>

using SerializedState = std::unique_ptr<XmlElement>;

/** Connects a value tree state to a combo box and preset directory. */
class PresetManager : public ComboBox::Listener, Button::Listener
{
public:
    PresetManager(AudioProcessorValueTreeState& vts, ComboBox& comboBox, Button* saveButton);
    ~PresetManager() {}

	void comboBoxChanged(ComboBox* pComboBox) override;
	void buttonClicked(Button* button) override;

	bool setState(const SerializedState& state);

private:
	int addPreset(
		const String& name,
		SerializedState state
	);

	void savePreset(
		const String& name,
		const SerializedState& state
	);

    AudioProcessorValueTreeState& vts;
	const ValueTree& initState;
	ComboBox& comboBox;
	File presetDir;

	std::vector<Identifier> parameterIds;
	String currentName = "";
	int currentIdx = -1;

	std::vector<SerializedState> states;
	// map a state name to its index in the states vector
	HashMap<String, size_t> map;
};
