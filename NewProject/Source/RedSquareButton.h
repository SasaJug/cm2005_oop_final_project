/*
  ==============================================================================

    RedSquareButton.h
    Created: 31 Aug 2024 10:31:32am
    Author:  jugur

  ==============================================================================
*/
#pragma once
#include "SquareButtonBase.h"

using namespace juce;

class RedSquareButton : public SquareButtonBase
{
public:
    RedSquareButton(const juce::String& buttonName);

protected:
    juce::Colour getButtonColor() const override;
    void drawCentralContent(juce::Graphics& g, juce::Rectangle<float> bounds) override;
};

