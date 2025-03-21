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

#pragma once

#include <visage/app.h>
#include <visage/graphics.h>

#include "../PluginProcessor.hpp"

namespace zlPanel {
    class PeakPanel : public visage::Frame  {
    public:
        explicit PeakPanel(PluginProcessor &processor);

        void draw(visage::Canvas &canvas) override;

        void run(double nextTimeStamp);

        void resized() override {
            width_.store(width());
            height_.store(height());
        }

        void setTimeLength(const float x) {
            magAnalyzer.setTimeLength(x);
            numPerSecond.store(static_cast<double>(zlDSP::Controller::analyzerPointNum - 1) / static_cast<double>(x));
        }

    private:
        zlMagAnalyzer::MagReductionAnalyzer<double, zlDSP::Controller::analyzerPointNum> &magAnalyzer;
        juce::SpinLock lock;

        std::atomic<double> numPerSecond{50.0};

        std::vector<float> xs;
        std::vector<float> inYs, outYs, reductionYs;
        std::atomic<float> width_{0.f}, height_{0.f};

        visage::Line inLine, outLine, reductionLine;

        double startTime{0.0};
        double currentCount{0.0};

        bool isFirstPoint{true};
        double smoothError{0.f};
        int consErrorCount{0};
    };
} // zlPanel
