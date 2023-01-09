/*
  ==============================================================================

    VUMeter.cpp
    Created: 31 Dec 2022 12:04:43am
    Author:  pcber

  ==============================================================================
*/

#include "VUMeter.h"
#include "InterfaceDefines.h"
#include "Parameters.h"

VUMeter::VUMeter(SecondPluginAudioProcessor* inProcessor)
    : mProcessor(inProcessor),
      mParameterID(-1),
      mCh0Level(0.0f),
      mCh1Level(0.0f)
{

}

VUMeter::~VUMeter()
{

}

void VUMeter::paint(juce::Graphics& g)
{
    const int meterWidth = getWidth() / 3;
    // left meter
    g.setColour(colourBlackTrans20);
    g.fillRect(0, 0, meterWidth, getHeight());
    g.setColour(colourGray);
    g.fillRect(0, getHeight() - int(mCh0Level * getHeight()), meterWidth, int(mCh0Level * getHeight()));

    // right meter
    g.setColour(colourBlackTrans20);
    g.fillRect(meterWidth * 2, 0, meterWidth, getHeight());
    g.setColour(colourGray);
    g.fillRect(meterWidth * 2, getHeight() - int(mCh1Level * getHeight()), meterWidth, int(mCh1Level * getHeight()));
}

void VUMeter::timerCallback()
{
    float updatedCh0Level = 0.0f;
    float updatedCh1Level = 0.0f;

    switch (mParameterID)
    {
        case ((int) ParameterID::inputGain):
        {
            updatedCh0Level = mProcessor->getInputGainMeterLevel(0);
            updatedCh1Level = mProcessor->getInputGainMeterLevel(1);
        }
        break;

        case ((int) ParameterID::outputGain):
        {
            updatedCh0Level = mProcessor->getOutputGainMeterLevel(0);
            updatedCh1Level = mProcessor->getOutputGainMeterLevel(1);
        }
        break;
    }

    if (updatedCh0Level > mCh0Level)
    {
        mCh0Level = updatedCh0Level;
    }
    else
    {
        mCh0Level = smoothingCoeffMeter * (mCh0Level - updatedCh0Level) + updatedCh0Level;
    }

    if (updatedCh1Level > mCh1Level)
    {
        mCh1Level = updatedCh1Level;
    }
    else
    {
        mCh1Level = smoothingCoeffMeter * (mCh1Level - updatedCh1Level) + updatedCh1Level;
    }

    mCh0Level = 0.0f ? fabs(mCh0Level) < 1e-15 : mCh0Level;
    mCh1Level = 0.0f ? fabs(mCh1Level) < 1e-15 : mCh1Level;

    if (mCh0Level && mCh1Level) {
        repaint();
    }
}

void VUMeter::setParameterID(int inParameterID)
{
    mParameterID = inParameterID;
    startTimer(25);
}
