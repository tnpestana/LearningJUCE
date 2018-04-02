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
class MaxSynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    MaxSynthAudioProcessorEditor (MaxSynthAudioProcessor&);
    ~MaxSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void writeLabel(String);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MaxSynthAudioProcessor& processor;
	Label label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MaxSynthAudioProcessorEditor)
};
