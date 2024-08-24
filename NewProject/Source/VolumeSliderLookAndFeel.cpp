/*
  ==============================================================================

    VolumeSliderLookAndFeel.cpp
    Created: 23 Aug 2024 9:40:33pm
    Author:  jugur

  ==============================================================================
*/

#include "VolumeSliderLookAndFeel.h"


VolumeSliderLookAndFeel::VolumeSliderLookAndFeel()
{
    // You can initialize default colors or resources here if needed
}

void VolumeSliderLookAndFeel::drawLinearSlider(juce::Graphics& g,
    int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const juce::Slider::SliderStyle style, juce::Slider& slider)
{

    // Draw white measuring lines around the slid
// er
    g.setColour(juce::Colours::lightgrey);
    // Determine the number of measuring lines you want to draw
    int numLines = 12; // Change this to control the number of measuring lines

    if (style == juce::Slider::SliderStyle::LinearVertical)
    {
        int step = height / numLines;
        for (int i = 0; i <= numLines; ++i)
        {
            float lineY =y +  i * step;

            // Draw a line across the width of the slider's area
            g.drawLine(x, lineY, x + width, lineY, 0.5f);
        }
        // Draw the slider track
        juce::Rectangle<float> track(x + width * 0.5f - 2.0f, y, 5.0f, height);
        g.setColour(juce::Colours::black);
        g.fillRect(track);


        // Draw the slider thumb
        juce::Rectangle<float> thumb(x, sliderPos - 10.0f, width, 15.0f);
        g.setColour(juce::Colour::fromRGB(0x23, 0x23, 0x23));
        g.fillRect(thumb);

        // Draw a border around the thumb
        g.setColour(juce::Colours::black.withAlpha(1.0f));
        g.drawRect(thumb);
    }
    else if (style == juce::Slider::SliderStyle::LinearHorizontal)
    {
        int step = width / numLines;
        for (int i = 0; i <= numLines; ++i)
        {
            float lineX = x + i * step;

            // Draw a line across the height of the slider's area
            g.drawLine(lineX, y, lineX, y+height, 0.5f);
        }
        // Draw the slider track
        juce::Rectangle<float> track(x, y + height * 0.5f - 2.0f, width, 5.0f);
        g.setColour(juce::Colours::black);
        g.fillRect(track);


        // Draw the slider thumb
        juce::Rectangle<float> thumb(sliderPos - 10.0f, y, 15.0f, height);
        g.setColour(juce::Colour::fromRGB(0x23, 0x23, 0x23));
        g.fillRect(thumb);

        // Draw a border around the thumb
        g.setColour(juce::Colours::black.withAlpha(1.0f));
        g.drawRect(thumb);
    }


}

void VolumeSliderLookAndFeel::drawLinearSliderThumb(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    // Draw the slider thumb as a custom rectangle
    juce::Rectangle<float> thumbArea(x, sliderPos - (width * 0.5f), width, width);
    g.setColour(juce::Colours::silver);
    g.fillRect(thumbArea);

    // Add a shadow to the thumb for some depth
    g.setColour(juce::Colours::black.withAlpha(0.5f));
    g.drawRect(thumbArea);
}
