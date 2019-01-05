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
class TnpEqAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TnpEqAudioProcessorEditor (TnpEqAudioProcessor&);
    ~TnpEqAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TnpEqAudioProcessor& processor;
	AudioProcessorValueTreeState& treeState;

	Slider loBand;
	Slider midBand;
	Slider hiBand;
	Slider loCutoff;
	Slider hiCutoff;

	Label labelLoBand;
	Label labelMidBand;
	Label labelHiBand;
	Label labelLoCutoff;
	Label labelHiCutoff;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attLoBand;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attMidBand;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attHiBand;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attLoCutoff;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attHiCutoff;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TnpEqAudioProcessorEditor)
};
