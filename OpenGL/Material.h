#pragma once
#pragma once
#include <glm/glm.hpp>

class Material {
public:
    Material();

    // Constructor
    Material(float a, float d, float s, float sh, glm::vec3 color, bool doubleSided);

    // Getters and setters
    float getAmbient() const { return _ambient; }
    void setAmbient(float a) { _ambient = a; }
    float getDiffuse() const { return _diffuse; }
    void setDiffuse(float d) { _diffuse = d; }
    float getSpecular() const { return _specular; }
    void setSpecular(float s) { _specular = s; }
    float getShininess() const { return _shininess; }
    void setShininess(float sh) { _shininess = sh; }
    glm::vec3 getBaseColor() const { return _baseColor; }
    void setBaseColor(const glm::vec3& color) { _baseColor = color; }
    bool isDoubleSided() const { return _doubleSided; }
    void setDoubleSided(bool ds) { _doubleSided = ds; }

private:
    float _ambient;   // k_a
    float _diffuse;   // k_d
    float _specular;  // k_s
    float _shininess; // specular exponent for highlights
    glm::vec3 _baseColor; // RGB base color of the material
    bool _doubleSided;    // whether lighting is double-sided

};