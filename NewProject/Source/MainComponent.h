#pragma once

#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "DeckGUI.h"
#include "MidSection.h"
#include "DJAudioPlayer.h"
#include "Constants.h"
using namespace juce;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AudioAppComponent

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

private:
    //==============================================================================
    // Your private member variables go here...
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{ 100 };
   
    DJAudioPlayer player1 { formatManager };
    DeckGUI deck1{ &player1, formatManager, thumbCache };
    DJAudioPlayer player2 { formatManager };
    DeckGUI deck2{ &player2, formatManager, thumbCache };
    MidSection midSection { &player1, &player2 };
    MixerAudioSource mixerSource;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
