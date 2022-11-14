/*
  ==============================================================================

    MainPanel.cpp
    Created: 5 Nov 2022 7:43:18pm
    Author:  pcber

  ==============================================================================
*/

#include "MainPanel.h"
#include "Parameters.h"

MainPanel::MainPanel(SecondPluginAudioProcessor* inProcessor)
    : BasePanel(inProcessor)
{
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);

    mTopPanel = std::make_unique<TopPanel>(inProcessor);
    mTopPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(*mTopPanel);

    mGainInputPanel = std::make_unique<GainPanel>(inProcessor);
    mGainInputPanel->setTopLeftPosition(0, TOP_PANEL_HEIGHT);
    mGainInputPanel->setParameterID(ParameterID::inputGain);
    addAndMakeVisible(*mGainInputPanel);

    mGainOutputPanel = std::make_unique<GainPanel>(inProcessor);
    mGainOutputPanel->setTopLeftPosition(MAIN_PANEL_WIDTH - GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    mGainOutputPanel->setParameterID(ParameterID::outputGain);
    addAndMakeVisible(*mGainOutputPanel);

    mCenterPanel = std::make_unique<CenterPanel>(inProcessor);
    mCenterPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    addAndMakeVisible(*mCenterPanel);
}

MainPanel::~MainPanel()
{

}
