/*
  ==============================================================================

    Parameters.h
    Created: 9 Nov 2022 10:28:29pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

enum parameterID
{
    inputGain = 0,
    delayTime,
    delayFeedback,
    delayWetDry,
    delayType,
    modulationRate,
    modulationDepth,
    outputGain
};

const static int totalNumParameters = 8;

static juce::String parameterName[totalNumParameters] =
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
