/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstPluginAudioProcessorEditor::FirstPluginAudioProcessorEditor (FirstPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    auto& params = audioProcessor.getParameters();
    juce::AudioParameterFloat* gainParameter = (juce::AudioParameterFloat*)params.getUnchecked(0);
    juce::AudioParameterFloat* dryWetParameter = (juce::AudioParameterFloat*)params.getUnchecked(1);
    juce::AudioParameterFloat* feedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(2);
    juce::AudioParameterFloat* depthParameter = (juce::AudioParameterFloat*)params.getUnchecked(3);
    juce::AudioParameterFloat* rateParameter = (juce::AudioParameterFloat*)params.getUnchecked(4);
    juce::AudioParameterFloat* phaseOffsetParameter = (juce::AudioParameterFloat*)params.getUnchecked(5);
    juce::AudioParameterInt* typeParameter = (juce::AudioParameterInt*)params.getUnchecked(6);
    
    mGainControlSlider.setBounds(0, 0, 100, 100);
    mGainControlSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mGainControlSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mGainControlSlider.setRange(gainParameter->range.start, gainParameter->range.end);
    mGainControlSlider.setValue(*gainParameter);

    mDryWetSlider.setBounds(100, 0, 100, 100);
    mDryWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDryWetSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mDryWetSlider.setRange(dryWetParameter->range.start, dryWetParameter->range.end);
    mDryWetSlider.setValue(*dryWetParameter);

    mFeedbackSlider.setBounds(200, 0, 100, 100);
    mFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mFeedbackSlider.setRange(feedbackParameter->range.start, feedbackParameter->range.end);
    mFeedbackSlider.setValue(*feedbackParameter);

    mDepthSlider.setBounds(0, 100, 100, 100);
    mDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDepthSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mDepthSlider.setRange(depthParameter->range.start, depthParameter->range.end);
    mDepthSlider.setValue(*depthParameter);

    mRateSlider.setBounds(100, 100, 100, 100);
    mRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mRateSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mRateSlider.setRange(rateParameter->range.start, rateParameter->range.end);
    mRateSlider.setValue(*rateParameter);

    mPhaseOffsetSlider.setBounds(200, 100, 100, 100);
    mPhaseOffsetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mPhaseOffsetSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mPhaseOffsetSlider.setRange(phaseOffsetParameter->range.start, phaseOffsetParameter->range.end);
    mPhaseOffsetSlider.setValue(*phaseOffsetParameter);

    mGainControlSlider.onDragStart = [gainParameter] {gainParameter->beginChangeGesture();};
    mGainControlSlider.onValueChange = [this, gainParameter] {gainParameter->setValueNotifyingHost(mGainControlSlider.getValue()); };
    mGainControlSlider.onDragEnd = [gainParameter] {gainParameter->endChangeGesture();};
    addAndMakeVisible(mGainControlSlider);

    mDryWetSlider.onDragStart = [dryWetParameter] {dryWetParameter->beginChangeGesture(); };
    mDryWetSlider.onValueChange = [this, dryWetParameter] {dryWetParameter->setValueNotifyingHost(mDryWetSlider.getValue()); };
    mDryWetSlider.onDragEnd = [dryWetParameter] {dryWetParameter->endChangeGesture(); };
    addAndMakeVisible(mDryWetSlider);

    mFeedbackSlider.onDragStart = [feedbackParameter] {feedbackParameter->beginChangeGesture(); };
    mFeedbackSlider.onValueChange = [this, feedbackParameter] {feedbackParameter->setValueNotifyingHost(mFeedbackSlider.getValue()); };
    mFeedbackSlider.onDragEnd = [feedbackParameter] {feedbackParameter->endChangeGesture(); };
    addAndMakeVisible(mFeedbackSlider);

    mDepthSlider.onDragStart = [depthParameter] {depthParameter->beginChangeGesture(); };
    mDepthSlider.onValueChange = [this, depthParameter] {depthParameter->setValueNotifyingHost(mDepthSlider.getValue()); };
    mDepthSlider.onDragEnd = [depthParameter] {depthParameter->endChangeGesture(); };
    addAndMakeVisible(mDepthSlider);

    mRateSlider.onDragStart = [rateParameter] {rateParameter->beginChangeGesture(); };
    mRateSlider.onValueChange = [this, rateParameter] {rateParameter->setValueNotifyingHost(mRateSlider.getValue()); };
    mRateSlider.onDragEnd = [rateParameter] {rateParameter->endChangeGesture(); };
    addAndMakeVisible(mRateSlider);

    mPhaseOffsetSlider.onDragStart = [phaseOffsetParameter] {phaseOffsetParameter->beginChangeGesture(); };
    mPhaseOffsetSlider.onValueChange = [this, phaseOffsetParameter] {phaseOffsetParameter->setValueNotifyingHost(mPhaseOffsetSlider.getValue()); };
    mPhaseOffsetSlider.onDragEnd = [phaseOffsetParameter] {phaseOffsetParameter->endChangeGesture(); };
    addAndMakeVisible(mPhaseOffsetSlider);

    mTypeDropdown.setBounds(300, 100, 100, 100);
    mTypeDropdown.addItem("Chorus", 1);
    mTypeDropdown.addItem("Flanger", 2);
    mTypeDropdown.setSelectedId(typeParameter->get());
    mTypeDropdown.onChange = [this, typeParameter] {
        typeParameter->beginChangeGesture();
        *typeParameter = mTypeDropdown.getSelectedId();
        typeParameter->endChangeGesture();
    };
    addAndMakeVisible(mTypeDropdown);
}

FirstPluginAudioProcessorEditor::~FirstPluginAudioProcessorEditor()
{
}

//==============================================================================
void FirstPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void FirstPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
