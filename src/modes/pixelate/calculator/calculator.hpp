#pragma once

#include <mapi/graphics/color.hpp>
#include <vector>

namespace pix {

    class Calculator {
    public:
        struct ColorItem {
            Color color;
            int count;
        };

        struct State {
            std::vector<ColorItem> colors;
        };

    public:
        virtual ~Calculator();

        virtual void calculate() = 0;
        virtual void breakCalculation() = 0;

        virtual State* state() = 0;
    };
}
