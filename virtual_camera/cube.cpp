#include "cube.h"

Cube::Cube(float cx, float cy, float cz, float edgeLength) {
    float halfEdge = edgeLength / 2.0f;
    vertices = {
        {cx - halfEdge, cy - halfEdge, cz - halfEdge, 1.0f}, {cx + halfEdge, cy - halfEdge, cz - halfEdge, 1.0f},
        {cx + halfEdge, cy + halfEdge, cz - halfEdge, 1.0f}, {cx - halfEdge, cy + halfEdge, cz - halfEdge, 1.0f},
        {cx - halfEdge, cy - halfEdge, cz + halfEdge, 1.0f}, {cx + halfEdge, cy - halfEdge, cz + halfEdge, 1.0f},
        {cx + halfEdge, cy + halfEdge, cz + halfEdge, 1.0f}, {cx - halfEdge, cy + halfEdge, cz + halfEdge, 1.0f}
    };
}
