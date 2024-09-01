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

class WaveformDisplay : public juce::Component,
    public ChangeListener
{
public:
    /**
     * @brief Constructor to initialize the WaveformDisplay.
     * @param formatManagerToUse Reference to the AudioFormatManager for managing audio formats.
     * @param cacheToUse Reference to the AudioThumbnailCache for caching audio thumbnails.
     * @param player Pointer to the DJAudioPlayer instance.
     * @param side Indicates which side (1 or 2) this waveform display is on.
     */
    WaveformDisplay(AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse,
        DJAudioPlayer* player,
        int side);

    /**
     * @brief Destructor for WaveformDisplay.
     */
    ~WaveformDisplay() override;

    /**
     * @brief Paints the WaveformDisplay component.
     * @param g The Graphics object used for drawing.
     */
    void paint(juce::Graphics& g) override;

    /**
     * @brief Resizes the WaveformDisplay component.
     */
    void resized() override;

    /**
     * @brief Loads an audio file from a URL.
     * @param audioURL The URL of the audio file to be loaded.
     */
    void loadURL(URL audioURL);

    /**
     * @brief Handles changes to the waveform display.
     * @param source The ChangeBroadcaster that triggered the change.
     */
    void changeListenerCallback(ChangeBroadcaster* source) override;

    /**
     * @brief Sets the playback position relative to the track's length.
     * @param placeholder A placeholder string (not used).
     */
    void setPositionRelative(const std::string& placeholder);

    /**
     * @brief Handles the removal of the currently loaded file.
     * @param side A string representing the side.
     */
    void handleFileRemoved(const std::string& side);

private:
    DJAudioPlayer* player;
    AudioThumbnail audioThumbnail;
    bool fileLoaded;
    double position;
    int side;

    /**
     * @brief Loads a URL from an event payload.
     * @param payload The event payload containing the URL.
     */
    void loadURLfromEvent(std::string payload);

    std::function<void(const std::string&)> fileLoadedCallback;
    std::function<void(const std::string&)> timerTickCallback;
    std::function<void(const std::string&)> fileRemovedCallback;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
