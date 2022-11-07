/*
  ==============================================================================

    CenterPanel.h
    Created: 5 Nov 2022 7:42:27pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "BasePanel.h"
#include "CenterPanelMenuBar.h"

class CenterPanel
    : public BasePanel
{
public:
    CenterPanel(SecondPluginAudioProcessor* inProcessor);
    ~CenterPanel();

private:
    juce::ScopedPointer<CenterPanelMenuBar> mMenuBar;
};
