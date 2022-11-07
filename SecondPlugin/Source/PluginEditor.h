/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MainPanel.h"

//==============================================================================
/**
*/
class SecondPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SecondPluginAudioProcessorEditor (SecondPluginAudioProcessor&);
    ~SecondPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SecondPluginAudioProcessor& audioProcessor;

    // std::unique_ptr<MainPanel> mMainPanel;
    juce::ScopedPointer<MainPanel> mMainPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SecondPluginAudioProcessorEditor)
};
