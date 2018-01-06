#pragma once

#include "engine/camera/camera.hpp"
#include <mapi/graphics/bitmap.hpp>

namespace ray {

    class Engine {
    public:
        Engine();
        virtual ~Engine();

        mapi::Bitmap* getImage(unsigned width, unsigned height);

    private:
        Camera *mCamera;
    };
}
