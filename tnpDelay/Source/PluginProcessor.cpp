/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TnpDelayAudioProcessor::TnpDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
	treeState(*this, nullptr, "TnpDelayState",
	{
		std::make_unique<AudioParameterFloat>("delayTime", "Delay Time",
			NormalisableRange<float>(0.f, 2.f, 0.001f), 0.5f),
		std::make_unique<AudioParameterFloat>("feedback", "Feedback",
			NormalisableRange<float>(0.f, 1.f, 0.001f), 0.5f),
		std::make_unique<AudioParameterFloat>("wetMix", "Dry/Wet",
			NormalisableRange<float>(0.f, 1.f, 0.001f), 0.5f)
	}),
	delay()
#endif
{
}

TnpDelayAudioProcessor::~TnpDelayAudioProcessor()
{
}

//==============================================================================
const String TnpDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TnpDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TnpDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TnpDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TnpDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TnpDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TnpDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TnpDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String TnpDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void TnpDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TnpDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	treeState.addParameterListener("delayTime", this);
	treeState.addParameterListener("feedback", this);
	treeState.addParameterListener("wetMix", this);
	delay.prepareToPlay(sampleRate);
	updateDelay();
}

void TnpDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TnpDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void TnpDelayAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	processDelay(buffer);
}

//==============================================================================
void TnpDelayAudioProcessor::updateDelay()
{
	delay.updateParams(*treeState.getRawParameterValue("delayTime"),
		*treeState.getRawParameterValue("feedback"),
		*treeState.getRawParameterValue("wetMix"));
}

void TnpDelayAudioProcessor::processDelay(AudioBuffer<float>& buffer)
{
	for (int sample = 0; sample < buffer.getNumSamples(); sample++)
	{
		float* outputDataL = buffer.getWritePointer(0, sample);
		float* outputDataR = buffer.getWritePointer(1, sample);
		delay.processAudio(outputDataL, outputDataR);
	}
}

//==============================================================================
bool TnpDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TnpDelayAudioProcessor::createEditor()
{
    return new TnpDelayAudioProcessorEditor (*this);
}

//==============================================================================
void TnpDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	auto state = treeState.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void TnpDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(treeState.state.getType()))
			treeState.replaceState(ValueTree::fromXml(*xmlState));
}

AudioProcessorValueTreeState & TnpDelayAudioProcessor::getTreeState()
{
	return treeState;
}

void TnpDelayAudioProcessor::parameterChanged(const String & parameterID, float newValue)
{
	updateDelay();
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TnpDelayAudioProcessor();
}
