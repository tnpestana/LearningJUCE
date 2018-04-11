/*
  ==============================================================================

    OscillatorEditor.cpp
    Created: 11 Apr 2018 4:14:44pm
    Author:  tnpes

  ==============================================================================
*/

#include "OscillatorEditor.h"

OscillatorEditor::OscillatorEditor()
{
	// attack slider
	addAndMakeVisible(attackSlider);
	attackSlider.setSliderStyle(Slider::LinearVertical);
	attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20, 15);
	// attack label
	addAndMakeVisible(attackLabel);
	attackLabel.setText("attack", dontSendNotification);

	// decay slider
	addAndMakeVisible(decaySlider);
	decaySlider.setSliderStyle(Slider::LinearVertical);
	decaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20, 15);
	// decay label
	addAndMakeVisible(decayLabel);
	decayLabel.setText("decay", dontSendNotification);

	// sustain slider
	addAndMakeVisible(sustainSlider);
	sustainSlider.setSliderStyle(Slider::LinearVertical);
	sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20, 15);
	// sustain label
	addAndMakeVisible(sustainLabel);
	sustainLabel.setText("sustain", dontSendNotification);

	// release slider
	addAndMakeVisible(releaseSlider);
	releaseSlider.setSliderStyle(Slider::LinearVertical);
	releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20, 15);
	// release label
	addAndMakeVisible(releaseLabel);
	releaseLabel.setText("release", dontSendNotification);
}

OscillatorEditor::~OscillatorEditor()
{
}

void OscillatorEditor::paint(Graphics &)
{
}

void OscillatorEditor::resized()
{
	const int sliderWidth = getWidth() / 4;
	const int labelWidth = sliderWidth;

	const int labelHeight = 20;
	const int sliderHeight = getHeight() - labelHeight;
	
	Rectangle<int> area(getLocalBounds());
	Rectangle<int> sliders (area.removeFromTop(sliderHeight));
	Rectangle<int> labels(area.removeFromTop(labelHeight));

	attackSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	attackLabel.setBounds(labels.removeFromLeft(labelWidth));

	decaySlider.setBounds(sliders.removeFromLeft(sliderWidth));
	decayLabel.setBounds(labels.removeFromLeft(labelWidth));

	sustainSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	sustainLabel.setBounds(labels.removeFromLeft(labelWidth));

	releaseSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	releaseLabel.setBounds(labels.removeFromLeft(labelWidth));
}
