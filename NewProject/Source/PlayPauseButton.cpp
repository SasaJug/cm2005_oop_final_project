/*
  ==============================================================================

    PlayPauseButton.cpp
    Created: 22 Aug 2024 8:48:26pm
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#include "PlayPauseButton.h"

PlayPauseButton::PlayPauseButton()
    : RoundButtonBase("PlayPauseButton")
{
}

Colour PlayPauseButton::getButtonColor() const
{
    return isEnabled() ? Colours::green.brighter(0.5f) : Colours::green.darker(0.5f);
}

void PlayPauseButton::drawCentralContent(Graphics& g, Rectangle<float> bounds)
{
    auto circleRadius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto center = bounds.getCentre();
    auto symbolSize = circleRadius * 0.3f;

    // Play symbol
    Path playSymbol;
    playSymbol.addTriangle(center.x - symbolSize * 1.5f, center.y - symbolSize / 2.0f,
        center.x - symbolSize * 0.7f, center.y,
        center.x - symbolSize * 1.5f, center.y + symbolSize / 2.0f);
    g.fillPath(playSymbol);

    // Pause symbol
    float barWidth = symbolSize / 4.0f;
    g.fillRect(center.x + symbolSize * 0.5f, center.y - symbolSize / 2.0f, barWidth, symbolSize);
    g.fillRect(center.x + symbolSize, center.y - symbolSize / 2.0f, barWidth, symbolSize);

    // Middle line
    float lineStartX = center.x + symbolSize * 0.15f;
    float lineStartY = center.y - symbolSize * 0.6f;
    float lineEndX = center.x - symbolSize * 0.15f;
    float lineEndY = center.y + symbolSize * 0.6f;

    g.drawLine(lineStartX, lineStartY, lineEndX, lineEndY, 2.0f);
}
