#include "pixelate_mode.hpp"

#include <QLabel>
#include <QVBoxLayout>

namespace pix {

    void PixelateMode::init(QWidget *mainWidget) {
        QLabel *label = new QLabel("test, very long string to show it even if menu cover it");

        QLayout *layout = new QVBoxLayout();
        layout->addWidget(label);
        layout->setAlignment(Qt::AlignCenter);

        mainWidget->setLayout(layout);
        printf("added\n");
    }
}
