#include "kmeans_calculator.hpp"

#include <ctime>
#include <cmath>
#include <limits>
#include <cstdlib>

namespace pix {
    KMeansCalculator::~KMeansCalculator() {
    }

    void KMeansCalculator::init(int centersCount, std::vector<ColorItem> &colors) {
        mIteration = 0;
        mCentersCount = centersCount;

        mColors.clear();
        for (auto item : colors) {
            mColors.push_back(item);
        }

        randomFirstState();
    }

    void KMeansCalculator::calculate() {
        mCalculate = true;
        printf("Calculator: start\n");

        while (mCalculate) {
            ++mIteration;
            printf("Calculator: iteration %d\n", mIteration);

            State oldState = state();
            resetNewCenters(oldState);

            for (auto item : mColors) {
                unsigned centerIndex = findNearestCenterIndex(oldState, item);
                updateCenter(centerIndex, item);
            }

            State newState = createNewState(oldState);

            mStateMutex.lock();
            mState = newState;
            mStateMutex.unlock();
        }
        printf("Calculator: end\n");
    }

    void KMeansCalculator::breakCalculation() {
        mCalculate = false;
    }

    void KMeansCalculator::setMetric(Metric *metric) {
        mMetric = metric;
    }

    Calculator::State KMeansCalculator::state() {
        mStateMutex.lock();

        State state;
        for (auto center : mState.centers) {
            state.centers.push_back(center);
        }

        mStateMutex.unlock();

        return state;
    }

    int KMeansCalculator::iteration() {
        return mIteration;
    }

    Metric* KMeansCalculator::metric() {
        return mMetric;
    }

    void KMeansCalculator::randomFirstState() {
        srand(time(NULL));
        mState.centers.clear();

        for (int i = 0; i < mCentersCount; ++i) {
            mState.centers.push_back(mapi::Color(rand() % 256, rand() % 256, rand() % 256));
        }
    }

    void KMeansCalculator::resetNewCenters(State &oldState) {
        mNewCenters.clear();
        for (unsigned i = 0; i < oldState.centers.size(); ++i) {
            mNewCenters.push_back(nullptr);
        }
    }

    unsigned KMeansCalculator::findNearestCenterIndex(State &oldState, ColorItem &item) {
        unsigned centerIndex = 0;
        float minDistance = std::numeric_limits<float>::max();

        for (unsigned i = 0; i < oldState.centers.size(); ++i) {
            auto &center = oldState.centers[i];
            float distance = mMetric->distance(item.color, center);
            if (distance < minDistance) {
                minDistance = distance;
                centerIndex = i;
            }
        }
        return centerIndex;
    }

    void KMeansCalculator::updateCenter(unsigned centerIndex, ColorItem &color) {
        if (mNewCenters[centerIndex] == nullptr) {
            mNewCenters[centerIndex] = new ColorItem{ color.color, color.count };
        } else {
            float newCount = mNewCenters[centerIndex]->count + color.count;
            float oldCount = mNewCenters[centerIndex]->count;
            auto oldMean = mNewCenters[centerIndex]->color;

            float centerWeight = oldCount / newCount;
            float colorWeight = 1.0f - centerWeight;

            int r = (int) round((oldMean.rf() * centerWeight + color.color.rf() * colorWeight) * 255);
            int g = (int) round((oldMean.gf() * centerWeight + color.color.gf() * colorWeight) * 255);
            int b = (int) round((oldMean.bf() * centerWeight + color.color.bf() * colorWeight) * 255);

            mNewCenters[centerIndex]->color = mapi::Color(r, g, b);
            mNewCenters[centerIndex]->count = (int) newCount;
        }
    }

    Calculator::State KMeansCalculator::createNewState(State &oldState) {
        State newState;
        for (unsigned i = 0; i < mNewCenters.size(); ++i) {
            if (mNewCenters[i] != nullptr) {
                newState.centers.push_back(mNewCenters[i]->color);
                delete mNewCenters[i];
            } else {
                newState.centers.push_back(oldState.centers[i]);
            }
        }
        return newState;
    }
}
