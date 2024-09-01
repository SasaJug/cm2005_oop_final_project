/*
  ==============================================================================

    Knob.cpp
    Created: 24 Aug 2024 5:09:37pm
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Knob.h"

Knob::Knob()
{
    knobSlider.setLookAndFeel(&knobLookAndFeel);

    knobSlider.setSliderStyle(Slider::Rotary);
    knobSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    knobSlider.setRange(0.0, 1.0, 0.01);
    addAndMakeVisible(knobSlider);

    knobLabel.setFont(Font(11.0f));
    knobLabel.setColour(Label::textColourId, Constants::textColor);
    knobLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(knobLabel);
}

Knob::~Knob()
{
    knobSlider.setLookAndFeel(nullptr);
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

void Knob::setLabel(const String& labelText)
{
    knobLabel.setText(labelText, dontSendNotification);
}

void Knob::resized()
{
    auto area = getLocalBounds();
    auto labelHeight = 20;
    knobLabel.setBounds(area.removeFromTop(labelHeight));

    knobSlider.setBounds(area);
}
