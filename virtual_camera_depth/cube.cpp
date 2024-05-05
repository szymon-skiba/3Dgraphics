#include "cube.h"

Cube::Cube(float cx, float cy, float cz, float edgeLength){
    float halfEdge = edgeLength / 2.0f;
    vertices = {
        {cx - halfEdge, cy - halfEdge, cz - halfEdge, 1.0f}, {cx + halfEdge, cy - halfEdge, cz - halfEdge, 1.0f}, {cx + halfEdge, cy + halfEdge, cz - halfEdge, 1.0f}, {cx - halfEdge, cy + halfEdge, cz - halfEdge, 1.0f}, {cx - halfEdge, cy - halfEdge, cz + halfEdge, 1.0f}, {cx + halfEdge, cy - halfEdge, cz + halfEdge, 1.0f}, {cx + halfEdge, cy + halfEdge, cz + halfEdge, 1.0f}, {cx - halfEdge, cy + halfEdge, cz + halfEdge, 1.0f}};

    faces[0] = {0, 1, 2, 3}; // Bottom face
    faces[1] = {4, 5, 6, 7}; // Top face
    faces[2] = {0, 3, 7, 4}; // Left face
    faces[3] = {1, 2, 6, 5}; // Right face
    faces[4] = {0, 1, 5, 4}; // Front face
    faces[5] = {3, 2, 6, 7}; // Back face
}
