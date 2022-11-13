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
    const juce::String& inParameterID
)
    : juce::ComboBox(inParameterID)
{
    mAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(stateToControl, inParameterID, *this);
}

ParameterComboBox::~ParameterComboBox()
{

}
