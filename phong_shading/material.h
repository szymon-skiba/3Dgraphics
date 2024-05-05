#ifndef PHONG_MATERIAL_H
#define PHONG_MATERIAL_H

#include <algorithm> 
#include <cmath>     

#include "vector3.h"  

class PhongMaterial {
public:
    Vector3 _diffuseColor;
    Vector3 _matDiffuse;
    Vector3 _specularColor;
    Vector3 _matSpecular;
    Vector3 _ambientColor;
    Vector3 _matAmbient;
    float _exponent;
    int _nMeridian;
    int _nParallel;
    Vector3 _lightColor;
    Vector3 _lightPos;

    PhongMaterial(
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
        const Vector3 &lightPos);

    Vector3 Shade(const Vector3 &position, const Vector3 &normal) const;

    Vector3 getDiffuseColor() const { return _diffuseColor; }
    Vector3 getMatDiffuse() const { return _matDiffuse; }
    Vector3 getSpecularColor() const { return _specularColor; }
    Vector3 getMatSpecular() const { return _matSpecular; }
    Vector3 getAmbientColor() const { return _ambientColor; }
    Vector3 getMatAmbient() const { return _matAmbient; }
    float getExponent() const { return _exponent; }
    Vector3 getLightPosition() const { return _lightPos; }
    int getNmeridian() const { return _nMeridian; }
    int getNparallel() const { return _nParallel; }

    void changeDiffuseColor(float r, float g, float b);
    void increaseDiffuse(float increment);
    void decreaseDiffuse(float decrement);
    void changeAmbientColor(float r, float g, float b);
    void increaseAmbient(float increment);
    void decreaseAmbient(float decrement);
    void changeSpecularColor(float r, float g, float b);
    void increaseSpecular(float increment);
    void decreaseSpecular(float decrement);
    void increaseExponent(float increment);
    void decreaseExponent(float decrement);
    void moveLightX(float delta);
    void moveLightY(float delta);
    void moveLightZ(float delta);
    void changeMerPar(int delta);
};

#endif // PHONG_MATERIAL_H
