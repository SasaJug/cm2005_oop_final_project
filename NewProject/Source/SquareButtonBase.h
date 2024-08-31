/*
  ==============================================================================

    SquareButtonBase.h
    Created: 31 Aug 2024 10:25:45am
    Author:  jugur

  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>

class SquareButtonBase : public juce::Button
{
public:
    SquareButtonBase(const juce::String& buttonName);
    ~SquareButtonBase() override;

    void paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override;
    void resized() override;

protected:
    virtual juce::Colour getButtonColor() const = 0;  // Subclasses should define the button color
    virtual void drawCentralContent(juce::Graphics& g, juce::Rectangle<float> bounds) = 0; // To be overridden by subclasses
};

