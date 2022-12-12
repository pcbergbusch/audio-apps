/*
  ==============================================================================

    TopPanel.h
    Created: 5 Nov 2022 7:42:33pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "BasePanel.h"

class TopPanel
    : public BasePanel, juce::Button::Listener, juce::ComboBox::Listener, juce::ValueTree::Listener
{
public:
    TopPanel(SecondPluginAudioProcessor* inProcessor);
    ~TopPanel();

    void paint(juce::Graphics& g) override;

private:
    void buttonClicked(juce::Button* button) override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    void valueTreePropertyChanged(
        juce::ValueTree& treeWhosePropertyHasChanged,
        const juce::Identifier& property
    ) override;

    void configureButton(juce::Button& button, const juce::String& buttonText);
    void loadPresetList();
    void resized() override;

    juce::TextButton mSaveButton, mDeleteButton, mPreviousPresetButton, mNextPresetButton;
    juce::ComboBox mPresetList;
    std::unique_ptr<juce::FileChooser> mFileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TopPanel);
};
