#include "pixelate_mode.hpp"

namespace pix {

    void PixelateMode::init(QWidget *mainWidget) {
        mView = new View();
        mView->init(mainWidget);
    }

    void PixelateMode::loadImage() {
    }
}
