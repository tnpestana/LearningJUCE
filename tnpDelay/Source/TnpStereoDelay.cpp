/*
  ==============================================================================

    TnpStereoDelay.cpp
    Created: 15 Jun 2018 5:41:31pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpStereoDelay.h"

TnpStereoDelay::TnpStereoDelay(AudioProcessorValueTreeState& treeState)
	: treeState(treeState),
	currentDelayTime(0.0f),
	currentFeedback(0.0f),
	currentMix(0.0f),
	delayLeft(),
	delayRight()
{
	// zero values

	NormalisableRange<float> delayTimeRange(0.f, 2.f, 0.001f);
	treeState.createAndAddParameter("delayTime", "DelayTime", String(), delayTimeRange, 0.5f, nullptr, nullptr);
	NormalisableRange<float> feedbackRange(0.f, 1.f, 0.001f);
	treeState.createAndAddParameter("feedback", "Feedback", String(), feedbackRange, .5f, nullptr, nullptr);
	NormalisableRange<float> wetMixRange(0.f, 1.f, 0.001f);
	treeState.createAndAddParameter("wetMix", "WetMix", String(), wetMixRange, 0.5f, nullptr, nullptr);

	treeState.state = ValueTree(Identifier("DelayState"));
}

TnpStereoDelay::~TnpStereoDelay()
{
}

void TnpStereoDelay::setDelayTime(float delayTime)
{
	delayLeft.setDelayTime(delayTime);
	delayRight.setDelayTime(delayTime);
}

void TnpStereoDelay::updateParams()
{
	if (currentDelayTime != *treeState.getRawParameterValue("delayTime"))
	{
		setDelayTime(*treeState.getRawParameterValue("delayTime"));
	}

	float feedbackparam = *treeState.getRawParameterValue("feedback");
	if (currentFeedback != feedbackparam)
	{
		delayLeft.setFeedback(feedbackparam);
		delayRight.setFeedback(feedbackparam);
	}

	float mixParam = *treeState.getRawParameterValue("wetMix");
	if (currentMix != mixParam)
	{
		delayLeft.setWetMix(mixParam);
		delayRight.setWetMix(mixParam);
	}
}

void TnpStereoDelay::prepareToPlay(double sampleRate)
{
	delayLeft.resetDelay(sampleRate);
	delayRight.resetDelay(sampleRate);

	updateParams();
}

void TnpStereoDelay::processAudio(float* inputBufferL, float* inputBufferR)
{
	delayLeft.processAudio(inputBufferL);
	delayRight.processAudio(inputBufferR);
}
