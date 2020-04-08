/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "stft.h"
#include "istft.h"
#include "shifter.h"
#include <complex>
#include <vector>

typedef std::complex<float> Cfloat;
constexpr auto MINBLOCKSPERWINDOW = 16;

//==============================================================================
/**
*/
class PitchShifterAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    PitchShifterAudioProcessor();
    ~PitchShifterAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	

private:
    //==============================================================================
    std::vector<std::unique_ptr<SHIFTER>> shifterBank;

	AudioProcessorValueTreeState parameters;
	std::atomic<float>* semitonesParam = nullptr;
    std::atomic<float>* effectlevelParam = nullptr;
    AudioBuffer<float> mixbuffer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PitchShifterAudioProcessor)
};
