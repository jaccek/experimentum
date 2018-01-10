#pragma once

namespace math {

    class Vec3 {
    public:
        Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

        float length();
        void normalize();

        Vec3 operator*(float value);
        Vec3& operator*=(float value);
        Vec3 operator/(float value);
        Vec3& operator/=(float value);

        Vec3 operator+(Vec3 &vector);
        Vec3& operator+=(Vec3 &vector);
        Vec3 operator-(Vec3 &vector);
        Vec3& operator-=(Vec3 &vector);

        float dot(Vec3 &vector);
        Vec3 cross(Vec3 &vector);

        float x, y, z;
    };
}
