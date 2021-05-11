/*
  ==============================================================================

    MaxSynth.h
    Created: 28 Mar 2018 6:35:42pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Maximilian.h"
#include "ADSR.h"

//==============================================================================
class MaxSynthSound : public SynthesiserSound
{
public:
	MaxSynthSound();
	~MaxSynthSound();

	// Inherited via SynthesiserSound
	virtual bool appliesToNote(int midiNoteNumber) override;

	virtual bool appliesToChannel(int midiChannel) override;
};

//==============================================================================
class MaxSynthVoice : public SynthesiserVoice
{
public:
	MaxSynthVoice();
	~MaxSynthVoice();

	// Inherited via SynthesiserVoice
	virtual bool canPlaySound(SynthesiserSound *) override;
	virtual void startNote(int midiNoteNumber, float velocity, SynthesiserSound * sound, int currentPitchWheelPosition) override;
	virtual void stopNote(float velocity, bool allowTailOff) override;
	virtual void pitchWheelMoved(int newPitchWheelValue) override;
	virtual void controllerMoved(int controllerNumber, int newControllerValue) override;
	virtual void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

	//==============================================================================
	double playSinewave();
	double playSquarewave(); 
	void getEnvelopeParameters(float attack, float decay, float sustain, float release);
	void getReverbParameters(float dryWet, float roomSize, float damping);

private:
	double frequency, level;
	maxiOsc sineOsc;
	maxiFilter sineFilter;
	ADSR* sineEnv;
	Reverb reverb;
	Reverb::Parameters reverbParameters;
};
