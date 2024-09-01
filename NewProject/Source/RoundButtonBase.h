/*
  ==============================================================================

    RoundButtonBase.h
    Created: 22 Aug 2024 8:47:50pm
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

class RoundButtonBase : public Button
{
public:
    /**
     * @brief Constructor to initialize the RoundButtonBase.
     * @param buttonName The name of the button.
     */
    RoundButtonBase(const String& buttonName);

    /**
     * @brief Virtual destructor for RoundButtonBase.
     */
    virtual ~RoundButtonBase();

    /**
     * @brief Draws the central content of the button.
     * @param g The Graphics object used for drawing.
     * @param bounds The rectangular area within which to draw the content.
     */
    virtual void drawCentralContent(Graphics& g, Rectangle<float> bounds) = 0;

    /**
     * @brief Gets the color of the button.
     * @return juce::Colour The color to be used for the button.
     */
    virtual Colour getButtonColor() const = 0;

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

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RoundButtonBase)
};
