/*
  ==============================================================================

    TnpLookAndFeel.h
    Created: 20 Feb 2019 9:48:12pm
    Author:  tnpes

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