/*
  ==============================================================================

    Equalizer.cpp
    Created: 25 Aug 2024 7:31:54pm
    Author:  Sasa Jugurdzija, with help from external resources.

  ==============================================================================
*/

#include "Equalizer.h"

Equalizer::Equalizer()
{
    updateLowCutFilter();
    updateMidCutFilter();
    updateHighCutFilter();
}

void Equalizer::prepare(const dsp::ProcessSpec& spec)
{
    lowCutFilter.prepare(spec);
    midCutFilter.prepare(spec);
    highCutFilter.prepare(spec);
}

void Equalizer::process(dsp::AudioBlock<float>& block)
{
    auto context = dsp::ProcessContextReplacing<float>(block);

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
    auto coefficients = dsp::IIR::Coefficients<float>::makeLowShelf(
        44100.0, 200.0f, 0.707f, Decibels::decibelsToGain(lowGain));
    *lowCutFilter.state = *coefficients;
}

void Equalizer::updateMidCutFilter()
{
    auto coefficients = dsp::IIR::Coefficients<float>::makePeakFilter(
        44100.0, 1000.0f, 0.707f, Decibels::decibelsToGain(midGain));
    *midCutFilter.state = *coefficients;
}

void Equalizer::updateHighCutFilter()
{
    auto coefficients = dsp::IIR::Coefficients<float>::makeHighShelf(
        44100.0, 5000.0f, 0.707f, Decibels::decibelsToGain(highGain));
    *highCutFilter.state = *coefficients;
}
