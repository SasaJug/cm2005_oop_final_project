/*
  ==============================================================================

    Equalizer.h
    Created: 25 Aug 2024 7:31:54pm
    Author:  Sasa Jugurdzija, with help from external resources.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

class Equalizer
{
public:
    /**
     * @brief Constructor to initialize the Equalizer.
     */
    Equalizer();

    /**
     * @brief Prepares the equalizer for processing audio.
     * @param spec The processing specification including sample rate, block size, etc.
     */
    void prepare(const dsp::ProcessSpec& spec);

    /**
     * @brief Processes the audio block with the equalizer filters.
     * @param block The audio block to process.
     */
    void process(dsp::AudioBlock<float>& block);

    /**
     * @brief Sets the gain for the low-frequency band (bass).
     * @param gain The gain value for the low frequencies.
     */
    void setLowGain(float gain);

    /**
     * @brief Sets the gain for the mid-frequency band.
     * @param gain The gain value for the mid frequencies.
     */
    void setMidGain(float gain);

    /**
     * @brief Sets the gain for the high-frequency band (treble).
     * @param gain The gain value for the high frequencies.
     */
    void setHighGain(float gain);

private:
    float lowGain = 1.0f;
    float midGain = 1.0f;
    float highGain = 1.0f;

    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> lowCutFilter;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> midCutFilter;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> highCutFilter;

    void updateLowCutFilter();
    void updateMidCutFilter();
    void updateHighCutFilter();
};
