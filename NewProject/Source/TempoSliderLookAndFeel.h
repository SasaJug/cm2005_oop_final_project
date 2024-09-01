/*
  ==============================================================================

    TempoSliderLookAndFeel.h
    Created: 20 Aug 2024 8:29:38pm
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Constants.h"

class TempoSliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    /**
     * @brief Constructor to initialize the TempoSliderLookAndFeel.
     *
     */
    TempoSliderLookAndFeel();

    /**
     * @brief Destructor for TempoSliderLookAndFeel.
     *
     */
    ~TempoSliderLookAndFeel() override = default;

    /**
     * @brief Customizes the drawing of a linear slider.
     *
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
     *
     * This method is responsible for rendering the visual appearance of the slider,
     * including the track, thumb, and any additional decorations. It allows the slider
     * to have a customized look that fits the overall design of the application.
     */
    void drawLinearSlider(juce::Graphics& g,
        int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const juce::Slider::SliderStyle, juce::Slider& slider) override;
};
