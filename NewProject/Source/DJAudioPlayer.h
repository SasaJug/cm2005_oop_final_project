/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 1 Aug 2024 7:39:19pm
    Author:  The solution is mostly copied from the course videos and lesson worksheets.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "Equalizer.h"

using namespace juce;

class DJAudioPlayer : public AudioSource
{
public:
    /**
     * @brief Constructor to initialize the DJAudioPlayer.
     *
     * @param _formatManager Reference to the AudioFormatManager used for loading audio files.
     */
    DJAudioPlayer(AudioFormatManager& _formatManager);

    /**
     * @brief Destructor for DJAudioPlayer.
     *
     */
    ~DJAudioPlayer();

    /**
     * @brief Prepares the audio player for playback.
     *
     * @param samplesPerBlockExpected The expected number of samples per audio block.
     * @param sampleRate The sample rate of the audio stream.
     *
     */
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    /**
     * @brief Provides the next audio block to be played.
     *
     * @param bufferToFill The buffer that needs to be filled with audio data.
     *
     */
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;

    /**
     * @brief Releases resources when playback stops.
     *
     */
    void releaseResources() override;

    /**
     * @brief Loads an audio file from a URL.
     *
     * @param audioURL The URL of the audio file to be loaded.
     *
     */
    void loadURL(URL audioURL);

    /**
     * @brief Unloads the current audio file.
     *
     */
    void unload();

    /**
     * @brief Gets the current gain (volume) of the player.
     *
     * @return double The current gain value.
     *
     */
    double getGain();

    /**
     * @brief Sets the gain (volume) of the player.
     *
     * @param gain The gain value to set.
     *
     */
    void setGain(double gain);

    /**
     * @brief Sets the playback speed of the player.
     *
     * @param speed The speed multiplier.
     *
     */
    void setSpeed(double speed);

    /**
     * @brief Sets the playback position of the player in seconds.
     *
     * @param posInSecs The position in seconds.
     *
     */
    void setPosition(double posInSecs);

    /**
     * @brief Gets the relative playback position of the player.
     *
     * @return double The relative position (0.0 to 1.0) of the playback.
     *
     */
    double getPositionRelative();

    /**
     * @brief Sets the playback position relative to the track's length.
     *
     * @param pos The relative position (0.0 to 1.0).
     *
     */
    void setPositionRelative(double pos);

    /**
     * @brief Changes the playback position by a relative amount.
     *
     * @param change The amount to change the position by (relative to track length).
     *
     */
    void setPositionChange(double change);

    /**
     * @brief Starts playback of the loaded audio file.
     *
     */
    void start();

    /**
     * @brief Stops playback of the loaded audio file.
     *
     */
    void stop();

    /**
     * @brief Sets the low-frequency gain (bass).
     *
     * @param gain The gain value for low frequencies.
     *
     */
    void setLowGain(float gain);

    /**
     * @brief Sets the mid-frequency gain.
     *
     * @param gain The gain value for mid frequencies.
     *
     */
    void setMidGain(float gain);

    /**
     * @brief Sets the high-frequency gain (treble).
     *
     * @param gain The gain value for high frequencies.
     *
     */
    void setHighGain(float gain);

private:
    AudioFormatManager& formatManager;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    Equalizer equalizer;

    juce::FileChooser fChooser{ "Select a file..." };

    double phase;
    double dPhase;
    Random rand;
};
