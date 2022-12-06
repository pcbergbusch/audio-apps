/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PresetManager.h"

//==============================================================================
SecondPluginAudioProcessor::SecondPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (
        BusesProperties()
        #if ! JucePlugin_IsMidiEffect
            #if ! JucePlugin_IsSynth
                .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
            #endif
            .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
        #endif
      ),
      mValueTreeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    // It is better to save the current preset name and version in the juce::ApplicationProperties
    // rather than as properties of the state - because the xml file can be renamed by the user
    mValueTreeState.state.setProperty(PresetManager::presetNameProperty, "", nullptr);
    mValueTreeState.state.setProperty("version", ProjectInfo::versionString, nullptr);
    mPresetManager = std::make_unique<PresetManager>(mValueTreeState);
    initializeDSP();
}

SecondPluginAudioProcessor::~SecondPluginAudioProcessor()
{
}

//==============================================================================
const juce::String SecondPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SecondPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SecondPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SecondPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SecondPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SecondPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SecondPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SecondPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SecondPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void SecondPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SecondPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    for (int i = 0; i < 2; i++) {
        mDelay[i]->reset();
        mDelay[i]->setSampleRate(sampleRate);
        mLFO[i]->reset();
        mLFO[i]->setSampleRate(sampleRate);
    }
}

void SecondPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    for (int i = 0; i < 2; i++) {
        mDelay[i]->reset();
        mLFO[i]->reset();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SecondPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void SecondPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

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
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        // ..do something to the data...
        int param = 0;

        mGainInput[channel]->process(
            channelData,
            mValueTreeState.getParameter(parameterName[(int)ParameterID::inputGain])->getValue(),
            channelData,
            buffer.getNumSamples()
        );

        mDelay[channel]->process(
            channelData,
            mValueTreeState.getParameter(parameterName[(int)ParameterID::delayTime])->getValue(),
            mValueTreeState.getParameter(parameterName[(int)ParameterID::delayFeedback])->getValue(),
            mValueTreeState.getParameter(parameterName[(int)ParameterID::delayWetDry])->getValue(),
            mValueTreeState.getParameter(parameterName[(int)ParameterID::delayType])->getValue(),
            mLFO[channel]->getBuffer(),
            channelData,
            buffer.getNumSamples()
        );
        param++;

        mLFO[channel]->process(
            // no osc on channel 0, only channel 1 -> chorus effect
            (channel == 0) ? 0.0f : mValueTreeState.getParameter(parameterName[(int)ParameterID::modulationRate])->getValue(),
            mValueTreeState.getParameter(parameterName[(int)ParameterID::modulationDepth])->getValue(),
            buffer.getNumSamples()
        );

        mGainOutput[channel]->process(
            channelData,
            mValueTreeState.getParameter(parameterName[(int)ParameterID::outputGain])->getValue(),
            channelData,
            buffer.getNumSamples()
        );
    }
}

//==============================================================================
bool SecondPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SecondPluginAudioProcessor::createEditor()
{
    return new SecondPluginAudioProcessorEditor (*this);
}

//==============================================================================
void SecondPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = mValueTreeState.copyState();
    std::unique_ptr<juce::XmlElement> xml = state.createXml();
    copyXmlToBinary(*xml, destData);
}

void SecondPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState = getXmlFromBinary(data, sizeInBytes);

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(mValueTreeState.state.getType()))
            // to maintain backwards compatibility with previous preset versions, it is usually better to loop
            // through the state variables and reset just those required, rather than to replace the whole state
            mValueTreeState.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessorValueTreeState::ParameterLayout SecondPluginAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    for (int i = 0; i < (int)ParameterID::numParameters; i++) {
        layout.add(
            std::make_unique<juce::AudioParameterFloat>(
                parameterName[i],
                parameterName[i],
                juce::NormalisableRange<float>(0.0f, 1.0f),
                0.5f
            )
        );
    }

    return layout;
}

void SecondPluginAudioProcessor::initializeDSP()
{
    for (int i = 0; i < 2; i++) {
        mGainInput[i] = std::make_unique<Gain>();
        mDelay[i] = std::make_unique<Delay>();
        mLFO[i] = std::make_unique<LFO>();
        mGainOutput[i] = std::make_unique<Gain>();
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SecondPluginAudioProcessor();
}
