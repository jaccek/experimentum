#include "engine.hpp"

#include "engine/camera/base_camera.hpp"

namespace ray {

    Engine::Engine() {
        mCamera = new BaseCamera();
        mWorld = new World();
    }

    Engine::~Engine() {
        delete mWorld;
        delete mCamera;
    }

    mapi::Bitmap* Engine::getImage(unsigned width, unsigned height) {
        auto bitmap = new mapi::Bitmap(width, height, mapi::Color());

        for (unsigned x = 0; x < width; ++x) {
            for (unsigned y = 0; y < height; ++y) {
                auto ray = mCamera->generateRay(x, y, width, height);

                auto intersectInfo = mWorld->castRay(ray);
                if (intersectInfo.hitsObject) {
                    auto direction = ray.direction() / 2.0f;

                    auto color = mapi::Color(
                        (uint8_t) (255.0f * (direction.x + 0.5f)),
                        (uint8_t) (255.0f * (direction.y + 0.5f)),
                        (uint8_t) (255.0f * (direction.z + 0.5f))
                    );
                    bitmap->setPixel(x, y, color);
                }
            }
        }

        return bitmap;
    }
}
