/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbAudioProcessorEditor::ReverbAudioProcessorEditor (ReverbAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueStateTree (vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize (300, 150);

	addAndMakeVisible(dryWetSlider);
	dryWetSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	dryWetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 35, 20);
	dryWetSlider.setRange(0, 1, 0.01);

	addAndMakeVisible(dryWetLabel);
	dryWetLabel.setText("Dry/Wet", dontSendNotification);
	dryWetLabel.setJustificationType(Justification::centred);
	dryWetAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueStateTree,
		"dryWet", dryWetSlider);

	addAndMakeVisible(roomSizeSlider);
	roomSizeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	roomSizeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 35, 20);
	roomSizeSlider.setRange(0, 1, 0.01);

	addAndMakeVisible(roomSizeLabel);
	roomSizeLabel.setText("Room Size", dontSendNotification);
	roomSizeLabel.setJustificationType(Justification::centred);
	roomSizeAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueStateTree,
		"roomSize", roomSizeSlider);

	addAndMakeVisible(dampingSlider);
	dampingSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	dampingSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 35, 20);
	dampingSlider.setRange(0, 1, 0.01);

	addAndMakeVisible(dampingLabel);
	dampingLabel.setText("Damping", dontSendNotification);
	dampingLabel.setJustificationType(Justification::centred);
	dampingAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueStateTree,
		"damping", dampingSlider);
}

ReverbAudioProcessorEditor::~ReverbAudioProcessorEditor()
{
}


void ReverbAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colours::black);
}

void ReverbAudioProcessorEditor::resized()
{
	const int labelWidth = getWidth() / 3;
	const int labelHeight = 25;
	const int sliderWidth = getWidth() / 3;
	const int sliderHeight = getHeight() - labelHeight;

	Rectangle<int> area(getLocalBounds());

	dryWetSlider.setBounds(0, 0, sliderWidth, sliderHeight);
	dryWetLabel.setBounds(0, sliderHeight, labelWidth, labelHeight);

	roomSizeLabel.setBounds(sliderWidth, sliderHeight, labelWidth, labelHeight);
	roomSizeSlider.setBounds(sliderWidth, 0, sliderWidth, sliderHeight);

	dampingLabel.setBounds(sliderWidth * 2, sliderHeight, labelWidth, labelHeight);
	dampingSlider.setBounds(sliderWidth * 2, 0, sliderWidth, sliderHeight);
}
