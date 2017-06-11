#include "euclides_hsv_metric.hpp"

#include <QMatrix4x4>

namespace pix {

    EuclidesHsvMetric::~EuclidesHsvMetric() {
    }

    std::string EuclidesHsvMetric::name() {
        return "Euclides HSV Metric";
    }

    float EuclidesHsvMetric::distance(mapi::Color &first, mapi::Color &second) {
        QVector3D firstVector = convertColorToVector(first);
        QVector3D secondVector = convertColorToVector(second);

        return firstVector.distanceToPoint(secondVector);
    }

    QVector3D EuclidesHsvMetric::convertColorToVector(mapi::Color &color) {
        QVector3D vector(color.sf(), color.vf(), 0.0f);
        QMatrix4x4 rotation;
        rotation.rotate(color.hf(), 0.0f, 1.0f, 0.0f);

        return vector * rotation;
    }
}
