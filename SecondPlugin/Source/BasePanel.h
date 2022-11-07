/*
  ==============================================================================

    BasePanel.h
    Created: 5 Nov 2022 7:42:43pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "InterfaceDefines.h"

class BasePanel
    : public juce::Component
{
public:
    BasePanel(SecondPluginAudioProcessor* inProcessor);
    ~BasePanel();

    void paint(juce::Graphics& g) override;

protected:
    SecondPluginAudioProcessor* mProcessor;
};
