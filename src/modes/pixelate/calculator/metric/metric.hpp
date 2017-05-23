#pragma once

#include <mapi/graphics/color.hpp>

namespace pix {

    class Metric {
    public:
        virtual ~Metric() {}

        virtual float distance(mapi::Color &first, mapi::Color &second) = 0;
    };
}
