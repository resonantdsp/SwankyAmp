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

#include "PresetManager.h"
#include "Components/PresetGroup.h"

using PresetOrder = std::tuple<int, String, size_t>;

std::vector<Identifier> getParameterIds(const SerializedState& state)
{
	std::vector<Identifier> parameterIds;

	XmlElement* element = state->getFirstChildElement();

	while (element != nullptr)
	{
		if (
			element->getTagName() == "PARAM"
			&& element->hasAttribute("id"))
		{
			const String& id = element->getStringAttribute("id");
			parameterIds.push_back(Identifier(id));
		}

		element = element->getNextElement();
	}

	return parameterIds;
}

void loadPreset(
	std::vector<PresetOrder>& order,
	std::vector<SerializedState>& states,
	SerializedState state)
{
	const String& name = state->getStringAttribute("presetName");
	const int orderValue =
		state->hasAttribute("presetOrder") 
		? state->getIntAttribute("presetOrder") 
		: INT_MAX;

	order.push_back(std::make_tuple(orderValue, name, states.size()));
	states.push_back(std::move(state));
}

void loadPresetsFromXml(
	std::vector<PresetOrder>& order,
	std::vector<SerializedState>& states,
	const std::unique_ptr<XmlElement>& xml,
	const Identifier& stateType)
{
	XmlElement* stateXml = xml->getFirstChildElement();
	while (stateXml != nullptr)
	{
		if (stateXml->hasTagName(stateType) && stateXml->hasAttribute("presetName"))
		{
			// make a deep copy of the preset state and take ownership
			SerializedState state = std::make_unique<XmlElement>(*stateXml);
			loadPreset(order, states, std::move(state));
		}

		stateXml = stateXml->getNextElement();
	}
}

void loadPresetsFromDir(
	std::vector<PresetOrder>& order,
	std::vector<SerializedState>& states,
	const File& dir,
	const Identifier& stateType)
{
	const auto files = dir.findChildFiles(File::TypesOfFileToFind::findFiles, false);

	for (int i = 0; i < files.size(); i++)
	{
		const File& file = files[i];
		if (file.getFileExtension() != ".xml" && file.getFileExtension() != ".XML")
			continue;

		SerializedState state = XmlDocument::parse(file);
		if (state->hasTagName(stateType) && state->hasAttribute("presetName"))
			loadPreset(order, states, std::move(state));
	}
}

PresetManager::PresetManager(
	AudioProcessorValueTreeState& vts,
	ComboBox& comboBox,
	Button* saveButton) :
	vts(vts),
	initState(vts.state),
	comboBox(comboBox)
{
	presetDir = File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory);
	#ifdef JUCE_MAC
		presetDir = presetDir.getChildFile("Audio").getChildFile("Presets");
	#endif
	presetDir = presetDir.getChildFile(JucePlugin_Manufacturer).getChildFile(JucePlugin_Name);
	// silent if invalid, will only notify user when they try to save
	presetDir.createDirectory();

	// get the list of parameter ids up front since it's not accessible at first;
	// vst.state.getNumParameters() returns zero until it initializes its object.
	parameterIds = getParameterIds(SerializedState(vts.state.createXml()));

	const auto factoryPresets = XmlDocument::parse(BinaryData::presets_xml);

	comboBox.addListener(this);
	// NOTE: possible to work without saving capability
	if (saveButton != nullptr)
		saveButton->addListener(this);

	addPreset("init", SerializedState(nullptr));

	const Identifier stateType = vts.state.getType();
	std::vector<std::tuple<int, String, size_t>> presetOrder;
	std::vector<SerializedState> presetStates;

	loadPresetsFromXml(presetOrder, presetStates, factoryPresets, stateType);
	loadPresetsFromDir(presetOrder, presetStates, presetDir, stateType);

	std::sort(presetOrder.begin(), presetOrder.end());
	for (const auto& order : presetOrder)
	{
		const String& name = std::get<1>(order);
		const size_t i = std::get<2>(order);
		addPreset(name, std::move(presetStates[i]));
	}
}

