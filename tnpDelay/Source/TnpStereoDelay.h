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
	TnpStereoDelay(AudioProcessorValueTreeState&);
	~TnpStereoDelay();

	void setDelayTime(float delayTime);


	void prepareToPlay(double sampleRate);
	void processAudio(float* inputBufferL, float* inputBufferR);

private:
	AudioProcessorValueTreeState& treeState;
	TnpDelayLine delayLeft, delayRight;
	
};