/*
  ==============================================================================

    GainPanel.cpp
    Created: 5 Nov 2022 7:43:29pm
    Author:  pcber

  ==============================================================================
*/

#include "GainPanel.h"
#include "Parameters.h"

GainPanel::GainPanel(SecondPluginAudioProcessor* inProcessor)
    : BasePanel(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH, GAIN_PANEL_HEIGHT);
}

GainPanel::~GainPanel()
{

}

void GainPanel::setParameterID(ParameterID inParameterID)
{
    mSlider = std::make_unique<ParameterSlider>(*mProcessor->apvst, parameterName[(int)inParameterID]);
    const int sliderSize = 54;
    mSlider->setBounds(
        int(getWidth() * 0.5 - sliderSize * 0.5),
        int(getHeight() * 0.5 - sliderSize * 0.5),
        sliderSize,
        sliderSize
    );
    addAndMakeVisible(*mSlider);

    mSliderLabel = std::make_unique<juce::Label>(parameterName[(int)inParameterID], parameterName[(int)inParameterID]);
    mSliderLabel->attachToComponent(mSlider->getChildComponent(0), true);
    addAndMakeVisible(*mSliderLabel);
}
