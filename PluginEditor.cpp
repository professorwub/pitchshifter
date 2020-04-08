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

	effectlevelLabel.setText("Level of Effect", dontSendNotification);
	effectlevelLabel.setColour(Label::textColourId, Colours::black);
	addAndMakeVisible(effectlevelLabel);

	// Create sliders
	semitonesSlider.setColour(Slider::trackColourId, Colours::orangered);
	semitonesSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 60, 20);
	semitonesSlider.setColour(Slider::textBoxBackgroundColourId, Colours::white);
	semitonesSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	addAndMakeVisible(semitonesSlider);
	semitonesAttachment.reset(new SliderAttachment(valueTreeState, "SemiTones", semitonesSlider));

	effectlevelSlider.setColour(Slider::trackColourId, Colours::orangered);
	effectlevelSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 60, 20);
	effectlevelSlider.setColour(Slider::textBoxBackgroundColourId, Colours::white);
	effectlevelSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	addAndMakeVisible(effectlevelSlider);
	effectlevelAttachment.reset(new SliderAttachment(valueTreeState, "EffLevel", effectlevelSlider));

    setSize (TitleWidth + 2 * Margin, TitleHeight + 2 * SliderWidth + 4 * Margin);
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
	y += SliderWidth + Margin;
	x = Margin;
	effectlevelLabel.setBounds(x, y, LabelWidth, LabelHeight);
	x += LabelWidth;
	effectlevelSlider.setBounds(x, y, SliderLength, SliderWidth);
}
