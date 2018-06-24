/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TnpSampleSynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TnpSampleSynthAudioProcessorEditor (TnpSampleSynthAudioProcessor&, 
		AudioDeviceManager&, MidiKeyboardState&);
    ~TnpSampleSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TnpSampleSynthAudioProcessor& processor;
	AudioDeviceManager& deviceManager;
	MidiKeyboardState& keyboardState;

	MidiKeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TnpSampleSynthAudioProcessorEditor)
};
