/*
  ==============================================================================

    ParameterSlider.cpp
    Created: 12 Nov 2022 5:24:25pm
    Author:  pcber

  ==============================================================================
*/

#include "ParameterSlider.h"

ParameterSlider::ParameterSlider(
    juce::AudioProcessorValueTreeState& stateToControl,
    const juce::String& inParameterName
)
    : juce::Slider(inParameterName)
{
    setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);
    setRange(0.0f, 1.0f, 0.001f);

    mAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(stateToControl, inParameterName, *this);
}

ParameterSlider::~ParameterSlider()
{

}
