/*
  ==============================================================================

    SineOscillator.cpp
    Created: 2 Apr 2018 4:33:11pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "SineOscillator.h"

//==============================================================================
SineOscillator::SineOscillator()
	:	currentAngle(0.0),
		angleDelta(0.0)
{
}

SineOscillator::~SineOscillator()
{
}

void SineOscillator::setFrequency(float frequency, float sampleRate)
{
	float cyclesPerSample = frequency / sampleRate;
	angleDelta = cyclesPerSample * MathConstants<float>::twoPi;
}

float SineOscillator::getNextSample()
{
	float currentSample = std::sin(currentAngle);
	updateAngle();
	return currentSample;
}

void SineOscillator::updateAngle()
{
	currentAngle += angleDelta;
	if (currentAngle >= MathConstants<float>::twoPi)
		currentAngle -= MathConstants<float>::twoPi;
}
