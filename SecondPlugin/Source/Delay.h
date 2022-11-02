/*
  ==============================================================================

    Delay.h
    Created: 29 Oct 2022 2:37:56pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

static const int maxBufferSizeForDelay = 88200; // circular buffer must be longer than max delay time * sample rate

class Delay {
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
            float* outAudio,
            int numSamplesToRender
        );

    private:
        double mSampleRate;
        double mBuffer[maxBufferSizeForDelay];
        double mFeedbackSample;
        int mDelayIndex;

        double getInterpolatedSample(float delayTimeInSamples);
};
