/*
  ==============================================================================

    LFO.cpp
    Created: 29 Oct 2022 2:37:15pm
    Author:  pcber

  ==============================================================================
*/

#include "Lfo.h"
#include "JuceHeader.h"

LFO::LFO()
:   mSampleRate(-1),
    mPhase(0.0f)
{

}

LFO::~LFO()
{

}

void LFO::setSampleRate(float inSampleRate)
{
    mSampleRate = inSampleRate;
}

void LFO::reset()
{
    mPhase = 0.0f;
    juce::zeromem(mBuffer, sizeof(float) * maxBufferSize);
}

void LFO::process(float inRate, float inDepth, int inNumSamples)
{
    const float rate = juce::jmap(inRate, 0.01f, 10.0f);  // map 0->1 to 10Hz->10kHz

    for (int i = 0; i < inNumSamples; i++) {
        mPhase = mPhase + (rate / mSampleRate);
        if (mPhase > 1.0f) {
            mPhase -= 1.0f;
        }
        const float lfoPosition = sinf(mPhase * 2.0f * PI) * inDepth;
        mBuffer[i] = lfoPosition;
    }
}

float* LFO::getBuffer()
{
    return mBuffer;
}