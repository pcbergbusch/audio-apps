/*
  ==============================================================================

    ParameterSlider.h
    Created: 12 Nov 2022 5:24:25pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class ParameterSlider
    : public juce::Slider
{
public:
    ParameterSlider(
        juce::AudioProcessorValueTreeState& stateToControl,
        const juce::String& inParameterName
    );

    ~ParameterSlider();

private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterSlider);
};
