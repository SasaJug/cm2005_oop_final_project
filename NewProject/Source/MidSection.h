/*
  ==============================================================================

    MidSection.h
    Created: 11 Aug 2024 2:26:07pm
    Author:  Sasa Jugurdzija

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

class MidSection : public Component,
    public Slider::Listener
{
public:
    /**
     * @brief Constructor to initialize the MidSection.
     * @param _player1 Pointer to the first DJAudioPlayer.
     * @param _player2 Pointer to the second DJAudioPlayer.
     */
    MidSection(DJAudioPlayer* _player1, DJAudioPlayer* _player2);

    /**
     * @brief Destructor for MidSection.
     */
    ~MidSection() override;

    /**
     * @brief Paints the MidSection component.
     * @param g The Graphics object used for drawing.
     */
    void paint(Graphics& g) override;

    /**
     * @brief Resizes the MidSection component.
     *
     */
    void resized() override;

    /**
     * @brief Handles slider value changes.
     * @param slider Pointer to the Slider that was adjusted.
     */
    void sliderValueChanged(Slider* slider) override;

private:
    std::function<void(const std::string&)> fileLoadedCallback;
    void reevaluateSliders(const std::string& placeholder);

    Slider volumeSlider1;
    Slider volumeSlider2;
    Slider volumeSliderTransition;
    VolumeSliderLookAndFeel volumeSliderLookAndFeel;

    Knob hiKnob1;
    Knob midKnob1;
    Knob lowKnob1;

    Knob hiKnob2;
    Knob midKnob2;
    Knob lowKnob2;

    DJAudioPlayer* player1;
    DJAudioPlayer* player2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidSection)
};
