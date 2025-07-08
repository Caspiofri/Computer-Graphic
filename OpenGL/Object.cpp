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

	//_objectMatrix = _objectTranslationMatrix * _objectRotationMatrix;
	_objectMatrix = _objectRotationMatrix * _objectTranslationMatrix;

	std::cerr << "[ApplyTransformations] _objectTranslationMatrix:\n" << glm::to_string(_objectTranslationMatrix) << std::endl;
	std::cerr << "[ApplyTransformations] _objectRotationMatrix:\n" << glm::to_string(_objectRotationMatrix) << std::endl;
	std::cerr << "[ApplyTransformations] _objectMatrix:\n" << glm::to_string(_objectMatrix) << std::endl;
}
void Object::ApplyWorldTransformations() {
	std::cout << "ApplyTransformations called!" << std::endl;
	// the call order is row vector, cause of the shader

	//_objectMatrix = _objectTranslationMatrix * _objectRotationMatrix;
	_worldMatrix = _worldRotationMatrix * _worldTranslationMatrix;

	std::cerr << "[ApplyWorldTransformations] _worldRotationMatrix:\n" << glm::to_string(_worldRotationMatrix) << std::endl;
	std::cerr << "[ApplyWorldTransformations] _worldTranslationMatrix:\n" << glm::to_string(_worldTranslationMatrix) << std::endl;
	std::cerr << "[ApplyWorldTransformations] _worldMatrix:\n" << glm::to_string(_worldMatrix) << std::endl;
}

void Object::UpdateObjectLocalTransform() 
{
	glm::vec3 t(Settings::_objTransX, Settings::_objTransY, Settings::_objTransZ);
	//glm::vec3 r(Settings::_objRotX, Settings::_objRotY, Settings::_objRotZ);
	float s = static_cast<float>(Settings::_scale);

	clearObjTransformations();
	translate(t);
	rotate();
	scale(glm::vec3(s));
	ApplyTransformations();

}
void Object::UpdateWorldTransform()
{
	std::cerr << "Settings::_worldTransX = " << Settings::_worldTransX << std::endl;
	std::cerr << "Settings::_worldTransY = " << Settings::_worldTransY << std::endl;
	std::cerr << "Settings::_worldTransZ = " << Settings::_worldTransZ << std::endl;
	glm::vec3 t(Settings::_worldTransX, Settings::_worldTransY, Settings::_worldTransZ);

	clearWorldTransformations();
	std::cerr << "[UpdateWorldTransform] translateWorld:\n" << glm::to_string(t) << std::endl;

	translateWorld(t);
	std::cerr << "[UpdateWorldTransform] translateWorld:\n" << glm::to_string(_worldTranslationMatrix) << std::endl;

	rotateWorld();
	ApplyWorldTransformations();

}


void Object::translate(glm::vec3 translation) {
	glm::mat4 translationMatrix = glm::mat4(1.0f);
	translationMatrix = MathLib::translation(translation);
	_objectTranslationMatrix = translationMatrix * _objectTranslationMatrix;
	//ApplyTransformations();
}

void Object::rotate() {
	ConvertQuaternionToMatrix(Settings::_objQuaternion, _objectRotationMatrix);
	//ApplyTransformations();
}

void Object::translateWorld(glm::vec3 translation) {
	std::cerr << "[translateWorld] worldMatrix:\n" << glm::to_string(translation) << std::endl;

	glm::mat4 translationMatrix = glm::mat4(1.0f);
	translationMatrix = MathLib::translation(translation);
	std::cerr << "[translateWorld] worldMatrix:\n" << glm::to_string(translationMatrix) << std::endl;
	_worldTranslationMatrix = translationMatrix * _worldTranslationMatrix;
	//ApplyTransformations();
}

void Object::rotateWorld() {
	ConvertQuaternionToMatrix(Settings::_worldQuaternion, _worldRotationMatrix);
	std::cerr << "[rotateWorld] _worldRotationMatrix:\n" << glm::to_string(_worldRotationMatrix) << std::endl;

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

void Object::setWorldMatrix(const glm::mat4& mat)
{
	_worldMatrix = mat;
}
const glm::mat4& Object::getWorldMatrix() const {
	return _worldMatrix;
}

bool Object::loadMesh(const std::wstring& filePath) {
	if (!_meshLoader.uploadFrom(filePath)) {
		return false;
	}
	return true;
}
void Object::draw(const glm::mat4& objectMatrix, const glm::mat4& worldMatrix, const glm::mat4& view, const glm::mat4& projection , float scale) {
	//std::cerr << "[Object]:calling UpdateObjectLocalTransform" << std::endl;

	//UpdateObjectLocalTransform();
	if (_meshDrawer) {
	
		std::cerr << "[Object::draw] matrices before drawing: " << std::endl;
		std::cerr << "[Object::draw] projection:\n" << glm::to_string(projection) << std::endl;
		std::cerr << "[Object::draw] view:\n" << glm::to_string(view) << std::endl;
		std::cerr << "[Object::draw] worldMatrix:\n" << glm::to_string(worldMatrix) << std::endl;
		std::cerr << "[Object::draw] objectMatrix:\n" << glm::to_string(objectMatrix) << std::endl;
		_meshDrawer->draw(objectMatrix, worldMatrix,view, projection, scale);
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