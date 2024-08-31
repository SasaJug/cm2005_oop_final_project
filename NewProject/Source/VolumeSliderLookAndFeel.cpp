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

    int numLines = 10; // Change this to control the number of measuring lines

    if (style == juce::Slider::SliderStyle::LinearVertical)
    {
        int step = height / numLines;
        for (int i = 0; i <= numLines; ++i)
        {
            float lineY =y +  i * step;
            float lineThickness = 0.5f;
            if(i == 0 || i == numLines)
            {
                lineThickness = 1.0f;
            }

            g.setColour(Constants::textColor);
            g.drawLine(x, lineY, x + width, lineY, lineThickness);
        }

        juce::Rectangle<float> track(x + width * 0.5f - 2.0f, y, 5.0f, height-5);
        g.setColour(juce::Colours::black);
        g.fillRect(track);

        juce::ColourGradient thumbGradient(juce::Colours::grey.darker(0.4f), width / 2, sliderPos - 10.0f,
            juce::Colours::black, width/2, sliderPos + 5.0f, false);
        g.setGradientFill(thumbGradient);

        juce::Rectangle<float> thumb(x, sliderPos - 10.0f, width, 15.0f);
        g.fillRect(thumb);

        juce::Rectangle<float> thumbCut(x, sliderPos - 4.0f, width, 2.0f);
        g.setColour(juce::Colours::black.withAlpha(0.7f));
        g.fillRect(thumbCut);

       g.setColour(juce::Colours::black.withAlpha(0.5f));
       g.drawRect(thumb);
    }
    else if (style == juce::Slider::SliderStyle::LinearHorizontal)
    {
        int step = width / numLines;
        for (int i = 0; i <= numLines; ++i)
        {
            float lineX = x + i * step;
            float lineThickness = 0.5f;
            if (i == 0 || i == numLines)
            {
                lineThickness = 1.0f;
            }

            g.setColour(Constants::textColor);
            g.drawLine(lineX, y, lineX, y+height, lineThickness);
        }

        juce::Rectangle<float> track(x, y + height * 0.5f - 2.0f, width-5, 5.0f);
        g.setColour(juce::Colours::black);
        g.fillRect(track);


        juce::ColourGradient thumbGradient(juce::Colours::grey.darker(0.4f), sliderPos - 10.0f, height / 2,
            juce::Colours::black, sliderPos + 5.0f, height / 2,  false);
        g.setGradientFill(thumbGradient);

        juce::Rectangle<float> thumb(sliderPos - 10.0f, y, 15.0f, height);
        g.fillRect(thumb);

        juce::Rectangle<float> thumbCut(sliderPos - 4.0f, y, 2.0f, width);
        g.setColour(juce::Colours::black.withAlpha(0.7f));
        g.fillRect(thumbCut);

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
