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
#include "RedSquareButton.h"
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
        DJAudioPlayer* player,
        int side
    );

    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;
    void handlePlayButton();

    void sliderValueChanged(juce::Slider* slider) override;

private:

    int side;

    bool isPlaying = false;
    juce::Slider speedSlider;

    DJAudioPlayer* player;

    SearchComponent searchComponent;
    CustomSliderLookAndFeel customSliderLookAndFeel;
    PlayPauseButton playPauseButton;
    CueButton cueButton;

    RedSquareButton redButton1{ "redButton1" };
    RedSquareButton redButton2{ "redButton2" };
    RedSquareButton redButton3{ "redButton3" };
    RedSquareButton redButton4{ "redButton4" };
    RedSquareButton redButton5{ "redButton5" };
    RedSquareButton redButton6{ "redButton6" };
    RedSquareButton redButton7{ "redButton7" };
    RedSquareButton redButton8{ "redButton8" };

    double position;

    void setPositionRelative(const std::string& position);

    std::function<void(const std::string&)> timerTickCallback;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
