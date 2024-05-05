#include "transformations.h"
#include <cmath>
#include <stdio.h>

void TransformationManager::moveRight(std::vector<Cube>& cubes) {
    Matrix4x4 translationMatrix = Matrix4x4::translation(-0.05f, 0.0f, 0.0f); 

    for (auto& cube : cubes) {
        for (auto& vertex : cube.vertices) {
            vertex = translationMatrix * vertex;
        }
    }
}

void TransformationManager::moveLeft(std::vector<Cube>& cubes) {
    Matrix4x4 translationMatrix = Matrix4x4::translation(0.05f, 0.0f, 0.0f); 

    for (auto& cube : cubes) {
        for (auto& vertex : cube.vertices) {
            vertex = translationMatrix * vertex;
        }
    }
}
void TransformationManager::moveUp(std::vector<Cube>& cubes) {
    Matrix4x4 translationMatrix = Matrix4x4::translation(0.0f, -0.05f, 0.0f); 

    for (auto& cube : cubes) {
        for (auto& vertex : cube.vertices) {
            vertex = translationMatrix * vertex;
        }
    }
}
void TransformationManager::moveDown(std::vector<Cube>& cubes) {
    Matrix4x4 translationMatrix = Matrix4x4::translation(0.0f, 0.05f, 0.0f);

    for (auto& cube : cubes) {
        for (auto& vertex : cube.vertices) {
            vertex = translationMatrix * vertex;
        }
    }
}

void TransformationManager::moveForward(std::vector<Cube>& cubes) {
    Matrix4x4 translationMatrix = Matrix4x4::translation(0.0f, 0.0f, 0.05f); 

    for (auto& cube : cubes) {
        for (auto& vertex : cube.vertices) {
            vertex = translationMatrix * vertex;
        }
    }
}

void TransformationManager::moveBackward(std::vector<Cube>& cubes) {
    Matrix4x4 translationMatrix = Matrix4x4::translation(0.0f, 0.0f, -0.05f); 

    for (auto& cube : cubes) {
        for (auto& vertex : cube.vertices) {
            vertex = translationMatrix * vertex;
        }
    }
}
void TransformationManager::rotateX(std::vector<Cube>& cubes, float angle) {
    Quaternion rotation = Quaternion::fromAxisAngle(Vector4(-1, 0, 0), angle);
    for (auto& cube : cubes) {
        for (auto& vertex : cube.vertices) {
            Vector4 rotated = rotation.rotate(Vector4(vertex.x, vertex.y, vertex.z));
            vertex.x = rotated.x;
            vertex.y = rotated.y;
            vertex.z = rotated.z;
        }
    }
}

void TransformationManager::rotateY(std::vector<Cube>& cubes, float angle) {
    Quaternion rotation = Quaternion::fromAxisAngle(Vector4(0, -1, 0), angle);
    for (auto& cube : cubes) {
        for (auto& vertex : cube.vertices) {
            Vector4 rotated = rotation.rotate(Vector4(vertex.x, vertex.y, vertex.z));
            vertex.x = rotated.x;
            vertex.y = rotated.y;
            vertex.z = rotated.z;
        }
    }
}


void TransformationManager::rotateZ(std::vector<Cube>& cubes, float angle) {
    Quaternion rotation = Quaternion::fromAxisAngle(Vector4(0, 0, -1), angle);
    for (auto& cube : cubes) {
        for (auto& vertex : cube.vertices) {
            Vector4 rotated = rotation.rotate(Vector4(vertex.x, vertex.y, vertex.z));
            vertex.x = rotated.x;
            vertex.y = rotated.y;
            vertex.z = rotated.z;
        }
    }
}

float cumulativeScaleFactor = 1.0f;
const float minScaleFactor = 1.0f;
const float maxScaleFactor = 3.0f; 

void TransformationManager::zoom(std::vector<Cube>& cubes, float scaleFactor, const Vector4& zoomCenter) {
    
    float newScaleFactor = cumulativeScaleFactor * scaleFactor;
    if (newScaleFactor < minScaleFactor || newScaleFactor > maxScaleFactor) {
        return; 
    }

    cumulativeScaleFactor = newScaleFactor;
    
    Matrix4x4 scaleMatrix;
    scaleMatrix.m[0] = scaleFactor;
    scaleMatrix.m[5] = scaleFactor;
    scaleMatrix.m[10] = 1.0f;
    scaleMatrix.m[15] = 1.0f;

    for (auto& cube : cubes) {
        for (auto& vertex : cube.vertices) {
            Vector4 translated = vertex - Vector4(zoomCenter.x, zoomCenter.y, zoomCenter.z, 0);
            translated = scaleMatrix * translated;
            vertex = translated + Vector4(zoomCenter.x, zoomCenter.y, zoomCenter.z, 0);
        }
    }
}

