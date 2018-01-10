#include "base_camera.hpp"

using namespace math;

namespace ray {

    BaseCamera::BaseCamera(Vec3 position, Vec3 direction):
        mPosition(position),
        mDirection(direction),
        mMatrixWidth(0.1f),
        mFocalLength(0.035f) {
    }

    BaseCamera::~BaseCamera() {
    }

    Vec3 BaseCamera::position() {
        return mPosition;
    }

    Vec3 BaseCamera::direction() {
        return mDirection;
    }

    float BaseCamera::focalLength() {
        return mFocalLength;
    }

    void BaseCamera::setPosition(math::Vec3 position) {
        mPosition = position;
    }

    void BaseCamera::setDirection(math::Vec3 direction) {
        mDirection = direction;
    }

    void BaseCamera::setFocalLength(float focalLength) {
        mFocalLength = focalLength;
    }

    Ray BaseCamera::generateRay(int x, int y, int imageWidth, int imageHeight) {
        float matrixScale = mMatrixWidth / (float) imageWidth;
        //float matrixHeight = imageHeight * matrixScale;

        y = imageHeight - y;
        float lookAtX = (x - imageWidth / 2) * matrixScale;
        float lookAtY = (y - imageHeight / 2) * matrixScale;

        // TODO: this code works only if mDirection == (0, 0, 1)!!!
        Vec3 rayDirection = mDirection * mFocalLength;
        rayDirection.x += lookAtX;
        rayDirection.y += lookAtY;
        rayDirection.normalize();

        return Ray(mPosition, rayDirection);
    }
}
