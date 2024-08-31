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

    g.setFont(juce::Font(circleRadius * 0.4f));

    g.setColour(isEnabled() ? juce::Colours::orange.brighter(0.5f) : juce::Colours::orange.darker(0.5f));

    juce::String buttonText = "CUE";
    g.drawText(buttonText, bounds, juce::Justification::centred, true);
}

