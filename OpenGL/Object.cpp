#include "Object.h"
#include "MathLib.h"
#include <iostream>
#include "common_glm_config.h"
#include <glm/gtx/string_cast.hpp> 

Object::Object() : _meshLoader() {};

bool Object::loadMesh(const std::wstring& filePath) {
	if (!_meshLoader.uploadFrom(filePath)) {
		return false;
	}
	return true;
}
void Object::draw(const glm::mat4& rotation, const glm::mat4& translation, const glm::mat4& projection, const float scale) {
	if (_meshDrawer) {
		_meshDrawer->draw(rotation, translation, projection, scale);
	}
	else {
		std::cerr << "[Object::draw] No mesh drawer set. Cannot draw object." << std::endl;
	}
}

void Object::clear() {
	_meshLoader.reset();
}

void Object::buildMeshDrawerFromLoader(Shader* shader) {
	setMeshDrawer(std::make_unique<TriangleMesh>(
		_meshLoader.getVertices(),
		_meshLoader.getIndices(),
		shader));
}