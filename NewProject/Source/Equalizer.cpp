/*
  ==============================================================================

    Equalizer.cpp
    Created: 25 Aug 2024 7:31:54pm
    Author:  jugur

  ==============================================================================
*/

#include "Equalizer.h"

Equalizer::Equalizer()
{
    // Initialize with default coefficients
    updateLowCutFilter();
    updateMidCutFilter();
    updateHighCutFilter();
}

void Equalizer::prepare(const juce::dsp::ProcessSpec& spec)
{
    // Prepare the filters for multi-channel processing
    lowCutFilter.prepare(spec);
    midCutFilter.prepare(spec);
    highCutFilter.prepare(spec);
}

void Equalizer::process(juce::dsp::AudioBlock<float>& block)
{
    auto context = juce::dsp::ProcessContextReplacing<float>(block);

    // Apply the filters to the audio block (stereo/multi-channel support)
    lowCutFilter.process(context);
    midCutFilter.process(context);
    highCutFilter.process(context);
}

void Equalizer::setLowGain(float gain)
{
    lowGain = gain;
    updateLowCutFilter();
}

void Equalizer::setMidGain(float gain)
{
    midGain = gain;
    updateMidCutFilter();
}

void Equalizer::setHighGain(float gain)
{
    highGain = gain;
    updateHighCutFilter();
}

void Equalizer::updateLowCutFilter()
{
    // Update coefficients for the low shelf filter (for all channels)
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(44100.0, 200.0f, 0.707f, juce::Decibels::decibelsToGain(lowGain));
    *lowCutFilter.state = *coefficients;
}

void Equalizer::updateMidCutFilter()
{
    // Update coefficients for the peak filter (for all channels)
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100.0, 1000.0f, 0.707f, juce::Decibels::decibelsToGain(midGain));
    *midCutFilter.state = *coefficients;
}

void Equalizer::updateHighCutFilter()
{
    // Update coefficients for the high shelf filter (for all channels)
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(44100.0, 5000.0f, 0.707f, juce::Decibels::decibelsToGain(highGain));
    *highCutFilter.state = *coefficients;
}
