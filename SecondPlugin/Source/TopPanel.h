/*
  ==============================================================================

    TopPanel.h
    Created: 5 Nov 2022 7:42:33pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "BasePanel.h"

class TopPanel
    : public BasePanel
{
public:
    TopPanel(SecondPluginAudioProcessor* inProcessor);
    ~TopPanel();

    void paint(juce::Graphics& g) override;

private:

};
