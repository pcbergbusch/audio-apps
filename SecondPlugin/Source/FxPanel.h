/*
  ==============================================================================

    FxPanel.h
    Created: 5 Nov 2022 7:43:23pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "BasePanel.h"
#include "ParameterSlider.h"

enum class FxPanelStyle
{
    delay = 0,
    chorus,
    numStyles
};

class FxPanel
    : public BasePanel,
      public juce::ComboBox::Listener
{
public:
    FxPanel(SecondPluginAudioProcessor* inProcessor);
    ~FxPanel();

    void setFxPanelStyle(FxPanelStyle inStyle);
    void paint(juce::Graphics& g) override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

private:
    FxPanelStyle mStyle;
    juce::OwnedArray<ParameterSlider> mSliders;
};
