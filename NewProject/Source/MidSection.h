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
#include "VolumeSliderLookAndFeel.h"
#include "Knob.h"
#include "Constants.h"
#include "EventBus.h"
#include "EventTypes.h"
using namespace juce;

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


    std::function<void(const std::string&)> fileLoadedCallback;
    void reevaluateSliders(const std::string& placeholder);

    juce::Slider volumeSlider1;
    juce::Slider volumeSlider2;
    juce::Slider volumeSliderTransition;
    VolumeSliderLookAndFeel volumeSliderLookAndFeel;

    Knob hiKnob1;
    Knob midKnob1;
    Knob lowKnob1;

    Knob hiKnob2;
    Knob midKnob2;
    Knob lowKnob2;

    DJAudioPlayer* player1;
    DJAudioPlayer* player2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidSection)
};
