#include "mapi/graphics/color.hpp"

namespace mapi {
    Color::Color(uint8_t r, uint8_t g, uint8_t b) : mR(r), mG(g), mB(b) {
    }

    uint8_t Color::r() {
        return mR;
    }

    uint8_t Color::g() {
        return mG;
    }

    uint8_t Color::b() {
        return mB;
    }

    float Color::rf() {
        return (float) mR / 255.0f;
    }

    float Color::gf() {
        return (float) mG / 255.0f;
    }

    float Color::bf() {
        return (float) mB / 255.0f;
    }
}
