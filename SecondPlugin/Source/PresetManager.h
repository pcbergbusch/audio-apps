/*
  ==============================================================================

    PresetManager.h
    Created: 23 Nov 2022 11:17:55pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

class PresetManager
{
public:
    PresetManager(SecondPluginAudioProcessor* inProcessor);
    ~PresetManager();

    void setPresetsForXml(juce::XmlElement* inElement);
    void loadPresetFromXml(juce::XmlElement* inElement);

private:
    SecondPluginAudioProcessor* mProcessor;
    juce::XmlElement* mCurrentPresetXml;
};
