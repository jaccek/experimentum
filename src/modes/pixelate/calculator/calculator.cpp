#include "calculator.hpp"

namespace pix {

    void Calculator::init(int centersCount, std::vector<ColorItem> &colors) {
        mIteration = 0;
        mCentersCount = centersCount;

        mColors.clear();
        for (auto item : colors) {
            mColors.push_back(item);
        }

        randomFirstState();
    }

    void Calculator::calculate() {
        mCalculate = true;
        printf("Calculator: start\n");

        while (mCalculate) {
            ++mIteration;
            printf("Calculator: iteration %d\n", mIteration);

            State oldState = state();
            State newState = makeSingleIteration(oldState);

            mStateMutex.lock();
            mState = newState;
            mStateMutex.unlock();
        }
        printf("Calculator: end\n");
    }

    void Calculator::breakCalculation() {
        mCalculate = false;
    }

    Calculator::State Calculator::state() {
        mStateMutex.lock();

        State state;
        for (auto center : mState.centers) {
            state.centers.push_back(center);
        }

        mStateMutex.unlock();

        return state;
    }

    int Calculator::iteration() {
        return mIteration;
    }

    Metric* Calculator::metric() {
        return mMetric;
    }

    void Calculator::setMetric(Metric *metric) {
        mMetric = metric;
    }

    std::vector<Calculator::ColorItem>& Calculator::colors() {
        return mColors;
    }

    int Calculator::centersCount() {
        return mCentersCount;
    }

    void Calculator::randomFirstState() {
        srand(time(NULL));
        mState.centers.clear();

        for (int i = 0; i < mCentersCount; ++i) {
            mState.centers.push_back(mapi::Color(rand() % 256, rand() % 256, rand() % 256));
        }
    }
}
