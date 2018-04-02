/*
  ==============================================================================

    SineOscillator.h
    Created: 2 Apr 2018 4:33:11pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SineOscillator
{
public:
	SineOscillator();
	~SineOscillator();

	void setFrequency(float, float);
	float getNextSample();

private:
	float currentAngle, angleDelta;
};


