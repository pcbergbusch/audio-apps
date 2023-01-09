/*
  ==============================================================================

    AudioHelpers.h
    Created: 29 Oct 2022 2:36:49pm
    Author:  pcber

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "LookAndFeel.h"

const static float smoothingCoeffGeneric = 0.04f;
const static float smoothingCoeffFine = 0.002f;
const static float smoothingCoeffMeter = 0.2f;

const static float PI = 3.14159265359f;

const static int maxBufferSize = 88200; // circular buffer must be longer than max delay time * sample rate

inline void paintComponentLabel(juce::Graphics& g, juce::Component* inComponent)
{
    const int x = inComponent->getX() - int(inComponent->getWidth() * 0.25);
    const int y = inComponent->getY() + inComponent->getHeight();
    const int width = int(inComponent->getWidth() * 1.5);
    const int height = 20;

    const juce::String label = inComponent->getName();

    const float cornerSize = 3.0f;
    g.setColour(colourBlackTrans40);
    g.fillRoundedRectangle(x, y, width, height, cornerSize);

    g.setColour(colourSteel);
    g.setFont(fontHelv12Bold);
    g.drawFittedText(label, x, y, width, height, juce::Justification::centred, 1);
}
