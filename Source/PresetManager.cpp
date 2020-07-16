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

// TODO: no longer used but could be useful for building parameter list in
// processor?
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
	int id,
	const String& name,
	File file,
	std::optional<size_t> stateIdx) :
	id(id),
	name(name),
	file(file),
	stateIdx(stateIdx)
{}

PresetManager::PresetManager(
	ResonantAmpAudioProcessor& processor,
	AudioProcessorValueTreeState& vts,
	ComboBox& comboBox,
	Button& buttonSave,
	Button& buttonRemove,
	Button& buttonNext,
	Button& buttonPrev) :
	processor(processor),
	vts(vts),
	comboBox(comboBox),
	buttonSave(buttonSave),
	buttonRemove(buttonRemove),
	buttonNext(buttonNext),
	buttonPrev(buttonPrev)
{
	presetDir = File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory);
	#ifdef JUCE_MAC
		presetDir = presetDir.getChildFile("Audio").getChildFile("Presets");
	#endif
	presetDir = presetDir.getChildFile(JucePlugin_Manufacturer).getChildFile(JucePlugin_Name);
	// silent if invalid, will only notify user when they try to save
	presetDir.createDirectory();
	// preset master file indicates which presets to use
	presetMaster = presetDir.getChildFile("presetMaster.xml");

	stateEntries["init"] = StateEntry((int)usedIds.size(), "init", File(), std::nullopt);
	usedIds.push_back(true);

	// if not yet found, write factory presets to disk and build initial master
	// (also finds any existing presets in the directory)
	if (!presetMaster.existsAsFile())
	{
		loadPresetsFromDir();
		loadFactoryPresets();
		updatePresetMaster();
	}
	else
	{
		loadPresetsFromMaster();
	}

	comboBox.onChange = [&]() { comboBoxChanged(); };
	buttonSave.onClick = [&]() { buttonSaveClicked(); };
	buttonRemove.onClick = [&]() { buttonRemoveClicked(); };
	buttonNext.onClick = [&]() { buttonNextClicked(); };
	buttonPrev.onClick = [&]() { buttonPrevClicked(); };

	updateComboBox();
	clearUI();
}

PresetManager::~PresetManager()
{
	// UI elements can outlive the manager, ensure they don't try to use callbacks
	comboBox.onChange = [](){};
	buttonSave.onClick = [](){};
	buttonRemove.onClick = [](){};
	buttonNext.onClick = [](){};
	buttonPrev.onClick = [](){};
}

void PresetManager::loadPreset(
	SerializedState state,
	File file,
	const String& name)
{
	if (state == nullptr)
		return;

	states.push_back(std::move(state));
	stateEntries[name] = StateEntry(
		(int)usedIds.size(),
		name.isNotEmpty() ? name : state->getStringAttribute("presetName"),
		file,
		{ states.size() - 1 }
	);
	usedIds.push_back(true);
}

void PresetManager::loadFactoryPresets()
{
	const std::unique_ptr<XmlElement> xml = XmlDocument::parse(BinaryData::presets_xml);
	if (xml == nullptr)
		return;

	bool writingSuccess = true;
	const Identifier& stateType = vts.state.getType();

	XmlElement* stateXml = xml->getFirstChildElement();
	while (stateXml != nullptr)
	{
		if (stateXml->hasTagName(stateType) && stateXml->hasAttribute("presetName"))
		{
			const String& presetName = stateXml->getStringAttribute("presetName");
			File presetFile = presetDir.getChildFile(presetName + ".xml");
			if (!presetFile.existsAsFile())
			{
				writingSuccess &= stateXml->writeTo(presetFile);
				loadPreset(std::make_unique<XmlElement>(*stateXml), presetFile, presetName);
			}
		}
		stateXml = stateXml->getNextElement();
	}

	if (!writingSuccess)
	{
		AlertWindow::showMessageBox(
			AlertWindow::AlertIconType::WarningIcon,
			"Factory preset failure",
			"Unalble to persist factory presets to disk"
		);
	}
}

void PresetManager::loadPresetsFromDir()
{
	std::vector<String> filePaths;
	auto files = presetDir.findChildFiles(File::TypesOfFileToFind::findFiles, false);
	std::sort(files.begin(), files.end());

	const Identifier& stateType = vts.state.getType();

	for (int i = 0; i < files.size(); i++)
	{
		const File& presetFile = files[i];
		if (presetFile.getFileExtension() != ".xml" && presetFile.getFileExtension() != ".XML")
			continue;

		SerializedState stateXml = XmlDocument::parse(presetFile);

		if (stateXml->hasTagName(stateType) && stateXml->hasAttribute("presetName"))
		{
			const String& presetName = stateXml->getStringAttribute("presetName");
			loadPreset(std::make_unique<XmlElement>(*stateXml), presetFile, presetName);
		}
	}
}

