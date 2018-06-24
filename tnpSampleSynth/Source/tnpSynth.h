/*
  ==============================================================================

    tnpSynth.h
    Created: 24 Jun 2018 4:31:02pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/** Our demo synth sound is just a basic sine wave.. */
struct TnpSynthSound : public SynthesiserSound
{
	TnpSynthSound();

	bool appliesToNote(int /*midiNoteNumber*/) override;
	bool appliesToChannel(int /*midiChannel*/) override;
};

//==============================================================================
/** Our demo synth voice just plays a sine wave.. */
struct TnpSynthVoice : public SynthesiserVoice
{
	TnpSynthVoice();

	bool canPlaySound(SynthesiserSound* sound) override;

	void startNote(int midiNoteNumber, float velocity,
		SynthesiserSound*, int /*currentPitchWheelPosition*/) override;

	void stopNote(float /*velocity*/, bool allowTailOff) override;

	void pitchWheelMoved(int /*newValue*/) override;
	void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override;

	void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
	double currentAngle, angleDelta, level, tailOff;
};