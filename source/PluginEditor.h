#pragma once

#include "PluginProcessor.h"
#include <visage/app.h>

//==============================================================================
class PluginEditor : public juce::AudioProcessorEditor, private juce::ComponentMovementWatcher {
public:
    explicit PluginEditor(PluginProcessor &);

    ~PluginEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;

    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    void componentPeerChanged() override;

    void componentMovedOrResized(bool wasMoved, bool wasResized) override {
        juce::ignoreUnused(wasMoved, wasResized);
    }

    void componentVisibilityChanged() override {}

    PluginProcessor &processorRef;
    visage::ApplicationWindow appWindow{};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
