/*
  ==============================================================================

	DeckGUI.cpp
	Created: 3 Aug 2024 3:09:17pm
	Author:  jugur

  ==============================================================================
*/
#include "DeckGUI.h"


//==============================================================================
DeckGUI::DeckGUI(
	DJAudioPlayer* _player,
	int _side
)
	: player(_player), 
	searchComponent(_player), 
	side(_side)
	{

	position = 0.0;
	isPlaying = false;

	timerTickCallback = std::bind(&DeckGUI::setPositionRelative, this, std::placeholders::_1);
	EventBus::getInstance().subscribe(EventTypes::TIMER_TICK_EVENT, timerTickCallback);

	playPauseButton.addListener(this);
	cueButton.addListener(this);
	speedSlider.addListener(this);

	speedSlider.setSliderStyle(juce::Slider::LinearVertical);
	speedSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	speedSlider.setRange(0.0, 2.0);
	speedSlider.setValue(1.0);
	speedSlider.setLookAndFeel(&customSliderLookAndFeel);

	addAndMakeVisible(playPauseButton);
	addAndMakeVisible(speedSlider);
	addAndMakeVisible(searchComponent);
	addAndMakeVisible(playPauseButton);
	addAndMakeVisible(cueButton);

	addAndMakeVisible(redButton1);
	addAndMakeVisible(redButton2);
	addAndMakeVisible(redButton3);
	addAndMakeVisible(redButton4);
	addAndMakeVisible(redButton5);
	addAndMakeVisible(redButton6);
	addAndMakeVisible(redButton7);
	addAndMakeVisible(redButton8);
}

DeckGUI::~DeckGUI()
{
	speedSlider.setLookAndFeel(nullptr);
}

void DeckGUI::paint(juce::Graphics& g)
{
	/* This demo code just fills the component's background and
	   draws some placeholder text to get you started.

	   You should replace everything in this method with your own
	   drawing code..
	*/

	//g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

	if(side == 1)
	{
		juce::String text = "1";

		int xPosition = getWidth() - 40;
		int yPosition = 15;
		g.setColour(Constants::textColor);
		g.setFont(25.0f);
		g.drawText(text, xPosition, yPosition, 30, 12, juce::Justification::right);
	}
	else
	{
		juce::String text = "2";

		int xPosition = 10;
		int yPosition = 15;
		g.setColour(Constants::textColor);
		g.setFont(25.0f);
		g.drawText(text, xPosition, yPosition, 30, 12, juce::Justification::left);
	}
}

void DeckGUI::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..

	double rowH = getHeight()/11;
	double columnW = getWidth()/11;
	double firstRowY = 310;
	double redButtonsX = 65;

	int redButtonSize = 45;
	int redButtonMargin = 3;

	searchComponent.setBounds(30, 10, 260, 260);
	speedSlider.setBounds(getWidth()-Constants::smallMargin-50.0f, 250.0f, 50.0f, 155.0f);
	cueButton.setBounds(10, 300, 50, 50);
	playPauseButton.setBounds(10, 355, 50, 50);

	redButton1.setBounds(redButtonsX,                                     firstRowY, redButtonSize, redButtonSize);
	redButton2.setBounds(redButtonsX + redButtonSize + redButtonMargin,   firstRowY, redButtonSize, redButtonSize);
	redButton3.setBounds(redButtonsX + redButtonSize*2 + redButtonMargin*2, firstRowY, redButtonSize, redButtonSize);
	redButton4.setBounds(redButtonsX + redButtonSize*3 + redButtonMargin*3, firstRowY, redButtonSize, redButtonSize);

	redButton5.setBounds(redButtonsX,                                     firstRowY+redButtonSize+redButtonMargin,     redButtonSize, redButtonSize);
	redButton6.setBounds(redButtonsX + redButtonSize + redButtonMargin,   firstRowY + redButtonSize + redButtonMargin, redButtonSize, redButtonSize);
	redButton7.setBounds(redButtonsX + redButtonSize*2 + redButtonMargin*2, firstRowY + redButtonSize + redButtonMargin, redButtonSize, redButtonSize);
	redButton8.setBounds(redButtonsX + redButtonSize*3 + redButtonMargin*3, firstRowY + redButtonSize + redButtonMargin, redButtonSize, redButtonSize);

}

void DeckGUI::setPositionRelative(const std::string& position)
{
	double pos = player->getPositionRelative();
		if (pos >= 1.0) {
			isPlaying = false;
			//playPauseButton.setButtonText("PLAY");
			player->stop();
			player->setPositionRelative(0.0);
			repaint();
		}
}

void DeckGUI::buttonClicked(juce::Button* button)
{
	if (button == &playPauseButton)
	{
		handlePlayButton();
	}
}

void DeckGUI::handlePlayButton()
{
	if (isPlaying)
	{
		//playButton.setButtonText("PLAY");
		player->stop();
		isPlaying = false;
	}
	else
	{
		//playButton.setButtonText("PAUSE");
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

