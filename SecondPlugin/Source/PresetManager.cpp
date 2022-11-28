/*
  ==============================================================================

    PresetManager.cpp
    Created: 23 Nov 2022 11:17:55pm
    Author:  pcber

  ==============================================================================
*/

#include "PresetManager.h"
#include "Parameters.h"

PresetManager::PresetManager(SecondPluginAudioProcessor* inProcessor)
    : mProcessor(inProcessor),
      mCurrentPresetXml(nullptr)
{

}

PresetManager::~PresetManager()
{

}

void PresetManager::setPresetsForXml(juce::XmlElement* inElement)
{
    for (int i = 0; i < (int) ParameterID::numParameters; i++) {
        inElement->setAttribute(
            parameterName[i],
            mProcessor->apvst->getParameter(parameterName[i])->getValue()
        );
    }
}

void PresetManager::loadPresetFromXml(juce::XmlElement* inElement)
{
    mCurrentPresetXml = inElement;

    for (int j = 0; j < mCurrentPresetXml->getNumAttributes(); j++) {
        const juce::String name = mCurrentPresetXml->getAttributeName(j);
        const float value = mCurrentPresetXml->getDoubleAttribute(name);

        for (int i = 0; i < (int)ParameterID::numParameters; i++) {
            if (parameterName[i] == name) {
                mProcessor->setParameterNotifyingHost(i, value);
            }
        }
    }
}
