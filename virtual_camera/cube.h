#ifndef CUBE_H
#define CUBE_H

#include <vector>

struct Vector4 {
    float x, y, z, w;
    Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : x(x), y(y), z(z), w(w) {}
    Vector4 operator+(const Vector4& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vector4 operator-(const Vector4& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }
};

class Cube {
public:
    std::vector<Vector4> vertices;

    Cube(float cx, float cy, float cz, float edgeLength);
};

#endif 