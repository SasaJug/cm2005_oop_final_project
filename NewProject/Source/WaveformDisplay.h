/*
  ==============================================================================

    WaveformDisplay.h
    Created: 3 Aug 2024 8:15:01pm
    Author:  jugur

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "EventBus.h"
#include "EventTypes.h"
using namespace juce;

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager& formatManagerToUse,
                    AudioThumbnailCache& cacheToUse,
                    DJAudioPlayer* player,
                    int position);

    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void loadURL(URL audioURL);
    void changeListenerCallback(ChangeBroadcaster* source) override;
    void setPositionRelative(const std::string& placeholder);

private:

    DJAudioPlayer* player;
    AudioThumbnail audioThumbnail;
    bool fileLoaded;
    double position;
    int guiPosition;

    void loadURLfromEvent(std::string payload);

    std::function<void(const std::string&)> fileLoadedCallback;
    std::function<void(const std::string&)> timerTickCallback;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
