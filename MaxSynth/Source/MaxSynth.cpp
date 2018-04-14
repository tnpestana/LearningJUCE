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
	sineEnv = new ADSR();
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
	sineEnv->gate(true);
	frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);

	level = velocity;
}

void MaxSynthVoice::stopNote(float velocity, bool allowTailOff)
{
	sineEnv->gate(false);
	allowTailOff = true;

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
	if (outputBuffer.getNumChannels() == 1)
		reverb.processMono(outputBuffer.getWritePointer(startSample), numSamples);
	else if (outputBuffer.getNumChannels() == 2)
		reverb.processStereo(outputBuffer.getWritePointer(startSample), outputBuffer.getWritePointer(startSample + 1), numSamples);

	for (int sample = 0; sample < numSamples; sample++)
	{
		double output = playSinewave() / 5;
		double envelope = sineEnv->process() * output;
		double loPassFilter = sineFilter.lores(envelope, 10000.0, 1);
		double hiPassFilter = sineFilter.hires(loPassFilter, 100.0, 1);

		for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
		{
			outputBuffer.addSample(channel, startSample, hiPassFilter * level);
		}
		startSample++;
	}
}

double MaxSynthVoice::playSinewave()
{
	return sineOsc.sinewave(frequency);
}

double MaxSynthVoice::playSquarewave()
{
	return sineOsc.square(frequency);
}

void MaxSynthVoice::getEnvelopeParameters(float* attack, float* decay, float* sustain, float* release)
{
	double sampleRate = getSampleRate();
	sineEnv->setAttackRate(*attack * sampleRate);
	sineEnv->setDecayRate(*decay * sampleRate);
	sineEnv->setSustainLevel(*sustain);
	sineEnv->setReleaseRate(*release * sampleRate);
}

void MaxSynthVoice::getReverbParameters(float dryWet, float roomSize, float damping)
{
	reverbParameters.dryLevel = 1 - dryWet;
	reverbParameters.wetLevel = dryWet;
	reverbParameters.roomSize = roomSize;
	reverbParameters.damping = damping;

	reverb.setParameters(reverbParameters);
}
