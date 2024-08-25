/*
  ==============================================================================

    Equalizer.h
    Created: 25 Aug 2024 7:31:54pm
    Author:  jugur

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Equalizer
{
public:
    Equalizer();

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::dsp::AudioBlock<float>& block);
    void setLowGain(float gain);
    void setMidGain(float gain);
    void setHighGain(float gain);

private:
    float lowGain = 1.0f;
    float midGain = 1.0f;
    float highGain = 1.0f;

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> lowCutFilter;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> midCutFilter;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> highCutFilter;

    void updateLowCutFilter();
    void updateMidCutFilter();
    void updateHighCutFilter();
};
