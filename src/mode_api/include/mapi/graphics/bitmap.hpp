#pragma once

#include <QPixmap>
#include <string>

namespace mapi {

    class Bitmap : public QPixmap {
    public:
        Bitmap(std::string fileName);
    };
}
