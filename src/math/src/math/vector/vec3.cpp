#include <math/vector/vec3.hpp>
#include <cmath>

namespace math {

    Vec3::Vec3(float x, float y, float z): x(x), y(y), z(z) {
    }

    float Vec3::length() {
        return sqrt(x*x + y*y + z*z);
    }

    void Vec3::normalize() {
        auto length = this->length();
        x /= length;
        y /= length;
        z /= length;
    }
}