void PresetManager::loadPresetsFromMaster()
{
	XmlDocument master(presetMaster);
	std::unique_ptr<XmlElement> xml = master.getDocumentElement();

	if (xml->getTagName() != "presetList")
		return;

	XmlElement* entry = xml->getFirstChildElement();
	while (entry != nullptr)
	{
		if (entry->getTagName() == "entry" && entry->hasAttribute("name") && entry->hasAttribute("file"))
		{
			const String& name = entry->getStringAttribute("name");
			const File& file = entry->getStringAttribute("file");
			if (file.existsAsFile())
				loadPreset(XmlDocument(file).getDocumentElement(), file, name);
		}
		entry = entry->getNextElement();
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
		keyOrder.push_back(std::pair<int, String>(item.second.id, item.second.name));
	std::sort(keyOrder.begin(), keyOrder.end());

	for (const auto& item : keyOrder)
		comboBox.addItem(item.second, item.first);
}

void PresetManager::updatePresetMaster()
{
	XmlElement master = XmlElement("presetList");

	std::vector<std::pair<int, String>> keyOrder;
	for (const auto& item : stateEntries)
		keyOrder.push_back(std::pair<int, String>(item.second.id, item.second.name));
	std::sort(keyOrder.begin(), keyOrder.end());

	for (const auto& item : keyOrder)
	{
		const String& name = item.second;
		const File& file = stateEntries[name].file;
		if (file.existsAsFile())
		{
			XmlElement* presetEntry = new XmlElement("entry");
			presetEntry->setAttribute("name", name);
			presetEntry->setAttribute("file", file.getFullPathName());
			master.addChildElement(presetEntry);
		}
	}

	master.writeTo(presetMaster);
}

void PresetManager::comboBoxChanged()
{
	const String& name = comboBox.getText();

	if (name == "")
		return;

	if (stateEntries.find(name) == stateEntries.end())
	{
		// new entry
		states.push_back(std::move(SerializedState(vts.state.createXml())));
		stateEntries[name] = StateEntry(
			(int)usedIds.size(),
			name,
			File(),
			states.size() - 1
		);
		usedIds.push_back(true);
		currentEntry = &stateEntries[name];
		comboBox.addItem(name, currentEntry->id);
		// this definitely can be removed
		buttonRemove.setEnabled(true);
		// this can be saved as a new preset with the current state
		buttonSave.setEnabled(true);
		// NOTE: don't yet add to master as it is not persisted
	}
	else
	{
		// existing entry
		currentEntry = &stateEntries[name];
		if (currentEntry != nullptr && currentEntry->stateIdx != std::nullopt)
		{
			// load the state for this entry
			setState(states[currentEntry->stateIdx.value()]);
			// this is a custom state, can be removed
			buttonRemove.setEnabled(true);
			// can't save until modified
			buttonSave.setEnabled(false);
		}
		else
		{
			// the init preset
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

	// once a state is persisted, update the master
	updatePresetMaster();

	// can't save again until something changes
	buttonSave.setEnabled(false);
	buttonRemove.setEnabled(true);
}

void PresetManager::buttonRemoveClicked()
{
	if (currentEntry == nullptr)
		return;

	if (currentEntry->file.getFullPathName() != "")
	{
		currentEntry->file.deleteFile();
		currentEntry->file = File();
	}

	usedIds[currentEntry->id] = false;
	stateEntries.erase(currentEntry->name);
	currentEntry = nullptr;

	updateComboBox();
	updatePresetMaster();
	clearUI();
}

void PresetManager::buttonNextClicked()
{
	if (currentEntry == nullptr)
	{
		// will trigger changed
		comboBox.setSelectedId(1);
		return;
	}
	else
	{
		int nextId = currentEntry->id + 1;
		while (nextId < usedIds.size() && !usedIds[nextId])
			nextId++;
		if (nextId >= usedIds.size())
			return;
		comboBox.setSelectedId(nextId);
	}
}

void PresetManager::buttonPrevClicked()
{
	if (currentEntry == nullptr)
	{
		comboBox.setSelectedId(1);
		return;
	}
	else
	{
		int prevId = currentEntry->id - 1;
		while (prevId > 0 && !usedIds[prevId])
			prevId--;
		if (prevId <= 0)
			return;
		comboBox.setSelectedId(prevId);
	}
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

