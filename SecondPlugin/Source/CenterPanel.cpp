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
    mMenuBar = new CenterPanelMenuBar(inProcessor);
    mMenuBar->setTopLeftPosition(0, 0);
    addAndMakeVisible(mMenuBar);

}

CenterPanel::~CenterPanel()
{

}
