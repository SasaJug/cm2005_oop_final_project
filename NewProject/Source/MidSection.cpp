/*
  ==============================================================================

    MidSection.cpp
    Created: 11 Aug 2024 2:26:07pm
    Author:  jugur

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MidSection.h"

//==============================================================================
MidSection::MidSection(
    DJAudioPlayer* _player1, 
    DJAudioPlayer* _player2
    )
    : player1(_player1), player2(_player2)
{
    hiKnob1.setLabel("HI");
    hiKnob1.setRange(0.0, 1.0, 0.01);
    hiKnob1.setValue(0.5);
    addAndMakeVisible(hiKnob1);

    midKnob1.setLabel("MID");
    midKnob1.setRange(0.0, 1.0, 0.01);
    midKnob1.setValue(0.5);
    addAndMakeVisible(midKnob1);

    lowKnob1.setLabel("LOW");
    lowKnob1.setRange(0.0, 1.0, 0.01);
    lowKnob1.setValue(0.5);
    addAndMakeVisible(lowKnob1);

    hiKnob2.setLabel("HI");
    hiKnob2.setRange(0.0, 1.0, 0.01);
    hiKnob2.setValue(0.5);
    addAndMakeVisible(hiKnob2);

    midKnob2.setLabel("MID");
    midKnob2.setRange(0.0, 1.0, 0.01);
    midKnob2.setValue(0.5);
    addAndMakeVisible(midKnob2);

    lowKnob2.setLabel("LOW");
    lowKnob2.setRange(0.0, 1.0, 0.01);
    lowKnob2.setValue(0.5);
    addAndMakeVisible(lowKnob2);

    volumeSlider1.addListener(this);
    volumeSlider2.addListener(this);
    volumeSliderTransition.addListener(this);

    volumeSlider1.setSliderStyle(juce::Slider::LinearVertical);
    volumeSlider1.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider1.setRange(0.0, 1.0);
    volumeSlider1.setValue(0.5);
    volumeSlider1.setLookAndFeel(&volumeSliderLookAndFeel);

    volumeSlider2.setSliderStyle(juce::Slider::LinearVertical);
    volumeSlider2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider2.setRange(0.0, 1.0);
    volumeSlider2.setValue(0.5);
    volumeSlider2.setLookAndFeel(&volumeSliderLookAndFeel);

    volumeSliderTransition.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSliderTransition.setRange(0.0, 1.0);
    volumeSliderTransition.setValue(0.5);
    volumeSliderTransition.setLookAndFeel(&volumeSliderLookAndFeel);

    addAndMakeVisible(volumeSlider1);
    addAndMakeVisible(volumeSlider2);
    addAndMakeVisible(volumeSliderTransition);
}

MidSection::~MidSection()
{
    volumeSlider1.setLookAndFeel(nullptr);
	volumeSlider2.setLookAndFeel(nullptr);
	volumeSliderTransition.setLookAndFeel(nullptr);
}

void MidSection::paint (juce::Graphics& g)
{
    g.setColour(Colours::grey);
    g.drawLine(0,0,0,getHeight(), 2.0f);
    g.drawLine(getWidth(), 0, getWidth(), getHeight(), 2.0f);
}

void MidSection::resized()
{

    int verticalSliderHeight = 100.0f;
    int verticalSliderWidth = 60.0f;


    int horizontalSliderWidth = 60.0f;
    int horizontalSliderHeight = 100.0f;

    hiKnob1.setBounds(
        Constants::mediumMargin,
        Constants::smallMargin,
        70.0f,
        70.0f);

    midKnob1.setBounds(
        Constants::mediumMargin,
        80.0f,
        70.0f,
        70.0f);

    lowKnob1.setBounds(
        Constants::mediumMargin,
        150.0f,
        70.0f,
        70.0f);


    hiKnob2.setBounds(
        getWidth() - Constants::mediumMargin - 70.0f,
        Constants::smallMargin,
        70.0f,
        70.0f);

    midKnob2.setBounds(
        getWidth() - Constants::mediumMargin - 70.0f,
        80.0f,
        70.0f,
        70.0f);

    lowKnob2.setBounds(
        getWidth() - Constants::mediumMargin - 70.0f,
        150.0f,
        70.0f,
        70.0f);

    volumeSlider1.setBounds(
        Constants::mediumMargin,               
        250.0f,
        verticalSliderWidth,
        verticalSliderHeight
    );

    volumeSlider2.setBounds(
        getWidth()- verticalSliderWidth - Constants::mediumMargin,
        250.0f,
        verticalSliderWidth,
        verticalSliderHeight
    );

    // Position the horizontal slider in the center-bottom area
    volumeSliderTransition.setBounds(
        70.0f,
        350.0f,
        100.0f,
        60.0f
    );
}







void MidSection::sliderValueChanged(juce::Slider* slider)
{

    if (slider == &volumeSlider1)
    {
        player1->setGain(slider->getValue());
    }
	else if (slider == &volumeSlider2)
	{
		player2->setGain(slider->getValue());
	}
	else if (slider == &volumeSliderTransition)
	{
		player1->setGain(slider->getValue());
		player2->setGain(1 - slider->getValue());
	}

}
