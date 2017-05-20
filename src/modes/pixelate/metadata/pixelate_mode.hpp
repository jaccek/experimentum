#pragma once

#include "main_view/main_view.hpp"
#include <mapi/mode.hpp>
#include <mapi/widget/auto_resize_image_widget.hpp>
#include <QtWidgets>

namespace pix {

    class PixelateMode : public mapi::Mode, public QObject {
    public:
        virtual void init(QWidget *mainWidget);
        void loadImage();

    private:
        MainView *mView;
    };
}
