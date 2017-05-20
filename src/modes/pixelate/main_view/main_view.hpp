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
        virtual void blockAllWidgetsExceptCancelComputation();
        virtual void unlockAllWidgets();

    private:
        mapi::AutoResizeImageWidget* createImageWidget();
        QWidget* createToolsWidget();

    private slots:
        void loadImageClicked();
        void calculateClicked();

    private:
        MainContract::PresenterForView *mPresenter;

        QWidget *mMainWidget;
        mapi::AutoResizeImageWidget *mSourceImageView;
        mapi::AutoResizeImageWidget *mDestinationImageView;
        QPushButton *mCalculateButton;
        QPushButton *mLoadImageButton;
    };
}
