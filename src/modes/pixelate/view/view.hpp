#pragma once

#include <mapi/view/auto_resize_image_widget.hpp>
#include <QtWidgets>

namespace pix {

    class View : public QObject {
    public:
        void init(QWidget *mainWidget);

    private:
        mapi::AutoResizeImageWidget* createImageWidget();
        QWidget* createToolsWidget();

    private slots:
        void loadImage();

    private:
        QWidget *mMainWidget;
        mapi::AutoResizeImageWidget *mSourceImageView;
        mapi::AutoResizeImageWidget *mDestinationImageView;
    };
}
