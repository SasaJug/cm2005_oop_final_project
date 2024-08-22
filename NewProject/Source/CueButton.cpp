/*
  ==============================================================================

    CueButton.cpp
    Created: 22 Aug 2024 8:48:45pm
    Author:  jugur

  ==============================================================================
*/

#include "CueButton.h"

CueButton::CueButton()
    : RoundButtonBase("CueButton")
{
}

juce::Colour CueButton::getButtonColor() const
{
    return juce::Colours::orange;
}

void CueButton::drawCentralContent(juce::Graphics& g, juce::Rectangle<float> bounds)
{
    auto circleRadius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto center = bounds.getCentre();
    auto symbolSize = circleRadius * 0.3f;

    // Draw the play symbol
    juce::Path playSymbol;
    playSymbol.addTriangle(center.x - symbolSize * 1.5f, center.y - symbolSize / 2.0f,
        center.x - symbolSize * 0.7f, center.y,
        center.x - symbolSize * 1.5f, center.y + symbolSize / 2.0f);
    g.fillPath(playSymbol);

    // Draw the pause symbol
    float barWidth = symbolSize / 4.0f;
    g.fillRect(center.x + symbolSize * 0.5f, center.y - symbolSize / 2.0f, barWidth, symbolSize);
    g.fillRect(center.x + symbolSize, center.y - symbolSize / 2.0f, barWidth, symbolSize);

    // Draw the line symbol in the middle
    float lineStartX = center.x + symbolSize * 0.15f;
    float lineStartY = center.y - symbolSize * 0.6f;
    float lineEndX = center.x - symbolSize * 0.15f;
    float lineEndY = center.y + symbolSize * 0.6f;

    g.drawLine(lineStartX, lineStartY, lineEndX, lineEndY, 2.0f);
}

