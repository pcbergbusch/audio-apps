/*
  ==============================================================================

    Parameters.h
    Created: 9 Nov 2022 10:28:29pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

enum Parameter
{
    Parameter_InputGain = 0,
    Parameter_DelayTime,
    Parameter_DelayFeedback,
    Parameter_DelayWetDry,
    Parameter_DelayType,
    Parameter_OutputGain,
    Parameter_ModulationRate,
    Parameter_ModulationDepth,
    Parameter_TotalNumParameters
};

static juce::String ParameterID[Parameter_TotalNumParameters] =
{
    "Input Gain",
    "Time",
    "Feedback",
    "WetDry",
    "Type",
    "Output Gain",
    "Modulation Rate",
    "Modulation Depth",
};
