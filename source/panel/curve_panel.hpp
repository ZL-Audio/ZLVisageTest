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

#include "../PluginProcessor.hpp"
#include "peak_panel.hpp"

namespace zlPanel {
    class CurvePanel : public visage::Frame,
                       private juce::Thread {
    public:
        explicit CurvePanel(PluginProcessor &p);

        ~CurvePanel() override;

        void draw(visage::Canvas &canvas) override;

        void resized() override;

    private:
        PeakPanel peakPanel;
        visage::Frame dummyFrame;
        std::atomic<double> nextTimeStamp{0.};

        void run() override;
    };
} // zlPanel
