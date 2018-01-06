#pragma once

namespace math {

    class Vec3 {
    public:
        Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

        float length();
        void normalize();

        float x, y, z;
    };
}
