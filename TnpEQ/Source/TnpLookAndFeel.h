/*
  ==============================================================================

    TnpLookAndFeel.h
    Created: 27 Jan 2019 11:01:13pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TnpLookAndFeel : public LookAndFeel_V4 
{
public:
	void drawRotarySlider(Graphics &g, 
		int x, int y, 
		int width, int height, 
		float sliderPos,								// slider current value
		float rotaryStartAngle, float rotaryEndAngle,	// full motion angle
		Slider &slider) override;
};

