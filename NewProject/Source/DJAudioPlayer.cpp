/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 1 Aug 2024 7:39:19pm
    Author:  jugur

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager) : formatManager(_formatManager) {}

DJAudioPlayer::~DJAudioPlayer() {}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{

    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources() 
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL) {
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));

    if (reader != nullptr)
    {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
    else
    {
        DBG("Failed to create audio reader for the input stream.");
    }
}
void DJAudioPlayer::setGain(double gain) 
{
    if(gain < 0.0 || gain > 1.0) return;
	transportSource.setGain(gain);
}


void DJAudioPlayer::setSpeed(double speed)
{
    if(speed < 1.0 || speed > 10.0) return;
    resampleSource.setResamplingRatio(speed);
}

void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}


void DJAudioPlayer::setPositionRelative(double pos)
{
	if(pos < 0.0 || pos > 1.0) return;
    double posInSec = transportSource.getLengthInSeconds() * pos;
	setPosition(posInSec);
}

void DJAudioPlayer::setPositionChange(double change)
{
    double newPos = getPositionRelative() + change;
    double posInSec = transportSource.getLengthInSeconds() * newPos;
    DBG("New position: " << newPos);
    DBG("New position in seconds: " << posInSec);
	if(posInSec < 0.0 || posInSec > transportSource.getLengthInSeconds()) return;
	setPosition(posInSec);
}

void DJAudioPlayer::start() 
{
    transportSource.start();
}

void DJAudioPlayer::stop() 
{
	transportSource.stop(); 
}
