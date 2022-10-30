/*
  ==============================================================================

    Delay.cpp
    Created: 29 Oct 2022 2:37:57pm
    Author:  pcber

  ==============================================================================
*/

#include "Delay.h"
#include "JuceHeader.h"

Delay::Delay()
:   mSampleRate(-1),
    mFeedbackSample(0.0),
    mDelayIndex(0)
{
    
}

Delay::~Delay()
{

}

void Delay::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void Delay::reset()
{
    juce::zeromem(mBuffer, sizeof(double) * 2048);
}

void Delay::process(
    float* inAudio,
    float inTime,
    float inFeedback,
    float inWetDry,
    float* outAudio,
    int numSamplesToRender
)
{
    const float wet = inWetDry;
    const float dry = 1.0f - wet;
    const float feedbackMapped = juce::jmap(inFeedback, 0.0f, 0.95f);
}
