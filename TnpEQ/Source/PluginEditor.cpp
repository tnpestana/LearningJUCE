/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TnpEqAudioProcessorEditor::TnpEqAudioProcessorEditor (TnpEqAudioProcessor& p)
    : AudioProcessorEditor (&p),
	//	Processor references
	processor (p), 
	treeState (p.getTreeState()),
	//	Parameter Attachments
	attLoBand (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "loGain", loBand)),
	attMidBand (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "midGain", midBand)),
	attHiBand (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "hiGain", hiBand)),
	attLoCutoff (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "loCutoff", loCutoff)),
	attHiCutoff (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "hiCutoff", hiCutoff))
{
    setSize (350, 250 + 40 /*title section size*/);

	backgroundImage = ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);

	loBand.setSliderStyle(Slider::RotaryVerticalDrag);
	midBand.setSliderStyle(Slider::RotaryVerticalDrag);
	hiBand.setSliderStyle(Slider::RotaryVerticalDrag);
	loCutoff.setSliderStyle(Slider::RotaryVerticalDrag);
	hiCutoff.setSliderStyle(Slider::RotaryVerticalDrag);

	loBand.setSkewFactorFromMidPoint(1.0);
	midBand.setSkewFactorFromMidPoint(1.0);
	hiBand.setSkewFactorFromMidPoint(1.0);
	loCutoff.setSkewFactorFromMidPoint(1000.0);
	hiCutoff.setSkewFactorFromMidPoint(1000.0);

	loBand.setTextBoxStyle(Slider::TextBoxAbove, true, 50, 15);
	midBand.setTextBoxStyle(Slider::TextBoxAbove, true, 50, 15);
	hiBand.setTextBoxStyle(Slider::TextBoxAbove, true, 50, 15);
	loCutoff.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 15);
	hiCutoff.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 15);

	labelLoBand.setText("low", dontSendNotification);
	labelMidBand.setText("mid", dontSendNotification);
	labelHiBand.setText("high", dontSendNotification);
	labelLoCutoff.setText("low cutoff", dontSendNotification);
	labelHiCutoff.setText("high cutoff", dontSendNotification);

	labelLoBand.setJustificationType(Justification::centred);
	labelMidBand.setJustificationType(Justification::centred);
	labelHiBand.setJustificationType(Justification::centred);
	labelLoCutoff.setJustificationType(Justification::centred);
	labelHiCutoff.setJustificationType(Justification::centred);

	addAndMakeVisible(loBand);
	addAndMakeVisible(midBand);
	addAndMakeVisible(hiBand);
	addAndMakeVisible(loCutoff);
	addAndMakeVisible(hiCutoff);
	addAndMakeVisible(labelLoBand);
	addAndMakeVisible(labelMidBand);
	addAndMakeVisible(labelHiBand);
	addAndMakeVisible(labelLoCutoff);
	addAndMakeVisible(labelHiCutoff);

	loBand.setLookAndFeel(&tnpLookAndFeel);
	midBand.setLookAndFeel(&tnpLookAndFeel);
	hiBand.setLookAndFeel(&tnpLookAndFeel);
	loCutoff.setLookAndFeel(&tnpLookAndFeel);
	hiCutoff.setLookAndFeel(&tnpLookAndFeel);
}

TnpEqAudioProcessorEditor::~TnpEqAudioProcessorEditor()
{
}

//==============================================================================
void TnpEqAudioProcessorEditor::paint (Graphics& g)
{
    // Our component is opaque, so we must completely fill the background with a solid colour
    g.fillAll (Colours::rosybrown);
	g.drawImageAt(backgroundImage, 0, 0);

	getLookAndFeel().setColour(Label::textColourId, Colours::black);
	getLookAndFeel().setColour(Slider::textBoxBackgroundColourId, Colours::rosybrown);	// doesnt work?

	tnpLookAndFeel.setColour(Slider::textBoxBackgroundColourId, Colours::rosybrown);

	/*
	tnpLookAndFeel.setColour(Slider::textBoxOutlineColourId, Colours::black);
	tnpLookAndFeel.setColour(Slider::textBoxTextColourId, Colours::black);
	*/

	loBand.setColour(Slider::textBoxTextColourId, Colours::black);
	midBand.setColour(Slider::textBoxTextColourId, Colours::black);
	hiBand.setColour(Slider::textBoxTextColourId, Colours::black);
	loCutoff.setColour(Slider::textBoxTextColourId, Colours::black);
	hiCutoff.setColour(Slider::textBoxTextColourId, Colours::black);

	loBand.setColour(Slider::textBoxOutlineColourId, Colours::black);
	midBand.setColour(Slider::textBoxOutlineColourId, Colours::black);
	hiBand.setColour(Slider::textBoxOutlineColourId, Colours::black);
	loCutoff.setColour(Slider::textBoxOutlineColourId, Colours::black);
	hiCutoff.setColour(Slider::textBoxOutlineColourId, Colours::black);
	
	
}

void TnpEqAudioProcessorEditor::resized()
{
	Rectangle<int> area(getLocalBounds());
	Rectangle<int> titleSection(area.removeFromTop(40));
	Rectangle<int> top(area.removeFromTop(area.getHeight() / 2));

	Rectangle<int> loBandArea(top.removeFromLeft(top.getWidth() / 3).reduced(5));
	labelLoBand.setBounds(loBandArea.removeFromTop(20));
	loBand.setBounds(loBandArea);

	Rectangle<int> midBandArea(top.removeFromLeft(top.getWidth() / 2).reduced(5));
	labelMidBand.setBounds(midBandArea.removeFromTop(20));
	midBand.setBounds(midBandArea);

	Rectangle<int> hiBandArea(top.reduced(5));
	labelHiBand.setBounds(hiBandArea.removeFromTop(20));
	hiBand.setBounds(hiBandArea);

	Rectangle<int> loCutoffArea(area.removeFromLeft(area.getWidth() / 2).reduced(5));
	labelLoCutoff.setBounds(loCutoffArea.removeFromBottom(20));
	loCutoff.setBounds(loCutoffArea);

	Rectangle<int> hiCutoffArea(area.reduced(5));
	labelHiCutoff.setBounds(hiCutoffArea.removeFromBottom(20));
	hiCutoff.setBounds(hiCutoffArea);
}
