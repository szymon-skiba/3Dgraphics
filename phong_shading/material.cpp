#include "material.h"


PhongMaterial::PhongMaterial(
    const Vector3 &diffuseColor, 
    const Vector3 &matDiffuse,
    const Vector3 &specularColor,
    const Vector3 &matSpecular,
    const Vector3 &ambientColor,
    const Vector3 &matAmbient,
    float exponent,
    int nMeridian,
    int nParallel,
    const Vector3 &lightColor, 
    const Vector3 &lightPos)
: _diffuseColor(diffuseColor), 
  _matDiffuse(matDiffuse),
  _specularColor(specularColor),
  _matSpecular(matSpecular),
  _ambientColor(ambientColor),
  _matAmbient(matAmbient),
  _exponent(exponent),
  _nMeridian(nMeridian),
  _nParallel(nParallel),
  _lightColor(lightColor),
  _lightPos(lightPos) {}
  

Vector3 PhongMaterial::Shade(const Vector3 &position, const Vector3 &normal) const {
    Vector3 N = normal.normalize();
    Vector3 L = (_lightPos - position).normalize();
    Vector3 V = (Vector3(0.0, 0.0, 5.0) - position).normalize();
    Vector3 R = (2 * N.dot(L) * N - L).normalize();

    float lambertian = std::max(N.dot(L), 0.0f);
    float specular = 0.0f;

    if (lambertian > 0.0f) {
        float specAngle = std::max(V.dot(R), 0.0f);
        specular = std::pow(specAngle, _exponent);
    }

    Vector3 ambientComponent = _matAmbient * _ambientColor;
    Vector3 diffuseComponent = _matDiffuse * lambertian * _diffuseColor;
    Vector3 specularComponent = _matSpecular * specular * _specularColor; 

    return ambientComponent + diffuseComponent + specularComponent;
}

void PhongMaterial::changeDiffuseColor(float r, float g, float b) {
    _diffuseColor = Vector3(r / 255.0f, g / 255.0f, b / 255.0f);
}

void PhongMaterial::increaseDiffuse(float increment) {
    _matDiffuse = Vector3(std::min(_matDiffuse.x + increment, 1.0f),
                          std::min(_matDiffuse.y + increment, 1.0f),
                          std::min(_matDiffuse.z + increment, 1.0f));
}

void PhongMaterial::decreaseDiffuse(float decrement) {
    _matDiffuse = Vector3(std::max(_matDiffuse.x - decrement, 0.0f),
                          std::max(_matDiffuse.y - decrement, 0.0f),
                          std::max(_matDiffuse.z - decrement, 0.0f));
}

void PhongMaterial::changeAmbientColor(float r, float g, float b) {
    _ambientColor = Vector3(r / 255.0f, g / 255.0f, b / 255.0f);
}

void PhongMaterial::increaseAmbient(float increment) {
    _matAmbient = Vector3(std::min(_matAmbient.x + increment, 1.0f),
                          std::min(_matAmbient.y + increment, 1.0f),
                          std::min(_matAmbient.z + increment, 1.0f));
}

void PhongMaterial::decreaseAmbient(float decrement) {
    _matAmbient = Vector3(std::max(_matAmbient.x - decrement, 0.0f),
                          std::max(_matAmbient.y - decrement, 0.0f),
                          std::max(_matAmbient.z - decrement, 0.0f));
}

void PhongMaterial::changeSpecularColor(float r, float g, float b) {
    _specularColor = Vector3(r / 255.0f, g / 255.0f, b / 255.0f);
}

void PhongMaterial::increaseSpecular(float increment) {
    _matSpecular = Vector3(std::min(_matSpecular.x + increment, 1.0f),
                           std::min(_matSpecular.y + increment, 1.0f),
                           std::min(_matSpecular.z + increment, 1.0f));
}

void PhongMaterial::decreaseSpecular(float decrement) {
    _matSpecular = Vector3(std::max(_matSpecular.x - decrement, 0.0f),
                           std::max(_matSpecular.y - decrement, 0.0f),
                           std::max(_matSpecular.z - decrement, 0.0f));
}

void PhongMaterial::increaseExponent(float increment) {
    _exponent = std::min(_exponent + increment, 128.0f);
}

void PhongMaterial::decreaseExponent(float decrement) {
    _exponent = std::max(_exponent - decrement, 0.0f);
}

void PhongMaterial::moveLightX(float delta) {
    _lightPos.x += delta;
}

void PhongMaterial::moveLightY(float delta) {
    _lightPos.y += delta;
}

void PhongMaterial::moveLightZ(float delta) {
    _lightPos.z += delta;
}

void PhongMaterial::changeMerPar(int delta){
    _nMeridian = std::max((_nMeridian+delta), 0);
    _nParallel = std::max((_nParallel+delta), 0);
}