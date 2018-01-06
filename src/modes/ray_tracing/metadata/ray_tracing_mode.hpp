#pragma once

#include "engine/engine.hpp"
#include <mapi/mode.hpp>
#include <mapi/widget/auto_resize_image_widget.hpp>
#include <QWidget>

namespace ray {

    class RayTracingMode : public mapi::Mode, public QObject {
    public:
        virtual void init(QWidget *mainWidget);
        void loadImage();

    private:
        mapi::AutoResizeImageWidget *mImageWidget;

        Engine *mEngine;
    };
}
