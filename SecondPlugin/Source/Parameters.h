/*
  ==============================================================================

    Parameters.h
    Created: 9 Nov 2022 10:28:29pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

enum class ParameterID
{
    inputGain = 0,
    delayTime,
    delayFeedback,
    delayWetDry,
    delayType,
    modulationRate,
    modulationDepth,
    outputGain,
    numParameters
};

static juce::String parameterName[(int)ParameterID::numParameters] =
{
    "Input Gain",
    "Time",
    "Feedback",
    "WetDry",
    "Type",
    "Modulation Rate",
    "Modulation Depth",
    "Output Gain"
};
