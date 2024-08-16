/*
  ==============================================================================

    SearchComponent.cpp
    Created: 11 Aug 2024 4:52:47pm
    Author:  jugur

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SearchComponent.h"

//==============================================================================
SearchComponent::SearchComponent(DJAudioPlayer* _player)
    : player(_player)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SearchComponent::~SearchComponent()
{
}

void SearchComponent::paint (juce::Graphics& g)
{
        auto bounds = getLocalBounds().toFloat().reduced(10);
        auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;

        // Draw outer circle (the disc)        
        juce::ColourGradient gradient1(juce::Colour::fromRGB(0x05, 0x05, 0x05), 0, 0,
        juce::Colour::fromRGB(0xa3, 0xa3, 0xa3), bounds.getWidth(), bounds.getHeight(),false);
        g.setGradientFill(gradient1);
        g.fillEllipse(bounds);
      
        juce::ColourGradient gradient2(juce::Colour::fromRGB(0x53, 0x53, 0x53), 0, 0,
        juce::Colour::fromRGB(0x05, 0x05, 0x05), bounds.getWidth(), bounds.getHeight(), false);
        g.setGradientFill(gradient2);
        g.fillEllipse(bounds.reduced(radius * 0.05f));

        g.setColour(juce::Colours::white);
        g.fillEllipse(bounds.reduced(radius * 0.15f));

        g.setColour(juce::Colours::black);
        g.fillEllipse(bounds.reduced(radius * 0.18f));

        g.setColour(juce::Colours::black);
        g.fillEllipse(bounds.reduced(radius * 0.2f));

        g.setColour(juce::Colours::lightgrey);
        for (int i = 0; i < 100; ++i)
        {
            auto angle = juce::MathConstants<float>::twoPi * i / 100.0f;
            auto lineLength = radius * 0.4f;
            juce::Line<float> grooveLine(bounds.getCentre().translated(
                std::cos(angle) * lineLength,
                std::sin(angle) * lineLength),
                bounds.getCentre());

            g.drawLine(grooveLine, 1.0f);
        }

        g.setColour(juce::Colours::black);
        g.fillEllipse(bounds.reduced(radius * 0.7f));

        g.setColour(juce::Colours::lightgrey);
        g.fillEllipse(bounds.reduced(radius * 0.9f));

        g.setColour(juce::Colours::black);
        g.fillEllipse(bounds.reduced(radius * 0.98f));
}

void SearchComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void SearchComponent::mouseDown(const juce::MouseEvent& event)
{
    lastAngle = getAngleForPoint(event.position);
}

void SearchComponent::mouseDrag(const juce::MouseEvent& event)
{
    auto currentAngle = getAngleForPoint(event.position);
    auto angleChange = currentAngle - lastAngle;

    if (angleChange > juce::MathConstants<float>::pi)
        angleChange -= juce::MathConstants<float>::twoPi;
    else if (angleChange < -juce::MathConstants<float>::pi)
        angleChange += juce::MathConstants<float>::twoPi;

    lastAngle = currentAngle;

        player->setPositionChange(angleChange*0.01);
}

float SearchComponent::getAngleForPoint(juce::Point<float> point)
{
    auto center = getLocalBounds().getCentre().toFloat();
    return std::atan2(point.y - center.y, point.x - center.x);
}
