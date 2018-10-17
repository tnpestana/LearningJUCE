/*
  ==============================================================================

    TnpSynth.cpp
    Created: 4 Oct 2018 2:02:50pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpSynth.h"

//==============================================================================
TnpSynthSound::TnpSynthSound()
{
}

TnpSynthSound::~TnpSynthSound()
{
}

bool TnpSynthSound::appliesToNote(int midiNoteNumber)
{
	return true;
}

bool TnpSynthSound::appliesToChannel(int midiChannel)
{
	return true;
}

//==============================================================================
TnpSynthVoice::TnpSynthVoice()
{
}

TnpSynthVoice::~TnpSynthVoice()
{
}

bool TnpSynthVoice::canPlaySound(SynthesiserSound *sound)
{
	return dynamic_cast<TnpSynthSound*> (sound) != nullptr;
}

void TnpSynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound * sound, int currentPitchWheelPosition)
{
	oscillator.setFrequency(MidiMessage::getMidiNoteInHertz(midiNoteNumber), 
		getSampleRate());
}

void TnpSynthVoice::stopNote(float velocity, bool allowTailOff)
{
	allowTailOff = true;
	if (velocity == 0)
		clearCurrentNote();
}

void TnpSynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void TnpSynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void TnpSynthVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	outputBuffer.clear();
	for (int sample = 0; sample < numSamples; ++sample)
	{
		float currentSample = oscillator.getNextSample();
		for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
			outputBuffer.addSample(channel, startSample, currentSample);
		startSample++;
	}
}
