// Copyright (C) 2025 - zsliu98
// This file is part of ZLVisageTest
//
// ZLVisageTest is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License Version 3 as published by the Free Software Foundation.
//
// ZLVisageTest is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with ZLVisageTest. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "multiple_mag_analyzer.hpp"

namespace zlMagAnalyzer {
    template<typename FloatType, size_t PointNum>
    class MagReductionAnalyzer : public MultipleMagAnalyzer<FloatType, 2, PointNum> {
    public:
        explicit MagReductionAnalyzer() : MultipleMagAnalyzer<FloatType, 2, PointNum>() {
        }

        void prepare(const juce::dsp::ProcessSpec &spec) {
            this->sampleRate.store(spec.sampleRate);
            this->setTimeLength(this->timeLength.load());
        }

        void createPath(std::vector<float> &xs,
                        std::vector<float> &inYs, std::vector<float> &outYs, std::vector<float> &reductionYs,
                        const float width, const float height,
                        const float shift = 0.f, const float reductionBias = 0.f,
                        const float minDB = -72.f, const float maxDB = 0.f) {
            const auto deltaX = width / static_cast<float>(PointNum - 1);
            static constexpr float x0 = 0.f, y0 = 0.f;
            float x = x0 - shift * deltaX;
            for (size_t idx = 0; idx < PointNum; ++idx) {
                const auto inY = this->magToY(this->circularMags[0][idx], y0, height, minDB, maxDB);
                const auto outY = this->magToY(this->circularMags[1][idx], y0, height, minDB, maxDB);
                xs.emplace_back(x);
                inYs.emplace_back(inY);
                outYs.emplace_back(outY);
                reductionYs.emplace_back(outY - inY - reductionBias);
                x += deltaX;
            }
        }
    };
}
