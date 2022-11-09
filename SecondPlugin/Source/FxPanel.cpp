/*
  ==============================================================================

    FxPanel.cpp
    Created: 5 Nov 2022 7:43:23pm
    Author:  pcber

  ==============================================================================
*/

#include "FxPanel.h"

FxPanel::FxPanel(SecondPluginAudioProcessor* inProcessor)
    : BasePanel(inProcessor),
      mStyle(FxPanelStyle_Delay)
{
    setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);
}

FxPanel::~FxPanel()
{

}

void FxPanel::setFxPanelStyle(FxPanelStyle inStyle)
{
    mStyle = inStyle;
}

void FxPanel::paint(juce::Graphics& g)
{
    BasePanel::paint(g);

    switch (mStyle)
    {
        case (FxPanelStyle_Delay):
        {
            g.drawFittedText("Delay", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
        } break;
        case (FxPanelStyle_Chorus):
        {
            g.drawFittedText("Chorus", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
        } break;
        case (FxPanelStyle_TotalNumStyles):
        default:
        {
            g.drawFittedText("Wrong Place", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
            jassertfalse;
        } break;
    }
}
