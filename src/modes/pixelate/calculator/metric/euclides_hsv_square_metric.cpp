#include "euclides_hsv_square_metric.hpp"

namespace pix {

    EuclidesHsvSquareMetric::~EuclidesHsvSquareMetric() {
    }

    std::string EuclidesHsvSquareMetric::name() {
        return "Euclides HSV Square Metric";
    }

    float EuclidesHsvSquareMetric::distance(mapi::Color &first, mapi::Color &second) {
        float dx = first.xf() - second.xf();
        float dy = first.yf() - second.yf();
        float dv = first.vf() - second.vf();

        return dx * dx + dy * dy + dv * dv;
    }
}
