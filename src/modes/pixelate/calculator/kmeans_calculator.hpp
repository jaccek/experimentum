#pragma once

#include "calculator.hpp"
#include <mutex>

namespace pix {

    class KMeansCalculator : public Calculator {
    public:
        virtual ~KMeansCalculator();

        virtual void init(int centresCount, std::vector<ColorItem> &colors);

        virtual void calculate();
        virtual void breakCalculation();
        virtual void setMetric(Metric *metric);

        virtual State state();
        virtual int iteration();
        virtual Metric* metric();

    private:
        void randomFirstState();

    private:
        State mState;
        int mIteration;
        int mCentersCount;
        bool mCalculate = true;
        std::vector<ColorItem> mColors;

        std::mutex mStateMutex;

        Metric *mMetric = nullptr;
    };
}
