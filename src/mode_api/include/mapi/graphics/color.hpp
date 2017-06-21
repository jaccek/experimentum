#pragma once

#include <cstdint>

namespace mapi {

    class Color {
    public:
        Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0);

        uint8_t r();
        uint8_t g();
        uint8_t b();

        float rf();
        float gf();
        float bf();

        float hf();
        float sf();
        float vf();

        /**
            HSV color system is problematic, becouse hue is an angle and saturation is distance from 'value axis'.
            Other words its a polar coordinate system. Metric calculations are difficult in this system.

            I've introduced XYV color system. It's a cartesian coordinate system based on HSV.

            X, Y coords - they are calculated according to hue and saturation values.
            V coord - it's a value from HSV
        */
        float xf();
        float yf();

        uint32_t asUint32();

    private:
        uint8_t mR, mG, mB;
        float mH, mS, mV;
        float mX, mY;
    };
}
