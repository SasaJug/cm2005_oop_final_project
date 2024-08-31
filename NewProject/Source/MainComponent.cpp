#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent()
{
	// Make sure you set the size of the component after
	// you add any child components.
	setSize(
		Constants::windowWidth,
		Constants::windowHeight
	);

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

	startTimer(200);

	addAndMakeVisible(deck1);
	addAndMakeVisible(deck2);
	addAndMakeVisible(midSection);

	addAndMakeVisible(playlistComponent2);
	addAndMakeVisible(playlistComponent1);
	addAndMakeVisible(waveformDisplay1);
	addAndMakeVisible(waveformDisplay2);
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
	juce::ColourGradient baseGradient(Constants::backgroundColor.brighter(0.4f), getLocalBounds().getX(), getLocalBounds().getY(),
		Constants::backgroundColor.darker(0.5f), getWidth(), getHeight(), false);
	baseGradient.addColour(0.2, Constants::backgroundColor.brighter(0.1f));
	g.setGradientFill(baseGradient);
	g.fillRect(getLocalBounds());

	// Define the text for the first line
	juce::String textLine1 = "CM2005 OOP";

	// Define the text for the second line
	juce::String textLine2 = "OTODECKS";

	int xPosition = 5;
	int yPosition = 5;
	g.setColour(Constants::textColor);
	g.setFont(11.0f);
	g.drawText(textLine1, xPosition, yPosition, 100, 12, juce::Justification::left);

	g.setFont(12.0f);
	g.drawText(textLine2, xPosition, yPosition + 12, 100, 13, juce::Justification::left);
}

void MainComponent::resized()
{
	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.

	deck1.setBounds(0, 0, getWidth() * 0.36, 600);
	playlistComponent1.setBounds(0, 416, getWidth() * 0.36, 156);

	midSection.setBounds(getWidth() * 0.36, 0, getWidth() * 0.28, 416);

	deck2.setBounds(getWidth() * 0.64, 0, getWidth() * 0.36, 600);
	playlistComponent2.setBounds(getWidth() * 0.64, 416, getWidth() * 0.36, 156);


	waveformDisplay1.setBounds(
		getWidth() * 0.36,
		416.0f,
		getWidth() * 0.28,
		78
	);
	waveformDisplay2.setBounds(
		getWidth() * 0.36,
		494.0f,
		getWidth() * 0.28,
		78
	);
}


void MainComponent::timerCallback()
{
	EventBus::getInstance().triggerEvent(EventTypes::TIMER_TICK_EVENT, "");
}

