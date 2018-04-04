/*
  ==============================================================================

    WavetableOscillator.cpp
    Created: 4 Apr 2018 5:57:19pm
    Author:  tnpes

  ==============================================================================
*/

#include "WavetableOscillator.h"

WavetableOscillator::WavetableOscillator(const AudioSampleBuffer& wavetablePassed)
	:	wavetable (wavetablePassed),
		currentIndex(0.0f),
		tableDelta(0.0f)
{
}

WavetableOscillator::~WavetableOscillator()
{
}

void WavetableOscillator::setFrequency(float frequency, float sampleRate)
{
	auto tableSizeOverSampleRate = wavetable.getNumSamples() / sampleRate;
	tableDelta = frequency * tableSizeOverSampleRate;
}

float WavetableOscillator::getNextSample()
{
	float tableSize = wavetable.getNumSamples();

	int index0 = (int)currentIndex;
	int index1 = index0 == (tableSize - 1) ? 0 : index0 + 1;

	float fraction = currentIndex - (float)index0;

	const float* table = wavetable.getReadPointer(0);
	float value0 = table[index0];
	float value1 = table[index1];

	float currentSample = value0 + fraction * (value1 - value0);

	if ((currentIndex += tableDelta) > tableSize)
		currentIndex -= tableSize;

	return currentSample;
}
