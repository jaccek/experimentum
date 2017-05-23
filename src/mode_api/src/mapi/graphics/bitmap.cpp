#include "mapi/graphics/bitmap.hpp"

namespace mapi {

    Bitmap::Bitmap() {
    }

    Bitmap::Bitmap(QImage image) {
        mImage = image;
    }

    Bitmap::Bitmap(std::string fileName) {
        mImage = QImage(fileName.c_str());
    }

    int Bitmap::width() {
        return mImage.width();
    }

    int Bitmap::height() {
        return mImage.height();
    }

    Color Bitmap::pixel(int x, int y) {
        auto pixel = mImage.pixel(x, y);
        return Color(qRed(pixel), qGreen(pixel), qBlue(pixel));
    }

    void Bitmap::setPixel(int x, int y, Color color) {
        mImage.setPixel(x, y, color.asUint32());
    }

    Bitmap Bitmap::clone() {
        return Bitmap(mImage);
    }

    Bitmap Bitmap::scaled(int width, int height) {
        return Bitmap(mImage.scaled(width, height));
    }

    QImage& Bitmap::asQImage() {
        return mImage;
    }
}
