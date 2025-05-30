#pragma once

#include <JuceHeader.h>
#include "EffectsProcessor.h"

class AudioEngine : public juce::AudioSource
{
public:
    AudioEngine();
    ~AudioEngine() override;

    // AudioSource methods
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    // Audio file management
    bool loadAudioFile(const juce::File& file);
    void unloadAudioFile();

    // Playback control
    void startPlayback();
    void stopPlayback();
    void setLooping(bool shouldLoop);
    void setGain(float newGain);

    // Effects control
    EffectsProcessor& getEffectsProcessor() { return effectsProcessor; }
    void setEffectsEnabled(bool enabled) { effectsProcessor.setEffectEnabled(enabled); }
    bool isEffectsEnabled() const { return effectsProcessor.isEffectEnabled(); }

private:
    std::unique_ptr<juce::AudioFormatReader> audioFileReader;
    std::unique_ptr<juce::AudioFormatReaderSource> audioSource;
    juce::AudioTransportSource transportSource;
    juce::AudioFormatManager formatManager;
    juce::AudioDeviceManager deviceManager;
    EffectsProcessor effectsProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioEngine)
}; 