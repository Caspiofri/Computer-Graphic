
#include "Renderer.h"
#include "Utils/Utils.h"
#include "Utils/wavefront_obj.h"
#include "Scene.h"
#include "Shader.h"
#include "Renderer.h"
#include "TriangleMesh.h"
#include "Settings.h"
#include <iostream>
#include <string>

void Renderer::initScene() {
	std::cout << "\n-- Renderer::initScene: starting .. -- ";

	setTriangleShader(new Shader("..\\Shaders\\vertexShader.glsl", "..\\Shaders\\fragmentShader.glsl"));

	if (!_triangleShader->getID())
	{
		std::cout << "\nFatal Error in shader creation!\n\a\a\a";
		return;
	}
	
	std::cout << "\n -- Step 1 : Done!  ";
	std::cout << "\n-- Step 2 : init Scene With Cube .. -- ";
	_scene.initSceneWithCube(_triangleShader);

}

bool Renderer::loadModelToScene(const std::wstring& filename) {
	std::wcout << "[Renderer::loadModelToScene] loading model from file: " << filename << std::endl;
	if (!_triangleShader || !_triangleShader->getID())
	{
		std::cerr << "[Renderer::loadModelToScene] Shader not initialized or invalid." << std::endl;
		return false;
	}
	bool result = _scene.loadModel(filename, _triangleShader);
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

	glm::mat4x4 mat_rotation;
	ConvertQuaternionToMatrix(Settings::_quaternion, mat_rotation);

	glm::mat4x4 mat_translation;
	createTranslationMatrix(0.0f, 0.0f, -5.0f, mat_translation);

	glm::mat4x4 mat_projection;

	const float nearPlane = 1.0f;
	const float farPlane = 1000.0f;
	float top = 0.0f;
	float right = 0.0f;

	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	float aspectRatio = (float)width / (float)height;
	if (width > height)
	{
		top = 0.25f;
		right = aspectRatio * top;
	}
	else
	{
		right = 0.25f;
		top = right / aspectRatio;
	}

	createPerspectiveProjectionMatrix(nearPlane, farPlane, right, top, mat_projection);



	if (_isMeshLoaded)
	{
		std::cout << "[drawScene]: _isMeshLoaded is true... " << std::endl;

		// Bind the VAO of the mesh
		_scene.draw(mat_rotation, mat_translation, mat_projection, Settings::_scale);

		std::cout << "[drawScene]: draw mesh executed !" << std::endl;

	}
	else
	{
		std::cout << "[drawScene]: no mesh loaded - rendering cube ... " << std::endl;
		// If no mesh is loaded, draw a default cube
		int numIndices = 36; // 6 faces * 2 triangles per face * 3 indices per triangle
		std::cout << "[drawScene]: calling initSceneWithCube" << std::endl;
		_scene.initSceneWithCube(_triangleShader);

		std::cout << "[drawScene]: calling draw scene" << std::endl;
		_scene.draw(mat_rotation, mat_translation, mat_projection , Settings::_scale);
	}

	// Unbind the shader program after drawing
	glUseProgram(0);

}