/*
  ==============================================================================

    VUMeter.h
    Created: 31 Dec 2022 12:04:43am
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

class VUMeter
    : public juce::Component, juce::Timer
{
public:
    VUMeter(SecondPluginAudioProcessor* inProcessor);
    ~VUMeter();

    void paint(juce::Graphics& g) override;
    void timerCallback() override;
    void setParameterID(int inParameterID);

private:
    SecondPluginAudioProcessor* mProcessor;
    int mParameterID;
    float mCh0Level;
    float mCh1Level;
};
