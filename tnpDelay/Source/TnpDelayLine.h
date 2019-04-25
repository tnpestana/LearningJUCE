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
	void resetDelay(double sampleRate);
	void initBuffer();

	void setFeedback(float feedback);
	void setWetMix(float wetMix);

	void setDelayTime(double delayTime_ms);
	void setupBuffer();
	
	float processAudio(float* inputBufferL);

private:

	float* buffer;
	int bufferSize;
	int delayReadPosition, delayWritePosition;
	int sampleRate;
	float targetDelayLength, currentDelayLength, delayInSamples;
	LinearSmoothedValue<float> smoothDelayLength;
	double feedback, wetMix;
};
