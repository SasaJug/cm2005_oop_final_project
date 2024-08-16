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
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    volumeSlider1.addListener(this);
    volumeSlider2.addListener(this);
    volumeSliderTransition.addListener(this);

    volumeSlider1.setSliderStyle(juce::Slider::LinearVertical);
    volumeSlider1.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider1.setRange(0.0, 1.0);
    volumeSlider1.setValue(0.5);

    volumeSlider2.setSliderStyle(juce::Slider::LinearVertical);
    volumeSlider2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider2.setRange(0.0, 1.0);
    volumeSlider2.setValue(0.5);

    volumeSliderTransition.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSliderTransition.setRange(0.0, 1.0);
    volumeSliderTransition.setValue(0.5);

    addAndMakeVisible(volumeSlider1);
    addAndMakeVisible(volumeSlider2);
    addAndMakeVisible(volumeSliderTransition);
}

MidSection::~MidSection()
{
}

void MidSection::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void MidSection::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    volumeSlider1.setBounds(getWidth()*0.1, getHeight() * 0.41, 30, getHeight() * 0.2);
    volumeSlider2.setBounds(getWidth()*0.8, getHeight()*0.41, 30, getHeight()*0.2);
    volumeSliderTransition.setBounds(getWidth()*0.2, getHeight()*7/11, getWidth()*0.6, getHeight()*0.1);
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
