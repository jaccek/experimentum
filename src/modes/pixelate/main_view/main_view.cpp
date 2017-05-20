#include "main_view.hpp"
#include "main_presenter.hpp"

namespace pix {

    MainView::MainView() {
        mPresenter = new MainPresenter(this);
    }

    MainView::~MainView() {
        delete mPresenter;
    }

    void MainView::init(QWidget *mainWidget) {
        mMainWidget = mainWidget;

        QLayout *layout = new QHBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);

        mSourceImageView = createImageWidget();
        layout->addWidget(mSourceImageView);

        mDestinationImageView = createImageWidget();
        layout->addWidget(mDestinationImageView);

        layout->addWidget(createToolsWidget());

        mainWidget->setLayout(layout);
    }

    void MainView::displaySourceImage(mapi::Bitmap &bitmap) {
        mSourceImageView->setPixmap(bitmap);
        mDestinationImageView->setPixmap(bitmap);    // FIXME: temporary
    }

    mapi::AutoResizeImageWidget* MainView::createImageWidget() {
        mapi::AutoResizeImageWidget *imageWidget = new mapi::AutoResizeImageWidget();
        imageWidget->setStyleSheet("background-color: white");
        return imageWidget;
    }

    QWidget* MainView::createToolsWidget() {
        QWidget *toolsWidget = new QWidget();
        toolsWidget->setMinimumWidth(200);
        toolsWidget->setMaximumWidth(200);

        QLayout *toolsLayout = new QVBoxLayout();

        QPushButton *loadImageButton = new QPushButton("Load image");
        QObject::connect(loadImageButton, &QPushButton::clicked, this, &MainView::loadImage);
        toolsLayout->addWidget(loadImageButton);

        toolsWidget->setLayout(toolsLayout);
        return toolsWidget;
    }

    void MainView::loadImage() {
        mPresenter->onLoadButtonClicked();
    }
}
