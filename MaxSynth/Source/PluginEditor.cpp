/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MaxSynthAudioProcessorEditor::MaxSynthAudioProcessorEditor (MaxSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscillator(p)
{
    setSize (200, 200);

	addAndMakeVisible (&oscillator);
}

MaxSynthAudioProcessorEditor::~MaxSynthAudioProcessorEditor()
{
}

//==============================================================================
void MaxSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MaxSynthAudioProcessorEditor::resized()
{
	oscillator.setBounds(getLocalBounds());
}