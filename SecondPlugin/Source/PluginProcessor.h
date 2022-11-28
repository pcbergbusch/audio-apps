/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Gain.h"
#include "Delay.h"
#include "Lfo.h"
#include "Parameters.h"

//==============================================================================
/**
*/
class SecondPluginAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    SecondPluginAudioProcessor();
    ~SecondPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    std::unique_ptr<juce::AudioProcessorValueTreeState> apvst;

private:
    // juce::ScopedPointer<Gain> mGain[2];
    std::unique_ptr<Gain> mGainInput[2];
    std::unique_ptr<Delay> mDelay[2];
    std::unique_ptr<LFO> mLFO[2];
    std::unique_ptr<Gain> mGainOutput[2];
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void initializeDSP();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SecondPluginAudioProcessor);
};
