#include "bitmap.hpp"

namespace mapi {

    Bitmap::Bitmap(std::string fileName) : QPixmap(fileName.c_str()) {
    }
}
