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

#include "peak_panel.hpp"

namespace zlPanel {
    PeakPanel::PeakPanel(PluginProcessor &processor)
        : magAnalyzer(processor.getController().getMagAnalyzer()) {
        setIgnoresMouseEvents(true, false);
        for (auto &line : {&inLine, &outLine, &reductionLine}) {
            line->setNumPoints(zlDSP::Controller::analyzerPointNum);
        }
        magAnalyzer.setToReset();
        setTimeLength(6.f);
    }

    void PeakPanel::draw(visage::Canvas &canvas) {
        run(canvas.time());
        canvas.setColor({.25f, 1.f, 1.f, 1.f});
        canvas.lineFill(&inLine, 0.0f, 0.0f, width(), height(), height());
        canvas.setColor({.9f, 1.f, 1.f, 1.f});
        canvas.line(&outLine, 0.0f, 0.0f, width(), height(), 1.5f);
        canvas.setColor({1.f, 0.7803921568627451f, 0.08235294117647059f, 0.5215686274509804f});
        canvas.line(&reductionLine, 0.0f, 0.0f, width(), height(), 2.5f);

        redraw();
    }

    void PeakPanel::run(const double nextTimeStamp) {
        if (isFirstPoint) {
            if (magAnalyzer.run(1) > 0) {
                isFirstPoint = false;
                currentCount = 0.;
                startTime = nextTimeStamp;
                for (auto &v : {&xs, &inYs, &outYs, &reductionYs}) {
                    v->clear();
                }
                magAnalyzer.createPath(xs, inYs, outYs, reductionYs,
                    width_.load(), height_.load(), 0.f, 0.f);
            }
        } else {
            const auto targetCount = (nextTimeStamp - startTime) * numPerSecond.load();
            const auto targetDelta = targetCount - currentCount;
            const auto actualDelta = static_cast<double>(magAnalyzer.run(static_cast<int>(std::floor(targetDelta))));
            currentCount += static_cast<double>(actualDelta);
            const auto currentError = std::abs(targetDelta - actualDelta);
            if (currentError < smoothError) {
                smoothError = currentError;
            } else {
                smoothError = smoothError * 0.95 + currentError * 0.05;
            }
            if (smoothError > 1.0) {
                currentCount += std::floor(smoothError);
                if (consErrorCount < 5) {
                    consErrorCount += 1;
                }
            }
            if (actualDelta > 0) {
                consErrorCount = 0;
            }
            if (consErrorCount < 5) {
                for (auto &v : {&xs, &inYs, &outYs, &reductionYs}) {
                    v->clear();
                }
                magAnalyzer.createPath(xs, inYs, outYs, reductionYs,
                    width_.load(), height_.load(), 0.f);
            }
        }
        {
            // const juce::GenericScopedLock guard{lock};
            inLine.x = xs;
            inLine.y = inYs;
            inLine.values.resize(xs.size(), 0.f);
            outLine.x = xs;
            outLine.y = outYs;
            outLine.values.resize(xs.size(), 0.f);
            reductionLine.x = xs;
            reductionLine.y = reductionYs;
            reductionLine.values.resize(xs.size(), 0.f);
        }
    }
} // zlPanel
