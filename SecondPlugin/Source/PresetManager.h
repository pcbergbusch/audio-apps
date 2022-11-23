/*
  ==============================================================================

    PresetManager.h
    Created: 23 Nov 2022 11:17:55pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class PresetManager
{
public:
    PresetManager(juce::AudioProcessor* inProcessor);
    ~PresetManager();

    void setPresetsForXml(juce::XmlElement* inElement);
    void loadPresetFromXml(juce::XmlElement* inElement);

private:
    juce::AudioProcessor* mProcessor;
    juce::XmlElement* mCurrentPresetXml;
};
