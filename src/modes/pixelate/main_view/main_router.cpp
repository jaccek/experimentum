#include "main_router.hpp"
#include <QtWidgets>

namespace pix {
    MainRouter::~MainRouter() {
    }

    mapi::Bitmap MainRouter::loadImage() {
        QString fileName = QFileDialog::getOpenFileName(nullptr, "Open Image", "/home",
                "Image Files (*.png *.jpg *.bmp)");
        printf("Selected file: %s\n", fileName.toUtf8().constData());

        return mapi::Bitmap(fileName.toUtf8().constData());
    }
}
