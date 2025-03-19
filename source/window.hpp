#pragma once

#include <visage/app.h>
#include "visage_widgets/graph_line.h"

class AnimatedLines : public visage::Frame {
public:
    static constexpr int kNumLines = 2;
    static constexpr int kNumPoints = 400;

    AnimatedLines() {
        for (auto &graph_line: graph_lines_) {
            graph_line = std::make_unique<visage::GraphLine>(kNumPoints);
            addChild(graph_line.get());
        }
    }

    void resized() override {
        int line_offset = height() / kNumLines;
        for (int i = 0; i < kNumLines; ++i) {
            graph_lines_[i]->setBounds(0, line_offset * i, width(), line_offset);
            graph_lines_[i]->setFill(true);
        }
    }

    void draw(visage::Canvas &canvas) override {
        double render_time = canvas.time();
        for (int r = 0; r < kNumLines; ++r) {
            int render_height = graph_lines_[r]->height();
            int render_width = graph_lines_[r]->width();
            int line_height = static_cast<int>(static_cast<float>(render_height) * 0.9f);
            int offset = static_cast<int>(static_cast<float>(render_height) * 0.05f);

            float position = 0.0f;
            for (int i = 0; i < kNumPoints; ++i) {
                float t = i / (kNumPoints - 1.0f);
                float delta = std::min(t, 1.0f - t);
                position += 0.1f * delta * delta + 0.003f;
                double phase = (render_time + r) * 0.5;
                graph_lines_[r]->setXAt(i, t * render_width);
                graph_lines_[r]->setYAt(i, offset + (
                                               sin1(static_cast<float>(phase + position)) * 0.5f + 0.5f) * line_height);
            }
        }

        redraw();
    }

private:
    std::unique_ptr<visage::GraphLine> graph_lines_[kNumLines];

    inline static float quickSin1(float phase) {
        phase = 0.5f - phase;
        return phase * (8.0f - 16.0f * fabsf(phase));
    }

    inline static float sin1(const float phase) {
        const float approx = quickSin1(phase - floorf(phase));
        return approx * (0.776f + 0.224f * fabsf(approx));
    }
};

class Window : public visage::ApplicationWindow {
public:
    Window() {
        addChild(lines);
    }

    ~Window() override = default;

    void draw(visage::Canvas &canvas) override {
        canvas.setColor(0xff33393f);
        canvas.fill(0, 0, width(), height());
    }

    void resized() override {
        lines.setBounds(0, 0, width(), height());
    }

private:
    AnimatedLines lines;
};
