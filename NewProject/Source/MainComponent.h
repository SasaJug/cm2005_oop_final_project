#pragma once

#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "DeckGUI.h"
#include "MidSection.h"
#include "DJAudioPlayer.h"
#include "PlaylistComponent.h"
#include "WaveformDisplay.h"
#include "Constants.h"
#include "EventBus.h"
#include "EventTypes.h"
using namespace juce;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AudioAppComponent,
                      public Timer

{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

    void timerCallback() override;

private:
    //==============================================================================
    // Your private member variables go here...
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{ 100 };
   
    DJAudioPlayer player1 { formatManager };
    DeckGUI deck1{ &player1, 1};
    PlaylistComponent playlistComponent1{ &player1, 1 };

    DJAudioPlayer player2 { formatManager };
    DeckGUI deck2{ &player2, 2 };
    PlaylistComponent playlistComponent2{ &player2, 2 };

    MidSection midSection { &player1, &player2 };
    WaveformDisplay waveformDisplay1{ formatManager, thumbCache, &player1, 1 };
    WaveformDisplay waveformDisplay2{ formatManager, thumbCache, &player2, 2 };

    MixerAudioSource mixerSource;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
