/*
 *  Swanky Amp tube amplifier simulation
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

 #include <cmath>
 #include <sstream>
 #include <iomanip>

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
	SwankyAmpAudioProcessor& processor,
	AudioProcessorValueTreeState& vts,
	ComboBox& comboBox,
	Button& buttonSave,
	Button& buttonRemove,
	Button& buttonNext,
	Button& buttonPrev,
	Button& buttonOpen) :
	processor(processor),
	vts(vts),
	comboBox(comboBox),
	buttonSave(buttonSave),
	buttonRemove(buttonRemove),
	buttonNext(buttonNext),
	buttonPrev(buttonPrev),
	buttonOpen(buttonOpen)
{
	presetDir = File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory);
	#ifdef JUCE_MAC
		presetDir = presetDir.getChildFile("Audio").getChildFile("Presets");
	#endif
	presetDir = presetDir.getChildFile(JucePlugin_Manufacturer).getChildFile(JucePlugin_Name);
	// silent if invalid, will only notify user when they try to save
	presetDir.createDirectory();

	parameterIds = buildParameterIds(SerializedState(vts.state.createXml()));

	addStateEntry("init", File(), nullptr);

	// cleanup:
	// go through xml files
	// any without correct tag are removed
	// any with resonantamp tag are converted to swankyamp

	if (!loadPresetsFromDir())
		loadFactoryPresets();

	updatePresetDir();
	updateComboBox();
	clearUI();

	comboBox.onChange = [&]() { comboBoxChanged(); };
	buttonSave.onClick = [&]() { buttonSaveClicked(); };
	buttonRemove.onClick = [&]() { buttonRemoveClicked(); };
	buttonNext.onClick = [&]() { buttonNextClicked(); };
	buttonPrev.onClick = [&]() { buttonPrevClicked(); };
	buttonOpen.onClick = [&]() { buttonOpenClicked(); };
}

PresetManager::~PresetManager()
{
	// UI elements can outlive the manager, ensure they don't try to use callbacks
	comboBox.onChange = [](){};
	buttonSave.onClick = [](){};
	buttonRemove.onClick = [](){};
	buttonNext.onClick = [](){};
	buttonPrev.onClick = [](){};
	buttonOpen.onClick = [](){};
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
			loadPreset(std::make_unique<XmlElement>(*stateXml), presetFile, presetName);
			writingSuccess &= stateXml->writeTo(presetFile);
		}
		stateXml = stateXml->getNextElement();
	}

	if (!writingSuccess)
	{
		AlertWindow::showMessageBox(
			AlertWindow::AlertIconType::WarningIcon,
			"Factory preset failure",
			"Unalble to write factory presets to disk"
		);
	}
}

bool PresetManager::loadPresetsFromDir()
{
	std::vector<String> filePaths;
	auto files = presetDir.findChildFiles(File::TypesOfFileToFind::findFiles, false);

	if (files.isEmpty())
		return false;

	std::sort(files.begin(), files.end());

	const Identifier& stateType = vts.state.getType();

	for (int i = 0; i < files.size(); i++)
	{
		const File& presetFile = files[i];
		if (presetFile.getFileExtension() != ".xml" && presetFile.getFileExtension() != ".XML")
			continue;

		SerializedState stateXml = XmlDocument::parse(presetFile);

		// allow using preseets from version before name change
		if (stateXml->hasTagName("APVTSResonantAmp"))
			stateXml->setTagName("APVTSSwankyAmp");

		if (stateXml->hasTagName(stateType) && stateXml->hasAttribute("presetName"))
		{
			const String& presetName = stateXml->getStringAttribute("presetName");
			loadPreset(std::make_unique<XmlElement>(*stateXml), presetFile, presetName);
		}
	}

	return true;
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
		if (i > 0)
			comboBox.addItem(String(i) + ": " + entry.name, id);
		else
			comboBox.addItem(entry.name, id);
	}
}

void PresetManager::updatePresetDir()
{
	const size_t width = (size_t)(log10f((float)stateEntries.size())) + 1;

	size_t idx = 0;
	for (auto& entry : stateEntries)
	{
		if (!entry.file.existsAsFile())
			continue;

		idx++;

		std::ostringstream ss;
		ss << std::setfill('0') << std::setw(width);
		ss << idx << " " << entry.name << ".xml";

		const String targetPath = presetDir.getChildFile(ss.str()).getFullPathName();
		if (entry.file == targetPath)
			continue;

		if (entry.file.getParentDirectory() == presetDir)
		{
			if (entry.file.moveFileTo(targetPath))
				entry.file = File(targetPath);
		}
		else
		{
			if (entry.file.copyFileTo(targetPath))
				entry.file = File(targetPath);
		}
	}
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

		if (id > 0 && id != stateEntryIdx[name])
			moveStateEntry(stateEntryIdx[name], (size_t)id);
		updateComboBox();
		// note: don't yet update preset dir as it is not yet saved so it won't have
		// an impact

		currentName = name;

		// this definitely can be removed
		buttonRemove.setEnabled(true);
		// this can be saved as a new preset with the current state
		buttonSave.setEnabled(true);
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

			if (id > 0 && id != (int)(stateEntryIdx[name]))
			{
				moveStateEntry(stateEntryIdx[name], (size_t)id);
				updatePresetDir();
				updateComboBox();
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
	updatePresetDir();

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
	updatePresetDir();
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

void PresetManager::buttonOpenClicked()
{
	presetDir.startAsProcess();
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

