/*
  ==============================================================================

    RoundButtonBase.h
    Created: 22 Aug 2024 8:47:50pm
    Author:  jugur

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

class RoundButtonBase : public juce::Button
{
public:
    RoundButtonBase(const juce::String& buttonName);
    virtual ~RoundButtonBase();

    virtual void drawCentralContent(juce::Graphics& g, juce::Rectangle<float> bounds) = 0;

    virtual juce::Colour getButtonColor() const = 0;

    void paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override;

    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RoundButtonBase)
};

