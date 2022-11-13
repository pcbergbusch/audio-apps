/*
  ==============================================================================

    GainPanel.h
    Created: 5 Nov 2022 7:43:29pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "BasePanel.h"
#include "ParameterSlider.h"

class GainPanel
    : public BasePanel
{
public:
    GainPanel(SecondPluginAudioProcessor* inProcessor);
    ~GainPanel();

    void setParameterID(int inParameterID);

private:
    std::unique_ptr<ParameterSlider> mSlider;
};
