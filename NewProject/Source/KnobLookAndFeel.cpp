/*
  ==============================================================================

    KnobLookAndFeel.cpp
    Created: 24 Aug 2024 5:33:10pm
    Author:  jugur

  ==============================================================================
*/

#include "KnobLookAndFeel.h"

void KnobLookAndFeel::drawRotarySlider(juce::Graphics& g,
    int x, int y, int width, int height,
    float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
    juce::Slider& slider)
{
    // Adjust the radius to make the knob larger
    float outerMargin = 8.0f;  // Adjust this to control the size of the knob within the component
    auto radius = (float)juce::jmin(width, height) / 2.0f - outerMargin;

    // Keep the knob centered
    auto centerX = (float)x + (float)width * 0.5f;
    auto centerY = (float)y + (float)height * 0.5f;

    // Calculate the knob size based on the radius
    auto rw = radius * 2.0f;  // Knob width and height
    auto rx = centerX - radius;  // x position of the knob (centered)
    auto ry = centerY - radius;  // y position of the knob (centered)

    // Calculate the rotation angle of the knob
    auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    // Draw the knob base (simulating a top-down knob view)
    juce::ColourGradient gradient(Constants::backgroundColor.brighter(0.2f), centerX, centerY - radius,
        Constants::backgroundColor.darker(0.2f), centerX, centerY + radius, false);
    g.setGradientFill(gradient);
    g.fillEllipse(rx, ry, rw, rw);

    // Draw the knob outline
    g.setColour(Constants::backgroundColor.darker(0.5f));
    g.drawEllipse(rx, ry, rw, rw, 2.0f);

    // Draw the radial dots and lines outside the knob
    juce::Array<float> dotPositions = { 11.0f, 12.0f, 1.0f, 2.0f, 4.0f, 5.0f, 6.0f, 7.0f };
    juce::Array<float> linePositions = { 10.0f, 3.0f, 8.0f };

    float angleStep = juce::MathConstants<float>::twoPi / 12.0f;

    // Draw lines at 7, 12, and 5 hours
    for (auto linePos : linePositions)
    {
        float lineAngle = (linePos - 6.0f) * angleStep;
        g.setColour(juce::Colours::grey);
        juce::Line<float> line(centerX + (radius + outerMargin) * 0.8f * std::cos(lineAngle),
            centerY + (radius + outerMargin) * 0.8f * std::sin(lineAngle),
            centerX + (radius + outerMargin) * std::cos(lineAngle),
            centerY + (radius + outerMargin) * std::sin(lineAngle));
        g.drawLine(line, 2.0f); // Line thickness
    }

    // Draw dots at 8, 9, 10, 11, 1, 2, 3, and 4 hours
    for (auto dotPos : dotPositions)
    {
        float dotAngle = (dotPos - 6.0f) * angleStep;
        g.setColour(juce::Colours::grey);
        g.fillEllipse(centerX + (radius + outerMargin) * 0.9f * std::cos(dotAngle) - 2.5f,
            centerY + (radius + outerMargin) * 0.9f * std::sin(dotAngle) - 2.5f,
            3.0f, 3.0f); // Dot size
    }

    // Draw the indicator (the line showing the knob's current position)
    juce::Path pointer;
    auto pointerLength = radius * 0.6f;
    auto pointerThickness = 2.0f;
    pointer.addRectangle(-pointerThickness * 0.5f, -radius+5.0f, pointerThickness, pointerLength);
    pointer.applyTransform(juce::AffineTransform::rotation(angle).translated(centerX, centerY));

    g.setColour(juce::Colours::grey);
    g.fillPath(pointer);
}

