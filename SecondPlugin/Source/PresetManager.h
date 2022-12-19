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

    PresetManager();
    ~PresetManager();

    void savePreset(
        juce::AudioProcessorValueTreeState& valueTreeState,
        const juce::String& presetName
    );
    void deletePreset(const juce::String& presetName);
    void loadPreset(
        juce::AudioProcessorValueTreeState& valueTreeState,
        const juce::String& presetName
    );
    int loadNextPreset(juce::AudioProcessorValueTreeState& valueTreeState);
    int loadPreviousPreset(juce::AudioProcessorValueTreeState& valueTreeState);
    juce::StringArray getAllPresets() const;
    juce::String getCurrentPreset() const;
    void setCurrentPreset(juce::String currentPreset);

private:
    juce::String mCurrentPreset;
};