/*
  ==============================================================================

    FxPanel.cpp
    Created: 5 Nov 2022 7:43:23pm
    Author:  pcber

  ==============================================================================
*/

#include "FxPanel.h"
#include "Parameters.h"
#include "AudioHelpers.h"

FxPanel::FxPanel(SecondPluginAudioProcessor* inProcessor)
    : BasePanel(inProcessor),
      juce::ComboBox::Listener()
{
    setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);
    const int currentStyle = int(mProcessor->getValueTreeState().getParameter(parameterName[(int)ParameterID::delayType])->getValue());
    setFxPanelStyle((FxPanelStyle) currentStyle);
}

FxPanel::~FxPanel()
{

}

void FxPanel::setFxPanelStyle(FxPanelStyle inStyle)
{
    mStyle = inStyle;

    mSliders.clear();
    mSliderLabels.clear();

    const int sliderSize = 56;
    int x = 130;
    int y = int(getHeight() * 0.5);

    switch (mStyle)
    {
        case (FxPanelStyle::delay):
        {
            ParameterSlider* time = new ParameterSlider(
                mProcessor->getValueTreeState(), parameterName[(int)ParameterID::delayTime]
            );
            time->setBounds(x, y, sliderSize, sliderSize);

            juce::Label* timeLabel = new juce::Label(
                parameterName[(int)ParameterID::delayTime],
                parameterName[(int)ParameterID::delayTime]
            );
            timeLabel->attachToComponent(time->getParentComponent(), false);
            
            addAndMakeVisible(*time);
            /*addAndMakeVisible(timeLabel);*/
            mSliders.add(time);
            mSliderLabels.add(timeLabel);
            x += sliderSize * 2;

            ParameterSlider* feedback = new ParameterSlider(
                mProcessor->getValueTreeState(), parameterName[(int)ParameterID::delayFeedback]
            );
            feedback->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(*feedback);
            mSliders.add(feedback);
            x += sliderSize * 2;

            ParameterSlider* wetDry = new ParameterSlider(
                mProcessor->getValueTreeState(), parameterName[(int)ParameterID::delayWetDry]
            );
            wetDry->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(*wetDry);
            mSliders.add(wetDry);
            x += sliderSize * 2;
        } break;

        case (FxPanelStyle::chorus):
        {
            ParameterSlider* rate = new ParameterSlider(
                mProcessor->getValueTreeState(), parameterName[(int)ParameterID::modulationRate]
            );
            rate->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(*rate);
            mSliders.add(rate);
            x += sliderSize * 2;

            ParameterSlider* depth = new ParameterSlider(
                mProcessor->getValueTreeState(), parameterName[(int)ParameterID::modulationDepth]
            );
            depth->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(*depth);
            mSliders.add(depth);
            x += sliderSize * 2;

            ParameterSlider* wetDry = new ParameterSlider(
                mProcessor->getValueTreeState(), parameterName[(int)ParameterID::delayWetDry]
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
    repaint();
}

void FxPanel::paint(juce::Graphics& g)
{
    BasePanel::paint(g);

    switch (mStyle)
    {
        case (FxPanelStyle::delay):
        {
            g.drawFittedText("DELAY", 0, 0, getWidth(), int(getHeight() * 0.75), juce::Justification::centred, 1);
        } break;
        case (FxPanelStyle::chorus):
        {
            g.drawFittedText("CHORUS", 0, 0, getWidth(), int(getHeight() * 0.75), juce::Justification::centred, 1);
        } break;
        case (FxPanelStyle::numStyles):
        default:
        {
            g.drawFittedText("Wrong Place", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
            jassertfalse;
        } break;
    }

    for (int i = 0; i < mSliders.size(); i++) {
        paintComponentLabel(g, mSliders[i]);
    }
}

void FxPanel::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    FxPanelStyle style = (FxPanelStyle)comboBoxThatHasChanged->getSelectedItemIndex();
    setFxPanelStyle(style);
}
