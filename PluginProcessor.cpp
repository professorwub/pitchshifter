/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "VocoderTools.h"

//==============================================================================
PitchShifterAudioProcessor::PitchShifterAudioProcessor()
	: parameters(*this, nullptr, Identifier("CompTreeState"),
		{
			std::make_unique<AudioParameterFloat>("SemiTones", // parameter ID
												  "Semitones Shift", // parameter name
												  NormalisableRange<float>(-6.0f, 6.0f, 1.0f),
												  0.0f), // default
			std::make_unique<AudioParameterFloat>("EffLevel", // parameter ID
												  "Effect Level", // parameter name
												  NormalisableRange<float>(0.0f,1.0f,0.1f),
												  0.0f) // default
		})
{
    

	semitonesParam = parameters.getRawParameterValue("SemiTones");
    effectlevelParam = parameters.getRawParameterValue("EffLevel");
}

PitchShifterAudioProcessor::~PitchShifterAudioProcessor()
{
}

//==============================================================================
const String PitchShifterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PitchShifterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PitchShifterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PitchShifterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PitchShifterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PitchShifterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PitchShifterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PitchShifterAudioProcessor::setCurrentProgram (int index)
{
}

const String PitchShifterAudioProcessor::getProgramName (int index)
{
    return {};
}

void PitchShifterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PitchShifterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	// Determine FFT order
	int minWindowLength = MINBLOCKSPERWINDOW * samplesPerBlock;
	int order = 0;
	int windowLength = 1;
	while (windowLength < minWindowLength)
	{
		order++;
		windowLength *= 2;
	}
	// Initialize shifters
    shifterBank.resize(getNumInputChannels());
    for (auto ch = 0; ch < getNumInputChannels(); ch++)
    {
        shifterBank[ch] = std::unique_ptr<SHIFTER>(new SHIFTER);
        shifterBank[ch]->init(order);
    }
    mixbuffer.setSize(getNumInputChannels(), samplesPerBlock);
}

void PitchShifterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PitchShifterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PitchShifterAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	float hopratio = pow(2.0f, *semitonesParam / 12.0f);
    AudioBuffer<float> tmpBuffer(mixbuffer.getArrayOfWritePointers(), buffer.getNumChannels(), buffer.getNumSamples());
    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        tmpBuffer.copyFrom(ch, 0, buffer, ch, 0, buffer.getNumSamples());
    tmpBuffer.applyGain(1.0 - *effectlevelParam);
    buffer.applyGain(*effectlevelParam);
    for (auto ch = 0; ch < totalNumInputChannels; ch++)
    {
        shifterBank[ch]->step(buffer.getWritePointer(ch), buffer.getNumSamples(), hopratio);
        buffer.addFrom(ch, 0, tmpBuffer.getReadPointer(ch), buffer.getNumSamples());
    }
}

//==============================================================================
bool PitchShifterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PitchShifterAudioProcessor::createEditor()
{
    return new PitchShifterAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void PitchShifterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	auto state = parameters.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void PitchShifterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(parameters.state.getType()))
			parameters.replaceState(ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PitchShifterAudioProcessor();
}
