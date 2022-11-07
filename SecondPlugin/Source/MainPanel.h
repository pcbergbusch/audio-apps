/*
  ==============================================================================

    MainPanel.h
    Created: 5 Nov 2022 7:43:18pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "BasePanel.h"
#include "TopPanel.h"
#include "GainPanel.h"
#include "CenterPanel.h"

class MainPanel
    :   public BasePanel
{
public:
    MainPanel(SecondPluginAudioProcessor* inProcessor);
    ~MainPanel();

private:
    juce::ScopedPointer<TopPanel> mTopPanel;
    juce::ScopedPointer<GainPanel> mGainInputPanel;
    juce::ScopedPointer<GainPanel> mGainOutputPanel;
    juce::ScopedPointer<CenterPanel> mCenterPanel;
};
