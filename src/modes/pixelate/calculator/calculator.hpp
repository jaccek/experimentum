#pragma once

#include "metric/metric.hpp"
#include <mapi/graphics/color.hpp>
#include <vector>

namespace pix {

    class Calculator {
    public:
        struct ColorItem {
            mapi::Color color;
            int count;
        };

        struct State {
            std::vector<mapi::Color> centers;
        };

    public:
        virtual ~Calculator() {}

        virtual void init(int centresCount, std::vector<ColorItem> &colors) = 0;

        virtual void calculate() = 0;
        virtual void breakCalculation() = 0;
        virtual void setMetric(Metric *metric) = 0;

        virtual State state() = 0;
        virtual int iteration() = 0;
        virtual Metric* metric() = 0;
    };
}
