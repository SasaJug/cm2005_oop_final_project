/*
  ==============================================================================

    PlayPauseButton.h
    Created: 22 Aug 2024 8:48:26pm
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#pragma once
#include "RoundButtonBase.h"

using namespace juce;

class PlayPauseButton : public RoundButtonBase
{
public:
    /**
     * @brief Constructor to initialize the PlayPauseButton.
     */
    PlayPauseButton();

    /**
     * @brief Gets the color of the button.
     * @return juce::Colour The color to be used for the button.
     */
    juce::Colour getButtonColor() const override;

    /**
     * @brief Draws the central content of the button (play/pause symbols).
     * @param g The Graphics object used for drawing.
     * @param bounds The rectangular area within which to draw the content.
     */
    void drawCentralContent(juce::Graphics& g, juce::Rectangle<float> bounds) override;
};
