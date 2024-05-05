#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <array>

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
    std::array<std::vector<int>, 6> faces;

    Cube(float cx, float cy, float cz, float edgeLength);

    Vector4 faceCenter(int faceIndex) const {
        Vector4 center;
        for (int idx : faces[faceIndex]) {
            center = center + vertices[idx];
        }
        center = Vector4(center.x / 4, center.y / 4, center.z / 4, 1.0);
        return center;
    }
};

#endif 