/*
  ==============================================================================

    JogWheel.cpp
    Created: 11 Aug 2024 4:52:47pm
    Author:  Sasa Jugurdzija, with help from external resources for drawing ellipses, and for drag handling.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "JogWheel.h"

JogWheel::JogWheel(DJAudioPlayer* _player, int _side)
    : player(_player), side(_side)
{
}

JogWheel::~JogWheel()
{
}

void JogWheel::paint(Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;

    // Outer circles
    auto gradientStartColor = Colour::fromRGB(0x03, 0x03, 0x03).withAlpha(0.6f);
    auto gradientEndColor = Colour::fromRGB(0x83, 0x83, 0x83).withAlpha(0.6f);
    if (side == 2)
    {
        gradientStartColor = Colour::fromRGB(0x03, 0x03, 0x03).withAlpha(0.6f);
        gradientEndColor = Colour::fromRGB(0x63, 0x63, 0x63).withAlpha(0.6f);
    }

    ColourGradient gradient1(gradientStartColor, 0, 0,
        gradientEndColor, bounds.getWidth(), bounds.getHeight(), false);
    g.setGradientFill(gradient1);
    g.fillEllipse(bounds.withSizeKeepingCentre(radius * 2.0f, radius * 2.0f));

    ColourGradient gradient2(gradientEndColor, 0, 0,
        gradientStartColor, bounds.getWidth(), bounds.getHeight(), false);
    g.setGradientFill(gradient2);
    g.fillEllipse(bounds.reduced(radius * 0.05f).withSizeKeepingCentre(radius * 1.9f, radius * 1.9f));

    // Side ellipses
    int numEllipses = 20;
    float ellipseRadiusW = radius * 0.06f;
    float ellipseRadiusH = radius * 0.06f * 1.7f;
    float ellipseDistanceFromCenter = radius * 0.87f;

    auto ellipseStartColor = Colour::fromRGB(0x03, 0x03, 0x03).withAlpha(0.6f);
    auto ellipseEndColor = Colour::fromRGB(0x93, 0x93, 0x93);
    if (side == 2)
    {
        ellipseStartColor = Colour::fromRGB(0x02, 0x02, 0x02).withAlpha(0.6f);
        ellipseEndColor = Colour::fromRGB(0x73, 0x73, 0x73);
    }

    for (int i = 0; i < numEllipses; ++i)
    {
        auto angle = MathConstants<float>::twoPi * i / numEllipses;

        auto centerX = bounds.getCentreX() + std::cos(angle) * ellipseDistanceFromCenter;
        auto centerY = bounds.getCentreY() + std::sin(angle) * ellipseDistanceFromCenter;

        g.saveState();

        g.addTransform(AffineTransform::translation(centerX, centerY));
        g.addTransform(AffineTransform::rotation(angle));

        Point<float> gradientStart(-ellipseRadiusH, 0.0f);
        Point<float> gradientEnd(ellipseRadiusH, 0.0f);

        ColourGradient ellipseGradient(ellipseStartColor, gradientStart.x, gradientStart.y,
            ellipseEndColor, gradientEnd.x, gradientEnd.y, false);

        g.setGradientFill(ellipseGradient);

        g.fillEllipse(-ellipseRadiusW, -ellipseRadiusH, ellipseRadiusW * 2, ellipseRadiusH * 2);

        g.restoreState();
    }

    // Inner plate
    g.setColour(Colours::white);
    g.fillEllipse(bounds.reduced(radius * 0.15f).withSizeKeepingCentre(radius * 1.62f, radius * 1.62f));

    g.setColour(Colours::black);
    g.fillEllipse(bounds.reduced(radius * 0.18f).withSizeKeepingCentre(radius * 1.55f, radius * 1.55f));

    // Reflection
    float reflectionGradientAlpha = 0.2f;
    float reflectionGradientPercent = 0.3f;
    if (side == 1)
    {
        reflectionGradientAlpha = 0.3f;
        reflectionGradientPercent = 0.4f;
    }

    ColourGradient reflectionGradient(Colours::white.withAlpha(reflectionGradientAlpha), 0, 0,
        Colours::transparentBlack, bounds.getWidth(), bounds.getHeight(), false);
    reflectionGradient.addColour(reflectionGradientPercent, Colours::white.withAlpha(reflectionGradientAlpha));
    reflectionGradient.addColour(reflectionGradientPercent + 0.03f, Colours::transparentBlack);
    g.setGradientFill(reflectionGradient);
    g.fillEllipse(bounds.reduced(radius * 0.18f).withSizeKeepingCentre(radius * 1.55f, radius * 1.55f));

    // Inner grooves
    g.setColour(Colours::lightgrey);
    for (int i = 0; i < 100; ++i)
    {
        auto angle = MathConstants<float>::twoPi * i / 100.0f;
        auto lineLength = radius * 0.4f;
        Line<float> grooveLine(bounds.getCentre().translated(
            std::cos(angle) * lineLength,
            std::sin(angle) * lineLength),
            bounds.getCentre());

        g.drawLine(grooveLine, 1.0f);
    }

    // Innermost circle
    g.setColour(Colours::black);
    g.fillEllipse(bounds.reduced(radius * 0.7f).withSizeKeepingCentre(radius * 0.6f, radius * 0.6f));

    g.setColour(ellipseEndColor);
    g.fillEllipse(bounds.reduced(radius * 0.9f).withSizeKeepingCentre(radius * 0.2f, radius * 0.2f));

    g.setColour(Colours::black);
    g.fillEllipse(bounds.reduced(radius * 0.98f).withSizeKeepingCentre(radius * 0.04f, radius * 0.04f));
}

void JogWheel::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains.
}

void JogWheel::mouseDown(const MouseEvent& event)
{
    lastAngle = getAngleForPoint(event.position);
}

void JogWheel::mouseDrag(const MouseEvent& event)
{
    auto currentAngle = getAngleForPoint(event.position);
    auto angleChange = currentAngle - lastAngle;

    if (angleChange > MathConstants<float>::pi)
        angleChange -= MathConstants<float>::twoPi;
    else if (angleChange < -MathConstants<float>::pi)
        angleChange += MathConstants<float>::twoPi;

    lastAngle = currentAngle;

    player->setPositionChange(angleChange * 0.01);
}

float JogWheel::getAngleForPoint(Point<float> point)
{
    auto center = getLocalBounds().getCentre().toFloat();
    return std::atan2(point.y - center.y, point.x - center.x);
}
