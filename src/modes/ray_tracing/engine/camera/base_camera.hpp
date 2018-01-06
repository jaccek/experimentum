#pragma once

#include "engine/camera/camera.hpp"
#include <math/vector/vec2.hpp>
#include <cstdio>

namespace ray {

    class BaseCamera : public Camera {
    public:
        BaseCamera(math::Vec3 position = math::Vec3(), math::Vec3 direction = math::Vec3(0.0f, 0.0f, 1.0f));
        virtual ~BaseCamera();

        virtual math::Vec3 position();
        virtual math::Vec3 direction();
        virtual float focalLength();

        virtual void setPosition(math::Vec3 position);
        virtual void setDirection(math::Vec3 direction);
        virtual void setFocalLength(float focalLength);

        virtual Ray generateRay(int x, int y, int imageWidth, int imageHeight);

    private:
        math::Vec3 mPosition;
        math::Vec3 mDirection;
        float mMatrixWidth;
        float mFocalLength;
    };
}
