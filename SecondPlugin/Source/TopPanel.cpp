/*
  ==============================================================================

    TopPanel.cpp
    Created: 5 Nov 2022 7:42:33pm
    Author:  pcber

  ==============================================================================
*/

#include "TopPanel.h"

TopPanel::TopPanel(SecondPluginAudioProcessor* inProcessor)
    : BasePanel(inProcessor),
      juce::Button::Listener(), juce::ComboBox::Listener(), juce::ValueTree::Listener()
{
    setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    configureButton(mSaveButton, "Save");
    configureButton(mDeleteButton, "Delete");
    configureButton(mPreviousPresetButton, "<");
    configureButton(mNextPresetButton, ">");

    mPresetList.setTextWhenNothingSelected("No Preset Selected");
    mPresetList.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    addAndMakeVisible(mPresetList);
    loadPresetList();
    mPresetList.addListener(this);

    mProcessor->getValueTreeState().state.addListener(this);
}

TopPanel::~TopPanel()
{
    mSaveButton.removeListener(this);
    mDeleteButton.removeListener(this);
    mPreviousPresetButton.removeListener(this);
    mNextPresetButton.removeListener(this);
    mPresetList.removeListener(this);
    mProcessor->getValueTreeState().state.removeListener(this);
}

void TopPanel::paint(juce::Graphics& g)
{
    BasePanel::paint(g);
}

void TopPanel::buttonClicked(juce::Button* button)
{
    if (button == &mSaveButton)
    {
        mFileChooser = std::make_unique<juce::FileChooser>(
            "Please enter the name of the preset to save",
            PresetManager::defaultDirectory,
            "*." + PresetManager::extension
        );
        mFileChooser->launchAsync(
            juce::FileBrowserComponent::saveMode, [&](const juce::FileChooser& chooser)
                {
                    const auto resultFile = chooser.getResult();
                    mProcessor->getPresetManager().savePreset(
                        mProcessor->getValueTreeState(),
                        resultFile.getFileNameWithoutExtension()
                    );
                    loadPresetList();
                }
        );
    }
    if (button == &mPreviousPresetButton)
    {
        const auto index = mProcessor->getPresetManager().loadPreviousPreset(mProcessor->getValueTreeState());
        mPresetList.setSelectedItemIndex(index, juce::dontSendNotification);
    }
    if (button == &mNextPresetButton)
    {
        const auto index = mProcessor->getPresetManager().loadNextPreset(mProcessor->getValueTreeState());
        mPresetList.setSelectedItemIndex(index, juce::dontSendNotification);
    }
    if (button == &mDeleteButton)
    {
        mProcessor->getPresetManager().deletePreset(mProcessor->getPresetManager().getCurrentPreset());
        loadPresetList();
    }
}

void TopPanel::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &mPresetList)
    {
        mProcessor->getPresetManager().loadPreset(
            mProcessor->getValueTreeState(),
            mPresetList.getItemText(mPresetList.getSelectedItemIndex())
        );
    }
}

void TopPanel::valueTreePropertyChanged(
    juce::ValueTree& treeWhosePropertyHasChanged,
    const juce::Identifier& property
)
{
    if (property.toString() == PresetManager::presetNameProperty) {
        loadPresetList();
    }
}

void TopPanel::configureButton(juce::Button& button, const juce::String& buttonText)
{
    button.setButtonText(buttonText);
    button.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    addAndMakeVisible(button);
    button.addListener(this);
}

void TopPanel::loadPresetList()
{
    mPresetList.clear(juce::dontSendNotification);
    const auto allPresets = mProcessor->getPresetManager().getAllPresets();
    const auto currentPreset = mProcessor->getPresetManager().getCurrentPreset();
    mPresetList.addItemList(allPresets, 1);
    mPresetList.setSelectedItemIndex(allPresets.indexOf(currentPreset), juce::dontSendNotification);
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
