/*
  ==============================================================================

    Gain.cpp
    Created: 29 Oct 2022 2:37:07pm
    Author:  pcber

  ==============================================================================
*/

#include "Gain.h"

Gain::Gain()
{

}

Gain::~Gain()
{

}

void Gain::process(float* inAudio, float inGain, float* outAudio, int numSamplesToRender)
{
    for (int i = 0; i < numSamplesToRender; i++) {
        outAudio[i] = inAudio[i] * inGain;
    }
}
