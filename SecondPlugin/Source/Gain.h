/*
  ==============================================================================

    Gain.h
    Created: 29 Oct 2022 2:37:07pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

class Gain 
{
    public:
        Gain();
        ~Gain();

        void process(
            float* inAudio,
            float inGain,
            float* outAudio,
            int numSamplesToRender
        );

    private:
};
