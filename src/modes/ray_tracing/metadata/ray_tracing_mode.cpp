#include "ray_tracing_mode.hpp"

#include <QHBoxLayout>

namespace ray {

    void RayTracingMode::init(QWidget *mainWidget) {
        QLayout *layout = new QHBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);

        mImageWidget = new mapi::AutoResizeImageWidget();
        mImageWidget->setStyleSheet("background-color: white");
        layout->addWidget(mImageWidget);

        mainWidget->setLayout(layout);

        mEngine = new Engine();
        mImageWidget->setPixmap(QPixmap::fromImage(mEngine->getImage(800, 600)->asQImage()));
    }

    void RayTracingMode::loadImage() {
    }
}
