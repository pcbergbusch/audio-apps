/*
  ==============================================================================

    BasePanel.cpp
    Created: 5 Nov 2022 7:42:43pm
    Author:  pcber

  ==============================================================================
*/

#include "BasePanel.h"

BasePanel::BasePanel(SecondPluginAudioProcessor* inProcessor)
    : mProcessor(inProcessor)
{
    
}

BasePanel::~BasePanel()
{

}
void BasePanel::mouseEnter(const juce::MouseEvent& event)
{
    repaint();
}

void BasePanel::mouseExit(const juce::MouseEvent& event)
{
    repaint();
}

void BasePanel::paint(juce::Graphics& g)
{
    // here we could highlight panels as the mouse moves over them, etc.
    if (isMouseOver()) {
        // g.setColour(colourBlackTrans20);
        // g.fillAll();
    }
    // g.setColour(juce::Colours::whitesmoke);
    // g.fillAll();

    // g.setColour(juce::Colours::black);
    // g.drawRect(1, 1, getWidth() - 1, getHeight() - 1, 2);
}
