/*
  ==============================================================================

    TnpStereoDelay.h
    Created: 15 Jun 2018 5:41:30pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TnpDelayLine.h"

class TnpStereoDelay
{
public:
	TnpStereoDelay();
	~TnpStereoDelay();

	void updateParams(float delayTime, float feedback, float wet);

	void prepareToPlay(double sampleRate);
	void processAudio(float* inputBufferL, float* inputBufferR);

private:
	TnpDelayLine delayLeft, delayRight;
	float currentDelayTime, currentFeedback, currentMix;
	
};