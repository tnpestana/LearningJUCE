/*
  ==============================================================================

    TnpStereoDelay.cpp
    Created: 15 Jun 2018 5:41:31pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpStereoDelay.h"

TnpStereoDelay::TnpStereoDelay()
	: currentDelayTime(0.0f),
	currentFeedback(0.0f),
	currentMix(0.0f),
	delayLeft(),
	delayRight()
{
}

TnpStereoDelay::~TnpStereoDelay()
{
}

void TnpStereoDelay::updateParams(float delayTimeL, float delayTimeR, float feedback, float wet)
{
	delayLeft.setDelayTime(delayTimeL);
	delayRight.setDelayTime(delayTimeR);

	delayLeft.setFeedback(feedback);
	delayRight.setFeedback(feedback);

	delayLeft.setWetMix(wet);
	delayRight.setWetMix(wet);
}

void TnpStereoDelay::prepareToPlay(double sampleRate)
{
	delayLeft.resetDelay(sampleRate);
	delayRight.resetDelay(sampleRate);
}

void TnpStereoDelay::processAudio(float* inputBufferL, float* inputBufferR)
{
	delayLeft.processAudio(inputBufferL);
	delayRight.processAudio(inputBufferR);
}
