#pragma once

#include <QWidget>

namespace mapi {
    class Mode {
    public:
        virtual ~Mode() {}

        virtual void init(QWidget *mainWidget) = 0;
    };
}
