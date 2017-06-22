#include "kmeans_calculator.hpp"

#include <cmath>
#include <limits>

namespace pix {
    KMeansCalculator::~KMeansCalculator() {
    }

    Calculator::State KMeansCalculator::makeSingleIteration(State oldState) {
        resetNewCenters(oldState);

        for (auto item : colors()) {
            unsigned centerIndex = findNearestCenterIndex(oldState, item);
            updateCenter(centerIndex, item);
        }

        return createNewState(oldState);
    }

    void KMeansCalculator::resetNewCenters(State &oldState) {
        mNewCenters.clear();
        for (unsigned i = 0; i < oldState.colors.size(); ++i) {
            mNewCenters.push_back(nullptr);
        }
    }

    unsigned KMeansCalculator::findNearestCenterIndex(State &oldState, ColorItem &item) {
        unsigned centerIndex = 0;
        float minDistance = std::numeric_limits<float>::max();

        for (unsigned i = 0; i < oldState.colors.size(); ++i) {
            auto &center = oldState.colors[i];
            float distance = metric()->distance(item.color, center);
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
                newState.colors.push_back(mNewCenters[i]->color);
                delete mNewCenters[i];
            } else {
                newState.colors.push_back(oldState.colors[i]);
            }
        }
        return newState;
    }
}
