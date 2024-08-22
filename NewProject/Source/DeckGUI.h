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
#include "PlaylistComponent.h"
#include "SearchComponent.h"
#include "CustomSliderLookAndFeel.h"
#include "PlayPauseButton.h"
#include "CueButton.h"

using namespace juce;

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
                 public juce::Button::Listener,
                 public juce::Slider::Listener,
                 public Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
        AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse);

    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;
    void handlePlayButton();

    void sliderValueChanged(juce::Slider* slider) override;

    void timerCallback() override;

private:

    bool isPlaying = false;
    juce::Slider speedSlider;

    DJAudioPlayer* player;

    PlaylistComponent playlistComponent { player };
    SearchComponent searchComponent;
    CustomSliderLookAndFeel customSliderLookAndFeel;
    PlayPauseButton playPauseButton;
    CueButton cueButton;

    double position;

    void loadURL(URL audioURL);
    void setPositíonRelative(double pos);

   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
