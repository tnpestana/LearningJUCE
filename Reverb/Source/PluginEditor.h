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
class ReverbAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ReverbAudioProcessorEditor (ReverbAudioProcessor&);
    ~ReverbAudioProcessorEditor();
	
	void paint (Graphics&) override;
    void resized() override;

private:

	Slider dryWetSlider;
	Label dryWetLabel;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dryWetAttachment;

	Slider roomSizeSlider;
	Label roomSizeLabel;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;

	Slider dampingSlider;
	Label dampingLabel;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dampingAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ReverbAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbAudioProcessorEditor)
};
