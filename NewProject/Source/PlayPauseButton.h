/*
  ==============================================================================

    PlayPauseButton.h
    Created: 22 Aug 2024 8:48:26pm
    Author:  jugur

  ==============================================================================
*/

#pragma once

#include "RoundButtonBase.h"
using namespace juce;

class PlayPauseButton : public RoundButtonBase
{
public:
    PlayPauseButton();

    // Define the button color
    juce::Colour getButtonColor() const override;

    // Define the central drawing (play/pause symbols)
    void drawCentralContent(juce::Graphics& g, juce::Rectangle<float> bounds) override;
};

