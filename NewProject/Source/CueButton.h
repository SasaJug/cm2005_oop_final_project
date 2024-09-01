/*
  ==============================================================================

    CueButton.h
    Created: 22 Aug 2024 8:48:45pm
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#pragma once

#include "RoundButtonBase.h"

using namespace juce;

class CueButton : public RoundButtonBase
{
public:
    /**
     * @brief Constructor to initialize the CueButton.
     *
     * This constructor sets up the CueButton and prepares it for use.
     */
    CueButton();

    /**
     * @brief Returns the color of the button.
     *
     * @return juce::Colour The color to be used for drawing the button.
     *
     * This method determines the color of the button based on its state.
     * It is used during the painting process to set the button's appearance.
     */
    Colour getButtonColor() const override;

    /**
     * @brief Draws the central content (cue text) of the button.
     *
     * @param g The Graphics object.
     * @param bounds The rectangular area within which the content should be drawn.
     *
     * This method is responsible for rendering the central cue text.
     */
    void drawCentralContent(Graphics& g, Rectangle<float> bounds) override;
};
