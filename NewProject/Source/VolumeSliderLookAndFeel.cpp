/*
  ==============================================================================

    VolumeSliderLookAndFeel.cpp
    Created: 23 Aug 2024 9:40:33pm
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#include "VolumeSliderLookAndFeel.h"

VolumeSliderLookAndFeel::VolumeSliderLookAndFeel()
{

}

void VolumeSliderLookAndFeel::drawLinearSlider(Graphics& g,
    int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const Slider::SliderStyle style, Slider& slider)
{
    int numLines = 10;

    if (style == Slider::SliderStyle::LinearVertical)
    {
        int step = height / numLines;
        for (int i = 0; i <= numLines; ++i)
        {
            float lineY = y + i * step;
            float lineThickness = (i == 0 || i == numLines) ? 1.0f : 0.5f;

            g.setColour(Constants::textColor);
            g.drawLine(x, lineY, x + width, lineY, lineThickness);
        }

        Rectangle<float> track(x + width * 0.5f - 2.0f, y, 5.0f, height - 5);
        g.setColour(Colours::black);
        g.fillRect(track);

        ColourGradient thumbGradient(Colours::grey.darker(0.4f), width / 2, sliderPos - 10.0f,
            Colours::black, width / 2, sliderPos + 5.0f, false);
        g.setGradientFill(thumbGradient);

        Rectangle<float> thumb(x, sliderPos - 10.0f, width, 15.0f);
        g.fillRect(thumb);

        Rectangle<float> thumbCut(x, sliderPos - 4.0f, width, 2.0f);
        g.setColour(Colours::black.withAlpha(0.7f));
        g.fillRect(thumbCut);

        g.setColour(Colours::black.withAlpha(0.5f));
        g.drawRect(thumb);
    }
    else if (style == Slider::SliderStyle::LinearHorizontal)
    {
        int step = width / numLines;
        for (int i = 0; i <= numLines; ++i)
        {
            float lineX = x + i * step;
            float lineThickness = (i == 0 || i == numLines) ? 1.0f : 0.5f;

            g.setColour(Constants::textColor);
            g.drawLine(lineX, y, lineX, y + height, lineThickness);
        }

        Rectangle<float> track(x, y + height * 0.5f - 2.0f, width - 5, 5.0f);
        g.setColour(Colours::black);
        g.fillRect(track);

        ColourGradient thumbGradient(Colours::grey.darker(0.4f), sliderPos - 10.0f, height / 2,
            Colours::black, sliderPos + 5.0f, height / 2, false);
        g.setGradientFill(thumbGradient);

        Rectangle<float> thumb(sliderPos - 10.0f, y, 15.0f, height);
        g.fillRect(thumb);

        Rectangle<float> thumbCut(sliderPos - 4.0f, y, 2.0f, width);
        g.setColour(Colours::black.withAlpha(0.7f));
        g.fillRect(thumbCut);

        g.setColour(Colours::black.withAlpha(1.0f));
        g.drawRect(thumb);
    }
}
