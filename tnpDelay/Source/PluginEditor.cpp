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
	attDelayTimeL(std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "delayTimeL", sliderDelayTimeL)),
	attDelayTimeR(std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "delayTimeR", sliderDelayTimeR)),
	attFeedback(std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "feedback", sliderFeedback)),
	attWetMix(std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "wetMix", sliderWetMix))
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 200);

	setLookAndFeel(&tnpLookAndFeel);

	addAndMakeVisible(sliderDelayTimeL);
	addAndMakeVisible(sliderDelayTimeR);
	addAndMakeVisible(sliderFeedback);
	addAndMakeVisible(sliderWetMix);

	sliderDelayTimeL.setSliderStyle(Slider::RotaryVerticalDrag);
	sliderDelayTimeR.setSliderStyle(Slider::RotaryVerticalDrag);
	sliderFeedback.setSliderStyle(Slider::RotaryVerticalDrag);
	sliderWetMix.setSliderStyle(Slider::RotaryVerticalDrag);

	sliderDelayTimeL.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
	sliderDelayTimeR.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
	sliderFeedback.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
	sliderWetMix.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);

	addAndMakeVisible(lblDelayTimeL);
	addAndMakeVisible(lblDelayTimeR);
	addAndMakeVisible(lblFeedback);
	addAndMakeVisible(lblWetMix);

	lblDelayTimeL.setText("time L", dontSendNotification);
	lblDelayTimeR.setText("time R", dontSendNotification);
	lblFeedback.setText("feedback", dontSendNotification);
	lblWetMix.setText("dry/wet", dontSendNotification);

	sliderDelayTimeL.setTextValueSuffix(" s");
	sliderDelayTimeR.setTextValueSuffix(" s");
	sliderFeedback.setTextValueSuffix(" %");
	sliderWetMix.setTextValueSuffix(" %");

	lblDelayTimeL.setJustificationType(Justification::centred);
	lblDelayTimeR.setJustificationType(Justification::centred);
	lblFeedback.setJustificationType(Justification::centred);
	lblWetMix.setJustificationType(Justification::centred);
}

TnpDelayAudioProcessorEditor::~TnpDelayAudioProcessorEditor()
{
}

//==============================================================================
void TnpDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colours::grey);

	tnpLookAndFeel.setColour(Slider::rotarySliderFillColourId, Colours::whitesmoke);
	tnpLookAndFeel.setColour(Slider::rotarySliderOutlineColourId, Colours::darkslategrey);
	tnpLookAndFeel.setColour(Slider::thumbColourId, Colours::black);

	getLookAndFeel().setColour(Label::textColourId, Colours::black);

	// getLookAndFeel() doesn't seem to work for setting sliders text boxes colours
	// so I set them individually
	sliderDelayTimeL.setColour(Slider::textBoxTextColourId, Colours::black);
	sliderDelayTimeR.setColour(Slider::textBoxTextColourId, Colours::black);
	sliderFeedback.setColour(Slider::textBoxTextColourId, Colours::black);
	sliderWetMix.setColour(Slider::textBoxTextColourId, Colours::black);
}

void TnpDelayAudioProcessorEditor::resized()
{
	juce::Rectangle<int> area(getLocalBounds());

	juce::Rectangle<int> areaDelayTimeL(area.removeFromLeft(area.getWidth() / 4).reduced(5));
	lblDelayTimeL.setBounds(areaDelayTimeL.removeFromBottom(30));
	sliderDelayTimeL.setBounds(areaDelayTimeL);

	juce::Rectangle<int> areaDelayTimeR(area.removeFromLeft(area.getWidth() / 3).reduced(5));
	lblDelayTimeR.setBounds(areaDelayTimeR.removeFromBottom(30));
	sliderDelayTimeR.setBounds(areaDelayTimeR);

	juce::Rectangle<int> areaFeedback(area.removeFromLeft(area.getWidth() / 2).reduced(5));
	lblFeedback.setBounds(areaFeedback.removeFromBottom(30));
	sliderFeedback.setBounds(areaFeedback);

	juce::Rectangle<int> areaWetMix(area.reduced(5));
	lblWetMix.setBounds(areaWetMix.removeFromBottom(30));
	sliderWetMix.setBounds(areaWetMix);
}