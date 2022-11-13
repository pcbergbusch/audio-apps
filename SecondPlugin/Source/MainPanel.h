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
    std::unique_ptr<TopPanel> mTopPanel;
    std::unique_ptr<GainPanel> mGainInputPanel;
    std::unique_ptr<GainPanel> mGainOutputPanel;
    std::unique_ptr<CenterPanel> mCenterPanel;
};
