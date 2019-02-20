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
class TnpDelayAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
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

	juce::Image backgroundImage;

	TnpLookAndFeel tnpLookAndFeel;

	Slider delayTimeSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayTimeAttachment;
	Label delayTimeLabel;

	Slider feedbackSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;
	Label feedbackLabel;

	Slider wetMixSlider;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> wetMixAttachment;
	Label wetMixLabel;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TnpDelayAudioProcessorEditor)

		// Inherited via Listener
		virtual void sliderValueChanged(Slider * slider) override;
};
