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

    if (style == juce::Slider::SliderStyle::LinearVertical)
    {
        int numLines = 30;
        int lineThickness = 1;
        g.setColour(Constants::textColor);

        g.drawRect(x, y-10, width, height+20, lineThickness);

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

    juce::Rectangle<float> track(x + width * 0.5f - 2.0f, y, 5.0f, height);
    g.setColour(juce::Colours::black);
    g.fillRect(track);

    juce::ColourGradient thumbGradient(juce::Colours::darkgrey, width / 2, sliderPos - 20.0f,
        juce::Colours::black, width / 2, sliderPos + 20.0f, false);
    thumbGradient.addColour(0.25f, juce::Colours::black);
    thumbGradient.addColour(0.27f, juce::Colours::darkgrey);
    thumbGradient.addColour(0.35f, juce::Colours::darkgrey.darker(0.4f));
    thumbGradient.addColour(0.70f, juce::Colours::darkgrey.darker(0.8f));
    thumbGradient.addColour(0.75f, juce::Colours::black);
    thumbGradient.addColour(0.85f, juce::Colours::darkgrey.darker(0.8f));
    g.setGradientFill(thumbGradient);

    juce::Rectangle<float> thumb(x+3, sliderPos - 20.0f, width-6, 40.0f);
    g.fillRect(thumb);

    juce::Rectangle<float> thumbCut(x+3, sliderPos-2, width-6, 2.0f);
    g.setColour(juce::Colours::black.withAlpha(0.7f));
    g.fillRect(thumbCut);

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

