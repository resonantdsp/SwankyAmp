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

// TODO: could be useful for building parameter list in processor?
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
	const String& name,
	File file,
	std::optional<size_t> stateIdx) :
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

	parameterIds = buildParameterIds(SerializedState(vts.state.createXml()));

	addStateEntry("init", File(), nullptr);

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

void PresetManager::addStateEntry(const String& name, const File& file, SerializedState state)
{
	removeStateEntry(name);

	if (state != nullptr)
	{
		stateEntryIdx[name] = stateEntries.size();
		stateEntries.push_back(StateEntry(name, file, states.size()));
		states.push_back(std::move(state));
	}
	else
	{
		stateEntryIdx[name] = stateEntries.size();
		stateEntries.push_back(StateEntry(name, file, std::nullopt));
	}
}

void PresetManager::removeStateEntry(const String& name)
{
	if (stateEntryIdx.find(name) == stateEntryIdx.end())
		return;

	const size_t idx = stateEntryIdx[name];
	stateEntries.erase(stateEntries.begin() + idx);

	stateEntryIdx.clear();
	for (size_t i = 0; i < stateEntries.size(); i++)
		stateEntryIdx[stateEntries[i].name] = i;
}

void PresetManager::moveStateEntry(size_t idx, size_t newIdx)
{
	std::vector<StateEntry> moved;
	moved.reserve(stateEntries.size());

	if (newIdx < 1)
		newIdx = 1;

	if (newIdx == idx)
		return;

	if (newIdx > idx)
		newIdx += 1;

	for (size_t i = 0; i < stateEntries.size(); i++)
	{
		if (i == idx)
			continue;
		if (i == newIdx)
			moved.push_back(stateEntries[idx]);
		moved.push_back(stateEntries[i]);
	}

	if (newIdx >= stateEntries.size())
		moved.push_back(stateEntries[idx]);

	stateEntries = moved;

	stateEntryIdx.clear();
	for (size_t i = 0; i < stateEntries.size(); i++)
		stateEntryIdx[stateEntries[i].name] = i;
}

void PresetManager::loadPreset(
	SerializedState state,
	File file,
	const String& name)
{
	if (state == nullptr)
		return;

	addStateEntry(
		name.isNotEmpty() ? name : state->getStringAttribute("presetName"),
		file,
		std::move(state)
	);
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
	for (size_t i = 0; i < stateEntries.size(); i++)
	{
		const auto& entry = stateEntries[i];
		const int id = (int)(i + 1);
		comboBox.addItem(String(id) + ": " + entry.name, id);
	}
}

void PresetManager::updatePresetMaster()
{
	XmlElement master = XmlElement("presetList");

	for (const auto& entry : stateEntries)
	{
		if (entry.file.existsAsFile())
		{
			XmlElement* presetEntry = new XmlElement("entry");
			presetEntry->setAttribute("name", entry.name);
			presetEntry->setAttribute("file", entry.file.getFullPathName());
			master.addChildElement(presetEntry);
		}
	}

	master.writeTo(presetMaster);
}

std::pair<int, String> extractNumAndName(const String& name)
{
	static const String digits = "09";
	static const String div = ": ";

	int startIdx = -1;

	for (int i = 0; i < name.length(); i++)
	{
		const juce_wchar c = name[i];

		if (c >= digits[0] && c <= digits[1])
			continue;

		const bool hasNumber = i > 0;
		const bool hasDivider = i + div.length() <= name.length() && name.substring(i, i + div.length()) == div;

		if (hasNumber && hasDivider)
			startIdx = i + div.length();

		break;
	}

	if (startIdx > 1)
	{
		int num = std::atoi(name.substring(0, startIdx - div.length()).toRawUTF8());
		String nameStripped = name.substring(startIdx);
		return std::pair<int, String>(num, nameStripped);
	}
	else
	{
		return std::pair<int, String>(-1, name);
	}
}

