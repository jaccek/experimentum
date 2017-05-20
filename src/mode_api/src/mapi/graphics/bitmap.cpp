#include "mapi/graphics/bitmap.hpp"

namespace mapi {

    Bitmap::Bitmap() : QPixmap() {
    }

    Bitmap::Bitmap(std::string fileName) : QPixmap(fileName.c_str()) {
    }
}
