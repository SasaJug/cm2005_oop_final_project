/*
  ==============================================================================

    KnobLookAndFeel.cpp
    Created: 24 Aug 2024 5:33:10pm
    Author:  Sasa Jugurdzija, with help from external resources.

  ==============================================================================
*/

#include "KnobLookAndFeel.h"

void KnobLookAndFeel::drawRotarySlider(Graphics& g,
    int x, int y, int width, int height,
    float sliderPos, float startAngle, float endAngle,
    Slider& slider)
{

    float outerMargin = 8.0f;
    auto radius = (float)jmin(width, height) / 2.0f - outerMargin;

    auto centerX = (float)x + (float)width * 0.5f;
    auto centerY = (float)y + (float)height * 0.5f;

    auto rw = radius * 2.0f;
    auto rx = centerX - radius;
    auto ry = centerY - radius;

    auto angle = startAngle + sliderPos * (endAngle - startAngle);

    ColourGradient gradient(Constants::backgroundColor.brighter(0.2f), centerX, centerY - radius,
        Constants::backgroundColor.darker(0.2f), centerX, centerY + radius, false);
    g.setGradientFill(gradient);
    g.fillEllipse(rx, ry, rw, rw);

    g.setColour(Constants::backgroundColor.darker(0.5f));
    g.drawEllipse(rx, ry, rw, rw, 2.0f);

    Array<float> dotPositions = { 11.0f, 12.0f, 1.0f, 2.0f, 4.0f, 5.0f, 6.0f, 7.0f };
    Array<float> linePositions = { 10.0f, 3.0f, 8.0f };

    float angleStep = MathConstants<float>::twoPi / 12.0f;

    for (auto linePos : linePositions)
    {
        float lineAngle = (linePos - 6.0f) * angleStep;
        g.setColour(Colours::grey);
        Line<float> line(centerX + (radius + outerMargin) * 0.8f * std::cos(lineAngle),
            centerY + (radius + outerMargin) * 0.8f * std::sin(lineAngle),
            centerX + (radius + outerMargin) * std::cos(lineAngle),
            centerY + (radius + outerMargin) * std::sin(lineAngle));
        g.drawLine(line, 2.0f);
    }

    for (auto dotPos : dotPositions)
    {
        float dotAngle = (dotPos - 6.0f) * angleStep;
        g.setColour(Colours::grey);
        g.fillEllipse(centerX + (radius + outerMargin) * 0.9f * std::cos(dotAngle) - 2.5f,
            centerY + (radius + outerMargin) * 0.9f * std::sin(dotAngle) - 2.5f,
            3.0f, 3.0f);
    }

    Path pointer;
    auto pointerLength = radius * 0.6f;
    auto pointerThickness = 2.0f;
    pointer.addRectangle(-pointerThickness * 0.5f, -radius + 5.0f, pointerThickness, pointerLength);
    pointer.applyTransform(AffineTransform::rotation(angle).translated(centerX, centerY));

    g.setColour(Colours::grey);
    g.fillPath(pointer);
}
