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
    : player1(_player1), 
      player2(_player2)
{
    hiKnob1.setLabel("HI");
    hiKnob1.setRange(-24.0f, 24.0f, 0.1f);
    hiKnob1.setValue(0.0f);
    hiKnob1.knobSlider.addListener(this);
    addAndMakeVisible(hiKnob1);

    midKnob1.setLabel("MID");
    midKnob1.setRange(-24.0f, 24.0f, 0.1f);
    midKnob1.setValue(0.0f);
    midKnob1.knobSlider.addListener(this);
    addAndMakeVisible(midKnob1);

    lowKnob1.setLabel("LOW");
    lowKnob1.setRange(-24.0f, 24.0f, 0.1f);
    lowKnob1.setValue(0.0f);
    lowKnob1.knobSlider.addListener(this);
    addAndMakeVisible(lowKnob1);

    hiKnob2.setLabel("HI");
    hiKnob2.setRange(-24.0f, 24.0f, 0.1f);
    hiKnob2.setValue(0.0f);
    hiKnob2.knobSlider.addListener(this);
    addAndMakeVisible(hiKnob2);

    midKnob2.setLabel("MID");
    midKnob2.setRange(-24.0f, 24.0f, 0.1f);
    midKnob2.setValue(0.0f);
    midKnob2.knobSlider.addListener(this);
    addAndMakeVisible(midKnob2);

    lowKnob2.setLabel("LOW");
    lowKnob2.setRange(-24.0f, 24.0f, 0.1f);
    lowKnob2.setValue(0.0f);
    lowKnob2.knobSlider.addListener(this);
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
    g.setColour(Constants::textColor);

    //eq text left
    g.drawLine(
        Constants::mediumMargin+70, 
        Constants::smallMargin+42, 
        Constants::mediumMargin + 70 + 5, 
        Constants::smallMargin + 42, 
        1.0f);

    g.drawLine(
        Constants::mediumMargin + 70 + 5,
        Constants::smallMargin + 42, 
        Constants::mediumMargin + 70 + 5,
        Constants::smallMargin + 105,
        1.0f);

    g.setFont(10.0f);
    g.drawText("EQ", Constants::mediumMargin + 70, Constants::smallMargin + 105, 20, 12, juce::Justification::left);


    g.drawLine(
        Constants::mediumMargin + 70 + 5,
        Constants::smallMargin + 118,
        Constants::mediumMargin + 70 + 5,
        Constants::smallMargin + 183,
        1.0f);

    g.drawLine(
        Constants::mediumMargin + 70 + 5,
        Constants::smallMargin + 183,
        Constants::mediumMargin + 70,
        Constants::smallMargin + 183,
        1.0f);

    //eq text right
    g.drawLine(
        getWidth() - Constants::mediumMargin - 70,
        Constants::smallMargin + 42,
        getWidth() - Constants::mediumMargin - 70 - 5,
        Constants::smallMargin + 42,
        1.0f);

    g.drawLine(
        getWidth() - Constants::mediumMargin - 70 - 5,
        Constants::smallMargin + 42,
        getWidth() - Constants::mediumMargin - 70 - 5,
        Constants::smallMargin + 105,
        1.0f);

    g.setFont(10.0f);
    g.drawText("EQ", getWidth() - Constants::mediumMargin - 70 - 10, Constants::smallMargin + 105, 20, 12, juce::Justification::left);


    g.drawLine(
        getWidth() - Constants::mediumMargin - 70 - 5,
        Constants::smallMargin + 118,
        getWidth() - Constants::mediumMargin - 70 - 5,
        Constants::smallMargin + 183,
        1.0f);

    g.drawLine(
        getWidth() - Constants::mediumMargin - 70 - 5,
        Constants::smallMargin + 183,
        getWidth() - Constants::mediumMargin - 70,
        Constants::smallMargin + 183,
        1.0f);


    // transition slider text
    g.drawLine(0,5,0,getHeight()-5, 3.0f);
    g.drawLine(getWidth(), 5, getWidth(), getHeight()-5, 3.0f);

    g.setFont(10.0f);
    g.drawText("TRANSITION FX", 80, 317, 100, 12, juce::Justification::centredBottom);

    g.drawLine(105, 337, 130, 343, 2.0f);
    g.drawLine(130, 343, 155, 337, 2.0f);
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
        80.0f,
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
    else if (slider == &hiKnob1.knobSlider)
    {
        player1->setHighGain(juce::Decibels::decibelsToGain(slider->getValue()));
    }
    else if (slider == &midKnob1.knobSlider)
    {
        player1->setMidGain(juce::Decibels::decibelsToGain(slider->getValue()));
    }
    else if (slider == &lowKnob1.knobSlider)
    {
        player1->setLowGain(juce::Decibels::decibelsToGain(slider->getValue()));
    }
    else if (slider == &hiKnob2.knobSlider)
    {
        player2->setHighGain(juce::Decibels::decibelsToGain(slider->getValue()));
    }
    else if (slider == &midKnob2.knobSlider)
    {
        player2->setMidGain(juce::Decibels::decibelsToGain(slider->getValue()));
    }
    else if (slider == &lowKnob2.knobSlider)
    {
        player2->setLowGain(juce::Decibels::decibelsToGain(slider->getValue()));
    }

}
