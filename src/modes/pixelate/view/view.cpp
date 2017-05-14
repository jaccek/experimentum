#include "view.hpp"

namespace pix {

    void View::init(QWidget *mainWidget) {
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

    mapi::AutoResizeImageWidget* View::createImageWidget() {
        mapi::AutoResizeImageWidget *imageWidget = new mapi::AutoResizeImageWidget();
        imageWidget->setStyleSheet("background-color: white");
        return imageWidget;
    }

    QWidget* View::createToolsWidget() {
        QWidget *toolsWidget = new QWidget();
        toolsWidget->setMinimumWidth(200);
        toolsWidget->setMaximumWidth(200);

        QLayout *toolsLayout = new QVBoxLayout();

        QPushButton *loadImageButton = new QPushButton("Load image");
        QObject::connect(loadImageButton, &QPushButton::clicked, this, &View::loadImage);
        toolsLayout->addWidget(loadImageButton);

        toolsWidget->setLayout(toolsLayout);
        return toolsWidget;
    }

    void View::loadImage() {
        QString fileName = QFileDialog::getOpenFileName(mMainWidget, "Open Image", "/home",
                "Image Files (*.png *.jpg *.bmp)");
        printf("Selected file: %s\n", fileName.toUtf8().constData());

        QPixmap image(fileName);
        mSourceImageView->setPixmap(image);
        mDestinationImageView->setPixmap(image);
    }
}
