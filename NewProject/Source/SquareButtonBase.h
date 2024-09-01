/*
  ==============================================================================

    SquareButtonBase.h
    Created: 31 Aug 2024 10:25:45am
    Author:  jugur

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

class SquareButtonBase : public Button
{
public:
    /**
     * @brief Constructor to initialize the SquareButtonBase.
     * @param buttonName The name of the button.
     */
    SquareButtonBase(const String& buttonName);

    /**
     * @brief Destructor for SquareButtonBase.
     */
    ~SquareButtonBase() override;

    /**
     * @brief Paints the button with custom styling.
     * @param g The Graphics object used for drawing.
     * @param isMouseOverButton Indicates if the mouse is over the button.
     * @param isButtonDown Indicates if the button is currently pressed down.
     */
    void paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown) override;

    /**
     * @brief Handles resizing of the button.
     */
    void resized() override;

protected:
    /**
     * @brief Gets the color of the button.
     * @return juce::Colour The color to be used for the button.
     */
    virtual Colour getButtonColor() const = 0;

    /**
     * @brief Draws the central content of the button.
     * @param g The Graphics object used for drawing.
     * @param bounds The rectangular area within which to draw the content.
     */
    virtual void drawCentralContent(Graphics& g, Rectangle<float> bounds) = 0;
};