void PresetManager::comboBoxChanged(ComboBox* pComboBox)
{
	// this shouldn't happen... but of course it can
	if (pComboBox == nullptr) return;

	// Presumably this is called from the UI thread, so the UI shouldn't be 
	// changing the comboBox, but if it were changed from the audio threaad
	// through some mechanism this could be problematic.

	currentName = pComboBox->getText();
	currentIdx = pComboBox->getSelectedItemIndex();

	if (!map.contains(currentName))
	{
		currentIdx = addPreset(currentName, SerializedState(vts.state.createXml()));
		savePreset(currentName, states[map[currentName]]);
	}
	else
	{
		setState(states[map[currentName]]);
	}
}

bool PresetManager::setState(const SerializedState& state)
{
	// handle the init state, just use parameter defaults
	if (state.get() == nullptr)
	{
		for (const auto& id : parameterIds)
		{
			auto parameter = vts.getParameter(id);
			if (parameter == nullptr)
				continue;
			parameter->setValueNotifyingHost(parameter->getDefaultValue());
		}
		return true;
	}

	if (!state->hasTagName(vts.state.getType()))
		return false;

	const auto inputLevelPar = vts.getParameter("idInputLevel");
	const auto outputLevelPar = vts.getParameter("idOutputLevel");
	const float inputLevelVal = inputLevelPar != nullptr ? inputLevelPar->getValue() : 0.0f;
	const float outputLevelVal = outputLevelPar != nullptr ? outputLevelPar->getValue() : 0.0f;

	// copy the state into the plugin
	vts.replaceState(ValueTree::fromXml(*state));

	// and trigger all the callbacks... couldn't find a better interface
	for (const auto& id : parameterIds)
	{
		auto parameter = vts.getParameter(id);
		if (parameter == nullptr)
			continue;
		parameter->sendValueChangedMessageToListeners(parameter->getValue());
	}

	// TODO: this is a bit messy, an alternative is to go over all parameters
	// get it from the state if available, and set the others to default vavlues,
	// other than the levels. But the defaulting is already taken care of with
	// `replaceState`, so it's convenient to work with it.

	// preserve the levels
	if (inputLevelPar != nullptr) inputLevelPar->setValueNotifyingHost(inputLevelVal);
	if (outputLevelPar != nullptr) outputLevelPar->setValueNotifyingHost(outputLevelVal);

	return true;
}

void PresetManager::buttonClicked(Button* button)
{
	if (button == nullptr) return;
	if (currentName == "" || currentName == "init")
		return;
	// be sure to update the state in the map
	currentIdx = addPreset(currentName, vts.state.createXml());
	savePreset(currentName, states[map[currentName]]);
}

int PresetManager::addPreset(const String& name, SerializedState state)
{
	// NOTE: this does grow whenver a user creates a new preset or saves a new
	// state, but it is per-session and driven by user action
	states.push_back(std::move(state));
	map.set(name, states.size() - 1);

	// Possible threading issue here as well (see note in comboBoxChnaged)

	// if this name is already in the combo box, re-use it
	for (int idx = 0; idx < comboBox.getNumItems(); idx++)
	{
		if (comboBox.getItemText(idx) != name)
			continue;
		return idx;
	}

	const int idx = comboBox.getNumItems();
	// the ID is just the list index plus 1 since it can't be 0
	comboBox.addItem(name, idx + 1);
	return idx;
}

void PresetManager::savePreset(const String& name, const SerializedState& state)
{
	if (state.get() == nullptr)
		return;

	state->setAttribute("pluginVersion", JucePlugin_VersionString);
	state->setAttribute("presetName", currentName);
	state->setAttribute("presetOrder", currentIdx);

	File xmlFile = presetDir.getChildFile(name + ".xml");

	if (xmlFile.existsAsFile())
	{
		if (
			!AlertWindow::showOkCancelBox(
				AlertWindow::AlertIconType::QuestionIcon,
				"Overwrite",
				"Preset file exists, overwrite?"))
			return;
	}

	if (!state->writeTo(xmlFile))
	{
		AlertWindow::showMessageBox(
			AlertWindow::AlertIconType::WarningIcon,
			"Failed to save",
			"Failed to save preset file."
		);
	}
}
