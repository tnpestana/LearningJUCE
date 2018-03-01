/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ReverbAudioProcessor::ReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
			parameters(*this, nullptr)
#endif
{
	parameters.createAndAddParameter("dryWet", "DryWet", String(),
		NormalisableRange<float>(0.0f, 1.0f), 1.0f, nullptr, nullptr);
	parameters.createAndAddParameter("roomSize", "RoomSize", String(),
		NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);
	parameters.createAndAddParameter("damping", "Damping", String(),
		NormalisableRange<float>(0.0f, 1.0f), 0.0f, nullptr, nullptr);

	parameters.state = ValueTree(Identifier("ReverbState"));

	//reverb.setParameters(reverbParameters);
}

ReverbAudioProcessor::~ReverbAudioProcessor()
{
}

//==============================================================================
const String ReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ReverbAudioProcessor::setCurrentProgram (int index)
{
}

const String ReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void ReverbAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	reverb.setSampleRate(sampleRate);
}

void ReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ReverbAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

	const float currentDryWet = *parameters.getRawParameterValue("dryWet");
	const float currentRoomSize= *parameters.getRawParameterValue("roomSize");
	const float currentDamping= *parameters.getRawParameterValue("damping");

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	const auto numChannels = jmin(totalNumInputChannels, totalNumOutputChannels);

	reverbParameters.dryLevel = 1 - currentDryWet;
	reverbParameters.wetLevel = currentDryWet;
	reverbParameters.roomSize = currentRoomSize;
	reverbParameters.damping = currentDamping;

	reverb.setParameters(reverbParameters);

	if (numChannels == 1)
		reverb.processMono(buffer.getWritePointer(0), buffer.getNumSamples());
	else if (numChannels == 2)
		reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());

	// This is the place where you'd normally do the guts of your plugin's
	// audio processing...
	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		float* channelData = buffer.getWritePointer(channel);

		// ..do something to the data...
	}

}

//==============================================================================
bool ReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ReverbAudioProcessor::createEditor()
{
    return new ReverbAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void ReverbAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	ScopedPointer<XmlElement> xml(parameters.state.createXml());
	copyXmlToBinary(*xml, destData);
}

void ReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	ScopedPointer<XmlElement> savedParametersXml (getXmlFromBinary(data, sizeInBytes));
	if (savedParametersXml != nullptr)
	{
		if (savedParametersXml->hasTagName(parameters.state.getType()))
		{
			parameters.state = ValueTree::fromXml(*savedParametersXml);
		}

	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReverbAudioProcessor();
}
