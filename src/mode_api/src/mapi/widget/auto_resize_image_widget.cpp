#include "mapi/widget/auto_resize_image_widget.hpp"

namespace mapi {

    void AutoResizeImageWidget::setPixmap(const QPixmap &pixmap) {
        mPixmap = pixmap;
        QLabel::setPixmap(getResizedPixmap());
        setAlignment(Qt::AlignCenter);
    }

    void AutoResizeImageWidget::resizeEvent(QResizeEvent *event) {
        if (!mPixmap.isNull()) {
            QLabel::setPixmap(getResizedPixmap());
        }
    }

    QPixmap AutoResizeImageWidget::getResizedPixmap() {
        return mPixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
}
