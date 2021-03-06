/*
  ==============================================================================

    OscillatorEditor.cpp
    Created: 11 Apr 2018 4:14:44pm
    Author:  tnpes

  ==============================================================================
*/

#include "OscillatorEditor.h"

OscillatorEditor::OscillatorEditor(MaxSynthAudioProcessor& p)
{
	// attack
	addAndMakeVisible(attackSlider);
	attackSlider.setSliderStyle(Slider::LinearVertical);
	attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(attackLabel);
	attackLabel.setText("attack", dontSendNotification);
	attackAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "attack", attackSlider);

	// decay
	addAndMakeVisible(decaySlider);
	decaySlider.setSliderStyle(Slider::LinearVertical);
	decaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(decayLabel);
	decayLabel.setText("decay", dontSendNotification);
	decayAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "decay", decaySlider);

	// sustain slider
	addAndMakeVisible(sustainSlider);
	sustainSlider.setSliderStyle(Slider::LinearVertical);
	sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(sustainLabel);
	sustainLabel.setText("sustain", dontSendNotification);
	sustainAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "sustain", sustainSlider);

	// release 
	addAndMakeVisible(releaseSlider);
	releaseSlider.setSliderStyle(Slider::LinearVertical);
	releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(releaseLabel);
	releaseLabel.setText("release", dontSendNotification);
	releaseAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "release", releaseSlider);
}

OscillatorEditor::~OscillatorEditor()
{
}

void OscillatorEditor::paint(Graphics& g)
{
	g.fillAll(Colours::grey);
}

void OscillatorEditor::resized()
{
	const int sliderWidth = getWidth() / 4;
	const int labelWidth = sliderWidth;

	const int labelHeight = 20;
	const int sliderHeight = getHeight() - labelHeight;
	
	juce::Rectangle<int> area(getLocalBounds());
	juce::Rectangle<int> sliders (area.removeFromTop(sliderHeight));
	juce::Rectangle<int> labels(area.removeFromTop(labelHeight));

	attackSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	attackLabel.setBounds(labels.removeFromLeft(labelWidth));

	decaySlider.setBounds(sliders.removeFromLeft(sliderWidth));
	decayLabel.setBounds(labels.removeFromLeft(labelWidth));

	sustainSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	sustainLabel.setBounds(labels.removeFromLeft(labelWidth));

	releaseSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	releaseLabel.setBounds(labels.removeFromLeft(labelWidth));
}
