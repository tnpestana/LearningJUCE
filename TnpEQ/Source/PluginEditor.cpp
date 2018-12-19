/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TnpEqAudioProcessorEditor::TnpEqAudioProcessorEditor (TnpEqAudioProcessor& p, AudioProcessorValueTreeState& apvts)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	attLoBand = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(apvts, "loGain", loBand);
	attMidBand = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(apvts, "midGain", midBand);
	attHiBand = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(apvts, "hiGain", hiBand);
	attLoCutoff = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(apvts, "loCutoff", loCutoff);
	attHiCutoff = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(apvts, "hiCutoff", hiCutoff);

	loBand.setSliderStyle(Slider::RotaryVerticalDrag);
	midBand.setSliderStyle(Slider::RotaryVerticalDrag);
	hiBand.setSliderStyle(Slider::RotaryVerticalDrag);
	loCutoff.setSliderStyle(Slider::RotaryVerticalDrag);
	hiCutoff.setSliderStyle(Slider::RotaryVerticalDrag);

	loBand.setTextBoxStyle(Slider::TextBoxAbove, true, 45, 15);
	midBand.setTextBoxStyle(Slider::TextBoxAbove, true, 45, 15);
	hiBand.setTextBoxStyle(Slider::TextBoxAbove, true, 45, 15);
	loCutoff.setTextBoxStyle(Slider::TextBoxBelow, true, 45, 15);
	hiCutoff.setTextBoxStyle(Slider::TextBoxBelow, true, 45, 15);

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
}

TnpEqAudioProcessorEditor::~TnpEqAudioProcessorEditor()
{
}

//==============================================================================
void TnpEqAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

	Rectangle<int> area (getLocalBounds());
	Rectangle<int> top (area.removeFromTop(area.getHeight() / 2));

	Rectangle<int> loBandArea (top.removeFromLeft(top.getWidth() / 3));
	labelLoBand.setBounds (loBandArea.removeFromTop(20));
	loBand.setBounds (loBandArea);

	Rectangle<int> midBandArea (top.removeFromLeft(top.getWidth() / 2));
	labelMidBand.setBounds (midBandArea.removeFromTop(20));
	midBand.setBounds (midBandArea);

	Rectangle<int> hiBandArea (top);
	labelHiBand.setBounds (hiBandArea.removeFromTop(20));
	hiBand.setBounds (hiBandArea);

	Rectangle<int> loCutoffArea (area.removeFromLeft(area.getWidth() / 2));
	labelLoCutoff.setBounds(loCutoffArea.removeFromBottom(20));
	loCutoff.setBounds (loCutoffArea);


	Rectangle<int> hiCutoffArea(area);
	labelHiCutoff.setBounds(hiCutoffArea.removeFromBottom(20));
	hiCutoff.setBounds(hiCutoffArea);
}

void TnpEqAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
