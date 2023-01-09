/*
  ==============================================================================

    Gain.cpp
    Created: 29 Oct 2022 2:37:07pm
    Author:  pcber

  ==============================================================================
*/

#include "Gain.h"
#include "AudioHelpers.h"

Gain::Gain()
    : mLevelSmoothed(0.0f)
{

}

Gain::~Gain()
{

}

void Gain::process(float* inAudio, float inGain, float* outAudio, int numSamplesToRender)
{
    float gainMapped = juce::jmap(inGain, -24.0f, 24.0f);
    gainMapped = juce::Decibels::decibelsToGain(gainMapped, -24.0f);
    for (int i = 0; i < numSamplesToRender; i++) {
        outAudio[i] = inAudio[i] * gainMapped;
    }

    mLevelSmoothed = smoothingCoeffMeter * (mLevelSmoothed - fabs(outAudio[0])) + fabs(outAudio[0]);
}

float Gain::getMeterLevel()
{
    return mLevelSmoothed;
}
