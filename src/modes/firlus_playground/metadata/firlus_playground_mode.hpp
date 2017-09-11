#pragma once

#include <mapi/mode.hpp>
#include <QWidget>

namespace fp {

    class FirlusPlaygroundMode : public mapi::Mode, public QObject {
    public:
        virtual void init(QWidget *mainWidget);
        void loadImage();

    private:
    };
}
