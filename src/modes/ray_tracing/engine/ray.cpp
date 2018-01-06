#include "ray.hpp"

namespace ray {

    Ray::Ray(math::Vec3 castingPoint, math::Vec3 direction) :
            mCastingPoint(castingPoint),
            mDirection(direction) {
    }

    math::Vec3 Ray::direction() {
        return mDirection;
    }
}
