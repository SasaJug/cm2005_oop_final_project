/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 3 Aug 2024 8:15:01pm
    Author:  jugur

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
                                 AudioThumbnailCache& cacheToUse,
                                 DJAudioPlayer* _player,
                                 int _position)
    : audioThumbnail(1000, formatManagerToUse, cacheToUse),
      player(_player),
      guiPosition(_position),
      fileLoaded(false),
      position(0.0)
{


    fileLoadedCallback = std::bind(&WaveformDisplay::loadURLfromEvent, this, std::placeholders::_1);
    EventBus::getInstance().subscribe(EventTypes::FILE_LOADED_EVENT, fileLoadedCallback);

    timerTickCallback = std::bind(&WaveformDisplay::setPositionRelative, this, std::placeholders::_1);
    EventBus::getInstance().subscribe(EventTypes::TIMER_TICK_EVENT, timerTickCallback);

    audioThumbnail.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);
    g.setColour(Colours::orange);
    if (fileLoaded)
    {
        g.setColour(Colours::lightgreen);
        audioThumbnail.drawChannel(g, getLocalBounds(), 0, audioThumbnail.getTotalLength(), 0, 1);
        g.setColour(Colours::lightgreen);
        g.drawRect(position * getWidth()-getWidth()/40, 0, getWidth() / 20, getHeight());
    }
    else
    {
        g.setFont(24.0f);
        g.drawText("File not loaded", getLocalBounds(),
            Justification::centred, true);
    }
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(URL audioURL)
{
    audioThumbnail.clear();
    fileLoaded = audioThumbnail.setSource(new URLInputSource(audioURL));
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
    repaint();
}

void WaveformDisplay::setPositionRelative(const std::string& placeholder)
{
    double pos = player->getPositionRelative();
    if (pos != position)
    {
        position = pos;
        repaint();
    }
}

void WaveformDisplay::loadURLfromEvent(std::string payload)
{
    std::vector<std::string> tokens;
    std::stringstream ss(payload);
    std::string token;

    // Use getline with a comma as a delimiter
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (std::stoi(tokens[0]) == guiPosition) {
        juce::String juceStr(tokens[1]);

        // Create a juce::URL from the juce::String
        juce::URL url(juceStr);
        loadURL(url);
    }

}


