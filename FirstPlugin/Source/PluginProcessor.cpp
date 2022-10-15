/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#define _USE_MATH_DEFINES
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>

//==============================================================================
FirstPluginAudioProcessor::FirstPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(mGainParameter = new juce::AudioParameterFloat("gain", "Gain", 0.0f, 1.0f, 0.5f));
    addParameter(mDryWetParameter = new juce::AudioParameterFloat("drywet", "Dry Wet", 0.0f, 1.0f, 0.5f));
    addParameter(mFeedbackParameter = new juce::AudioParameterFloat("feedback", "Feedback", 0.0f, 1.0f, 0.5f));
    addParameter(mDepthParameter = new juce::AudioParameterFloat("depth", "Delay LFO Depth", 0.0f, 1.0f, 0.5f));
    addParameter(mRateParameter = new juce::AudioParameterFloat("rate", "Delay LFO Rate", 0.0f, 20.0f, 10.0f));
    addParameter(mPhaseOffsetParameter = new juce::AudioParameterFloat("phase", "Delay LFO Phase", 0.0f, 1.0f, 0.0f));
    addParameter(mTypeParameter = new juce::AudioParameterInt("type", "Type", 1, 2, 1));
    mGainSmoothed = 0.0;
    mDelayTimeSmoothed = 0.0;

    mCircularBufferLeft = nullptr;
    mCircularBufferRight = nullptr;
    mCircularBufferWriteHead = 0;
    mCircularBufferLength = 0;
    mLFOPhase = 0.0;
    mDelayTimeInSamples = 0.0;
    mDelayReadHead = 0.0;
    mFeedbackLeft = 0.0;
    mFeedbackRight = 0.0;
}

FirstPluginAudioProcessor::~FirstPluginAudioProcessor()
{
    if (mCircularBufferLeft != nullptr) {
        delete [] mCircularBufferLeft;
        mCircularBufferLeft = nullptr;
    }
    if (mCircularBufferRight != nullptr) {
        delete[] mCircularBufferRight;
        mCircularBufferRight = nullptr;
    }
}

//==============================================================================
const juce::String FirstPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FirstPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FirstPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FirstPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FirstPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FirstPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FirstPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FirstPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FirstPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void FirstPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FirstPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mGainSmoothed = mGainParameter->get();
    mDelayTimeSmoothed = 1.0;
    mLFOPhase = 0.0;

    mCircularBufferLength = sampleRate * MAX_DELAY_TIME;
    if (mCircularBufferLeft == nullptr) {
        mCircularBufferLeft = new float[mCircularBufferLength]();
    }
    if (mCircularBufferRight == nullptr) {
        mCircularBufferRight = new float[mCircularBufferLength]();
    }
    mCircularBufferWriteHead = 0;
}

void FirstPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FirstPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

float FirstPluginAudioProcessor::lin_interp(float x1, float x2, float phase)
{
    return x1 + phase * (x2 - x1);
}

void FirstPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    /*
    DBG("mGainParameter: " << (juce::String&)mGainParameter);
    DBG("mDryWetParameter:" << (juce::String&)mDryWetParameter);
    DBG("mFeedbackParameter:" << (juce::String&)mFeedbackParameter);
    DBG("mDepthParameter:" << (juce::String&)mDepthParameter);
    DBG("mRateParameter:" << (juce::String&)mRateParameter);
    DBG("mPhaseOffsetParameter:" << (juce::String&)mPhaseOffsetParameter);
    DBG("mTypeParameter:" << (juce::String&)mTypeParameter);
    */

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    auto* channelLeft = buffer.getWritePointer(0);
    auto* channelRight = buffer.getWritePointer(1);

    // ..do something to the data...
    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        // we want one full cycle, from [0, 2PI] radians, so mLFOPhase must range from [0, 1]
        float lfoOut = sin(2.0 * M_PI * mLFOPhase);
        mLFOPhase += *mRateParameter * getSampleRate();
        if (mLFOPhase > 1.0) {
            mLFOPhase -= 1.0;
        }
        // map the LFO ouptut range sin([0, 2PI]) = [-1, 1] to the range of delays we desire in seconds [0.005, 0.030]
        float lfoOutMapped = juce::jmap(lfoOut, -1.0f, 1.0f, 0.005f, 0.030f);

        mGainSmoothed -= 0.004 * (mGainSmoothed - mGainParameter->get());
        channelLeft[sample] *= mGainSmoothed;
        channelRight[sample] *= mGainSmoothed;
        mCircularBufferLeft[mCircularBufferWriteHead] = channelLeft[sample] + mFeedbackLeft;
        mCircularBufferRight[mCircularBufferWriteHead] = channelRight[sample] + mFeedbackRight;

        mDelayTimeSmoothed -= 0.001 * (mDelayTimeSmoothed - lfoOutMapped);
        mDelayTimeInSamples = getSampleRate() * mDelayTimeSmoothed;
        mDelayReadHead = mCircularBufferWriteHead - mDelayTimeInSamples;
        if (mDelayReadHead < 0) {
            mDelayReadHead += mCircularBufferLength;
        }

        int readHead_x1 = (int)mDelayReadHead;
        int readHead_x2 = readHead_x1 + 1;
        if (readHead_x2 >= mCircularBufferLength) {
            readHead_x2 -= mCircularBufferLength;
        }
        float readHeadPhase = mDelayReadHead - readHead_x1;

        float delay_sample_left = lin_interp(mCircularBufferLeft[readHead_x1], mCircularBufferLeft[readHead_x2], readHeadPhase);
        float delay_sample_right = lin_interp(mCircularBufferRight[readHead_x1], mCircularBufferRight[readHead_x2], readHeadPhase);
        // float delay_sample_left = mCircularBufferLeft[(int)mDelayReadHead];
        // float delay_sample_right = mCircularBufferRight[(int)mDelayReadHead];
        mFeedbackLeft = delay_sample_left * mFeedbackParameter->get();
        mFeedbackRight = delay_sample_right * mFeedbackParameter->get();

        buffer.setSample(0, sample, buffer.getSample(0, sample) * (1 - mDryWetParameter->get()) + delay_sample_left * mDryWetParameter->get());
        buffer.setSample(1, sample, buffer.getSample(1, sample) * (1 - mDryWetParameter->get()) + delay_sample_right * mDryWetParameter->get());

        mCircularBufferWriteHead++;
        if (mCircularBufferWriteHead >= mCircularBufferLength) {
            mCircularBufferWriteHead = 0;
        }
    }
}

//==============================================================================
bool FirstPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FirstPluginAudioProcessor::createEditor()
{
    return new FirstPluginAudioProcessorEditor(*this);
}

//==============================================================================
void FirstPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FirstPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FirstPluginAudioProcessor();
}
