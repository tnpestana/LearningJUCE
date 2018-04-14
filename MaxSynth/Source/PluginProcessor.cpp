/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MaxSynthAudioProcessor::MaxSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
		treeState(*this, nullptr)
#endif
{
	// Envelope parameters
	NormalisableRange<float> attackRange (0.0f, 5.0f, 0.001f);
	NormalisableRange<float> decayRange (0.0f, 5.0f, 0.001f);
	NormalisableRange<float> sustainRange (0.0f, 1.0f, 0.001f);
	NormalisableRange<float> releaseRange (0.0f, 5.0f, 0.001f);
	attackRange.setSkewForCentre(1.0);
	decayRange.setSkewForCentre(1.0);
	releaseRange.setSkewForCentre(1.0);

	treeState.createAndAddParameter("attack", "Attack", String(), attackRange, 0.1f, nullptr, nullptr);
	treeState.createAndAddParameter("decay", "Decay", String(), decayRange, 0.1f, nullptr, nullptr);
	treeState.createAndAddParameter("sustain", "Sustain", String(), sustainRange, 0.5f, nullptr, nullptr);
	treeState.createAndAddParameter("release", "Release", String(), releaseRange, 0.1f, nullptr, nullptr);

	// Reverb parameters
	NormalisableRange<float> dryWetRange (0.0f, 1.0f, 0.01f);
	NormalisableRange<float> roomSizeRange (0.0f, 1.0f, 0.01f);
	NormalisableRange<float> dampingRange (0.0f, 1.0f, 0.01f);

	treeState.createAndAddParameter("dryWet", "DryWet", String(), dryWetRange, 0.5f, nullptr, nullptr);
	treeState.createAndAddParameter("roomSize", "RoomSize", String(), roomSizeRange, 0.2f, nullptr, nullptr);
	treeState.createAndAddParameter("damping", "Damping", String(), dampingRange, 0.0f, nullptr, nullptr);

	treeState.state = ValueTree(Identifier("ReverbState"));

	synth.clearVoices();
	for (int i = 0; i < 5; i++)
		synth.addVoice(new MaxSynthVoice());

	synth.clearSounds();
	synth.addSound(new MaxSynthSound());
}

MaxSynthAudioProcessor::~MaxSynthAudioProcessor()
{
}

//==============================================================================
const String MaxSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MaxSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MaxSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MaxSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MaxSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MaxSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MaxSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MaxSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String MaxSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void MaxSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MaxSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	synth.setCurrentPlaybackSampleRate(sampleRate);
}

void MaxSynthAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MaxSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MaxSynthAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	buffer.clear();

	for (int i = 0; i < synth.getNumVoices(); i++)
	{
		if (maxSynthVoice = dynamic_cast<MaxSynthVoice*>(synth.getVoice(i)))
		{
			maxSynthVoice->getEnvelopeParameters(treeState.getRawParameterValue("attack"),
				treeState.getRawParameterValue("decay"),
				treeState.getRawParameterValue("sustain"),
				treeState.getRawParameterValue("release"));

			maxSynthVoice->getReverbParameters(*treeState.getRawParameterValue("dryWet"),
				*treeState.getRawParameterValue("roomSize"),
				*treeState.getRawParameterValue("damping"));
		}
	}

	synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool MaxSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MaxSynthAudioProcessor::createEditor()
{
    return new MaxSynthAudioProcessorEditor (*this);
}

//==============================================================================
void MaxSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MaxSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MaxSynthAudioProcessor();
}
