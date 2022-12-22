/*
  ==============================================================================

    LookAndFeel.h
    Created: 21 Dec 2022 5:42:21pm
    Author:  pbergbusch

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "InterfaceDefines.h"

class LookAndFeel
    :public juce::LookAndFeel_V4
{
public:
    LookAndFeel();
    ~LookAndFeel();

    juce::Font getTextButtonFont(juce::TextButton&, int buttonHeight) override
    {
        return fontHelv12Bold;
    }

    void drawButtonBackground(Graphics&, Button&, const Colour& backgroundColour,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        juce::Colour fillColour;
    }

};
