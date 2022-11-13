/*
  ==============================================================================

    CenterPanel.cpp
    Created: 5 Nov 2022 7:42:27pm
    Author:  pcber

  ==============================================================================
*/

#include "CenterPanel.h"

CenterPanel::CenterPanel(SecondPluginAudioProcessor* inProcessor)
    : BasePanel(inProcessor)
{
    setSize(CENTER_PANEL_WIDTH, CENTER_PANEL_HEIGHT);
    mMenuBar = std::make_unique<CenterPanelMenuBar>(inProcessor);
    mMenuBar->setTopLeftPosition(0, 0);
    addAndMakeVisible(*mMenuBar);

    mFxPanel = std::make_unique<FxPanel>(inProcessor);
    mFxPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    addAndMakeVisible(*mFxPanel);
}

CenterPanel::~CenterPanel()
{

}
