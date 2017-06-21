#pragma once

#include "calculator/metric/metric.hpp"

namespace pix {

    class EuclidesHsvSquareMetric : public Metric {
    public:
        virtual ~EuclidesHsvSquareMetric();

        virtual std::string name();

        virtual float distance(mapi::Color &first, mapi::Color &second);
    };
}
