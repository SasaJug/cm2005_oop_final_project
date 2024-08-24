/*
  ==============================================================================

    Knob.cpp
    Created: 24 Aug 2024 5:09:37pm
    Author:  jugur

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Knob.h"

Knob::Knob()
{
    // Apply custom look-and-feel to the knob
    knobSlider.setLookAndFeel(&knobLookAndFeel);

    // Set up the rotary slider (knob)
    knobSlider.setSliderStyle(juce::Slider::Rotary);
    knobSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobSlider.setRange(0.0, 1.0, 0.01);
    addAndMakeVisible(knobSlider);

    // Set up the label that appears above the knob
    knobLabel.setFont(juce::Font(11.0f));
    knobLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    knobLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(knobLabel);

    // Default knob color (used in future customization if needed)
    knobSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::blue);
}

Knob::~Knob()
{
    knobSlider.setLookAndFeel(nullptr); // Clean up custom look-and-feel
}

void Knob::setRange(double minValue, double maxValue, double interval)
{
    knobSlider.setRange(minValue, maxValue, interval);
}

void Knob::setValue(double value)
{
    knobSlider.setValue(value);
}

double Knob::getValue() const
{
    return knobSlider.getValue();
}

void Knob::setKnobColor(const juce::Colour& color)
{
    knobSlider.setColour(juce::Slider::rotarySliderFillColourId, color);
}

void Knob::setLabel(const juce::String& labelText)
{
    knobLabel.setText(labelText, juce::dontSendNotification);
}

void Knob::resized()
{
    // Position the label above the knob and dots
    auto area = getLocalBounds();
    auto labelHeight = 20;
    knobLabel.setBounds(area.removeFromTop(labelHeight));

    // Position the knob below the label, taking up most of the remaining space
    knobSlider.setBounds(area);
}
