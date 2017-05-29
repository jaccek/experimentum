#include "euclides_rgb_square_metric.hpp"

namespace pix {

    EuclidesRgbSquareMetric::~EuclidesRgbSquareMetric() {
    }

    float EuclidesRgbSquareMetric::distance(mapi::Color &first, mapi::Color &second) {
        float dr = first.rf() - second.rf();
        float dg = first.gf() - second.gf();
        float db = first.bf() - second.bf();

        return dr * dr + dg * dg + db * db;
    }
}
