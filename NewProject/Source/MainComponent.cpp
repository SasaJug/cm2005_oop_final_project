#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent()
{
	// Make sure you set the size of the component after
	// you add any child components.
	setSize(984, 600);

	// Some platforms require permissions to open input channels so request that here
	if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
		&& !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
	{
		juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
			[&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
	}
	else
	{
		// Specify the number of input and output channels that we want to open
		setAudioChannels(2, 2);
	}

	addAndMakeVisible(deck1);
	addAndMakeVisible(deck2);
	addAndMakeVisible(midSection);
}

MainComponent::~MainComponent()
{
	// This shuts down the audio device and clears the audio source.
	shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	formatManager.registerBasicFormats();
	mixerSource.addInputSource(&player1, false);
	mixerSource.addInputSource(&player2, false);
	mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	mixerSource.getNextAudioBlock(bufferToFill);

}

void MainComponent::releaseResources()
{
	mixerSource.removeAllInputs();
	mixerSource.releaseResources();
	player1.releaseResources();
	player2.releaseResources();

}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{/*
	juce::ColourGradient gradient(juce::Colour::fromRGB(0x7d, 0x7d, 0x7d), 0, 0,
		juce::Colour::fromRGB(0x18, 0x18, 0x18), getWidth(), getHeight(),
		false);

	gradient.addColour(0.2, juce::Colour::fromRGB(0x32, 0x32, 0x32));
	g.setGradientFill(gradient);
	*/
	g.setColour(juce::Colour::fromRGB(0x2c, 0x2c, 0x2c));
	g.fillRect(getLocalBounds());
}

void MainComponent::resized()
{
	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.

	deck1.setBounds(0, 0, getWidth() * 0.38, getHeight());
	midSection.setBounds(getWidth() * 0.38, 0, getWidth() * 0.24, getHeight());
	deck2.setBounds(getWidth() * 0.62, 0, getWidth() * 0.38, getHeight());
}
