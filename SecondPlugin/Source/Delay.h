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

        void setSampleRate(double inSampleRate);

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
        double mSampleRate;
        double mBuffer[maxBufferSize];
        double mFeedbackSample;
        int mDelayIndex;
        float mTimeSmoothed;

        double getInterpolatedSample(float delayTimeInSamples);
};
