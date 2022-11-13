/*
  ==============================================================================

    LFO.h
    Created: 29 Oct 2022 2:37:15pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "AudioHelpers.h"

class LFO
{
    public:
        LFO();
        ~LFO();

        void reset();
        void setSampleRate(float inSampleRate);
        void process(float inRate, float inDepth, int inNumSamples);
        float* getBuffer();

    private:
        float mSampleRate;
        float mPhase;
        float mBuffer[maxBufferSize];
};
