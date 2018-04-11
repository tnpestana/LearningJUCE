/*
  ==============================================================================

    OscillatorEditor.h
    Created: 11 Apr 2018 4:14:44pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class OscillatorEditor : public Component
{
public:
	OscillatorEditor();
	~OscillatorEditor();

	void paint(Graphics&) override;
	void resized() override;

private:
	Slider attackSlider, decaySlider, sustainSlider, releaseSlider;
	Label attackLabel, decayLabel, sustainLabel, releaseLabel;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorEditor)
};