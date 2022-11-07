/*
  ==============================================================================

    GainPanel.cpp
    Created: 5 Nov 2022 7:43:29pm
    Author:  pcber

  ==============================================================================
*/

#include "GainPanel.h"

GainPanel::GainPanel(SecondPluginAudioProcessor* inProcessor)
    : BasePanel(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH, GAIN_PANEL_HEIGHT);
}

GainPanel::~GainPanel()
{

}
