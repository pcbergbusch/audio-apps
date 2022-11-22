/*
  ==============================================================================

    ParameterComboBox.cpp
    Created: 12 Nov 2022 5:24:36pm
    Author:  pcber

  ==============================================================================
*/

#include "ParameterComboBox.h"

ParameterComboBox::ParameterComboBox(
    juce::AudioProcessorValueTreeState& stateToControl,
    const juce::String& inParameterName
)
    : juce::ComboBox(inParameterName)
{
    mAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(stateToControl, inParameterName, *this);
}

ParameterComboBox::~ParameterComboBox()
{

}
