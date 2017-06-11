#pragma once

#include "calculator/metric/metric.hpp"

namespace pix {

    class EuclidesRgbSquareMetric : public Metric {
    public:
        virtual ~EuclidesRgbSquareMetric();

        virtual std::string name();

        virtual float distance(mapi::Color &first, mapi::Color &second);
    };
}
