// Copyright (C) 2025 - zsliu98
// This file is part of ZLVisageTest
//
// ZLVisageTest is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License Version 3 as published by the Free Software Foundation.
//
// ZLVisageTest is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with ZLVisageTest. If not, see <https://www.gnu.org/licenses/>.

#include "PluginEditor.hpp"

PluginEditor::PluginEditor(PluginProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p), window(p) {
    juce::ignoreUnused(processorRef);

    setSize(600, 375);
}

PluginEditor::~PluginEditor() = default;

void PluginEditor::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::white);
}

void PluginEditor::resized() {
    const auto bound = getLocalBounds();
    window.setWindowDimensions(bound.getWidth(),
                               juce::roundToInt(static_cast<float>(bound.getHeight()) * .8f));
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
