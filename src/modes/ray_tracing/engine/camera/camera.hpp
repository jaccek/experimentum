#pragma once

#include "engine/ray.hpp"
#include <math/vector/vec3.hpp>

namespace ray {

    class Camera {
    public:
        virtual ~Camera() {}

        virtual math::Vec3 position() = 0;
        virtual math::Vec3 direction() = 0;
        virtual float focalLength() = 0;

        virtual void setPosition(math::Vec3 position) = 0;
        virtual void setDirection(math::Vec3 direction) = 0;
        virtual void setFocalLength(float focalLength) = 0;

        virtual Ray generateRay(int x, int y, int imageWidth, int imageHeight) = 0;
    };
}
