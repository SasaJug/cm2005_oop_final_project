/*
  ==============================================================================

    VolumeSliderLookAndFeel.h
    Created: 23 Aug 2024 9:40:33pm
    Author:  jugur

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class VolumeSliderLookAndFeel: public juce::LookAndFeel_V4
{
public:
    VolumeSliderLookAndFeel();
    ~VolumeSliderLookAndFeel() override = default;

    void drawLinearSlider(juce::Graphics& g,
        int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const juce::Slider::SliderStyle, juce::Slider& slider) override;

    void drawLinearSliderThumb(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style,
        juce::Slider& slider) override;
};
