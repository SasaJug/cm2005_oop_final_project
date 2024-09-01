/*
  ==============================================================================

    SquareButtonBase.cpp
    Created: 31 Aug 2024 10:25:45am
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#include "SquareButtonBase.h"

SquareButtonBase::SquareButtonBase(const String& buttonName)
    : Button(buttonName)
{
    setClickingTogglesState(true);
}

SquareButtonBase::~SquareButtonBase() = default;

void SquareButtonBase::paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    auto bounds = getLocalBounds().toFloat();

    g.setColour(Colour::fromRGB(0x1a, 0x1a, 0x1a).withAlpha(0.5f));
    g.fillRect(bounds);

    auto outerBounds = bounds.reduced(bounds.getWidth() * 0.025f);
    g.setColour(Colours::lightgrey);
    g.drawRect(outerBounds, 1.0f);

    auto innerBounds = bounds.reduced(bounds.getWidth() * 0.1f);
    g.setColour(getButtonColor());
    g.drawRect(innerBounds, 2.0f);

    drawCentralContent(g, bounds);
}

void SquareButtonBase::resized()
{
}
