#pragma once

#include <mapi/mode.hpp>
#include <mapi/widget/auto_resize_image_widget.hpp>
#include <QtWidgets>

namespace fp {

    class FirlusPlaygroundMode : public mapi::Mode, public QObject {
    public:
        virtual void init(QWidget *mainWidget);
        void loadImage();

    private:
    };
}
