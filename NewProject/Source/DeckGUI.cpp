/*
  ==============================================================================

    DeckGUI.cpp
    Created: 3 Aug 2024 3:09:17pm
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer* _player, int _side)
    : player(_player),
    jogWheel(_player, _side),
    side(_side)
{
    position = 0.0;
    isPlaying = false;

    fileLoadedCallback = std::bind(&DeckGUI::handleFileLoaded, this, std::placeholders::_1);
    EventBus::getInstance().subscribe(EventTypes::FILE_LOADED_EVENT, fileLoadedCallback);

    timerTickCallback = std::bind(&DeckGUI::setPositionRelative, this, std::placeholders::_1);
    EventBus::getInstance().subscribe(EventTypes::TIMER_TICK_EVENT, timerTickCallback);

    fileRemovedCallback = std::bind(&DeckGUI::handleFileUnloaded, this, std::placeholders::_1);
    EventBus::getInstance().subscribe(EventTypes::CURRENT_FILE_REMOVED, fileRemovedCallback);

    playPauseButton.addListener(this);
    cueButton.addListener(this);
    speedSlider.addListener(this);

    speedSlider.setSliderStyle(juce::Slider::LinearVertical);
    speedSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    speedSlider.setRange(0.0, 2.0);
    speedSlider.setValue(1.0);
    speedSlider.setLookAndFeel(&tempoSliderLookAndFeel);

    addAndMakeVisible(playPauseButton);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(jogWheel);
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

    reevaluateSliders(std::to_string(side));
    disableButtons(std::to_string(side));
}

DeckGUI::~DeckGUI()
{
    speedSlider.setLookAndFeel(nullptr);
}

void DeckGUI::paint(juce::Graphics& g)
{
    if (side == 1)
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
    double rowH = getHeight() / static_cast<double>(11);
    double columnW = getWidth() / static_cast<double>(11);
    double firstRowY = 310;
    double redButtonsX = 65;

    int redButtonSize = 45;
    int redButtonMargin = 3;

    jogWheel.setBounds(30, 10, 260, 260);
    speedSlider.setBounds(getWidth() - Constants::smallMargin - 50.0f, 250.0f, 50.0f, 155.0f);
    cueButton.setBounds(10, 300, 50, 50);
    playPauseButton.setBounds(10, 355, 50, 50);

    redButton1.setBounds(redButtonsX, firstRowY, redButtonSize, redButtonSize);
    redButton2.setBounds(redButtonsX + redButtonSize + redButtonMargin, firstRowY, redButtonSize, redButtonSize);
    redButton3.setBounds(redButtonsX + redButtonSize * 2 + redButtonMargin * 2, firstRowY, redButtonSize, redButtonSize);
    redButton4.setBounds(redButtonsX + redButtonSize * 3 + redButtonMargin * 3, firstRowY, redButtonSize, redButtonSize);

    redButton5.setBounds(redButtonsX, firstRowY + redButtonSize + redButtonMargin, redButtonSize, redButtonSize);
    redButton6.setBounds(redButtonsX + redButtonSize + redButtonMargin, firstRowY + redButtonSize + redButtonMargin, redButtonSize, redButtonSize);
    redButton7.setBounds(redButtonsX + redButtonSize * 2 + redButtonMargin * 2, firstRowY + redButtonSize + redButtonMargin, redButtonSize, redButtonSize);
    redButton8.setBounds(redButtonsX + redButtonSize * 3 + redButtonMargin * 3, firstRowY + redButtonSize + redButtonMargin, redButtonSize, redButtonSize);
}

void DeckGUI::handleFileLoaded(const std::string& payload)
{
    std::vector<std::string> tokens;
    std::stringstream ss(payload);
    std::string token;

    while (std::getline(ss, token, ','))
    {
        tokens.push_back(token);
    }

    if (tokens[0] == std::to_string(this->side))
    {
        enableButtons(tokens[0]);
        reevaluateSliders(tokens[0]);
        repaint();
    }
}

void DeckGUI::handleFileUnloaded(const std::string& side)
{
    if (side == std::to_string(this->side))
    {
        isPlaying = false;
        disableButtons(side);
        setPositionRelative(side);
        repaint();
    }
}

void DeckGUI::setPositionRelative(const std::string& placeholder)
{
    double pos = player->getPositionRelative();
    if (pos >= 1.0)
    {
        isPlaying = false;
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
    else if (button == &cueButton)
    {
        player->setPositionRelative(0.0);
    }
}

void DeckGUI::handlePlayButton()
{
    if (isPlaying)
    {
        player->stop();
        isPlaying = false;
    }
    else
    {
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

void DeckGUI::reevaluateSliders(const std::string& side)
{
    if (side == std::to_string(this->side))
    {
        sliderValueChanged(&speedSlider);
    }
}

void DeckGUI::enableButtons(const std::string& side)
{
    if (side == std::to_string(this->side))
    {
        playPauseButton.setEnabled(true);
        cueButton.setEnabled(true);
    }
}

void DeckGUI::disableButtons(const std::string& side)
{
    if (side == std::to_string(this->side))
    {
        playPauseButton.setEnabled(false);
        cueButton.setEnabled(false);
    }
}
