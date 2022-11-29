/*
  ==============================================================================

    TopPanel.cpp
    Created: 5 Nov 2022 7:42:33pm
    Author:  pcber

  ==============================================================================
*/

#include "TopPanel.h"

TopPanel::TopPanel(SecondPluginAudioProcessor* inProcessor)
    : BasePanel(inProcessor), juce::Button::Listener(), juce::ComboBox::Listener()
{
    setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    configureButton(mSaveButton, "Save");
    configureButton(mDeleteButton, "Delete");
    configureButton(mPreviousPresetButton, "<");
    configureButton(mNextPresetButton, ">");

    mPresetList.setTextWhenNothingSelected("No Preset Selected");
    mPresetList.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    addAndMakeVisible(mPresetList);
    mPresetList.addListener(this);
}

TopPanel::~TopPanel()
{
    mSaveButton.removeListener(this);
    mDeleteButton.removeListener(this);
    mPreviousPresetButton.removeListener(this);
    mNextPresetButton.removeListener(this);
    mPresetList.removeListener(this);
}

void TopPanel::paint(juce::Graphics& g)
{
    BasePanel::paint(g);

    /*g.drawFittedText(
        "PAUL'S SECOND PLUGIN",
        0, 0,
        getWidth() - 10, getHeight(),
        juce::Justification::centredRight,
        1
    );*/
}

void TopPanel::buttonClicked(juce::Button*)
{

}

void TopPanel::comboBoxChanged(juce::ComboBox*)
{

}

void TopPanel::configureButton(juce::Button& button, const juce::String& buttonText)
{
    button.setButtonText(buttonText);
    button.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    addAndMakeVisible(button);
    button.addListener(this);
}

void TopPanel::resized()
{
    const auto container = getLocalBounds().reduced(4);
    auto bounds = container;

    mSaveButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.2f)).reduced(4));
    mPreviousPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).reduced(4));
    mPresetList.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.4f)).reduced(4));
    mNextPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).reduced(4));
    mDeleteButton.setBounds(bounds.reduced(4));
}
