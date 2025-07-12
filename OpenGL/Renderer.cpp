
#include "Renderer.h"
#include "Utils/Utils.h"
#include "Utils/wavefront_obj.h"
#include "Scene.h"
#include "Shader.h"
#include "Renderer.h"
#include "TriangleMesh.h"
#include "common_glm_config.h"
#include "Settings.h"
#include <iostream>
#include <string>
#include <glm/gtx/string_cast.hpp>

void Renderer::initScene() {
	std::cout << "\n-- Renderer::initScene: starting .. -- ";

	setTriangleShader(new Shader("..\\Shaders\\vertexShader.glsl", "..\\Shaders\\fragmentShader.glsl"));

	if (!_triangleShader->getID())
	{
		std::cout << "\nFatal Error in Triangle shader creation!\n\a\a\a";
		return;
	}
	setLineShader(new Shader("lineVertexShader.glsl", "lineFragmentShader.glsl"));
	if (!_lineShader->getID())
	{
		std::cout << "\nFatal Error in Line shader creation!\n\a\a\a";
		return;
	}
	
	std::cout << "\n -- Step 1 : Done!  ";
	std::cout << "\n-- Step 2 : init Scene With Cube .. -- ";
	_scene.initializeScene();
	_scene.initSceneWithCube(_triangleShader);

}

bool Renderer::loadModelToScene(const std::wstring& filename) {
	std::wcout << "[Renderer::loadModelToScene] loading model from file: " << filename << std::endl;
	if (!_triangleShader || !_triangleShader->getID() || !_lineShader->getID())
	{
		std::cerr << "[Renderer::loadModelToScene] Shader not initialized or invalid." << std::endl;
		return false;
	}
	bool result = _scene.loadModel(filename, _triangleShader , _lineShader);
	if (result)
	{
		std::cout << "[Renderer::loadModelToScene] Model loaded successfully." << std::endl;
		_isMeshLoaded = true;
	}
	else
	{
		std::cerr << "[Renderer::loadModelToScene] Failed to load model." << std::endl;
	}
	return result;
}

void Renderer::drawScene()
{
	std::cerr << "[drawScene] starting .. " << std::endl;

	if (!_triangleShader->getID())
	{
		std::cerr << "[drawScene] no triangleShader id.. exiting .. " << std::endl;
		return;
	}

	//update object local transform
	getScene().getObject().UpdateObjectLocalTransform();
	getScene().getObject().UpdateWorldTransform();

	//get object matrix
	glm::mat4x4 objectMatrix;
	glm::mat4x4 worldMatrix;
	objectMatrix = getScene().getObject().getObjectMatrix();
	worldMatrix = getScene().getObject().getWorldMatrix();
	
	glm::mat4x4 mat_projection;
	glm::mat4x4 mat_view;

	getScene().updateCameraMatrices();

	mat_projection = getScene().getCamera().getProjectionMatrix();
	mat_view = getScene().getCamera().getViewMatrix();
	
	if (_isMeshLoaded)
	{
		std::cout << "[drawScene]: _isMeshLoaded is true... " << std::endl;

	}
	else
	{
		std::cout << "[drawScene]: no mesh loaded - rendering cube ... " << std::endl;
		// If no mesh is loaded, draw a default cube
		int numIndices = 36; // 6 faces * 2 triangles per face * 3 indices per triangle
		std::cout << "[drawScene]: calling initSceneWithCube" << std::endl;
		_scene.initSceneWithCube(_triangleShader);
	}
	//_scene.draw(mat_rotation, mat_translation, mat_projection, Settings::_scale);
	_scene.draw(objectMatrix, worldMatrix, mat_projection, mat_view, Settings::_scale);

	std::cout << "[drawScene]: draw mesh executed !" << std::endl;
	// Unbind the shader program after drawing
	glUseProgram(0);

}