#include "kmeans_calculator.hpp"

#include <cstdlib>
#include <ctime>
#include <limits>

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

        // TODO: refactor
        while (mCalculate) {
            ++mIteration;
            //printf("Calculator: iteration %d\n", mIteration);

            std::vector<ColorItem*> newCenters;
            State oldState = state();

            for (unsigned i = 0; i < oldState.centers.size(); ++i) {
                newCenters.push_back(nullptr);
            }

            for (auto item : mColors) {
                int centerIndex = 0;
                float minDistance = std::numeric_limits<float>::max();

                for (unsigned i = 0; i < oldState.centers.size(); ++i) {
                    auto center = oldState.centers[i];
                    float distance = mMetric->distance(item.color, center);
                    if (distance < minDistance) {
                        minDistance = distance;
                        centerIndex = i;
                    }
                }

                if (newCenters[centerIndex] == nullptr) {
                    newCenters[centerIndex] = new ColorItem{ item.color, item.count };
                } else {
                    int newCount = newCenters[centerIndex]->count + item.count;
                    int oldCount = newCenters[centerIndex]->count;
                    auto oldMean = newCenters[centerIndex]->color;

                    float r = (float) (oldMean.r() * oldCount + item.color.r() * item.count) / (float) newCount;
                    float g = (float) (oldMean.g() * oldCount + item.color.g() * item.count) / (float) newCount;
                    float b = (float) (oldMean.b() * oldCount + item.color.b() * item.count) / (float) newCount;

                    newCenters[centerIndex]->color = mapi::Color(r, g, b);
                    newCenters[centerIndex]->count = newCount;
                }
            }

            State newState;
            for (unsigned i = 0; i < newCenters.size(); ++i) {
                if (newCenters[i] != nullptr) {
                    newState.centers.push_back(newCenters[i]->color);
                    delete newCenters[i];
                } else {
                    newState.centers.push_back(oldState.centers[i]);
                }
            }

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
}
