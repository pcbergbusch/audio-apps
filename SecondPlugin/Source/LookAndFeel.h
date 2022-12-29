/*
  ==============================================================================

    LookAndFeel.h
    Created: 21 Dec 2022 5:42:21pm
    Author:  pbergbusch

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "InterfaceDefines.h"

class LookAndFeel
    :public juce::LookAndFeel_V4
{
public:
    LookAndFeel() {
        // image assets
        mSliderImage = juce::ImageCache::getFromMemory(BinaryData::kadenze_knob_png, BinaryData::kadenze_knob_pngSize);

        // buttons
        setColour(juce::TextButton::buttonColourId, colourBlackTrans100);
        setColour(juce::TextButton::textColourOnId, colourSteel);
        setColour(juce::TextButton::textColourOffId, colourGray);

        // combo boxes
        setColour(juce::ComboBox::backgroundColourId, colourBlackTrans100);
        setColour(juce::ComboBox::outlineColourId, colourBlackTrans70);
        setColour(juce::ComboBox::arrowColourId, colourBlackTrans40);
        setColour(juce::ComboBox::textColourId, colourBlackTrans20);
    };
    ~LookAndFeel()
    {
    };

    // buttons
    juce::Font getTextButtonFont(juce::TextButton&, int buttonHeight) override
    {
        return fontHelv12Bold;
    }

    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        juce::Colour fillColour;
        if (button.isDown()) {
            fillColour = colourBlackTrans20;
        }
        else if (button.isMouseOver()) {
            fillColour = colourBlackTrans40;
        }
        else
        {
            fillColour = colourBlackTrans70;
        }

        const float cornerSize = 6.0f;
        const juce::Rectangle<float> bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);
        g.setColour(fillColour);
        g.fillRoundedRectangle(bounds.reduced(1), cornerSize);


    }

    // combo boxes
    juce::Font getLabelFont(juce::Label& label) override
    {
        return fontHelv12Bold;
    }

    void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
        bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
        const juce::String& text, const juce::String& shortcutKeyText,
        const juce::Drawable* icon, const juce::Colour* textColour) override
    {
        juce::Colour fillColour = isHighlighted ? colourBlackTrans70 : colourBlackTrans40;
        g.setColour(fillColour);

        const juce::Rectangle<int> r(area);
        g.fillRect(r.getX(), r.getY(), r.getWidth(), r.getHeight() - 1);

        juce::Colour txtColour = isTicked ? colourGrayTrans70 : colourGray;
        g.setColour(txtColour);
        g.setFont(fontHelv12Bold);

        r.withLeft(10);
        r.withY(1);
        g.drawFittedText(text, r, juce::Justification::left, 1);
    }

    void drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown,
        int buttonX, int buttonY, int buttonW, int buttonH,
        juce::ComboBox& box) override
    {
        const float cornerSize = 3.0f;
        const juce::Rectangle<int> boxBounds(0, 0, width, height);

        g.setColour(colourGrayTrans70);
        g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);

        juce::Rectangle<int> arrow(width - 30, 0, 20, height);

        juce::Path path;
        path.startNewSubPath(arrow.getX() + 3.0f, arrow.getCentreY() - 2.0f);
        path.lineTo(arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() + 3.0f);
        path.lineTo(arrow.toFloat().getRight() - 3.0f, arrow.toFloat().getCentreY() - 2.0f);

        juce::Colour arrowColour = box.findColour(juce::ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 0.9f : 0.2f);
        g.setColour(arrowColour);
        g.strokePath(path, juce::PathStrokeType(2.0f));
    }

    // sliders
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle,
        float rotaryEndAngle, juce::Slider& slider) override
    {
        const int numFrames = mSliderImage.getHeight() / mSliderImage.getWidth();
        const int frameIndex = (int)std::ceil(sliderPosProportional * (numFrames - 1));

        const float radius = juce::jmin(width * 0.5, height * 0.5);
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;

        g.drawImage(
            mSliderImage,
            rx, ry, 2.0 * radius, 2.0 * radius,
            0, frameIndex * mSliderImage.getWidth(),
            mSliderImage.getWidth(), mSliderImage.getWidth()
        );
    }

private:
    juce::Image mSliderImage;

};
