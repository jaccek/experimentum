#pragma once

#include <mapi/mode.hpp>
#include <mapi/view/auto_resize_image_widget.hpp>
#include <QtWidgets>

namespace pix {

    class PixelateMode : public mapi::Mode, public QObject {
    public:
        virtual void init(QWidget *mainWidget);

    private slots:
        void loadImage();

    private:
        QWidget *mMainWidget = nullptr;
        mapi::AutoResizeImageWidget *mImageWidget = nullptr;
    };
}
