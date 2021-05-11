/*
  ==============================================================================

    TnpDelayLine.cpp
    Created: 12 Jun 2018 7:36:04pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpDelayLine.h"

TnpDelayLine::TnpDelayLine()
: buffer(nullptr),
bufferSize(0),
targetDelayLength(0.0f),
currentDelayLength(0.0f),
delayReadPosition(0),
delayWritePosition(0),
sampleRate(0),
feedback(0.0f),
wetMix(0.0f),
smoothDelayLength(0.0f)
{
}

TnpDelayLine::~TnpDelayLine()
{
	delete[] buffer;
}

void TnpDelayLine::resetDelay(double sampleRate)
{
	if (buffer)
		memset(buffer, 0, bufferSize);

	delayReadPosition = 0.0;
	delayWritePosition = 0.0;

	this->sampleRate = sampleRate;
	//smoothDelayLength.reset(sampleRate, 0.5);
	initBuffer();
}

void TnpDelayLine::initBuffer()
{
	// Set 2 second max delay in samples.
	bufferSize = (int)(2.0 * sampleRate);
	if (bufferSize < 1)
		bufferSize = 1;

	// delete old buffer
	if (buffer)
		delete[] buffer;

	// create new buffer
	buffer = new float[bufferSize];
	// flush new buffer
	memset(buffer, 0, bufferSize);

	setupBuffer();
}

void TnpDelayLine::setFeedback(float feedback)
{
	this->feedback = feedback;
}

void TnpDelayLine::setWetMix(float wetMix)
{
	this->wetMix = wetMix;
}

void TnpDelayLine::setDelayTime(double delayTime_ms)
{
	smoothDelayLength.setTargetValue(delayTime_ms);
	targetDelayLength = delayTime_ms;
}

void TnpDelayLine::setupBuffer()
{
	delayInSamples = currentDelayLength * sampleRate;
	//delayInSamples = smoothDelayLength.getNextValue() * sampleRate;

	delayReadPosition = (int)(delayWritePosition - delayInSamples);

	// Wrap delay read position to the buffers range.
	if (delayReadPosition < 0)
		delayReadPosition += bufferSize;
}

float TnpDelayLine::processAudio(float* inputBuffer)
{
	if (currentDelayLength != targetDelayLength)
	{
		currentDelayLength += (targetDelayLength - currentDelayLength) / bufferSize;
		setupBuffer();
	}

	//if (smoothDelayLength.isSmoothing())
	//	setupBuffer();

	float output = 0.0;
	
	if (buffer != NULL)
	{
		float yn = buffer[delayReadPosition];
		float xn = *inputBuffer;
		//if (smoothDelayLength.getNextValue() == 0)
		//	yn = xn;
		if (currentDelayLength == 0.0f)
			yn = xn;
		buffer[delayWritePosition] = xn + feedback * yn;
		output = (xn * (1 - wetMix)) + (yn * wetMix);
		*inputBuffer = output;
		delayReadPosition++;
		if (delayReadPosition >= bufferSize)
			delayReadPosition = 0;
		delayWritePosition++;
		if (delayWritePosition >= bufferSize)
			delayWritePosition = 0;
	}
	return output;
}
