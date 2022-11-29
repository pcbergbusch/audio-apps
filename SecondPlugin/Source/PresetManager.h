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
    PresetManager(juce::AudioProcessorValueTreeState& apvst);
    ~PresetManager();

    void savePreset(const juce::String& presetName);
    void deletePreset(const juce::String& presetName);
    void loadPreset(const juce::String& presetName);
    void loadNextPreset();
    void loadPreviousPreset();
    juce::StringArray getAllPresets() const;
    juce::String getCurrentPreset() const;

private:
    juce::String mCurrentPreset;
    juce::AudioProcessorValueTreeState& mApvts;
};