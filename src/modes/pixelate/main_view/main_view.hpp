#pragma once

#include "main_contract.hpp"
#include <mapi/widget/auto_resize_image_widget.hpp>
#include <QtWidgets>

namespace pix {

    class MainView : public MainContract::View, public QObject {
    public:
        MainView();
        ~MainView();

        void init(QWidget *mainWidget);

        virtual void displaySourceImage(mapi::Bitmap &bitmap);

    private:
        mapi::AutoResizeImageWidget* createImageWidget();
        QWidget* createToolsWidget();

    private slots:
        void loadImage();

    private:
        MainContract::PresenterForView *mPresenter;

        QWidget *mMainWidget;
        mapi::AutoResizeImageWidget *mSourceImageView;
        mapi::AutoResizeImageWidget *mDestinationImageView;
    };
}
