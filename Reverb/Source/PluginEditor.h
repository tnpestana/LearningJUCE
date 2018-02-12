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
class ReverbAudioProcessorEditor  : public AudioProcessorEditor,
									public SliderListener
{
public:
    ReverbAudioProcessorEditor (ReverbAudioProcessor&);
    ~ReverbAudioProcessorEditor();

    //==============================================================================
	void sliderValueChanged(Slider* slider) override;
	
	void paint (Graphics&) override;
    void resized() override;

private:

	Slider dryWetSlider;
	Label dryWetLabel;

	Slider roomSizeSlider;
	Label roomSizeLabel;

	Slider dampingSlider;
	Label dampingLabel;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ReverbAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbAudioProcessorEditor)
};
