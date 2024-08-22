/*
  ==============================================================================

    RoundButtonBase.cpp
    Created: 22 Aug 2024 8:47:50pm
    Author:  jugur

  ==============================================================================
*/

#include "RoundButtonBase.h"

RoundButtonBase::RoundButtonBase(const juce::String& buttonName)
    : juce::Button(buttonName)
{
    setClickingTogglesState(true);
}

RoundButtonBase::~RoundButtonBase() = default;

void RoundButtonBase::paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    auto bounds = getLocalBounds().toFloat();
    auto circleRadius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto center = bounds.getCentre();

    // Draw the background circle
    g.setColour(juce::Colour::fromRGB(0x2c, 0x2c, 0x2c));
    g.fillEllipse(center.x - circleRadius, center.y - circleRadius,
        circleRadius * 2, circleRadius * 2);

    // Draw outer circle
    float outerRadius = circleRadius * 0.95f;
    g.setColour(juce::Colours::lightgrey);
    g.drawEllipse(center.x - outerRadius, center.y - outerRadius,
        outerRadius * 2, outerRadius * 2, 2.0f);

    // Draw inner custom-colored circle
    float innerRadius = circleRadius * 0.7f;
    g.setColour(getButtonColor());
    g.drawEllipse(center.x - innerRadius, center.y - innerRadius,
        innerRadius * 2, innerRadius * 2, 4.0f);

    // Subclass draws the central content
    drawCentralContent(g, bounds);
}


void RoundButtonBase::resized()
{
    // Resizing behavior if necessary
}


