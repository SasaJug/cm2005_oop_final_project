/*
  ==============================================================================

    SearchComponent.cpp
    Created: 11 Aug 2024 4:52:47pm
    Author:  jugur

  ==============================================================================
*/
#include <JuceHeader.h>
#include "SearchComponent.h"

SearchComponent::SearchComponent(DJAudioPlayer* _player)
    : player(_player)
{
}

SearchComponent::~SearchComponent()
{
}

void SearchComponent::paint(juce::Graphics& g)
{
    // Get the bounds and maintain a circular shape
    auto bounds = getLocalBounds().toFloat();
    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;

    // Draw outer circle (the disc)
    juce::ColourGradient gradient1(juce::Colour::fromRGB(0x05, 0x05, 0x05).withAlpha(Constants::colorAlpha), 0, 0,
        juce::Colour::fromRGB(0xa3, 0xa3, 0xa3).withAlpha(Constants::colorAlpha), bounds.getWidth(), bounds.getHeight(), false);
    g.setGradientFill(gradient1);
    g.fillEllipse(bounds.withSizeKeepingCentre(radius * 2.0f, radius * 2.0f));

    juce::ColourGradient gradient2(juce::Colour::fromRGB(0x53, 0x53, 0x53).withAlpha(Constants::colorAlpha), 0, 0,
        juce::Colour::fromRGB(0x05, 0x05, 0x05), bounds.getWidth(), bounds.getHeight(), false);
    g.setGradientFill(gradient2);
    g.fillEllipse(bounds.reduced(radius * 0.05f).withSizeKeepingCentre(radius * 1.9f, radius * 1.9f));

    g.setColour(juce::Colours::white);
    g.fillEllipse(bounds.reduced(radius * 0.15f).withSizeKeepingCentre(radius * 1.62f, radius * 1.62f));

    g.setColour(juce::Colours::black);
    g.fillEllipse(bounds.reduced(radius * 0.18f).withSizeKeepingCentre(radius * 1.55f, radius * 1.55f));

    // Radial ellipses with gradient fill pointing along their shorter axis
    int numEllipses = 20;
    float ellipseRadiusW = radius * 0.06f;
    float ellipseRadiusH = radius * 0.06f * 1.7f;
    float ellipseDistanceFromCenter = radius * 0.87f;

    for (int i = 0; i < numEllipses; ++i)
    {
        // Calculate the angle for this ellipse
        auto angle = juce::MathConstants<float>::twoPi * i / numEllipses;

        // Calculate the position for the center of the ellipse
        auto centerX = bounds.getCentreX() + std::cos(angle) * ellipseDistanceFromCenter;
        auto centerY = bounds.getCentreY() + std::sin(angle) * ellipseDistanceFromCenter;

        // Save the current state of the graphics context (before applying transformations)
        g.saveState();

        // Translate and rotate the graphics context to place the ellipse
        g.addTransform(juce::AffineTransform::translation(centerX, centerY));
        g.addTransform(juce::AffineTransform::rotation(angle));

        // Calculate the gradient start and end points relative to the ellipse's position
        juce::Point<float> gradientStart(-ellipseRadiusH, 0.0f);  // Start on the left edge of the shorter axis
        juce::Point<float> gradientEnd(ellipseRadiusH, 0.0f);     // End on the right edge of the shorter axis

        // Create the gradient for the ellipse
        juce::ColourGradient ellipseGradient(juce::Colours::black.withAlpha(0.7f), gradientStart.x, gradientStart.y,
            juce::Colours::darkgrey.brighter(0.3f).withAlpha(0.7f), gradientEnd.x, gradientEnd.y, false);

        // Set the gradient fill for the ellipse
        g.setGradientFill(ellipseGradient);

        // Draw the ellipse at the transformed position and rotation
        g.fillEllipse(-ellipseRadiusW, -ellipseRadiusH, ellipseRadiusW * 2, ellipseRadiusH * 2);

        // Restore the previous state of the graphics context
        g.restoreState();
    }

    // Inner grooves
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

    // Smaller inner parts
    g.setColour(juce::Colours::black);
    g.fillEllipse(bounds.reduced(radius * 0.7f).withSizeKeepingCentre(radius * 0.6f, radius * 0.6f));

    g.setColour(juce::Colours::lightgrey);
    g.fillEllipse(bounds.reduced(radius * 0.9f).withSizeKeepingCentre(radius * 0.2f, radius * 0.2f));

    g.setColour(juce::Colours::black);
    g.fillEllipse(bounds.reduced(radius * 0.98f).withSizeKeepingCentre(radius * 0.04f, radius * 0.04f));
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

    player->setPositionChange(angleChange * 0.01);
}

float SearchComponent::getAngleForPoint(juce::Point<float> point)
{
    auto center = getLocalBounds().getCentre().toFloat();
    return std::atan2(point.y - center.y, point.x - center.x);
}
