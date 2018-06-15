/*
  ==============================================================================

    TnpStereoDelay.cpp
    Created: 15 Jun 2018 5:41:31pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpStereoDelay.h"

TnpStereoDelay::TnpStereoDelay(AudioProcessorValueTreeState& treeState)
	: treeState(treeState)
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
	float timeParam = *treeState.getRawParameterValue("delayTime");
	delayLeft.setDelayTime(timeParam);
	delayRight.setDelayTime(timeParam);

	float feedbackparam = *treeState.getRawParameterValue("feedback");
	delayLeft.setFeedback(feedbackparam);
	delayRight.setFeedback(*treeState.getRawParameterValue("feedback"));

	float wetParam = *treeState.getRawParameterValue("wetMix");
	delayLeft.setWetMix(wetParam);
	delayRight.setWetMix(wetParam);
}

void TnpStereoDelay::prepareToPlay(double sampleRate)
{
	delayLeft.resetDelay();
	delayRight.resetDelay();

	delayLeft.setSampleRate(sampleRate);
	delayRight.setSampleRate(sampleRate);

	updateParams();
}

void TnpStereoDelay::processAudio(float* inputBufferL, float* inputBufferR)
{
	delayLeft.processAudio(inputBufferL);
	delayRight.processAudio(inputBufferR);
}
