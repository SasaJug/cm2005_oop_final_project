/*
  ==============================================================================

    Knob.h
    Created: 24 Aug 2024 5:09:37pm
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "KnobLookAndFeel.h"
#include "Constants.h"
using namespace juce;

class Knob : public Component
{
public:
    /**
     * @brief Constructor to initialize the Knob.
     */
    Knob();

    /**
     * @brief Destructor for Knob.
     */
    ~Knob() override;

    /**
     * @brief Sets the range of values for the knob.
     * @param minValue The minimum value.
     * @param maxValue The maximum value.
     * @param interval The step interval between values.
     */
    void setRange(double minValue, double maxValue, double interval);

    /**
     * @brief Sets the current value of the knob.
     * @param value The value to set.
     */
    void setValue(double value);

    /**
     * @brief Gets the current value of the knob.
     * @return double The current value.
     */
    double getValue() const;

    /**
     * @brief Sets the label text for the knob.
     * @param labelText The label text to display.
     */
    void setLabel(const String& labelText);

    /**
     * @brief Resizes the knob component.
     */
    void resized() override;

    Slider knobSlider;

private:
    Label knobLabel;
    KnobLookAndFeel knobLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knob)
};
