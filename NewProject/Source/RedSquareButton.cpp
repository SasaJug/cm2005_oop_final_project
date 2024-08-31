/*
  ==============================================================================

    RedSquareButton.cpp
    Created: 31 Aug 2024 10:31:32am
    Author:  jugur

  ==============================================================================
*/
#include "RedSquareButton.h"

RedSquareButton::RedSquareButton(const juce::String& buttonName)
    : SquareButtonBase(buttonName)
{
}

juce::Colour RedSquareButton::getButtonColor() const
{
    return juce::Colours::red;
}

void RedSquareButton::drawCentralContent(juce::Graphics& g, juce::Rectangle<float> bounds)
{
  
}

