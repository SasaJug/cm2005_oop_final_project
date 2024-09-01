/*
  ==============================================================================

    DeckGUI.h
    Created: 3 Aug 2024 3:09:17pm
    Author:  Sasa Jugurdzija

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "DJAudioPlayer.h"
#include "JogWheel.h"
#include "TempoSliderLookAndFeel.h"
#include "PlayPauseButton.h"
#include "RedSquareButton.h"
#include "CueButton.h"
#include "Constants.h"
#include "EventBus.h"
#include "EventTypes.h"

using namespace juce;

class DeckGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener
{
public:
    /**
     * @brief Constructor to initialize the DeckGUI.
     *
     * @param player Pointer to the DJAudioPlayer instance controlling this deck.
     * @param side Indicates which side (1 or 2) this deck is on.
     *
     * This constructor sets up the user interface components of the deck,
     * including buttons, tempo slider, and jog wheel.
     */
    DeckGUI(DJAudioPlayer* player, int side);

    /**
     * @brief Destructor for DeckGUI.
     *
     */
    ~DeckGUI() override;

    /**
     * @brief Paints the DeckGUI component.
     *
     * @param g The Graphics object used for drawing.
     *
     * This method is responsible for rendering the visual elements of the deck,
     * including backgrounds, borders, and custom components.
     */
    void paint(juce::Graphics& g) override;

    /**
     * @brief Resizes the DeckGUI component.
     *
     * This method is called when the component is resized, and it adjusts
     * the layout of all child components accordingly.
     */
    void resized() override;

    /**
     * @brief Handles button click events.
     *
     * @param button Pointer to the Button that was clicked.
     *
     * This method is called when a button on the deck is clicked.
     */
    void buttonClicked(juce::Button* button) override;

    /**
     * @brief Handles the play button's functionality.
     *
     * This method manages the play/pause state when the play button is clicked.
     */
    void handlePlayButton();

    /**
     * @brief Handles slider value changes.
     *
     * @param slider Pointer to the Slider that was adjusted.
     *
     * This method is called when a slider on the deck is moved.
     */
    void sliderValueChanged(juce::Slider* slider) override;

private:
    int side;
    bool isPlaying = false;
    juce::Slider speedSlider;

    DJAudioPlayer* player;

    JogWheel jogWheel;
    TempoSliderLookAndFeel tempoSliderLookAndFeel;
    PlayPauseButton playPauseButton;
    CueButton cueButton;

    // Red buttons - do not have functionality yet
    RedSquareButton redButton1{ "redButton1" };
    RedSquareButton redButton2{ "redButton2" };
    RedSquareButton redButton3{ "redButton3" };
    RedSquareButton redButton4{ "redButton4" };
    RedSquareButton redButton5{ "redButton5" };
    RedSquareButton redButton6{ "redButton6" };
    RedSquareButton redButton7{ "redButton7" };
    RedSquareButton redButton8{ "redButton8" };

    double position;

    void setPositionRelative(const std::string& side);
    void handleFileLoaded(const std::string& side);
    void handleFileUnloaded(const std::string& side);
    void reevaluateSliders(const std::string& side);
    void enableButtons(const std::string& side);
    void disableButtons(const std::string& side);

    //Event callback functions
    std::function<void(const std::string&)> timerTickCallback;
    std::function<void(const std::string&)> fileRemovedCallback;
    std::function<void(const std::string&)> fileLoadedCallback;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
