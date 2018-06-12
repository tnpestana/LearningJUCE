/*
  ==============================================================================

    TnpDelayLine.h
    Created: 12 Jun 2018 7:36:03pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TnpDelayLine
{
public:
	TnpDelayLine();
	~TnpDelayLine();

	//==============================================================================
	void setupDelay(float time, float feedback, float wet);

	//==============================================================================
	void prepareToPlay(double);
	bool processAudio(AudioBuffer<float>&);

private:
	float* buffer;
	int bufferSize;
	int delayReadPosition, delayWritePosition;
	int sampleRate;
	float delayLength, delayInSamples;
	float wetMix;
	float feedback;

};
