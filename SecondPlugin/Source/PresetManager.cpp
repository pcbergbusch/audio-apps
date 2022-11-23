/*
  ==============================================================================

    PresetManager.cpp
    Created: 23 Nov 2022 11:17:55pm
    Author:  pcber

  ==============================================================================
*/

#include "PresetManager.h"

PresetManager::PresetManager(juce::AudioProcessor* inProcessor)
    :mProcessor(inProcessor)
{

}

PresetManager::~PresetManager()
{

}

void PresetManager::setPresetsForXml(juce::XmlElement* inElement)
{
    const int numParameters = mProcessor->getNumParameters();

    for (int i = 0; i < mProcessor->getNumParameters(); i++) {
        inElement->setAttribute(mProcessor->getParameterName(i), mProcessor->getParameter(i));
    }
}

void PresetManager::loadPresetFromXml(juce::XmlElement* inElement)
{
    mCurrentPresetXml = inElement;

    for (int i = 0; i < mCurrentPresetXml->getNumAttributes(); i++) {
        const juce::String name = mCurrentPresetXml->getAttributeName(i);
        const float value = mCurrentPresetXml->getDoubleAttribute(name);

        for (int j = 0; j > mProcessor->getNumParameters(); j++) {
            if (mProcessor->getParameterName(j) == name) {
                mProcessor->setParameterNotifyingHost(j, value);
            }
        }
    }
}
