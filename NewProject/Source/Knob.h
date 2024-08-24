/*
  ==============================================================================

    Knob.h
    Created: 24 Aug 2024 5:09:37pm
    Author:  jugur

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
#pragma once

#include <JuceHeader.h>
#include "KnobLookAndFeel.h"

class Knob : public juce::Component
{
public:
    Knob(); // Constructor
    ~Knob() override; // Destructor

    void setRange(double minValue, double maxValue, double interval); // Sets the range of the knob
    void setValue(double value); // Sets the current value of the knob
    double getValue() const; // Gets the current value of the knob

    void setKnobColor(const juce::Colour& color); // Set the knob color
    void setLabel(const juce::String& labelText); // Set the label for the knob

    void resized() override; // Handle the resizing of the component

private:
    juce::Slider knobSlider; // The rotary knob
    juce::Label knobLabel; // The label that appears below the knob

    KnobLookAndFeel knobLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knob)
};

