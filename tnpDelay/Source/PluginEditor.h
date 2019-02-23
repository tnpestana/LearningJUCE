/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "TnpLookAndFeel.h"

//==============================================================================
/**
*/
class TnpDelayAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TnpDelayAudioProcessorEditor (TnpDelayAudioProcessor&);
    ~TnpDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TnpDelayAudioProcessor& processor;
	AudioProcessorValueTreeState& treeState;

	TnpLookAndFeel tnpLookAndFeel;

	Slider sliderDelayTimeL;
	Slider sliderDelayTimeR;
	Slider sliderFeedback;
	Slider sliderWetMix;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attDelayTimeL;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attDelayTimeR;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attWetMix;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attFeedback;

	Label lblDelayTimeL;
	Label lblDelayTimeR;
	Label lblFeedback;
	Label lblWetMix;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TnpDelayAudioProcessorEditor)
};
