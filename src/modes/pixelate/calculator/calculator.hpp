#pragma once

#include "metric/metric.hpp"
#include <mapi/graphics/color.hpp>
#include <vector>
#include <mutex>

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

    protected:
        virtual State makeSingleIteration(State oldState) = 0;

    public:
        void init(int centresCount, std::vector<ColorItem> &colors);

        void calculate();
        void breakCalculation();

        State state();
        int iteration();
        Metric* metric();

        void setMetric(Metric *metric);

    protected:
        std::vector<ColorItem>& colors();
        int centersCount();

    private:
        void randomFirstState();

    private:
        bool mCalculate = true;
        int mIteration = 0;

        Metric* mMetric = nullptr;

        int mCentersCount;
        std::vector<ColorItem> mColors;

        State mState;
        std::mutex mStateMutex;
    };
}
