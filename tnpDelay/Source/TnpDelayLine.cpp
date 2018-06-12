/*
  ==============================================================================

    TnpDelayLine.cpp
    Created: 12 Jun 2018 7:36:04pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpDelayLine.h"

TnpDelayLine::TnpDelayLine()
{
	// Default values:
	buffer = nullptr;
	delayLength = 0.5;		// in seconds
	wetMix = 0.5;			// ratio
	feedback = 0.5;			// percentage
	bufferSize = 1;			// in samples
	delayReadPosition = 0;
	delayWritePosition = 0;
	sampleRate = 0;
}

TnpDelayLine::~TnpDelayLine()
{
	delete[] buffer;
}

void TnpDelayLine::setupDelay(float time, float feedback, float wet)
{
	// Delay processing.
	delayLength = time;
	feedback = feedback;
	wetMix = wet;

	delayInSamples = delayLength * sampleRate;

	delayReadPosition = (int)(delayWritePosition - delayInSamples);

	// Wrap delay read position to the buffers range.
	if (delayReadPosition < 0)
		delayReadPosition += bufferSize;
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
