/*
  ==============================================================================

    Delay.h
    Created: 29 Oct 2022 2:37:56pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

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
        double mBuffer[2048];
        double mFeedbackSample;
        int mDelayIndex;
};
