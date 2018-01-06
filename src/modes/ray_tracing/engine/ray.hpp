#pragma once

#include <math/vector/vec3.hpp>

namespace ray {

    class Ray {
    public:
        Ray(math::Vec3 castingPoint, math::Vec3 direction);

        math::Vec3 direction();

    private:
        math::Vec3 mCastingPoint;
        math::Vec3 mDirection;
    };
}
