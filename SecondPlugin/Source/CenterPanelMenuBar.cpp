/*
  ==============================================================================

    CenterPanelMenuBar.cpp
    Created: 5 Nov 2022 7:43:58pm
    Author:  pcber

  ==============================================================================
*/

#include "CenterPanelMenuBar.h"

CenterPanelMenuBar::CenterPanelMenuBar(SecondPluginAudioProcessor* inProcessor)
    : BasePanel(inProcessor)
{
    setSize(CENTER_PANEL_MENU_BAR_WIDTH, CENTER_PANEL_MENU_BAR_HEIGHT);
}

CenterPanelMenuBar::~CenterPanelMenuBar()
{

}
