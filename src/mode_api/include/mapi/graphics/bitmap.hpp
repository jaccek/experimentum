#pragma once

#include <QPixmap>
#include <string>

namespace mapi {

    class Bitmap : public QPixmap {
    public:
        Bitmap();
        Bitmap(std::string fileName);
    };
}
