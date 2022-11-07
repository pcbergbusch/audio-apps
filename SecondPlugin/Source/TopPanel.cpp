/*
  ==============================================================================

    TopPanel.cpp
    Created: 5 Nov 2022 7:42:33pm
    Author:  pcber

  ==============================================================================
*/

#include "TopPanel.h"

TopPanel::TopPanel(SecondPluginAudioProcessor* inProcessor)
    : BasePanel(inProcessor)
{
    setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);
}

TopPanel::~TopPanel()
{

}

void TopPanel::paint(juce::Graphics& g)
{
    BasePanel::paint(g);

    g.drawFittedText(
        "PAUL'S SECOND PLUGIN",
        0, 0,
        getWidth() - 10, getHeight(),
        juce::Justification::centredRight,
        1
    );
}
