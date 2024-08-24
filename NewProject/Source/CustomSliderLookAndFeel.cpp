/*
  ==============================================================================

    CustomSliderLookAndFeel.cpp
    Created: 20 Aug 2024 8:29:38pm
    Author:  jugur

  ==============================================================================
*/

#include "CustomSliderLookAndFeel.h"

CustomSliderLookAndFeel::CustomSliderLookAndFeel()
{
    // You can initialize default colors or resources here if needed
}

void CustomSliderLookAndFeel::drawLinearSlider(juce::Graphics& g,
    int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const juce::Slider::SliderStyle style, juce::Slider& slider)
{

    // Draw white measuring lines around the slid
// er
    g.setColour(juce::Colours::lightgrey);
    // Determine the number of measuring lines you want to draw
    int numLines = 30; // Change this to control the number of measuring lines
    float cornerRadius = 5.0f;
    float lineThickness = 1.0f;
    if (style == juce::Slider::SliderStyle::LinearVertical)
    {
        g.setColour(juce::Colours::lightgrey);

        g.drawRoundedRectangle(x, y-10, width, height+20, cornerRadius, lineThickness);

        int step = height / numLines;
        int initialY = y + 1.5*step;
        for (int i = 0; i <= numLines; ++i)
        {
            float lineY = initialY + i*step;

            // Draw a line across the width of the slider's area
            int length = 8;
            if(i % 5 == 0){
				length = 4;
            }
            g.drawLine(x + length, lineY, x + width - length, lineY, 0.5f);
        }
    }

    // Draw the background track (fader track)
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

void CustomSliderLookAndFeel::drawLinearSliderThumb(juce::Graphics& g, int x, int y, int width, int height,
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

