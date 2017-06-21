#pragma once

#include "calculator.hpp"
#include <mutex>

namespace pix {

    class KMeansCalculator : public Calculator {
    public:
        virtual ~KMeansCalculator();

    protected:
        virtual State makeSingleIteration(State oldState);

    private:
        void resetNewCenters(State &oldState);
        unsigned findNearestCenterIndex(State &oldState, ColorItem &item);
        void updateCenter(unsigned centerIndex, ColorItem &color);
        State createNewState(State &oldState);

    private:
        std::vector<ColorItem*> mNewCenters;
    };
}
