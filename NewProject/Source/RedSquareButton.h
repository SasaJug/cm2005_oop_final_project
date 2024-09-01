/*
  ==============================================================================

    RedSquareButton.h
    Created: 31 Aug 2024 10:31:32am
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#pragma once
#include "SquareButtonBase.h"

using namespace juce;

class RedSquareButton : public SquareButtonBase
{
public:
    /**
     * @brief Constructor to initialize the RedSquareButton.
     * @param buttonName The name of the button. Requested by the base class.
     */
    RedSquareButton(const String& buttonName);

protected:
    /**
     * @brief Gets the color of the button.
     * @return juce::Colour The color to be used for the button.
     */
    Colour getButtonColor() const override;

    /**
     * @brief Draws the central content of the button.
     * @param g The Graphics object used for drawing.
     * @param bounds The rectangular area within which to draw the content.
     */
    void drawCentralContent(Graphics& g, Rectangle<float> bounds) override;
};
