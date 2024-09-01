/*
  ==============================================================================

    JogWheel.h
    Created: 11 Aug 2024 4:52:47pm
    Author:  Sasa Jugurdzija, and additional resources for drag handling.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Constants.h"
#include "DJAudioPlayer.h"

using namespace juce;

class JogWheel : public Component
{
public:

    /**
     * @brief Constructor to initialize the JogWheel.
     * @param player Pointer to the DJAudioPlayer instance.
     * @param side Indicates which side (1 or 2) this jog wheel is on.
     */
    JogWheel(DJAudioPlayer* player, int side);

    /**
     * @brief Destructor for JogWheel.
     */
    ~JogWheel() override;

    /**
     * @brief Paints the JogWheel component.
     * @param g The Graphics object used for drawing.
     */
    void paint(Graphics& g) override;

    /**
     * @brief Resizes the JogWheel component.
     */
    void resized() override;

    /**
     * @brief Handles mouse down events on the JogWheel.
     * @param event The MouseEvent object containing details of the mouse down event.
     */
    void mouseDown(const MouseEvent& event) override;

    /**
     * @brief Handles mouse drag events on the JogWheel.
     * @param event The MouseEvent object containing details of the mouse drag event.
     */
    void mouseDrag(const MouseEvent& event) override;

private:
    DJAudioPlayer* player;
    int side;

    /**
     * @brief Calculates the angle for a given point relative to the center of the JogWheel.
     * @param point The point to calculate the angle for.
     * @return float The angle in radians.
     */
    float getAngleForPoint(Point<float> point);

    float lastAngle = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JogWheel)
};
