/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TnpSampleSynthAudioProcessorEditor::TnpSampleSynthAudioProcessorEditor (TnpSampleSynthAudioProcessor& p,
	AudioDeviceManager& dm, MidiKeyboardState& ks)
    : AudioProcessorEditor (&p), processor (p), deviceManager(dm), 
	keyboardState(ks), keyboardComponent(ks, MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	addAndMakeVisible(keyboardComponent);
}

TnpSampleSynthAudioProcessorEditor::~TnpSampleSynthAudioProcessorEditor()
{
}

//==============================================================================
void TnpSampleSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void TnpSampleSynthAudioProcessorEditor::resized()
{
	keyboardComponent.setBounds(getLocalBounds());
}
