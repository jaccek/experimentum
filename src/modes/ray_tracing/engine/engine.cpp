#include "engine.hpp"

#include "engine/camera/base_camera.hpp"

namespace ray {

    Engine::Engine() {
        mCamera = new BaseCamera();
    }

    Engine::~Engine() {
        delete mCamera;
    }

    mapi::Bitmap* Engine::getImage(unsigned width, unsigned height) {
        auto bitmap = new mapi::Bitmap(width, height, mapi::Color());

        for (unsigned x = 0; x < width; ++x) {
            for (unsigned y = 0; y < height; ++y) {
                auto ray = mCamera->generateRay(x, y, width, height);

                auto direction = ray.direction();
                direction.z = 0.0f;
                direction.normalize();

                // printf("color = (%.3f, %.3f, %.3f)\n", direction.x, lookAtY);

                auto color = mapi::Color(
                    (uint8_t) (255.0f * direction.x),
                    (uint8_t) (255.0f * direction.y),
                    (uint8_t) (255.0f * direction.z)
                );
                bitmap->setPixel(x, y, color);
            }
        }

        return bitmap;
    }
}
