/*
  ==============================================================================

    FxPanel.h
    Created: 5 Nov 2022 7:43:23pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "BasePanel.h"

enum FxPanelStyle
{
    FxPanelStyle_Delay,
    FxPanelStyle_Chorus,
    FxPanelStyle_TotalNumStyles
};

class FxPanel
    : public BasePanel
{
public:
    FxPanel(SecondPluginAudioProcessor* inProcessor);
    ~FxPanel();

    void setFxPanelStyle(FxPanelStyle iNStyle);
    void paint(juce::Graphics& g) override;

private:
    FxPanelStyle mStyle;
};
