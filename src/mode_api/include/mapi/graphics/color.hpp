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

        uint32_t asUint32();

    private:
        uint8_t mR, mG, mB;
        float mH, mS, mV;
    };
}
