#pragma once
#include <string>
#include <Glew/include/gl/glew.h>
#include <glm/glm.hpp>
#include <vector>
//#include "Utils.h"
//#include "../Obj Parser/wavefront_obj.h"
#include "Camera.h"
//#include <glm/ext/matrix_float4x4.hpp>
#include "MeshLoader.h"
#include "TriangleMesh.h"
#include "Object.h"
//#include "Mathlib.h"
//#include "Light.h"

class Scene {
public:
	bool loadModel(const std::wstring& filename, Shader* meshShader, Shader* lineShader, Shader* grouaudShader);
	void draw(const glm::mat4& objectMatrix, const glm::mat4& worldMatrix, const glm::mat4& projection, const glm::mat4& view, float scale);
	void initializeScene();
	// Loading of the model from a file
	//void draw(const glm::mat4& rotation, const glm::mat4& translation, const glm::mat4& projection);          // Render the scene with the given view-projection matrix
	void initSceneWithCube(Shader* shader);
	void toggleNormals(bool show);
	void toggleBBox(bool show);

	void updateCameraMatrices();

	void updateMaterial();

	void updateLight();
	
	std::vector<Vertex> convertNormalsToLine(const std::vector<Vertex>& vertices);

	Object& getObject() { return _object; }
	Camera& getCamera() { return _camera; }
	
	//  Light Managment
	const Light& getLight1() const { return _light1; }
	const Light& getLight2() const { return _light2; }
	const glm::vec3 getAmbientLight() const { return _ambientLight; }

private:

	Object _object;
	Camera _camera;
	bool _isCube = true;
	bool _showNormals = false;
	bool _showBBox = false;

	Light _light1, _light2;
	glm::vec3 _ambientLight;

};


