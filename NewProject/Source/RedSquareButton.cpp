/*
  ==============================================================================

    RedSquareButton.cpp
    Created: 31 Aug 2024 10:31:32am
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#include "RedSquareButton.h"

RedSquareButton::RedSquareButton(const String& buttonName)
    : SquareButtonBase(buttonName)
{
}

Colour RedSquareButton::getButtonColor() const
{
    return Colours::red;
}

void RedSquareButton::drawCentralContent(Graphics& g, Rectangle<float> bounds)
{

}
