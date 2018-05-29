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
    setSize (400, 300);

	addAndMakeVisible(delayTimeSlider);
	delayTimeAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState, "delayTime", delayTimeSlider);
}

TnpDelayAudioProcessorEditor::~TnpDelayAudioProcessorEditor()
{
}

//==============================================================================
void TnpDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

}

void TnpDelayAudioProcessorEditor::resized()
{
	delayTimeSlider.setBounds(getLocalBounds());
}