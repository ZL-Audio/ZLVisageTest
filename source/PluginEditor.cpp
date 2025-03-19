#include "PluginEditor.h"

PluginEditor::PluginEditor(PluginProcessor &p)
        : AudioProcessorEditor(&p), ComponentMovementWatcher(this), processorRef(p) {
    juce::ignoreUnused(processorRef);

    setResizeLimits(static_cast<int>(10),
                    static_cast<int>(10),
                    static_cast<int>(10000),
                    static_cast<int>(10000));
    setResizable(true, p.wrapperType != PluginProcessor::wrapperType_AudioUnitv3);
    setSize(300, 300);
}

PluginEditor::~PluginEditor() = default;

void PluginEditor::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
}

void PluginEditor::resized() {
    // layout the positions of your child components here
    if (auto d = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()) {
        const auto bound = d->userArea;
        appWindow.setWindowDimensions(bound.getWidth(), bound.getHeight());
    }
}

void PluginEditor::componentPeerChanged() {
    if (getPeer()) {
        appWindow.show(100, 100, getPeer()->getNativeHandle());
        resized();
    }
}
