#pragma once

#include "PluginProcessor.h"
#include "window.hpp"

//==============================================================================
class PluginEditor : public juce::AudioProcessorEditor,
                     private juce::AsyncUpdater {
public:
    explicit PluginEditor(PluginProcessor &);

    ~PluginEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;

    void resized() override;

    void parentHierarchyChanged() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    PluginProcessor &processorRef;
    Window window{};

    void handleAsyncUpdate() override {
        resized();
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
