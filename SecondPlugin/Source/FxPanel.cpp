/*
  ==============================================================================

    FxPanel.cpp
    Created: 5 Nov 2022 7:43:23pm
    Author:  pcber

  ==============================================================================
*/

#include "FxPanel.h"
#include "Parameters.h"

FxPanel::FxPanel(SecondPluginAudioProcessor* inProcessor)
    : BasePanel(inProcessor)
{
    setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);
    setFxPanelStyle(FxPanelStyle::delay);
}

FxPanel::~FxPanel()
{

}

void FxPanel::setFxPanelStyle(FxPanelStyle inStyle)
{
    mStyle = inStyle;

    mSliders.clear();

    const int sliderSize = 56;
    int x = 130;
    int y = getHeight() * 0.5;

    switch (mStyle)
    {
        case (FxPanelStyle::delay):
        {
            ParameterSlider* time = new ParameterSlider(
                mProcessor->apvst, parameterName[(int)ParameterID::delayTime]
            );
            time->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(*time);
            mSliders.add(time);
            x += sliderSize * 2;

            ParameterSlider* feedback = new ParameterSlider(
                mProcessor->apvst, parameterName[(int)ParameterID::delayFeedback]
            );
            feedback->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(*feedback);
            mSliders.add(feedback);
            x += sliderSize * 2;

            ParameterSlider* wetDry = new ParameterSlider(
                mProcessor->apvst, parameterName[(int)ParameterID::delayWetDry]
            );
            wetDry->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(*wetDry);
            mSliders.add(wetDry);
            x += sliderSize * 2;
        } break;

        case (FxPanelStyle::chorus):
        {
            ParameterSlider* rate = new ParameterSlider(
                mProcessor->apvst, parameterName[(int)ParameterID::modulationRate]
            );
            rate->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(*rate);
            mSliders.add(rate);
            x += sliderSize * 2;

            ParameterSlider* depth = new ParameterSlider(
                mProcessor->apvst, parameterName[(int)ParameterID::modulationDepth]
            );
            depth->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(*depth);
            mSliders.add(depth);
            x += sliderSize * 2;

            ParameterSlider* wetDry = new ParameterSlider(
                mProcessor->apvst, parameterName[(int)ParameterID::delayWetDry]
            );
            wetDry->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(*wetDry);
            mSliders.add(wetDry);
            x += sliderSize * 2;
        } break;

        case (FxPanelStyle::numStyles):
        default:
        {

            jassertfalse;
        } break;
    }
}

void FxPanel::paint(juce::Graphics& g)
{
    BasePanel::paint(g);

    switch (mStyle)
    {
        case (FxPanelStyle::delay):
        {
            g.drawFittedText("Delay", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
        } break;
        case (FxPanelStyle::chorus):
        {
            g.drawFittedText("Chorus", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
        } break;
        case (FxPanelStyle::numStyles):
        default:
        {
            g.drawFittedText("Wrong Place", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
            jassertfalse;
        } break;
    }
}
