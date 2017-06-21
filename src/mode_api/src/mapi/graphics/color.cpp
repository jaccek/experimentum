#include "mapi/graphics/color.hpp"

#include <QColor>
#include <QMatrix4x4>
#include <QVector3D>

namespace mapi {
    Color::Color(uint8_t r, uint8_t g, uint8_t b) : mR(r), mG(g), mB(b) {
        QColor color(mR, mG, mB);
        mH = color.hue();
        mS = color.saturationF();
        mV = color.valueF();

        QVector3D vector(mS, 0.0f, 0.0f);
        QMatrix4x4 rotation;
        rotation.rotate(mH, 0.0f, 1.0f, 0.0f);

        auto xyv = vector * rotation;
        mX = xyv.x();
        mY = xyv.z();
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
        return mH;
    }

    float Color::sf() {
        return mS;
    }

    float Color::vf() {
        return mV;
    }

    float Color::xf() {
        return mX;
    }

    float Color::yf() {
        return mY;
    }

    uint32_t Color::asUint32() {
        return 0xff000000 | mR << 16 | mG << 8 | mB;
    }
}
