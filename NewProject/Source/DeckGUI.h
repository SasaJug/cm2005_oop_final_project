/*
  ==============================================================================

    DeckGUI.h
    Created: 3 Aug 2024 3:09:17pm
    Author:  jugur

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "DJAudioPlayer.h"
#include "SearchComponent.h"
#include "CustomSliderLookAndFeel.h"
#include "PlayPauseButton.h"
#include "CueButton.h"
#include "Constants.h"
#include "EventBus.h"
#include "EventTypes.h"

using namespace juce;

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
                 public juce::Button::Listener,
                 public juce::Slider::Listener
{
public:
    DeckGUI(
        DJAudioPlayer* player
    );

    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;
    void handlePlayButton();

    void sliderValueChanged(juce::Slider* slider) override;

private:

    bool isPlaying = false;
    juce::Slider speedSlider;

    DJAudioPlayer* player;

    SearchComponent searchComponent;
    CustomSliderLookAndFeel customSliderLookAndFeel;
    PlayPauseButton playPauseButton;
    CueButton cueButton;

    double position;

    void setPositionRelative(const std::string& position);

    std::function<void(const std::string&)> timerTickCallback;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
