/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TnpDelayAudioProcessorEditor::TnpDelayAudioProcessorEditor (TnpDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 200);

	//backgroundImage = ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);

	addAndMakeVisible(delayTimeSlider);
	addAndMakeVisible(feedbackSlider);
	addAndMakeVisible(wetMixSlider);

	delayTimeSlider.setLookAndFeel(&tnpLookAndFeel);
	feedbackSlider.setLookAndFeel(&tnpLookAndFeel);
	wetMixSlider.setLookAndFeel(&tnpLookAndFeel);

	delayTimeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	feedbackSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	wetMixSlider.setSliderStyle(Slider::RotaryVerticalDrag);

	delayTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
	feedbackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
	wetMixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);

	delayTimeAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState, "delayTime", delayTimeSlider);
	feedbackAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState, "feedback", feedbackSlider);
	wetMixAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState, "wetMix", wetMixSlider);

	addAndMakeVisible(delayTimeLabel);
	addAndMakeVisible(feedbackLabel);
	addAndMakeVisible(wetMixLabel);

	delayTimeLabel.setText("time", dontSendNotification);
	feedbackLabel.setText("feedback", dontSendNotification);
	wetMixLabel.setText("dry/wet", dontSendNotification);

	delayTimeLabel.setJustificationType(Justification::centred);
	feedbackLabel.setJustificationType(Justification::centred);
	wetMixLabel.setJustificationType(Justification::centred);
}

TnpDelayAudioProcessorEditor::~TnpDelayAudioProcessorEditor()
{
}

//==============================================================================
void TnpDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colours::grey);
	//g.drawImageAt(backgroundImage, 0, 0);

	tnpLookAndFeel.setColour(Slider::backgroundColourId, Colours::whitesmoke);
	tnpLookAndFeel.setColour(Slider::rotarySliderOutlineColourId, Colours::darkslategrey);
	tnpLookAndFeel.setColour(Slider::thumbColourId, Colours::black);

	getLookAndFeel().setColour(Label::textColourId, Colours::black);

	// getLookAndFeel() doesn't seem to work for setting sliders text boxes colours
	// so I set them individually
	delayTimeSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	feedbackSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	wetMixSlider.setColour(Slider::textBoxTextColourId, Colours::black);
}

void TnpDelayAudioProcessorEditor::resized()
{
	juce::Rectangle<int> area(getLocalBounds());

	juce::Rectangle<int> delayTimeArea(area.removeFromLeft(area.getWidth() / 3));
	delayTimeLabel.setBounds(delayTimeArea.removeFromBottom(30));
	delayTimeSlider.setBounds(delayTimeArea);

	juce::Rectangle<int> feedbackArea(area.removeFromLeft(area.getWidth() / 2));
	feedbackLabel.setBounds(feedbackArea.removeFromBottom(30));
	feedbackSlider.setBounds(feedbackArea);

	juce::Rectangle<int> wetMixArea(area);
	wetMixLabel.setBounds(wetMixArea.removeFromBottom(30));
	wetMixSlider.setBounds(wetMixArea);	
}