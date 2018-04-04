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
	WavetableOscillator();
	~WavetableOscillator();

	void setFrequency(float, float);
	float getNextSample();

	static AudioSampleBuffer* wavetable;
	static void createWavetable();
	static int tableSize;

private:
	float currentIndex, tableDelta;
};