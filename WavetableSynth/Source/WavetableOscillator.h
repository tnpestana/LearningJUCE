/*
  ==============================================================================

    WavetableOscillator.h
    Created: 4 Apr 2018 5:57:19pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class WavetableOscillator
{
public:
	WavetableOscillator(const AudioSampleBuffer&);
	~WavetableOscillator();

	void setFrequency(float, float);
	float getNextSample();

private:
	const AudioSampleBuffer& wavetable;
	float currentIndex, tableDelta;
};