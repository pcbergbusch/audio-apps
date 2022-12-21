/*
  ==============================================================================

    PresetManager.h
    Created: 29 Nov 2022 10:57:43pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class PresetManager
{
public:
    static const juce::File defaultDirectory;
    static const juce::String extension;
    static const juce::String presetNameProperty;
    static const juce::String presetNameDefault;

    PresetManager(juce::AudioProcessorValueTreeState& inValueTreeState);
    ~PresetManager();

    void savePreset(const juce::String& presetName);
    void deletePreset(const juce::String& presetName);
    void loadPreset(const juce::String& presetName);
    int loadNextPreset();
    int loadPreviousPreset();
    juce::StringArray getAllPresets() const;
    juce::String getCurrentPreset() const;
    void setCurrentPreset(juce::String currentPreset);

private:
    juce::String mCurrentPreset;
    juce::AudioProcessorValueTreeState& valueTreeState;
};