/*
  ==============================================================================

    TnpDelayLine.cpp
    Created: 12 Jun 2018 7:36:04pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpDelayLine.h"

TnpDelayLine::TnpDelayLine(AudioProcessorValueTreeState& treeState)
	:	treeState(treeState)
{
	// zero everything
	buffer = nullptr;
	delayLength = 0.0;		// in seconds
	wetMix = 0.0;			// ratio
	feedback = 0.0;			// percentage
	bufferSize = 1;			// in samples
	delayReadPosition = 0;
	delayWritePosition = 0;
	sampleRate = 0;

	NormalisableRange<float> delayTimeRange(0.f, 2.f, 0.001f);
	treeState.createAndAddParameter("delayTime", "DelayTime", String(), delayTimeRange, 0.f, nullptr, nullptr);
	NormalisableRange<float> feedbackRange(0.f, 1.f, 0.001f);
	treeState.createAndAddParameter("feedback", "Feedback", String(), feedbackRange, .5f, nullptr, nullptr);
	NormalisableRange<float> wetMixRange(0.f, 1.f, 0.001f);
	treeState.createAndAddParameter("wetMix", "WetMix", String(), wetMixRange, 0.5f, nullptr, nullptr);

	treeState.state = ValueTree(Identifier("DelayState"));
}

TnpDelayLine::~TnpDelayLine()
{
	delete[] buffer;
}

void TnpDelayLine::setupDelay()
{
	if (delayLength != *treeState.getRawParameterValue("delayTime"))
	{
		delayLength = *treeState.getRawParameterValue("delayTime");
		delayInSamples = delayLength * sampleRate;

		delayReadPosition = (int)(delayWritePosition - delayInSamples);

		// Wrap delay read position to the buffers range.
		if (delayReadPosition < 0)
			delayReadPosition += bufferSize;
	}

	if (feedback = *treeState.getRawParameterValue("feedback"))
		feedback = *treeState.getRawParameterValue("feedback");
	if (wetMix = *treeState.getRawParameterValue("wetMix"))
		wetMix = *treeState.getRawParameterValue("wetMix");
}

void TnpDelayLine::prepareToPlay(double sampleRate)
{
	this->sampleRate = sampleRate;

	// Set 2 second max delay in samples.
	bufferSize = (int)(2.0 * sampleRate);
	if (bufferSize < 1)
		bufferSize = 1;

	buffer = new float[bufferSize];
	memset(buffer, 0, bufferSize);

	setupDelay();
}

float TnpDelayLine::processAudio(int inputBufferSize, float* inputBuffer)
{
	float yn = buffer[delayReadPosition];

	float xn = *inputBuffer;

	if (delayLength == 0)
		yn = xn;

	buffer[delayWritePosition] = xn + feedback * yn;

	float output = (xn * (1 - wetMix)) + (yn * wetMix);

	*inputBuffer = output;

	delayReadPosition++;
	if (delayReadPosition >= bufferSize)
		delayReadPosition = 0;
	delayWritePosition++;
	if (delayWritePosition >= bufferSize)
		delayWritePosition = 0;

	return output;
}
