/*
  ==============================================================================

   This file is part of the JUCE tutorials.
   Copyright (c) 2020 - Raw Material Software Limited

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:             SimpleSynthNoiseTutorial
 version:          2.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Simple noise synthesiser.

 dependencies:     juce_audio_basics, juce_audio_devices, juce_audio_formats,
                   juce_audio_processors, juce_audio_utils, juce_core,
                   juce_data_structures, juce_events, juce_graphics,
                   juce_gui_basics, juce_gui_extra
 exporters:        xcode_mac, vs2019, linux_make

 type:             Component
 mainClass:        MainContentComponent

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/


#pragma once

//==============================================================================
class MainContentComponent   : public juce::AudioAppComponent
{
public:
    MainContentComponent()
    {
        for (auto channel = 0; channel < 2; ++channel)
        {
            levelSlider[channel].setRange(0.0, 0.25);
            levelSlider[channel].setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
            levelLabel[channel].setText("Noise Level", juce::dontSendNotification);

            addAndMakeVisible(&levelSlider[channel]);
            addAndMakeVisible(&levelLabel[channel]);
        }

        setSize (800, 100);
        setAudioChannels (0, 2);
    }

    ~MainContentComponent() override
    {
        shutdownAudio();
    }

    void prepareToPlay (int, double) override {}

    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            auto levelChannel = std::min(channel, 1);
            auto level = (float) levelSlider[levelChannel].getValue();
            auto levelScale = level * 2.0f;

            auto* buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);

            for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
                *buffer++ = random.nextFloat() * levelScale - level;
        }
    }

    void releaseResources() override {}

    void resized() override
    {
        levelLabel[0].setBounds(10, 10, 90, 20);
        levelSlider[0].setBounds(100, 10, getWidth() - 110, 20);
        levelLabel[1].setBounds(10, 40, 90, 20);
        levelSlider[1].setBounds(100, 40, getWidth() - 110, 20);
    }

private:
    juce::Random random;
    juce::Slider levelSlider[2];
    juce::Label levelLabel[2];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
