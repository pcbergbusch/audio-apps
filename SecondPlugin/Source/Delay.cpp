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
    juce::zeromem(mBuffer, sizeof(double) * maxBufferSizeForDelay);
}

void Delay::process(
    float* inAudio,
    float inTime,
    float inFeedback,
    float inWetDry,
    float* outAudio,
    int inNumSamplesToRender
)
{
    const float wet = inWetDry;
    const float dry = 1.0f - wet;
    const float feedbackMapped = juce::jmap(inFeedback, 0.0f, 0.95f);
    const float delayTimeInSamples = inTime * mSampleRate;
    DBG(inTime);

    for (int i = 0; i < inNumSamplesToRender; i++) {
        const float delaySample = getInterpolatedSample(delayTimeInSamples);
        mBuffer[mDelayIndex] = inAudio[i] + mFeedbackSample * feedbackMapped;
        outAudio[i] = inAudio[i] * dry + delaySample * wet;
        mFeedbackSample = delaySample;
        mDelayIndex++;
        if (mDelayIndex >= maxBufferSizeForDelay) {
            mDelayIndex -= maxBufferSizeForDelay;
        }
        DBG(outAudio[i], inAudio[i]);
    }
}

double Delay::getInterpolatedSample(
    float inDelayTimeInSamples
)
{
    double readPosition = (double)mDelayIndex - inDelayTimeInSamples;
    if (readPosition < 0.0f) {
        readPosition += maxBufferSizeForDelay;
    }

    int readPosition1 = (int)readPosition;
    int readPosition2 = readPosition1 + 1;
    if (readPosition2 >= maxBufferSizeForDelay) {
        readPosition2 -= maxBufferSizeForDelay;
    }
    double value = (mBuffer[readPosition2] - mBuffer[readPosition1]) * (readPosition - readPosition1) + mBuffer[readPosition1];
    return value;
}
