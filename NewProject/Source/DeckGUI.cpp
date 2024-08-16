/*
  ==============================================================================

	DeckGUI.cpp
	Created: 3 Aug 2024 3:09:17pm
	Author:  jugur

  ==============================================================================
*/
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
	AudioFormatManager& formatManagerToUse,
	AudioThumbnailCache& cacheToUse)
	: player(_player), playlistComponent(_player), searchComponent(_player)
	{

	position = 0.0;
	isPlaying = false;
	startTimer(200);


	playButton.addListener(this);
	speedSlider.addListener(this);

	speedSlider.setSliderStyle(juce::Slider::LinearVertical);
	speedSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	speedSlider.setRange(0.0, 2.0);
	speedSlider.setValue(1.0);

	addAndMakeVisible(playButton);
	addAndMakeVisible(speedSlider);
	addAndMakeVisible(playlistComponent);
	addAndMakeVisible(searchComponent);
}


DeckGUI::~DeckGUI()
{
}

void DeckGUI::paint(juce::Graphics& g)
{
	/* This demo code just fills the component's background and
	   draws some placeholder text to get you started.

	   You should replace everything in this method with your own
	   drawing code..
	*/

	//g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
}

void DeckGUI::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..

	double rowH = getHeight()/11;
	double columnW = getWidth()/11;

	searchComponent.setBounds(columnW, 10, columnW * 9, columnW * 9);
	speedSlider.setBounds(getWidth()*0.9, rowH*4, getWidth()*0.1, rowH*3.8);
	playButton.setBounds(0, rowH*6.8, rowH, rowH);
	playlistComponent.setBounds(0, rowH * 8, getWidth(), rowH * 3);

}

void DeckGUI::loadURL(URL audioURL) {
	player->loadURL(audioURL);
}

void DeckGUI::setPositíonRelative(double pos)
{
	if (pos != position)
	{

		position = pos;
		if (position >= 1.0) {
			isPlaying = false;
			playButton.setButtonText("PLAY");
			player->stop();
			player->setPositionRelative(0.0);
			repaint();
		}
	}
}

void DeckGUI::buttonClicked(juce::Button* button)
{
	if (button == &playButton)
	{
		handlePlayButton();
	}
}

void DeckGUI::handlePlayButton()
{
	if (isPlaying)
	{
		playButton.setButtonText("PLAY");
		player->stop();
		isPlaying = false;
	}
	else
	{
		playButton.setButtonText("PAUSE");
		player->start();
		isPlaying = true;
	}
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{

	if (slider == &speedSlider)
	{
		player->setSpeed(slider->getValue());
	}	
}

void DeckGUI::timerCallback()
{
	if(isPlaying)
		setPositíonRelative(player->getPositionRelative());
}


