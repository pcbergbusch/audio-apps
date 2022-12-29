/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SecondPluginAudioProcessorEditor::SecondPluginAudioProcessorEditor (SecondPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    mMainPanel = std::make_unique<MainPanel>(&audioProcessor);
    mMainPanel->setBounds(0, 0, MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    addAndMakeVisible(*mMainPanel);

    mLookAndFeel = std::make_unique<LookAndFeel>();
    setLookAndFeel(mLookAndFeel.get());
    LookAndFeel::setDefaultLookAndFeel(mLookAndFeel.get());
    mBackgroundImage = juce::ImageCache::getFromMemory(BinaryData::kadenze_bg_png, BinaryData::kadenze_bg_pngSize);

    float sizeRatio = (float)MAIN_PANEL_WIDTH / (float)MAIN_PANEL_HEIGHT;
    getConstrainer()->setFixedAspectRatio(sizeRatio);  // fix the aspect ratio
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    setResizable(true, true);
    setResizeLimits(128, 128, 1024, 1024);
}

SecondPluginAudioProcessorEditor::~SecondPluginAudioProcessorEditor()
{
}

//==============================================================================
void SecondPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.drawImage(mBackgroundImage, getLocalBounds().toFloat());
}

void SecondPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    // mMainPanel->setBounds(getLocalBounds().removeFromTop(proportionOfHeight(0.1f)));
    float sc = (float) getLocalBounds().getWidth() / MAIN_PANEL_WIDTH;
    mMainPanel->setTransform(juce::AffineTransform::scale(sc));
}
