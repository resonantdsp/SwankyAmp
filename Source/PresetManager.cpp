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

#include "unordered_map"

#include "PresetManager.h"
#include "Components/PresetGroup.h"

std::vector<String> buildParameterIds(const SerializedState& state)
{
	if (state == nullptr)
		return {};

	std::vector<String> parameterIds;

	XmlElement* element = state->getFirstChildElement();

	while (element != nullptr)
	{
		if (
			element->getTagName() == "PARAM"
			&& element->hasAttribute("id"))
		{
			const String& id = element->getStringAttribute("id");
			parameterIds.push_back(id);
		}

		element = element->getNextElement();
	}

	return parameterIds;
}

StateEntry::StateEntry(
	int order,
	const String& name,
	File file,
	std::optional<size_t> stateIdx,
	std::optional<size_t> factoryStateIdx) :
	order(order),
	name(name),
	file(file),
	stateIdx(stateIdx),
	factoryStateIdx(factoryStateIdx)
{}

StateEntry::StateEntry() :
	order(INT_MAX),
	name(),
	file(),
	stateIdx(std::nullopt),
	factoryStateIdx(std::nullopt)
{}

bool StateEntry::operator>(const StateEntry& other)
{
	return
		order != other.order ?
		order > other.order :
		name > other.name;
}

PresetManager::PresetManager(
	ResonantAmpAudioProcessor& processor,
	AudioProcessorValueTreeState& vts,
	ComboBox& comboBox,
	Button& buttonSave,
	Button& buttonRemove) :
	processor(processor),
	vts(vts),
	comboBox(comboBox),
	buttonSave(buttonSave),
	buttonRemove(buttonRemove)
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
	parameterIds = buildParameterIds(SerializedState(vts.state.createXml()));

	const auto factoryPresets = XmlDocument::parse(BinaryData::presets_xml);
	const Identifier stateType = vts.state.getType();

	stateEntries["init"] = StateEntry(0, "init", File(), std::nullopt, std::nullopt);
	loadPresetsFromXml(factoryPresets, stateType, true);
	loadPresetsFromDir(presetDir, stateType, false);

	comboBox.onChange = [&]() { comboBoxChanged(); };
	buttonSave.onClick = [&]() { buttonSaveClicked(); };
	buttonRemove.onClick = [&]() { buttonRemoveClicked(); };

	updateComboBox();
	clearUI();
}

PresetManager::~PresetManager()
{
	// UI elements can outlive the manager, ensure they don't try to use callbacks
	comboBox.onChange = [](){};
	buttonSave.onClick = [](){};
	buttonRemove.onClick = [](){};
}

void PresetManager::loadPreset(
	SerializedState state,
	File file,
	bool isFactory)
{
	if (state == nullptr)
		return;

	const String& name = state->getStringAttribute("presetName");
	const int orderValue =
		state->hasAttribute("presetOrder") 
		? state->getIntAttribute("presetOrder") 
		: INT_MAX;

	states.push_back(std::move(state));
	if (isFactory)
		stateEntries[name] = StateEntry(
			orderValue,
			name,
			file,
			std::nullopt,
			{ states.size() - 1 }
		);
	else
		stateEntries[name] = StateEntry(
			orderValue,
			name,
			file,
			{ states.size() - 1 },
			std::nullopt
		);
}

void PresetManager::loadPresetsFromXml(
	const std::unique_ptr<XmlElement>& xml,
	const Identifier& stateType,
	bool isFactory)
{
	if (xml == nullptr)
		return;

	XmlElement* stateXml = xml->getFirstChildElement();
	while (stateXml != nullptr)
	{
		if (stateXml->hasTagName(stateType) && stateXml->hasAttribute("presetName"))
		{
			// make a deep copy of the preset state and take ownership
			SerializedState state = std::make_unique<XmlElement>(*stateXml);
			loadPreset(std::move(state), File(), isFactory);
		}

		stateXml = stateXml->getNextElement();
	}
}

void PresetManager::loadPresetsFromDir(
	const File& dir,
	const Identifier& stateType,
	bool isFactory)
{
	std::vector<String> filePaths;
	const auto files = dir.findChildFiles(File::TypesOfFileToFind::findFiles, false);

	for (int i = 0; i < files.size(); i++)
	{
		const File& file = files[i];
		if (file.getFileExtension() != ".xml" && file.getFileExtension() != ".XML")
			continue;

		SerializedState state = XmlDocument::parse(file);
		if (state != nullptr && state->hasTagName(stateType) && state->hasAttribute("presetName"))
			loadPreset(std::move(state), file, isFactory);
	}
}

