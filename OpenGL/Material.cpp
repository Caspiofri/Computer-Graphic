#include "Material.h"

#include <iostream>


Material::Material()
	: _ambient(0.0f), _diffuse(0.0f), _specular(0.0f), _shininess(0.0f),
	_baseColor(1.0f, 1.0f, 1.0f), _doubleSided(false) {
}
Material::Material(float a, float d, float s, float sh, glm::vec3 color, bool doubleSided)
	: _ambient(a), _diffuse(d), _specular(s), _shininess(sh),
	_baseColor(color), _doubleSided(doubleSided) {
}