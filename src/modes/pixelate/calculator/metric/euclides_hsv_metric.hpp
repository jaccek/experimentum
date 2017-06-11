#pragma once

#include "calculator/metric/metric.hpp"
#include <QVector3D>

namespace pix {

    class EuclidesHsvMetric : public Metric {
    public:
        virtual ~EuclidesHsvMetric();

        virtual std::string name();

        virtual float distance(mapi::Color &first, mapi::Color &second);

    private:
        QVector3D convertColorToVector(mapi::Color &color);
    };
}
