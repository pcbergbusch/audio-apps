/*
  ==============================================================================

    InterfaceDefines.h
    Created: 5 Nov 2022 7:56:44pm
    Author:  pcber

  ==============================================================================
*/

#include "JuceHeader.h"

#pragma once

#define MAIN_PANEL_WIDTH                750
#define MAIN_PANEL_HEIGHT               300

#define TOP_PANEL_WIDTH                 MAIN_PANEL_WIDTH
#define TOP_PANEL_HEIGHT                45

#define GAIN_PANEL_WIDTH                100
#define GAIN_PANEL_HEIGHT               MAIN_PANEL_HEIGHT - TOP_PANEL_HEIGHT

#define CENTER_PANEL_WIDTH              MAIN_PANEL_WIDTH - 2 * GAIN_PANEL_WIDTH
#define CENTER_PANEL_HEIGHT             GAIN_PANEL_HEIGHT

#define CENTER_PANEL_MENU_BAR_WIDTH     CENTER_PANEL_WIDTH
#define CENTER_PANEL_MENU_BAR_HEIGHT    35

#define FX_PANEL_WIDTH                  CENTER_PANEL_WIDTH
#define FX_PANEL_HEIGHT                 CENTER_PANEL_HEIGHT - CENTER_PANEL_MENU_BAR_HEIGHT

const juce::Colour colourSteel = juce::Colour(125, 125, 125);
const juce::Colour colourGray = juce::Colour(105, 105, 105);
const juce::Colour colourGrayTrans70 = juce::Colour(105, 105, 105).withAlpha(0.3f);
const juce::Colour colourBlackTrans100 = juce::Colour(0, 0, 0).withAlpha(0.0f);
const juce::Colour colourBlackTrans70 = juce::Colour(0, 0, 0).withAlpha(0.3f);
const juce::Colour colourBlackTrans40 = juce::Colour(0, 0, 0).withAlpha(0.6f);
const juce::Colour colourBlackTrans20 = juce::Colour(0, 0, 0).withAlpha(0.8f);

const juce::Font fontHelv12Bold{ "Helvetica Neue", 12.00f, juce::Font::bold };
const juce::Font fontHelv22Bold{ "Helvetica Neue", 22.00f, juce::Font::bold };
const juce::Font fontHelv48Bold{ "Helvetica Neue", 48.00f, juce::Font::bold };
