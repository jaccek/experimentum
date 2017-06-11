#pragma once

#include <mapi/graphics/color.hpp>
#include <string>

namespace pix {

    class Metric {
    public:
        virtual ~Metric() {}

        virtual std::string name() = 0;

        virtual float distance(mapi::Color &first, mapi::Color &second) = 0;
    };
}
