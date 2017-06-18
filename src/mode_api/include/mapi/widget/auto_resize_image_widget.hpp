#pragma once

#include <QLabel>

namespace mapi {

    class AutoResizeImageWidget : public QLabel {

    public:
        void setPixmap(const QPixmap &pixmap, Qt::TransformationMode mode);

    public slots:
        void setPixmap(const QPixmap &pixmap);
        void resizeEvent(QResizeEvent *event);

    private:
        QPixmap getResizedPixmap();

    private:
        QPixmap mPixmap;
        Qt::TransformationMode mTransformationMode = Qt::SmoothTransformation;
    };
}
