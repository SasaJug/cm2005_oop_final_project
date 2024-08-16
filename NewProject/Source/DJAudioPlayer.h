/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 1 Aug 2024 7:39:19pm
    Author:  jugur

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
using namespace juce;

class DJAudioPlayer : public AudioSource
{
    public:
		DJAudioPlayer(AudioFormatManager& _formatManager);
		~DJAudioPlayer();

		void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
		void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
		void releaseResources() override;

		void loadURL(URL audioURL);
		void unload();
		void setGain(double gain);
		void setSpeed(double speed);
		void setPosition(double posInSecs);

		double getPositionRelative();
		void setPositionRelative(double pos); 
		void setPositionChange(double change);

		void start();
		void stop();	

	private:
		AudioFormatManager& formatManager;
		juce::AudioTransportSource transportSource;
		juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
		std::unique_ptr<juce::AudioFormatReaderSource> readerSource;

		juce::FileChooser fChooser{ "Select a file..." };

		double phase;
		double dPhase;
		Random rand;
};
