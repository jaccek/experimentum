#pragma once

#include "mapi/graphics/color.hpp"
#include <QImage>
#include <string>

namespace mapi {

    class Bitmap {
    public:
        Bitmap();
        Bitmap(std::string fileName);

        Color pixel(int x, int y);

        QImage& asQImage();

    private:
        QImage mImage;
    };
}
