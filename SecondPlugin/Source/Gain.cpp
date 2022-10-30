/*
  ==============================================================================

    Gain.cpp
    Created: 29 Oct 2022 2:37:07pm
    Author:  pcber

  ==============================================================================
*/

#include "Gain.h"
#include "JuceHeader.h"

Gain::Gain()
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
}
