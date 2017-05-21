#include "mapi/graphics/bitmap.hpp"

namespace mapi {

    Bitmap::Bitmap() {
    }

    Bitmap::Bitmap(std::string fileName) {
        mImage = QImage(fileName.c_str());
    }

    Color Bitmap::pixel(int x, int y) {
        auto pixel = mImage.pixel(x, y);
        return Color(qRed(pixel), qGreen(pixel), qBlue(pixel));
    }

    QImage& Bitmap::asQImage() {
        return mImage;
    }
}
