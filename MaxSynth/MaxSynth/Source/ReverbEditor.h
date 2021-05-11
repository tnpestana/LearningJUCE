/*
  ==============================================================================

    ReverbEditor.h
    Created: 14 Apr 2018 12:35:38am
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class ReverbEditor : public Component
{
public:
	ReverbEditor(MaxSynthAudioProcessor&);
	~ReverbEditor();

private:
	void paint(Graphics&) override;
	void resized() override;
	
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
	MaxSynthAudioProcessor& processor;
};
