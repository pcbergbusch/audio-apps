/*
  ==============================================================================

    CenterPanelMenuBar.cpp
    Created: 5 Nov 2022 7:43:58pm
    Author:  pcber

  ==============================================================================
*/

#include "CenterPanelMenuBar.h"
#include "Parameters.h"

CenterPanelMenuBar::CenterPanelMenuBar(SecondPluginAudioProcessor* inProcessor)
    : BasePanel(inProcessor)
{
    setSize(CENTER_PANEL_MENU_BAR_WIDTH, CENTER_PANEL_MENU_BAR_HEIGHT);

    mFxTypeComboBox = std::make_unique<ParameterComboBox>(
        mProcessor->getValueTreeState(),
        parameterName[(int)ParameterID::delayType]
    );
    const int width = 85;
    mFxTypeComboBox->setBounds(getWidth() - width, 0, width, getHeight());
    mFxTypeComboBox->addItem("DELAY", 1);
    mFxTypeComboBox->addItem("CHORUS", 2);
    int currentStyle = int(mProcessor->getValueTreeState().getParameter(parameterName[(int)ParameterID::delayType])->getValue());
    mFxTypeComboBox->setSelectedItemIndex(currentStyle);
    addAndMakeVisible(*mFxTypeComboBox);
}

CenterPanelMenuBar::~CenterPanelMenuBar()
{

}

void CenterPanelMenuBar::addFxTypeComboBoxListener(juce::ComboBox::Listener* inListener)
{
    mFxTypeComboBox->addListener(inListener);
}

void CenterPanelMenuBar::removeFxTypeComboBoxListener(juce::ComboBox::Listener* inListener)
{
    mFxTypeComboBox->removeListener(inListener);
}
