/*
  ==============================================================================

    VolumeSliderLookAndFeel.h
    Created: 23 Aug 2024 9:40:33pm
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Constants.h"

using namespace juce;

class VolumeSliderLookAndFeel : public LookAndFeel_V4
{
public:
    /**
     * @brief Constructor to initialize the VolumeSliderLookAndFeel.
     */
    VolumeSliderLookAndFeel();

    /**
     * @brief Customizes the drawing of a linear slider.
     * @param g The Graphics object used for drawing.
     * @param x The x-coordinate of the slider's bounding box.
     * @param y The y-coordinate of the slider's bounding box.
     * @param width The width of the slider's bounding box.
     * @param height The height of the slider's bounding box.
     * @param sliderPos The current position of the slider's thumb.
     * @param minSliderPos The minimum possible position for the slider's thumb.
     * @param maxSliderPos The maximum possible position for the slider's thumb.
     * @param style The style of the slider (e.g., linear horizontal or vertical).
     * @param slider A reference to the Slider object being drawn.
     */
    void drawLinearSlider(Graphics& g,
        int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider) override;
};
