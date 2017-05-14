#pragma once

#include <QLabel>

namespace mapi {

    class AutoResizeImageWidget : public QLabel {

    public slots:
        void setPixmap(const QPixmap &pixmap);
        void resizeEvent(QResizeEvent *event);

    private:
        QPixmap getResizedPixmap();

    private:
        QPixmap mPixmap;
    };
}
