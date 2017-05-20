#include "pixelate_mode.hpp"

namespace pix {

    void PixelateMode::init(QWidget *mainWidget) {
        mView = new MainView();
        mView->init(mainWidget);
    }

    void PixelateMode::loadImage() {
    }
}
