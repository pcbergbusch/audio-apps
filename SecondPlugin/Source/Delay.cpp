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
    mDelayIndex(0),
    mTimeSmoothed(0.0)
{
    
}

Delay::~Delay()
{

}

void Delay::setSampleRate(float inSampleRate)
{
    mSampleRate = inSampleRate;
}

void Delay::reset()
{
    mTimeSmoothed = 0.0;
    juce::zeromem(mBuffer, sizeof(float) * maxBufferSize);
}

void Delay::process(
    float* inAudio,
    float inTime,
    float inFeedback,
    float inWetDry,
    float inType,
    float* inModulationBuffer,
    float* outAudio,
    int inNumSamplesToRender
)
{
    const float wet = inWetDry;
    const float dry = 1.0f - wet;
    const float feedbackMapped = juce::jmap(inFeedback, 0.0f, 0.95f);

    // block-level smoothing: OK for audio parameters that are static, i.e., not modulated
    // mTimeSmoothed = mTimeSmoothed - smoothingCoeffGeneric * (mTimeSmoothed - inTime);

    for (int i = 0; i < inNumSamplesToRender; i++) {

        if ((int) inType == (int) DelayType::delay) {
            mTimeSmoothed = mTimeSmoothed - \
                smoothingCoeffFine * (mTimeSmoothed - inTime);
        }
        else {
            // sample-level smoothing: first modulate the parameter, then smooth the modulated value
            const float delayTimeModulation = (0.003f + (0.002f * inModulationBuffer[i]));
            mTimeSmoothed = mTimeSmoothed - \
                smoothingCoeffFine * (mTimeSmoothed - delayTimeModulation);
        }
        const float delayTimeInSamples = mTimeSmoothed * mSampleRate;

        // fill circular buffer with the current sample + desired feedback
        mBuffer[mDelayIndex] = inAudio[i] + mFeedbackSample * feedbackMapped;
        // get the earlier sample that we want to delay and add it to the output and the feedback
        const float delaySample = getInterpolatedSample(delayTimeInSamples);
        mFeedbackSample = delaySample;
        outAudio[i] = inAudio[i] * dry + delaySample * wet;
        // increment the circular buffer index
        mDelayIndex++;
        if (mDelayIndex >= maxBufferSize) {
            mDelayIndex -= maxBufferSize;
        }
    }
}

float Delay::getInterpolatedSample(
    float inDelayTimeInSamples
)
{
    float readPosition = mDelayIndex - inDelayTimeInSamples;
    if (readPosition < 0.0) {
        readPosition += maxBufferSize;
    }

    int readPosition1 = (int)readPosition;
    int readPosition2 = readPosition1 + 1;
    if (readPosition2 >= maxBufferSize) {
        readPosition2 -= maxBufferSize;
    }
    float value = (mBuffer[readPosition2] - mBuffer[readPosition1]) * (readPosition - readPosition1) + mBuffer[readPosition1];
    return value;
}
