#pragma once

#include <mapi/mode.hpp>
#include <QWidget>

namespace pix {

    class PixelateMode : public mapi::Mode {
    public:
        virtual void init(QWidget *mainWidget);
    };
}
