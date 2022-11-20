/*
  ==============================================================================

    CenterPanelMenuBar.h
    Created: 5 Nov 2022 7:43:58pm
    Author:  pcber

  ==============================================================================
*/

#pragma once

#include "BasePanel.h"
#include "ParameterComboBox.h"

class CenterPanelMenuBar
    : public BasePanel
{
public:
    CenterPanelMenuBar(SecondPluginAudioProcessor* inProcessor);
    ~CenterPanelMenuBar();

    void addFxTypeComboBoxListener(juce::ComboBox::Listener* inListener);
    void removeFxTypeComboBoxListener(juce::ComboBox::Listener* inListener);


private:
    std::unique_ptr<ParameterComboBox> mFxTypeComboBox;
};
