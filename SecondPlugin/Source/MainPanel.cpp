/*
  ==============================================================================

    MainPanel.cpp
    Created: 5 Nov 2022 7:43:18pm
    Author:  pcber

  ==============================================================================
*/

#include "MainPanel.h"

MainPanel::MainPanel(SecondPluginAudioProcessor* inProcessor)
    : BasePanel(inProcessor)
{
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);

    mTopPanel = new TopPanel(inProcessor);
    mTopPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(mTopPanel);

    mGainInputPanel = new GainPanel(inProcessor);
    mGainInputPanel->setTopLeftPosition(0, TOP_PANEL_HEIGHT);
    addAndMakeVisible(mGainInputPanel);

    mGainOutputPanel = new GainPanel(inProcessor);
    mGainOutputPanel->setTopLeftPosition(MAIN_PANEL_WIDTH - GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    addAndMakeVisible(mGainOutputPanel);

    mCenterPanel = new CenterPanel(inProcessor);
    mCenterPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    addAndMakeVisible(mCenterPanel);
}

MainPanel::~MainPanel()
{

}
