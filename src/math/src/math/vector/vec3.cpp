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
        *this /= length;
    }

    Vec3 Vec3::operator*(float value) {
        return Vec3(x * value, y * value, z * value);
    }

    Vec3& Vec3::operator*=(float value) {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    Vec3 Vec3::operator/(float value) {
        return Vec3(x / value, y / value, z / value);
    }

    Vec3& Vec3::operator/=(float value) {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    Vec3 Vec3::operator+(Vec3 &vector) {
        return Vec3(x + vector.x, y + vector.y, z + vector.z);
    }

    Vec3& Vec3::operator+=(Vec3 &vector) {
        x += vector.x;
        y += vector.y;
        z += vector.z;
        return *this;
    }

    Vec3 Vec3::operator-(Vec3 &vector) {
        return Vec3(x - vector.x, y - vector.y, z - vector.z);
    }

    Vec3& Vec3::operator-=(Vec3 &vector) {
        x -= vector.x;
        y -= vector.y;
        z -= vector.z;
        return *this;
    }

    float Vec3::dot(Vec3 &vector) {
        return x * vector.x + y * vector.y + z * vector.z;
    }

    Vec3 Vec3::cross(Vec3 &vector) {
        // a2b3−a3b2; a3b1−a1b3; a1b2−a2b1
        return Vec3(y*vector.z - z*vector.y, z*vector.x - x*vector.z, x*vector.y - y*vector.x);
    }
}