void PresetManager::clearUI()
{
	comboBox.setSelectedId(0);
	buttonSave.setEnabled(false);
	buttonRemove.setEnabled(false);
}

void PresetManager::updateComboBox()
{
	comboBox.clear();

	std::vector<std::pair<int, String>> keyOrder;
	for (const auto& item : stateEntries)
		keyOrder.push_back(std::pair<int, String>(item.second.order, item.second.name));
	std::sort(keyOrder.begin(), keyOrder.end());

	for (const auto& item : keyOrder)
		comboBox.addItem(item.second, comboBox.getNumItems() + 1);
}

void PresetManager::comboBoxChanged()
{
	const String& name = comboBox.getText();

	if (name != "" && stateEntries.find(name) == stateEntries.end())
	{
		states.push_back(std::move(SerializedState(vts.state.createXml())));
		stateEntries[name] = StateEntry(
			(int)stateEntries.size(),
			name,
			File(),
			states.size() - 1,
			std::nullopt
		);
		currentEntry = &stateEntries[name];
		comboBox.addItem(name, comboBox.getNumItems() + 1);
		// this definitely can be removed
		buttonRemove.setEnabled(true);
		// this can be saved as a new preset with the current state
		buttonSave.setEnabled(true);
	}
	else
	{
		currentEntry = &stateEntries[name];
		if (currentEntry != nullptr && currentEntry->stateIdx != std::nullopt)
		{
			setState(states[currentEntry->stateIdx.value()]);
			// this is a custom state, can be removed
			buttonRemove.setEnabled(true);
			// can't save until modified
			buttonSave.setEnabled(false);
		}
		else if (currentEntry != nullptr && currentEntry->factoryStateIdx != std::nullopt)
		{
			setState(states[currentEntry->factoryStateIdx.value()]);
			// can't remove factory presets
			buttonRemove.setEnabled(false);
			buttonSave.setEnabled(false);
		}
		else
		{
			setState(nullptr);
			buttonRemove.setEnabled(false);
			buttonSave.setEnabled(false);
		}
	}
}

void PresetManager::buttonSaveClicked()
{
	if (currentEntry == nullptr)
		return;
	if (currentEntry->name == "")
		return;

	SerializedState state = vts.state.createXml();
	if (state == nullptr)
		return;

	state->setAttribute("pluginVersion", JucePlugin_VersionString);
	state->setAttribute("presetName", currentEntry->name);
	state->setAttribute("presetOrder", currentEntry->order);

	// TODO: sanitize preset names for valid file paths... could be tricky with
	// multiple os support
	File xmlFile = presetDir.getChildFile(currentEntry->name + ".xml");

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
		return;
	}
	

	states.push_back(std::move(state));
	currentEntry->stateIdx = { states.size() - 1 };
	currentEntry->file = xmlFile;

	// can't save again until something changes
	buttonSave.setEnabled(false);
	// can definitely remove this preset (can't be factory)
	buttonRemove.setEnabled(true);
}

void PresetManager::buttonRemoveClicked()
{
	if (currentEntry == nullptr)
		return;
	if (currentEntry->name == "")
		return;
	if (currentEntry->file.getFullPathName() != "")
	{
		if (!currentEntry->file.deleteFile())
		{
			AlertWindow::showMessageBox(
				AlertWindow::AlertIconType::WarningIcon,
				"Failed to remove",
				"Failed to remove preset file"
			);
			return;
		}
		currentEntry->file = File();
	}
	if (currentEntry->factoryStateIdx != std::nullopt)
		currentEntry->stateIdx = std::nullopt;
	else
		stateEntries.erase(currentEntry->name);

	currentEntry = nullptr;
	// TODO: separate sync UI state, here order of calls matters!
	updateComboBox();
	clearUI();
}

void PresetManager::parameterChanged(const String& id, float)
{
	if (
		currentEntry != nullptr 
		&& currentEntry->name != "init"
		&& id != "idInputLevel"
		&& id != "idOutputLevel")
		buttonSave.setEnabled(true);
}

void PresetManager::setState(const SerializedState& state)
{
	processor.setStateInformation(state, false);
}

