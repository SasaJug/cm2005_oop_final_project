/*
  ==============================================================================

    SquareButtonBase.cpp
    Created: 31 Aug 2024 10:25:45am
    Author:  jugur

  ==============================================================================
*/

#include "SquareButtonBase.h"

SquareButtonBase::SquareButtonBase(const juce::String& buttonName)
    : juce::Button(buttonName)
{
    setClickingTogglesState(true);
}

SquareButtonBase::~SquareButtonBase() = default;

void SquareButtonBase::paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    auto bounds = getLocalBounds().toFloat();

    g.setColour(juce::Colour::fromRGB(0x1a, 0x1a, 0x1a).withAlpha(0.5f));
    g.fillRect(bounds);

    auto outerBounds = bounds.reduced(bounds.getWidth() * 0.025f);
    g.setColour(juce::Colours::lightgrey);
    g.drawRect(outerBounds, 1.0f);

    auto innerBounds = bounds.reduced(bounds.getWidth() * 0.1f);
    g.setColour(getButtonColor());
    g.drawRect(innerBounds, 2.0f);

    // Subclass draws the central content
    drawCentralContent(g, bounds);
}

void SquareButtonBase::resized()
{
    // Resizing behavior if necessary
}

