/*
  ==============================================================================

    ParameterComboBox.h
    Created: 12 Nov 2022 5:24:36pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class ParameterComboBox
    : public juce::ComboBox
{
public:
    ParameterComboBox(
        juce::AudioProcessorValueTreeState& stateToControl,
        const juce::String& inParameterID
    );

    ~ParameterComboBox();

private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterComboBox);
};
