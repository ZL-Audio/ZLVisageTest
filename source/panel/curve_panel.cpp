// Copyright (C) 2025 - zsliu98
// This file is part of ZLVisageTest
//
// ZLVisageTest is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License Version 3 as published by the Free Software Foundation.
//
// ZLVisageTest is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with ZLVisageTest. If not, see <https://www.gnu.org/licenses/>.

//
// Created by Zishu Liu on 3/21/25.
//

#include "curve_panel.hpp"

namespace zlPanel {
    CurvePanel::CurvePanel(PluginProcessor &p)
        : Thread("curve"), peakPanel(p) {
        addChild(peakPanel, true);
        // addChild(dummyFrame, true);
        setIgnoresMouseEvents(true, false);
        // startThread(juce::Thread::Priority::low);
        // dummyFrame.onDraw() = [this](visage::Canvas&) {
        //     this->notify();
        // };
    }

    CurvePanel::~CurvePanel() {
        if (isThreadRunning()) {
            stopThread(-1);
        }
    }

    void CurvePanel::draw(visage::Canvas &canvas) {
        canvas.setColor(0xff000000);
        canvas.fill(0, 0, width(), height());
    }

    void CurvePanel::resized() {
        peakPanel.setBounds(0.f, 0.f, width(), height());
        dummyFrame.setBounds(0.f, 0.f, width(), height());
    }
    //
    void CurvePanel::run() {
        // while (!threadShouldExit()) {
        //     const auto flag = wait(-1);
        //     juce::ignoreUnused(flag);
        //     peakPanel.run(nextTimeStamp.load());
        // }
    }
} // zlPanel
