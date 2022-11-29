/*
  ==============================================================================

    PresetManager.cpp
    Created: 29 Nov 2022 10:57:43pm
    Author:  pcber

  ==============================================================================
*/

#include "PresetManager.h"

PresetManager::PresetManager(juce::AudioProcessorValueTreeState& apvts)
    : mApvts(apvts), mCurrentPreset("this")
{

}

PresetManager::~PresetManager()
{

}

void PresetManager::savePreset(const juce::String& presetName)
{

}

void PresetManager::deletePreset(const juce::String& presetName)
{

}

void PresetManager::loadPreset(const juce::String& presetName)
{

}

void PresetManager::loadNextPreset()
{

}

void PresetManager::loadPreviousPreset()
{

}

juce::StringArray PresetManager::getAllPresets() const
{
    return juce::StringArray("this");
}

juce::String PresetManager::getCurrentPreset() const
{
    return juce::String("that");
}
