/*
  ==============================================================================

    MidSection.h
    Created: 11 Aug 2024 2:26:07pm
    Author:  jugur

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class MidSection: public juce::Component,
                  public juce::Slider::Listener
{
public:
    MidSection(
        DJAudioPlayer* _player1,
        DJAudioPlayer* _player2);

    ~MidSection() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:

    juce::Slider volumeSlider1;
    juce::Slider volumeSlider2;
    juce::Slider volumeSliderTransition;

    DJAudioPlayer* player1;
    DJAudioPlayer* player2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidSection)
};
