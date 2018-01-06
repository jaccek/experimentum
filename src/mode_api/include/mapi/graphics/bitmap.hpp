#pragma once

#include "mapi/graphics/color.hpp"
#include <QImage>
#include <string>

namespace mapi {

    class Bitmap {
    public:
        Bitmap();
        Bitmap(QImage image);
        Bitmap(std::string fileName);
        Bitmap(unsigned width, unsigned height, Color color);

        int width();
        int height();

        Color pixel(int x, int y);
        void setPixel(int x, int y, Color color);

        Bitmap clone();
        Bitmap scaled(int width, int height);

        QImage& asQImage();

    private:
        QImage mImage;
    };
}
