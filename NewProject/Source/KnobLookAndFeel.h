/*
  ==============================================================================

    KnobLookAndFeel.h
    Created: 24 Aug 2024 5:33:10pm
    Author:  Sasa Jugurdzija, with help from external resources.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Constants.h"

using namespace juce;

class KnobLookAndFeel : public juce::LookAndFeel_V4
{
public:
    /**
     * @brief Draws the rotary slider with custom style.
     * 
     * @param g The Graphics object used for drawing.
     * @param x The x-coordinate of the slider's bounding box.
     * @param y The y-coordinate of the slider's bounding box.
     * @param width The width of the slider's bounding box.
     * @param height The height of the slider's bounding box.
     * @param sliderPos The current position of the slider's thumb.
     * @param startAngle The starting angle for the rotary slider.
     * @param endAngle The ending angle for the rotary slider.
     * @param slider A reference to the Slider object being drawn.
     */
    void drawRotarySlider(juce::Graphics& g,
        int x, int y, int width, int height,
        float sliderPos, float startAngle, float endAngle,
        juce::Slider& slider) override;
};
