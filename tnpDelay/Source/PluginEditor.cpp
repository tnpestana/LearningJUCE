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

	backgroundImage = ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);

	addAndMakeVisible(delayTimeSlider);
	delayTimeAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState, "delayTime", delayTimeSlider);
	addAndMakeVisible(delayTimeLabel);
	delayTimeLabel.setText("time", dontSendNotification);
	delayTimeLabel.setJustificationType(Justification::centred);

	addAndMakeVisible(feedbackSlider);
	feedbackAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState, "feedback", feedbackSlider);
	addAndMakeVisible(feedbackLabel);
	feedbackLabel.setText("feedback", dontSendNotification);
	feedbackLabel.setJustificationType(Justification::centred);

	addAndMakeVisible(wetMixSlider);
	wetMixAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState, "wetMix", wetMixSlider);
	addAndMakeVisible(wetMixLabel);
	wetMixLabel.setText("dry/wet", dontSendNotification);
	wetMixLabel.setJustificationType(Justification::centred);
}

TnpDelayAudioProcessorEditor::~TnpDelayAudioProcessorEditor()
{
}

//==============================================================================
void TnpDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	g.drawImageAt(backgroundImage, 0, 0);
	getLookAndFeel().setColour(Label::textColourId, Colours::black);
	getLookAndFeel().setColour(Slider::backgroundColourId, Colours::whitesmoke);
	getLookAndFeel().setColour(Slider::trackColourId, Colours::darkslategrey);
	getLookAndFeel().setColour(Slider::thumbColourId, Colours::black);

	// getLookAndFeel() doesn't seem to work for setting sliders text boxes colours
	// so I set them individually
	delayTimeSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	feedbackSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	wetMixSlider.setColour(Slider::textBoxTextColourId, Colours::black);
}

void TnpDelayAudioProcessorEditor::resized()
{
	juce::Rectangle<int> area(getLocalBounds());

	juce::Rectangle<int> wetMixArea(area.removeFromTop(getHeight() / 3));
	wetMixLabel.setBounds(wetMixArea.removeFromLeft(100));
	wetMixSlider.setBounds(wetMixArea);

	juce::Rectangle<int> delayTimeArea(area.removeFromTop(area.getHeight() / 2));
	delayTimeLabel.setBounds(delayTimeArea.removeFromLeft(100));
	delayTimeSlider.setBounds(delayTimeArea);

	juce::Rectangle<int> feedbackArea(area);
	feedbackLabel.setBounds(feedbackArea.removeFromLeft(100));
	feedbackSlider.setBounds(feedbackArea);
}

void TnpDelayAudioProcessorEditor::sliderValueChanged(Slider * slider)
{
	processor.delay.setDelayTime(delayTimeSlider.getValue());
}
