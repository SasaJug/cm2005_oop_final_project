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
        g.setColour(juce::Colours::grey);
        g.fillEllipse(bounds);

        // Draw inner circle (label area)
        g.setColour(juce::Colours::darkgrey);
        g.fillEllipse(bounds.reduced(radius * 0.4f));

        // Draw very center circle (spindle hole)
        g.setColour(juce::Colours::black);
        g.fillEllipse(bounds.reduced(radius * 0.8f));

        // Optionally draw some radial lines to simulate disc grooves
        g.setColour(juce::Colours::lightgrey.withAlpha(0.5f));
        for (int i = 0; i < 12; ++i)
        {
            auto angle = juce::MathConstants<float>::twoPi * i / 12.0f;
            auto lineLength = radius * 0.6f;
            juce::Line<float> grooveLine(bounds.getCentre().translated(
                std::cos(angle) * lineLength,
                std::sin(angle) * lineLength),
                bounds.getCentre());

            g.drawLine(grooveLine, 2.0f);
        }
}

void SearchComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

/*
* 
	if (slider == &positionSlider)
	{
		player->setPositionRelative(slider->getValue());
	}
*/

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

    // Apply the angle change
    //if (onRotation)
        DBG("Angle change: " << angleChange);
        player->setPositionChange(angleChange);
        //onRotation(angleChange);
}

float SearchComponent::getAngleForPoint(juce::Point<float> point)
{
    auto center = getLocalBounds().getCentre().toFloat();
    return std::atan2(point.y - center.y, point.x - center.x);
}
