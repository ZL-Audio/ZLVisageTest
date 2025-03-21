// Copyright (C) 2025 - zsliu98
// This file is part of ZLVisageTest
//
// ZLVisageTest is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License Version 3 as published by the Free Software Foundation.
//
// ZLVisageTest is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with ZLVisageTest. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <visage/app.h>
#include "PluginProcessor.hpp"

#include "panel/curve_panel.hpp"

class Window final : public visage::ApplicationWindow {
public:
    explicit Window(PluginProcessor &p) : curvePanel(p) {
        addChild(curvePanel, true);
    }

    ~Window() override = default;

    void draw(visage::Canvas &canvas) override {
        canvas.setColor(0xffffffff);
        canvas.fill(0, 0, width(), height());
    }

    void resized() override {
        curvePanel.setBounds(0.f, 0.f, width(), height());
    }

private:
    zlPanel::CurvePanel curvePanel;
};

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
    Window window;

    void handleAsyncUpdate() override {
        resized();
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
