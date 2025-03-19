#include "PluginEditor.h"

PluginEditor::PluginEditor(PluginProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p) {
    juce::ignoreUnused(processorRef);

    setResizeLimits(static_cast<int>(10),
                    static_cast<int>(10),
                    static_cast<int>(10000),
                    static_cast<int>(10000));
    setResizable(true, p.wrapperType != PluginProcessor::wrapperType_AudioUnitv3);
    setSize(600, 300);
}

PluginEditor::~PluginEditor() = default;

void PluginEditor::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::black);
}

void PluginEditor::resized() {
    const auto bound = getLocalBounds();
    window.setWindowDimensions(bound.getWidth(),
                               juce::roundToInt(static_cast<float>(bound.getHeight()) * .75f));
    // DBG(std::to_string(bound.getWidth()) + "\t" + std::to_string(window.width()));
}

void PluginEditor::parentHierarchyChanged() {
    if (getPeer()) {
        // const auto bound = getLocalBounds();
        window.show(0,
                    0,
                    getPeer()->getNativeHandle());
        triggerAsyncUpdate();
    }
}
