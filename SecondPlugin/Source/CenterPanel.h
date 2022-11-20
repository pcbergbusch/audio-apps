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
#include "FxPanel.h"

class CenterPanel
    : public BasePanel
{
public:
    CenterPanel(SecondPluginAudioProcessor* inProcessor);
    ~CenterPanel();


private:
    std::unique_ptr<CenterPanelMenuBar> mMenuBar;
    std::unique_ptr<FxPanel> mFxPanel;
};
