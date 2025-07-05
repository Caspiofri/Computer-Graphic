#include "Object.h"
#include "MathLib.h"
#include "Utils/Utils.h"
#include <iostream>
#include "common_glm_config.h"
#include "Settings.h"
#include <glm/gtx/string_cast.hpp> 

Object::Object() : _meshLoader() {};

void Object::ApplyTransformations() {
	std::cout << "ApplyTransformations called!" << std::endl;
	// the call order is row vector, cause of the shader


	_objectMatrix = _objectTranslationMatrix * _objectRotationMatrix * _objectScaleMatrix;

	std::cerr << "[ApplyTransformations] _objectMatrix:\n" << glm::to_string(_objectTranslationMatrix) << std::endl;
	std::cerr << "[ApplyTransformations] worldMatrix:\n" << glm::to_string(_objectRotationMatrix) << std::endl;
	std::cerr << "[ApplyTransformations] rotation:\n" << glm::to_string(_objectScaleMatrix) << std::endl;
	std::cerr << "[ApplyTransformations] rotation:\n" << glm::to_string(_objectMatrix) << std::endl;


}

void Object::UpdateObjectLocalTransform() 
{
	glm::vec3 t(Settings::_objTransX, Settings::_objTransY, Settings::_objTransZ);
	//glm::vec3 r(Settings::_objRotX, Settings::_objRotY, Settings::_objRotZ);
	float s = static_cast<float>(Settings::_scale);

	clearTransformations();
	translate(t);
	rotate();
	scale(glm::vec3(s));
	ApplyTransformations();

}

void Object::translate(glm::vec3 translation) {
	glm::mat4 translationMatrix = glm::mat4(1.0f);
	translationMatrix = MathLib::translation(translation);
	_objectTranslationMatrix = translationMatrix * _objectTranslationMatrix;
	//ApplyTransformations();
}

void Object::rotate() {
	ConvertQuaternionToMatrix(Settings::_quaternion, _objectRotationMatrix);
	//ApplyTransformations();
}
void Object::scale(glm::vec3 scaleFactor) {
	_objectScaleMatrix = MathLib::scaling(scaleFactor);
	ApplyTransformations();
}

void Object::setObjectMatrix(const glm::mat4& mat)
{
	_objectMatrix = mat;
}
const glm::mat4& Object::getObjectMatrix() const {
	return _objectMatrix;
}

bool Object::loadMesh(const std::wstring& filePath) {
	if (!_meshLoader.uploadFrom(filePath)) {
		return false;
	}
	return true;
}
void Object::draw(const glm::mat4& rotation, const glm::mat4& translation, const glm::mat4& projection, const float scale) {
	//std::cerr << "[Object]:calling UpdateObjectLocalTransform" << std::endl;

	//UpdateObjectLocalTransform();
	if (_meshDrawer) {
	
		glm::mat4 worldMatrix = glm::mat4(1.0f);
		std::cerr << "[Object::draw] matrices before drawing: " << std::endl;
		std::cerr << "[Object::draw] _objectMatrix:\n" << glm::to_string(_objectMatrix) << std::endl;
		std::cerr << "[Object::draw] worldMatrix:\n" << glm::to_string(worldMatrix) << std::endl;
		std::cerr << "[Object::draw] rotation:\n" << glm::to_string(rotation) << std::endl;
		std::cerr << "[Object::draw] new translation:\n" << glm::to_string(translation) << std::endl;
		std::cerr << "[Object::draw] projection:\n" << glm::to_string(projection) << std::endl;
		std::cerr << "[Object::draw] scale: " << scale << std::endl;
		_meshDrawer->draw(rotation, translation, projection,worldMatrix,_objectMatrix, scale);
	}
	else {
		std::cerr << "[Object::draw] No mesh drawer set. Cannot draw object." << std::endl;
	}
}

void Object::clear() {
	_meshLoader.reset();
	_meshDrawer.reset();
	_objectTranslationMatrix = glm::mat4(1.0f);
	_objectRotationMatrix = glm::mat4(1.0f);
	_objectScaleMatrix = glm::mat4(1.0f);
	_objectMatrix = glm::mat4(1.0f);
}

void Object::buildMeshDrawerFromLoader(Shader* shader) {
	setMeshDrawer(std::make_unique<TriangleMesh>(
		_meshLoader.getVertices(),
		_meshLoader.getIndices(),
		shader));
}