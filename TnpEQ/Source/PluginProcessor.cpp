/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TnpEqAudioProcessor::TnpEqAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
	treeState(*this, nullptr),
	localSampleRate(1.0)
#endif
{
	// IRR Filter parameter(S).
	// One filter instance for each channel to avoid distortion.
	NormalisableRange<float> filterCutoffRange(20.f, 20000.f, 0.01f);
	NormalisableRange<float> filterGainRange(0.01f, 3.f, 0.01f);
	NormalisableRange<float> toggleFilterRange(0.0f, 1.0f, 1.0f);
	filterCutoffRange.setSkewForCentre(1000.0f);
	filterGainRange.setSkewForCentre(1.0f);
	treeState.createAndAddParameter("loCutoff", "Low/Mid Cutoff", String(), filterCutoffRange, 200.0f, nullptr, nullptr);
	treeState.createAndAddParameter("hiCutoff", "Mid/High Cutoff", String(), filterCutoffRange, 2000.0f, nullptr, nullptr);
	treeState.createAndAddParameter("loGain", "Low Band Gain", String(), filterGainRange, 1.0f, nullptr, nullptr);
	treeState.createAndAddParameter("midGain", "Mid Band Gain", String(), filterGainRange, 1.0f, nullptr, nullptr);
	treeState.createAndAddParameter("hiGain", "High Band Gain", String(), filterGainRange, 1.0f, nullptr, nullptr);
	
	treeState.state = ValueTree(Identifier("TnpEQ"));
}

TnpEqAudioProcessor::~TnpEqAudioProcessor()
{
}

//==============================================================================
const String TnpEqAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TnpEqAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TnpEqAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TnpEqAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TnpEqAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TnpEqAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TnpEqAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TnpEqAudioProcessor::setCurrentProgram (int index)
{
}

const String TnpEqAudioProcessor::getProgramName (int index)
{
    return {};
}

void TnpEqAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TnpEqAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	localSampleRate = sampleRate;
}

void TnpEqAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TnpEqAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void TnpEqAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
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

	const float loGain = *treeState.getRawParameterValue("loGain");
	const float midGain = *treeState.getRawParameterValue("midGain");
	const float hiGain = *treeState.getRawParameterValue("hiGain");
	const float loCutoff = *treeState.getRawParameterValue("loCutoff");
	const float hiCutoff = *treeState.getRawParameterValue("hiCutoff");

	filterLoLeft.setCoefficients(IIRCoefficients::makeLowShelf(
		localSampleRate, loCutoff, 2.0f, loGain));
	filterLoRight.setCoefficients(IIRCoefficients::makeLowShelf(
		localSampleRate, loCutoff, 2.0f, loGain));
	filterMidLeft.setCoefficients(IIRCoefficients::makePeakFilter(
		localSampleRate, (loCutoff + hiCutoff) / 2, 2.0f, midGain));
	filterMidRight.setCoefficients(IIRCoefficients::makePeakFilter(
		localSampleRate, (loCutoff + hiCutoff) / 2, 2.0f, midGain));
	filterHiLeft.setCoefficients(IIRCoefficients::makeHighShelf(
		localSampleRate, hiCutoff, 2.0f, hiGain));
	filterHiRight.setCoefficients(IIRCoefficients::makeHighShelf(
		localSampleRate, hiCutoff, 2.0f, hiGain));

	if (buffer.getNumChannels() == 1)
	{
		filterLoLeft.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
		filterMidLeft.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
		filterHiLeft.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
	}	
	else if (buffer.getNumChannels() == 2)
	{
		filterLoLeft.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
		filterLoRight.processSamples(buffer.getWritePointer(1), buffer.getNumSamples());
		filterMidLeft.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
		filterMidRight.processSamples(buffer.getWritePointer(1), buffer.getNumSamples());
		filterHiLeft.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
		filterHiRight.processSamples(buffer.getWritePointer(1), buffer.getNumSamples());
	}
}

//==============================================================================
bool TnpEqAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TnpEqAudioProcessor::createEditor()
{
    return new TnpEqAudioProcessorEditor (*this, treeState);
}

//==============================================================================
void TnpEqAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TnpEqAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TnpEqAudioProcessor();
}
