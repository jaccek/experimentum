#include "mapi/widget/auto_resize_image_widget.hpp"

namespace mapi {

    void AutoResizeImageWidget::setPixmap(const QPixmap &pixmap, Qt::TransformationMode mode) {
        mTransformationMode = mode;
        mPixmap = pixmap;
        QLabel::setPixmap(getResizedPixmap());
        setAlignment(Qt::AlignCenter);
    }

    void AutoResizeImageWidget::setPixmap(const QPixmap &pixmap) {
        setPixmap(pixmap, Qt::SmoothTransformation);
    }

    void AutoResizeImageWidget::resizeEvent(QResizeEvent *event) {
        if (!mPixmap.isNull()) {
            QLabel::setPixmap(getResizedPixmap());
        }
    }

    QPixmap AutoResizeImageWidget::getResizedPixmap() {
        return mPixmap.scaled(size(), Qt::KeepAspectRatio, mTransformationMode);
    }
}
