/*
  ==============================================================================

    PresetManager.cpp
    Created: 29 Nov 2022 10:57:43pm
    Author:  pcber

  ==============================================================================
*/

#include "PresetManager.h"

const juce::File PresetManager::defaultDirectory{ juce::File::getSpecialLocation(
    juce::File::SpecialLocationType::commonDocumentsDirectory)
    .getChildFile(ProjectInfo::companyName)
    .getChildFile(ProjectInfo::projectName)
};

const juce::String PresetManager::extension{ "preset" };

const juce::String PresetManager::presetNameProperty{ "presetName" };

PresetManager::PresetManager()
    : mCurrentPreset("")
{
    // Create a default directory for presets if it doesn't exist
    if (!defaultDirectory.exists())
    {
        const auto result = defaultDirectory.createDirectory();
        if (result.failed())
        {
            DBG("Could not create preset directory: " + result.getErrorMessage());
            jassertfalse;
        }
    }
}

PresetManager::~PresetManager()
{

}

void PresetManager::savePreset(
    juce::AudioProcessorValueTreeState& valueTreeState,
    const juce::String& presetName
)
{
    if (presetName.isEmpty())
        return;
    
    mCurrentPreset = presetName;
    // It may be better to save the current preset name and version in the juce::ApplicationProperties
    // rather than as properties of the state - because the xml file can be renamed by the user
    valueTreeState.state.setProperty(PresetManager::presetNameProperty, presetName, nullptr);
    const auto xml = valueTreeState.state.createXml();
    const auto presetFile = defaultDirectory.getChildFile(presetName + "." + extension);
    if (!xml->writeTo(presetFile))
    {
        DBG("Could not create preset file: " + presetFile.getFullPathName());
        jassertfalse;
    }
}

void PresetManager::deletePreset(const juce::String& presetName)
{
    if (presetName.isEmpty())
        return;

    const auto presetFile = defaultDirectory.getChildFile(presetName + "." + extension);
    if (!presetFile.existsAsFile())
    {
        DBG("Preset file " + presetFile.getFullPathName() + " does not exist.");
        jassertfalse;
        return;
    }
    if (!presetFile.deleteFile())
    {
        DBG("Could not create preset file: " + presetFile.getFullPathName());
        jassertfalse;
        return;
    }
    mCurrentPreset = "";
}

void PresetManager::loadPreset(
    juce::AudioProcessorValueTreeState& valueTreeState,
    const juce::String& presetName
)
{
    if (presetName.isEmpty())
        return;

    const auto presetFile = defaultDirectory.getChildFile(presetName + "." + extension);
    if (!presetFile.existsAsFile())
    {
        DBG("Preset file " + presetFile.getFullPathName() + " does not exist.");
        jassertfalse;
        return;
    }
    // to maintain backwards compatibility with previous preset versions, it is usually better to loop
    // through the state variables and reset just those required, rather than to replace the whole state
    juce::XmlDocument xmlDocument{ presetFile };
    const auto valueTreeToLoad = juce::ValueTree::fromXml(*xmlDocument.getDocumentElement());
    valueTreeState.replaceState(valueTreeToLoad);
    mCurrentPreset = presetName;
}

int PresetManager::loadNextPreset(juce::AudioProcessorValueTreeState& valueTreeState)
{
    const auto allPresets = getAllPresets();
    if (allPresets.isEmpty())
        return -1;
    
    const auto currentIndex = allPresets.indexOf(mCurrentPreset);
    const auto nextIndex = (currentIndex + 1 > (allPresets.size() - 1)) ? 0 : currentIndex + 1;
    loadPreset(valueTreeState, allPresets.getReference(nextIndex));
    return nextIndex;
}

int PresetManager::loadPreviousPreset(juce::AudioProcessorValueTreeState& valueTreeState)
{
    const auto allPresets = getAllPresets();
    if (allPresets.isEmpty())
        return -1;

    const auto currentIndex = allPresets.indexOf(mCurrentPreset);
    const auto previousIndex = (currentIndex - 1 < 0) ? allPresets.size() - 1 : currentIndex - 1;
    loadPreset(valueTreeState, allPresets.getReference(previousIndex));
    return previousIndex;
}

juce::StringArray PresetManager::getAllPresets() const
{
    juce::StringArray presets;
    const auto fileArray = defaultDirectory.findChildFiles(
        juce::File::TypesOfFileToFind::findFiles, false, "*." + extension
    );
    for (const auto& file : fileArray)
    {
        presets.add(file.getFileNameWithoutExtension());
    }
    return presets;
}

juce::String PresetManager::getCurrentPreset() const
{
    return mCurrentPreset;
}

void PresetManager::setCurrentPreset(juce::String currentPreset)
{
    mCurrentPreset = currentPreset;
}

//void PresetManager::valueTreeRedirected(juce::ValueTree& treeWhichHasBeenChanged)
//{
//    mCurrentPreset.referTo(treeWhichHasBeenChanged.getPropertyAsValue(presetNameProperty, nullptr));
//}
