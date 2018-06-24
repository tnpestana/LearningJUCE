/*
  ==============================================================================

    tnpSynth.cpp
    Created: 24 Jun 2018 4:31:02pm
    Author:  tnpes

  ==============================================================================
*/

#include "tnpSynth.h"

//==============================================================================
/** Our demo synth sound is just a basic sine wave.. */
TnpSynthSound::TnpSynthSound() 
{
}

bool TnpSynthSound::appliesToNote(int /*midiNoteNumber*/)
{
	return true; 

}
bool TnpSynthSound::appliesToChannel(int /*midiChannel*/)
{
	return true; 
}



TnpSynthVoice::TnpSynthVoice()
{

}

bool TnpSynthVoice::canPlaySound(SynthesiserSound* sound)
{
	return dynamic_cast<TnpSynthSound*> (sound) != nullptr;
}

void TnpSynthVoice::startNote(int midiNoteNumber, float velocity,
	SynthesiserSound*, int /*currentPitchWheelPosition*/)
{
	currentAngle = 0.0;
	level = velocity * 0.15;
	tailOff = 0.0;

	auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	auto cyclesPerSample = cyclesPerSecond / getSampleRate();

	angleDelta = cyclesPerSample * MathConstants<double>::twoPi;
}

void TnpSynthVoice::stopNote(float /*velocity*/, bool allowTailOff)
{
	if (allowTailOff)
	{
		// start a tail-off by setting this flag. The render callback will pick up on
		// this and do a fade out, calling clearCurrentNote() when it's finished.

		if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
			tailOff = 1.0;  // stopNote method could be called more than once.
	}
	else
	{
		// we're being told to stop playing immediately, so reset everything..
		clearCurrentNote();
		angleDelta = 0.0;
	}
}

void TnpSynthVoice::pitchWheelMoved(int /*newValue*/) 
{
}

void TnpSynthVoice::controllerMoved(int /*controllerNumber*/, int /*newValue*/)
{
}

void TnpSynthVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	if (angleDelta != 0.0)
	{
		if (tailOff > 0.0)
		{
			while (--numSamples >= 0)
			{
				auto currentSample = (float)(std::sin(currentAngle) * level * tailOff);

				for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);

				currentAngle += angleDelta;
				++startSample;

				tailOff *= 0.99;

				if (tailOff <= 0.005)
				{
					clearCurrentNote();

					angleDelta = 0.0;
					break;
				}
			}
		}
		else
		{
			while (--numSamples >= 0)
			{
				auto currentSample = (float)(std::sin(currentAngle) * level);

				for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);

				currentAngle += angleDelta;
				++startSample;
			}
		}
	}
}

