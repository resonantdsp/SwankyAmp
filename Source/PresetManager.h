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
#include <unordered_map>
#include <optional>

#include "PluginProcessor.h"

using SerializedState = std::unique_ptr<XmlElement>;

struct StateEntry
{
	StateEntry(
		size_t order,
		const String& name,
		File file,
		std::optional<size_t> stateIdx);
	StateEntry() {}

	size_t order = 0;
	String name;
	File file;
	std::optional<size_t> stateIdx = std::nullopt;
};

/** Connects a value tree state to a combo box and preset directory. */
class PresetManager : public AudioProcessorValueTreeState::Listener
{
public:
    PresetManager(
		ResonantAmpAudioProcessor& processor,
		AudioProcessorValueTreeState& vts,
		ComboBox& comboBox,
		Button& bntSave,
		Button& bntRemove
	);
    ~PresetManager();

	void comboBoxChanged();
	void buttonSaveClicked();
	void buttonRemoveClicked();
	void parameterChanged(const String& id, float newValue);

	const std::vector<String>& getParameterIds() const { return parameterIds; }

	void setState(const SerializedState& state);

private:
	void loadPreset(SerializedState state, File file, const String& name);
	void loadFactoryPresets();
	void loadPresetsFromDir();
	void loadPresetsFromMaster();

	void clearUI();
	void updateComboBox();
	void updatePresetMaster();

	ResonantAmpAudioProcessor& processor;
    AudioProcessorValueTreeState& vts;
	ComboBox& comboBox;
	Button& buttonSave;
	Button& buttonRemove;
	File presetDir;
	File presetMaster;

	std::vector<String> parameterIds;

	StateEntry* currentEntry = nullptr;
	std::unordered_map<String, StateEntry> stateEntries;
	std::vector<SerializedState> states;
	size_t nextOrderValue = 0;
};
