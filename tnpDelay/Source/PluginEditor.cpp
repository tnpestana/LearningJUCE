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
    : AudioProcessorEditor (&p), 
	processor (p),
	treeState(p.getTreeState()),
	delayTimeAttachment(std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "delayTime", delayTimeSlider)),
	feedbackAttachment(std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "feedback", feedbackSlider)),
	wetMixAttachment(std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "wetMix", wetMixSlider))
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 200);

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

	juce::Rectangle<int> delayTimeArea(area.removeFromLeft(area.getWidth() / 3).reduced(5));
	delayTimeLabel.setBounds(delayTimeArea.removeFromBottom(30));
	delayTimeSlider.setBounds(delayTimeArea);

	juce::Rectangle<int> feedbackArea(area.removeFromLeft(area.getWidth() / 2).reduced(5));
	feedbackLabel.setBounds(feedbackArea.removeFromBottom(30));
	feedbackSlider.setBounds(feedbackArea);

	juce::Rectangle<int> wetMixArea(area.reduced(5));
	wetMixLabel.setBounds(wetMixArea.removeFromBottom(30));
	wetMixSlider.setBounds(wetMixArea);	
}