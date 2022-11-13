/*
  ==============================================================================

    Delay.h
    Created: 29 Oct 2022 2:37:56pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "AudioHelpers.h"

class Delay
{
    public:
        Delay();
        ~Delay();

        void setSampleRate(float inSampleRate);

        void reset();

        void process(
            float* inAudio,
            float inTime,
            float inFeedback,
            float inWetDry,
            float* inModulationBuffer,
            float* outAudio,
            int numSamplesToRender
        );

    private:
        float mSampleRate;
        float mBuffer[maxBufferSize];
        float mFeedbackSample;
        int mDelayIndex;
        float mTimeSmoothed;

        float getInterpolatedSample(float delayTimeInSamples);
};
