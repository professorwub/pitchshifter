/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PitchShifterAudioProcessorEditor::PitchShifterAudioProcessorEditor (PitchShifterAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    // Create labels
	semitonesLabel.setText("Semitone Shift", dontSendNotification);
	semitonesLabel.setColour(Label::textColourId, Colours::black);
	addAndMakeVisible(semitonesLabel);

	// Create sliders
	semitonesSlider.setColour(Slider::trackColourId, Colours::orangered);
	semitonesSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 60, 20);
	semitonesSlider.setColour(Slider::textBoxBackgroundColourId, Colours::white);
	semitonesSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	addAndMakeVisible(semitonesSlider);
	semitonesAttachment.reset(new SliderAttachment(valueTreeState, "SemiTones", semitonesSlider));

    setSize (TitleWidth + 2 * Margin, TitleHeight + SliderWidth + 3 * Margin);
}

PitchShifterAudioProcessorEditor::~PitchShifterAudioProcessorEditor()
{
}

//==============================================================================
void PitchShifterAudioProcessorEditor::paint (Graphics& g)
{
	int x = Margin;
	int y = 0;
	g.fillAll(Colours::burlywood);
	g.setColour(Colours::black);
	g.setFont(24.0f);
	g.drawFittedText("Audio Pitch Shifter", x, y, TitleWidth, TitleHeight, Justification::centred, 1);
}

void PitchShifterAudioProcessorEditor::resized()
{
	int x = Margin;
	int y = TitleHeight + Margin;
	semitonesLabel.setBounds(x, y, LabelWidth, LabelHeight);
	x += LabelWidth;
	semitonesSlider.setBounds(x, y, SliderLength, SliderWidth);
}
