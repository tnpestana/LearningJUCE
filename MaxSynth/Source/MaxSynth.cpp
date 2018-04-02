/*
==============================================================================

MaxSynth.cpp
Created: 28 Mar 2018 6:35:42pm
Author:  tnpes

==============================================================================
*/

#include "MaxSynth.h"

//==============================================================================
MaxSynthSound::MaxSynthSound()
{

}

MaxSynthSound::~MaxSynthSound()
{

}

bool MaxSynthSound::appliesToNote(int midiNoteNumber)
{
	return true;
}

bool MaxSynthSound::appliesToChannel(int midiChannel)
{
	return true;
}

//==============================================================================
MaxSynthVoice::MaxSynthVoice()
	:	level(0.0),
		frequency(0.0)
{
	
}

MaxSynthVoice::~MaxSynthVoice()
{

}

bool MaxSynthVoice::canPlaySound(SynthesiserSound * sound)
{
	return dynamic_cast<MaxSynthSound*> (sound) != nullptr;
}

void MaxSynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound * sound, int currentPitchWheelPosition)
{
	sineEnv.setAttack(0);
	sineEnv.setDecay(1);
	sineEnv.setSustain(0.8);
	sineEnv.setRelease(2000);

	sineEnv.trigger = 1;
	level = velocity;
	frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);

}

void MaxSynthVoice::stopNote(float velocity, bool allowTailOff)
{
	sineEnv.trigger = 0;
	level = velocity;

	if(velocity == 0)
		clearCurrentNote();
}

void MaxSynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void MaxSynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void MaxSynthVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	

	for (int sample = 0; sample < numSamples; sample++)
	{
		double sinewave = playSine();
		double envelope = sineEnv.adsr(sinewave, sineEnv.trigger);

		for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
		{
			outputBuffer.addSample(channel, startSample, envelope * level);
		}
		startSample++;
	}
}

double MaxSynthVoice::playSine()
{
	return sineOsc.sinewave(frequency);
}
