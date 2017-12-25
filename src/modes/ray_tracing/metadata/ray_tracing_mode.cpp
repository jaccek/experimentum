#include "ray_tracing_mode.hpp"

#include <QHBoxLayout>

namespace fp {

    void RayTracingMode::init(QWidget *mainWidget) {
        QLayout *layout = new QHBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);

        // auto glWidget = new mapi::GlWidget();
        // glWidget->setRenderer(new FirlusRenderer());
        // layout->addWidget(glWidget);

        mainWidget->setLayout(layout);
    }

    void RayTracingMode::loadImage() {
    }
}
