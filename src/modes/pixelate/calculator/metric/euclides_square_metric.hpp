#pragma once

#include "calculator/metric/metric.hpp"

namespace pix {

    class EuclidesSquareMetric : public Metric {
        virtual ~EuclidesSquareMetric();

        virtual float distance(mapi::Color &first, mapi::Color &second);
    };
}
