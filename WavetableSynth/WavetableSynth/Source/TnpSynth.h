/*
  ==============================================================================

    TnpSynth.h
    Created: 4 Oct 2018 2:02:50pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "WavetableOscillator.h"

class TnpSynthSound : public SynthesiserSound
{
public:
	TnpSynthSound();
	~TnpSynthSound();

	// Inherited via SynthesiserSound
	virtual bool appliesToNote(int midiNoteNumber) override;
	virtual bool appliesToChannel(int midiChannel) override;
};

class TnpSynthVoice : public SynthesiserVoice
{
public:
	TnpSynthVoice();
	~TnpSynthVoice();

	// Inherited via SynthesiserVoice
	virtual bool canPlaySound(SynthesiserSound *) override;
	virtual void startNote(int midiNoteNumber, float velocity, SynthesiserSound * sound, int currentPitchWheelPosition) override;
	virtual void stopNote(float velocity, bool allowTailOff) override;
	virtual void pitchWheelMoved(int newPitchWheelValue) override;
	virtual void controllerMoved(int controllerNumber, int newControllerValue) override;
	virtual void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
	WavetableOscillator oscillator;
};