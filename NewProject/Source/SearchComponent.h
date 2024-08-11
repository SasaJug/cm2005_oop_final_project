/*
  ==============================================================================

    SearchComponent.h
    Created: 11 Aug 2024 4:52:47pm
    Author:  jugur

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
using namespace juce;

//==============================================================================
/*
*/
class SearchComponent  : public juce::Component
{
public:
    SearchComponent(DJAudioPlayer* player);
    ~SearchComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;

   // std::function<void(float)> onRotation;

private:

    DJAudioPlayer* player;

    float getAngleForPoint(juce::Point<float> point);

    float lastAngle = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SearchComponent)
};
