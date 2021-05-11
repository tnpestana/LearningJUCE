/*
  ==============================================================================

    tnpAudioSource.h
    Created: 24 Jun 2018 4:31:18pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "C:/Users/tnpes/Documents/JUCE/examples/Assets/DemoUtilities.h"

//==============================================================================
// This is an audio source that streams the output of our demo synth.
struct TnpAudioSource : public AudioSource
{
	TnpAudioSource(MidiKeyboardState& keyState);

	void setUsingSampledSound();

	void prepareToPlay(int /*samplesPerBlockExpected*/, double sampleRate) override;

	void releaseResources() override;

	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;

	//==============================================================================
	// this collects real-time midi messages from the midi input device, and
	// turns them into blocks that we can process in our audio callback
	MidiMessageCollector midiCollector;

	// this represents the state of which keys on our on-screen keyboard are held
	// down. When the mouse is clicked on the keyboard component, this object also
	// generates midi messages for this, which we can pass on to our synth.
	MidiKeyboardState& keyboardState;

	// the synth itself!
	Synthesiser synth;
	AudioFormatManager formatManager;
};