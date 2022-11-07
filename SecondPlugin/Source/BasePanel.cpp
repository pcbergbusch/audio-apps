/*
  ==============================================================================

    BasePanel.cpp
    Created: 5 Nov 2022 7:42:43pm
    Author:  pcber

  ==============================================================================
*/

#include "BasePanel.h"

BasePanel::BasePanel(SecondPluginAudioProcessor* inProcessor)
{

}

BasePanel::~BasePanel()
{

}

void BasePanel::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::whitesmoke);
    g.fillAll();

    g.setColour(juce::Colours::black);
    g.drawRect(1, 1, getWidth() - 1, getHeight() - 1, 2);
}
