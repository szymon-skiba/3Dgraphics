#include "cube.h"
#include <cmath>
#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

struct Matrix4x4 {
    float m[16];

    Matrix4x4() {
        for (int i = 0; i < 16; ++i) m[i] = 0.0f;
        m[0] = m[5] = m[10] = m[15] = 1.0f;
    }

    Vector4 operator*(const Vector4& v) const {
        return Vector4(
            m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12] * v.w,
            m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13] * v.w,
            m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14] * v.w,
            m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15] * v.w
        );
    }
    
    static Matrix4x4 translation(float tx, float ty, float tz) {
        Matrix4x4 result;
        result.m[12] = tx;
        result.m[13] = ty;
        result.m[14] = tz;
        return result;
    }
};

struct Quaternion {
    float w, x, y, z;

    Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

    static Quaternion fromAxisAngle(const Vector4& axis, float angle) {
        float halfAngle = angle / 2.0f;
        float s = sin(halfAngle);
        return Quaternion(cos(halfAngle), axis.x * s, axis.y * s, axis.z * s);
    }

    Quaternion conjugate() const {
        return Quaternion(w, -x, -y, -z);
    }

    Quaternion operator*(const Quaternion& q) const {
        return Quaternion(
            w * q.w - x * q.x - y * q.y - z * q.z,
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w);
    }

    Vector4 rotate(const Vector4& v) const {
        Quaternion qv(0, v.x, v.y, v.z);
        Quaternion qr = (*this) * qv * conjugate();
        return Vector4(qr.x, qr.y, qr.z);
    }
};

class TransformationManager {
public:
    //simple translations
    static void moveRight(std::vector<Cube>& cubes);
    static void moveLeft(std::vector<Cube>& cubes);
    static void moveUp(std::vector<Cube>& cubes);
    static void moveDown(std::vector<Cube>& cubes);
    static void moveForward(std::vector<Cube>& cubes);
    static void moveBackward(std::vector<Cube>& cubes);

    //rest
    static void rotateX(std::vector<Cube>& cubes, float angle);
    static void rotateY(std::vector<Cube>& cubes, float angle);
    static void rotateZ(std::vector<Cube>& cubes, float angle);
    static void zoom(std::vector<Cube>& cubes, float scaleFactor,const Vector4& zoomCenter);
};

#endif