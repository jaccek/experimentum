#include "mapi/graphics/color.hpp"

#include <QColor>

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

    float Color::hf() {
        return QColor(mR, mG, mB).hue();
    }

    float Color::sf() {
        return QColor(mR, mG, mB).saturationF();
    }

    float Color::vf() {
        return QColor(mR, mG, mB).valueF();
    }

    uint32_t Color::asUint32() {
        return 0xff000000 | mR << 16 | mG << 8 | mB;
    }
}