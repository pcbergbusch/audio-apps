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

PresetManager::PresetManager(juce::AudioProcessorValueTreeState& valueTreeState)
    : juce::ValueTree::Listener(),
      mValueTreeState(valueTreeState)
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

    mValueTreeState.state.addListener(this);
    mCurrentPreset.setValue(mValueTreeState.state.getProperty(presetNameProperty));
    //mCurrentPreset.referTo(mValueTreeState.state.getPropertyAsValue(presetNameProperty, nullptr));
    loadPreset(getCurrentPreset());
}

PresetManager::~PresetManager()
{
    mValueTreeState.state.removeListener(this);
}

void PresetManager::savePreset(const juce::String& presetName)
{
    if (presetName.isEmpty())
        return;
    
    mCurrentPreset.setValue(presetName);
    const auto xml = mValueTreeState.copyState().createXml();
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
    mCurrentPreset.setValue("");
}

void PresetManager::loadPreset(const juce::String& presetName)
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
    juce::XmlDocument xmlDocument{ presetFile };
    const auto valueTreeToLoad = juce::ValueTree::fromXml(*xmlDocument.getDocumentElement());

    // to maintain backwards compatibility with previous preset versions, it is usually better to loop
    // through the state variables and reset just those required, rather than to replace the whole state
    mValueTreeState.replaceState(valueTreeToLoad);
    mCurrentPreset.setValue(presetName);
}

int PresetManager::loadNextPreset()
{
    const auto allPresets = getAllPresets();
    if (allPresets.isEmpty())
        return -1;
    
    const auto currentIndex = allPresets.indexOf(mCurrentPreset.toString());
    const auto nextIndex = (currentIndex + 1 > (allPresets.size() - 1)) ? 0 : currentIndex + 1;
    loadPreset(allPresets.getReference(nextIndex));
    return nextIndex;
}

int PresetManager::loadPreviousPreset()
{
    const auto allPresets = getAllPresets();
    if (allPresets.isEmpty())
        return -1;

    const auto currentIndex = allPresets.indexOf(mCurrentPreset.toString());
    const auto previousIndex = (currentIndex - 1 < 0) ? allPresets.size() - 1 : currentIndex - 1;
    loadPreset(allPresets.getReference(previousIndex));
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
    return mCurrentPreset.toString();
}

//void PresetManager::valueTreeRedirected(juce::ValueTree& treeWhichHasBeenChanged)
//{
//    mCurrentPreset.referTo(treeWhichHasBeenChanged.getPropertyAsValue(presetNameProperty, nullptr));
//}

void PresetManager::valueTreePropertyChanged(
    juce::ValueTree& treeWhosePropertyHasChanged,
    const juce::Identifier& property
)
{
    if (property.toString() == presetNameProperty)
        mCurrentPreset.setValue(treeWhosePropertyHasChanged.getProperty(property.toString()));
}
