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
    juce::AudioParameterFloat* delayTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(3);

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

    mDelayTimeSlider.setBounds(300, 0, 100, 100);
    mDelayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTimeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mDelayTimeSlider.setRange(delayTimeParameter->range.start, delayTimeParameter->range.end);
    mDelayTimeSlider.setValue(*delayTimeParameter);
   
    mGainControlSlider.onDragStart = [gainParameter] {gainParameter->beginChangeGesture();};
    mGainControlSlider.onValueChange = [this, gainParameter] {*gainParameter = mGainControlSlider.getValue();};
    mGainControlSlider.onDragEnd = [gainParameter] {gainParameter->endChangeGesture();};
    addAndMakeVisible(mGainControlSlider);

    mDryWetSlider.onDragStart = [dryWetParameter] {dryWetParameter->beginChangeGesture(); };
    mDryWetSlider.onValueChange = [this, dryWetParameter] {*dryWetParameter = mDryWetSlider.getValue(); };
    mDryWetSlider.onDragEnd = [dryWetParameter] {dryWetParameter->endChangeGesture(); };
    addAndMakeVisible(mDryWetSlider);

    mFeedbackSlider.onDragStart = [feedbackParameter] {feedbackParameter->beginChangeGesture(); };
    mFeedbackSlider.onValueChange = [this, feedbackParameter] {*feedbackParameter = mFeedbackSlider.getValue(); };
    mFeedbackSlider.onDragEnd = [feedbackParameter] {feedbackParameter->endChangeGesture(); };
    addAndMakeVisible(mFeedbackSlider);

    mDelayTimeSlider.onDragStart = [delayTimeParameter] {delayTimeParameter->beginChangeGesture(); };
    mDelayTimeSlider.onValueChange = [this, delayTimeParameter] {*delayTimeParameter = mDelayTimeSlider.getValue(); };
    mDelayTimeSlider.onDragEnd = [delayTimeParameter] {delayTimeParameter->endChangeGesture(); };
    addAndMakeVisible(mDelayTimeSlider);
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