void PresetManager::comboBoxChanged()
{
	const auto numAndName = extractNumAndName(comboBox.getText());
	const String& name = numAndName.second;
	const int id = numAndName.first;

	if (name == "")
		return;

	comboBox.setText(name);

	if (stateEntryIdx.find(name) == stateEntryIdx.end())
	{
		// new entry
		addStateEntry(name, File(), std::move(SerializedState(vts.state.createXml())));

		if (id > 0 && id != stateEntryIdx[name] + 1)
			moveStateEntry(stateEntryIdx[name], (size_t)id - 1);
		updateComboBox();

		currentName = name;

		// this definitely can be removed
		buttonRemove.setEnabled(true);
		// this can be saved as a new preset with the current state
		buttonSave.setEnabled(true);
		// NOTE: don't yet add to master as it is not persisted
	}
	else
	{
		// existing entry
		currentName = name;
		const StateEntry& currentEntry = stateEntries[stateEntryIdx[name]];

		if (currentEntry.stateIdx != std::nullopt)
		{
			// load the state for this entry
			setState(states[currentEntry.stateIdx.value()]);

			// this is a custom state, can be removed
			buttonRemove.setEnabled(true);
			// can't save until modified
			buttonSave.setEnabled(false);

			if (id > 0 && id != (int)(stateEntryIdx[name] + 1))
			{
				moveStateEntry(stateEntryIdx[name], (size_t)id - 1);
				updateComboBox();
				// can save change to order
				buttonSave.setEnabled(true);
			}
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
	if (!currentName.has_value())
		return;
	StateEntry& currentEntry = stateEntries[stateEntryIdx[*currentName]];
	if (currentEntry.name == "")
		return;

	SerializedState state = vts.state.createXml();
	if (state == nullptr)
		return;

	state->setAttribute("pluginVersion", JucePlugin_VersionString);
	state->setAttribute("presetName", currentEntry.name);

	// TODO: sanitize preset names for valid file paths... could be tricky with
	// multiple os support
	File xmlFile = presetDir.getChildFile(currentEntry.name + ".xml");

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
	currentEntry.stateIdx = { states.size() - 1 };
	currentEntry.file = xmlFile;

	// once a state is persisted, update the master
	updatePresetMaster();

	// can't save again until something changes
	buttonSave.setEnabled(false);
	buttonRemove.setEnabled(true);
}

void PresetManager::buttonRemoveClicked()
{
	if (!currentName.has_value())
		return;
	StateEntry& currentEntry = stateEntries[stateEntryIdx[*currentName]];

	if (currentEntry.file.getFullPathName() != "")
	{
		currentEntry.file.deleteFile();
		currentEntry.file = File();
	}

	removeStateEntry(currentEntry.name);
	currentName = std::nullopt;

	updateComboBox();
	updatePresetMaster();
	clearUI();
}

void PresetManager::buttonNextClicked()
{
	if (currentName == std::nullopt)
	{
		comboBox.setSelectedId(1);
		return;
	}

	size_t currentIdx = stateEntryIdx[*currentName];

	if (currentIdx < stateEntries.size() - 1)
	{
		currentIdx += 1;
		currentName = stateEntries[currentIdx].name;
		const int id = (int)(currentIdx + 1);
		comboBox.setSelectedId(id);
	}
}

void PresetManager::buttonPrevClicked()
{
	if (currentName == std::nullopt)
	{
		comboBox.setSelectedId(1);
		return;
	}

	size_t currentIdx = stateEntryIdx[*currentName];

	if (currentIdx > 1)
	{
		currentIdx -= 1;
		currentName = stateEntries[currentIdx].name;
		const int id = (int)(currentIdx + 1);
		comboBox.setSelectedId(id);
	}
}

void PresetManager::parameterChanged(const String& id, float)
{
	if (!currentName.has_value())
		return;
	StateEntry& currentEntry = stateEntries[stateEntryIdx[*currentName]];
	if (
		currentEntry.name != "init"
		&& id != "idInputLevel"
		&& id != "idOutputLevel")
		buttonSave.setEnabled(true);
}

void PresetManager::setState(const SerializedState& state)
{
	processor.setStateInformation(state, false);
}

