#include "Object.h"
#include "MathLib.h"
#include "Utils/Utils.h"
#include <iostream>
#include "common_glm_config.h"
#include "Settings.h"
#include <glm/gtx/string_cast.hpp> 

Object::Object() : _meshLoader() {};

void Object::ApplyTransformations() {
	// the call order is row vector, cause of the shader

	//_objectMatrix = _objectTranslationMatrix * _objectRotationMatrix;
	_objectMatrix = _objectRotationMatrix * _objectTranslationMatrix;
}
void Object::ApplyWorldTransformations() {
	// the call order is row vector, cause of the shader

	//_objectMatrix = _objectTranslationMatrix * _objectRotationMatrix;
	_worldMatrix = _worldRotationMatrix * _worldTranslationMatrix;
}

void Object::UpdateObjectLocalTransform() 
{
	glm::vec3 t(Settings::_objTransX, Settings::_objTransY, Settings::_objTransZ);
	float s = static_cast<float>(Settings::_scale);

	clearObjTransformations();
	translateObj(t);
	rotateObj();
	scale(glm::vec3(s));
	ApplyTransformations();

}
void Object::UpdateWorldTransform()
{
	glm::vec3 t(Settings::_worldTransX, Settings::_worldTransY, Settings::_worldTransZ);

	clearWorldTransformations();
	translateWorld(t);

	rotateWorld();
	ApplyWorldTransformations();

}

// Calculations for object metrics
void Object::translateObj(glm::vec3 translation) {
	glm::mat4 translationMatrix = glm::mat4(1.0f);
	translationMatrix = MathLib::translation(translation);
	_objectTranslationMatrix = translationMatrix * _objectTranslationMatrix;
}

void Object::rotateObj() {
	ConvertQuaternionToMatrix(Settings::_objQuaternion, _objectRotationMatrix);
}

void Object::scale(glm::vec3 scaleFactor) {
	_objectScaleMatrix = MathLib::scaling(scaleFactor);
	ApplyTransformations();
}


// World Calculations for world metrics
void Object::translateWorld(glm::vec3 translation) {

	glm::mat4 translationMatrix = glm::mat4(1.0f);
	translationMatrix = MathLib::translation(translation);
	_worldTranslationMatrix = translationMatrix * _worldTranslationMatrix;
	//ApplyTransformations();
}

void Object::rotateWorld() {
	ConvertQuaternionToMatrix(Settings::_worldQuaternion, _worldRotationMatrix);

	//ApplyTransformations();
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
void Object::draw(const glm::mat4& objectMatrix, const glm::mat4& worldMatrix, const glm::mat4& view, const glm::mat4& projection , const float scale, const glm::vec3 cameraPos){

	switch(Settings::_shadingMode) {
		case SIMPLE: {
			_meshDrawer->draw(objectMatrix, worldMatrix, view, projection, scale);
			break;
		}
		case GOURAUD: {
			_gouraudSet->setCameraPos(cameraPos);
			_gouraudSet->draw(objectMatrix, worldMatrix, view, projection, scale);
			break;
		}
		/*case PHONG: {
			_bboxDrawer->draw(objectMatrix, worldMatrix, view, projection, scale);
			break;
		}*/
	}
	
}

void Object::clear() {
	_meshLoader.reset();
	_meshDrawer.reset();
	_normalsDrawer.reset();
	_bboxDrawer.reset();
	_objectTranslationMatrix = glm::mat4(1.0f);
	_objectRotationMatrix = glm::mat4(1.0f);
	_objectScaleMatrix = glm::mat4(1.0f);
	_objectMatrix = glm::mat4(1.0f);
}
