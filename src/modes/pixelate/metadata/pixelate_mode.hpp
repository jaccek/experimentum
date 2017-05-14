#pragma once

#include "view/view.hpp"
#include <mapi/mode.hpp>
#include <mapi/view/auto_resize_image_widget.hpp>
#include <QtWidgets>

namespace pix {

    class PixelateMode : public mapi::Mode, public QObject {
    public:
        virtual void init(QWidget *mainWidget);
        void loadImage();

    private:
        View *mView;
    };
}
