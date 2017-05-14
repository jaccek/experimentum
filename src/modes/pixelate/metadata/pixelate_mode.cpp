#include "pixelate_mode.hpp"

namespace pix {

    void PixelateMode::init(QWidget *mainWidget) {
        mMainWidget = mainWidget;

        QLayout *layout = new QHBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);

        mImageWidget = new mapi::AutoResizeImageWidget();
        mImageWidget->setStyleSheet("background-color: white");
        layout->addWidget(mImageWidget);

        QWidget *toolsWidget = new QWidget();
        toolsWidget->setMinimumWidth(200);
        toolsWidget->setMaximumWidth(200);

        QLayout *toolsLayout = new QVBoxLayout();

        QPushButton *loadImageButton = new QPushButton("Load image");
        QObject::connect(loadImageButton, &QPushButton::clicked, this, &PixelateMode::loadImage);
        toolsLayout->addWidget(loadImageButton);

        toolsWidget->setLayout(toolsLayout);
        layout->addWidget(toolsWidget);

        mainWidget->setLayout(layout);
    }

    void PixelateMode::loadImage() {
        QString fileName = QFileDialog::getOpenFileName(mMainWidget, "Open Image", "/home",
                "Image Files (*.png *.jpg *.bmp)");
        printf("Selected file: %s\n", fileName.toUtf8().constData());

        QPixmap image(fileName);
        mImageWidget->setPixmap(image);
    }
}
