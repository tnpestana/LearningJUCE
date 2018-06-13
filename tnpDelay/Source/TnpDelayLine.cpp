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
	treeState.createAndAddParameter("delayTime", "DelayTime", String(), delayTimeRange, 0.5f, nullptr, nullptr);
	NormalisableRange<float> feedbackRange(0.f, 1.f, 0.001f);
	treeState.createAndAddParameter("feedback", "Feedback", String(), feedbackRange, 1.f, nullptr, nullptr);
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
	double targetDelayLength = *treeState.getRawParameterValue("delayTime");
	if (delayLength != targetDelayLength)
	{
		delayLength = targetDelayLength;
		delayInSamples = delayLength * sampleRate;

		delayReadPosition = (int)(delayWritePosition - delayInSamples);

		// Wrap delay read position to the buffers range.
		if (delayReadPosition < 0)
			delayReadPosition += bufferSize;
	}

	double targetFeedback = *treeState.getRawParameterValue("feedback");
	if (feedback != targetFeedback)
		feedback = targetFeedback;

	double targetWetMix = *treeState.getRawParameterValue("wetMix");
	if (wetMix != targetWetMix)
		wetMix = targetWetMix;
}

void TnpDelayLine::prepareToPlay(double sampleRate)
{
	this->sampleRate = sampleRate;

	// Set 2 second max delay in samples.
	bufferSize = (int)(2.0 * sampleRate);
	if (bufferSize < 1)
		bufferSize = 1;

	buffer = new float[bufferSize];
	if (buffer != nullptr)
		memset(buffer, 0, bufferSize);
}

bool TnpDelayLine::processAudio(AudioBuffer<float>& inputBuffer)
{
	setupDelay();

	int drp, dwp;

	for (int channel = 0; channel < inputBuffer.getNumChannels(); ++channel)
	{
		float* channelData = inputBuffer.getWritePointer(channel);

		// Temporarily store the pointer values.
		drp = delayReadPosition;
		dwp = delayWritePosition;

		for (int sample = 0; sample < inputBuffer.getNumSamples(); sample++)
		{


			// Will Pirkle:
			// Step 1 - Read delayed audio data.
			float yn = buffer[drp];

			// Step 2 - Calculate mixed output.
			if (delayLength != 0.0f)
				channelData[sample] = (1 - wetMix) * channelData[sample] + wetMix * (channelData[sample] + (feedback * yn));

			// Step 3 - Write input data into delay line at write location.
			buffer[drp] = channelData[sample];

			if (++drp >= delayInSamples)
				drp = 0;
			if (++dwp >= delayInSamples)
				dwp = 0;
		}
	}

	delayReadPosition = drp;
	delayWritePosition = dwp;

	return true;
}
