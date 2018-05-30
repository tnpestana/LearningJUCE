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
	treeState(*this, nullptr)
#endif
{
	// Default values:
	delayLength = 0.5;		// in seconds
	wetMix = 0.5;			// ratio
	feedback = 0.5;			// percentage
	delayBufferLength = 1;	// in samples
	delayReadPosition = 0;
	delayWritePosition = 0;

	NormalisableRange<float> delayTimeRange (0.f, 2.f, 0.001f);
	treeState.createAndAddParameter("delayTime", "DelayTime", String(), delayTimeRange, 0.5f, nullptr, nullptr);
	NormalisableRange<float> feedbackRange(0.f, 1.f, 0.001f);
	treeState.createAndAddParameter("feedback", "Feedback", String(), feedbackRange, 0.5f, nullptr, nullptr);
	NormalisableRange<float> wetMixRange(0.f, 1.f, 0.001f);
	treeState.createAndAddParameter("wetMix", "WetMix", String(), wetMixRange, 0.5f, nullptr, nullptr);

	treeState.state = ValueTree(Identifier("DelayState"));
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
void TnpDelayAudioProcessor::setupDelay()
{
	// Delay processing.
	delayLength = *treeState.getRawParameterValue("delayTime");
	feedback = *treeState.getRawParameterValue("feedback");
	wetMix = *treeState.getRawParameterValue("wetMix");

	delayInSamples = delayLength * sampleRate;

	delayReadPosition = (int)(delayWritePosition - delayInSamples);

	// Wrap delay read position to the buffers range.
	if (delayReadPosition < 0)
		delayReadPosition += delayBufferLength;
}

//==============================================================================
void TnpDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	this->sampleRate = sampleRate;

	// Set max delay in samples.
	delayBufferLength = (int)(2.0 * sampleRate); 
	if (delayBufferLength < 1)
		delayBufferLength = 1;

	delayBuffer.setSize(2, delayBufferLength);
	delayBuffer.clear();

	setupDelay();
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

void TnpDelayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	int drp, dwp;

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
		auto* delayData = delayBuffer.getWritePointer (channel);
		
		if (delayLength != *treeState.getRawParameterValue("delayTime") ||
			feedback != *treeState.getRawParameterValue("feedback") ||
			wetMix != *treeState.getRawParameterValue("wetMix"))
		{
			setupDelay();
		}
		// Temporarily store the pointer values.
		drp = delayReadPosition;
		dwp = delayWritePosition;
		
		for (int sample = 0; sample < buffer.getNumSamples(); sample++)
		{
			// Will Pirkle:
			// Step 1 - Read delayed audio data.
			float yn = delayData[drp];
			
			// Step 2 - Calculate mixed output.
			if (delayLength != 0.0f)
				channelData[sample] = (1 - wetMix) * channelData[sample] + wetMix * (channelData[sample] + (feedback * yn));

			// Step 3 - Write input data into delay line at write location.
			delayData[drp] = channelData[sample];
			
			if (++drp >= delayInSamples)
				drp = 0;
			if (++dwp >= delayInSamples)
				dwp = 0;
		}
    }

	delayReadPosition = drp;
	delayWritePosition = dwp;
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
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TnpDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TnpDelayAudioProcessor();
}
