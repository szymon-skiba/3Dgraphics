#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath> // Include for sqrt function

struct Vector3 {
    float x, y, z;

    Vector3(float _x = 0.0, float _y = 0.0, float _z = 0.0) : x(_x), y(_y), z(_z) {}

    Vector3 operator-(const Vector3& v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 normalize() const {
        float len = sqrt(x * x + y * y + z * z);
        return Vector3(x / len, y / len, z / len);
    }

    float dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 operator*(const Vector3& v) const {
        return Vector3(x * v.x, y * v.y, z * v.z);
    }

    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    friend Vector3 operator*(float scalar, const Vector3& v) {
        return Vector3(scalar * v.x, scalar * v.y, scalar * v.z);
    }
};

#endif // VECTOR3_H
