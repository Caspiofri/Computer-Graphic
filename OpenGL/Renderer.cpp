
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

GLuint Renderer::loadTextureFromFile(const std::wstring& filename) {
	GLuint textureID = getScene().getObject().getTextureID();
	if (textureID)
	{
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}
	BYTE* imageRawData = 0;
	unsigned int imageWidth = 0;
	unsigned int imageHeight = 0;
	FREE_IMAGE_FORMAT format = FreeImage_GetFileTypeU(filename.c_str(), 0);
	if (format == FIF_UNKNOWN) {
		format = FreeImage_GetFIFFromFilenameU(filename.c_str());
	}
	if (format == FIF_UNKNOWN || !FreeImage_FIFSupportsReading(format)) {
		std::cout << "Unknown image format!\n";
		return 0;
	}
	FIBITMAP* bitmap = FreeImage_LoadU(format, filename.c_str());
	if (!bitmap) {
		std::cout << "Failed to load image: " << filename.c_str() << "\n";
		return 0;
	}
	FIBITMAP* image = FreeImage_ConvertTo32Bits(bitmap);
	FreeImage_Unload(bitmap);
	if (!image) {
		std::cout << "Failed to convert image: " << filename.c_str() << "\n";
		return 0;
	}
	imageRawData = (BYTE*)FreeImage_GetBits(image);
	imageWidth = FreeImage_GetWidth(image);
	imageHeight = FreeImage_GetHeight(image);
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, imageRawData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	FreeImage_Unload(image);
	return textureID;
}

void Renderer::initScene() {

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
	setGrouaudShader(new Shader("gouraudVertexShader.glsl", "gouraudFragmentShader.glsl"));
	if (!_gouraudShader->getID())
	{
		std::cout << "\nFatal Error in Line shader creation!\n\a\a\a";
		return;
	}
	setPhongShader(new Shader("phongVertexShader.glsl", "phongFragmentShader.glsl"));
	if (!_lineShader->getID())
	{
		std::cout << "\nFatal Error in Line shader creation!\n\a\a\a";
		return;
	}
	_scene.initializeScene(_lineShader);
	_scene.initSceneWithCube(_triangleShader);

}


bool Renderer::loadModelToScene(const std::wstring& filename) {
	if (filename.empty() || filename.find(L".obj") == std::wstring::npos) {
		std::cerr << "[Renderer::loadModelToScene] Invalid file name." << std::endl;
		return false;
	}
	if (!_triangleShader || !_triangleShader->getID() || !_lineShader->getID())
	{
		std::cerr << "[Renderer::loadModelToScene] Shader not initialized or invalid." << std::endl;
		return false;
	}
	bool result = _scene.loadModel(filename, _triangleShader , _lineShader , _gouraudShader , _phongShader);
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

	if (!_triangleShader->getID())
	{
		std::cerr << "[drawScene] no triangleShader id.. exiting .. " << std::endl;
		return;
	}

	//update object local transform
	getScene().getObject().UpdateObjectLocalTransform();
	getScene().getObject().UpdateWorldTransform();

	//get object matrix
	glm::mat4x4 objectMatrix, worldMatrix, mat_projection , mat_view;
	objectMatrix = getScene().getObject().getObjectMatrix();
	worldMatrix = getScene().getObject().getWorldMatrix();

	getScene().updateCameraMatrices();

	mat_projection = getScene().getCamera().getProjectionMatrix();
	mat_view = getScene().getCamera().getViewMatrix();
	
	getScene().updateMaterial();
	getScene().updateLight();
	if (Settings::_playAnimation || Settings::_enableDeformation) {
		updateAnimation();
	}
	if(!_isMeshLoaded)
	{
		// If no mesh is loaded, draw a default cube
		int numIndices = 36; // 6 faces * 2 triangles per face * 3 indices per triangle
		_scene.initSceneWithCube(_triangleShader);
	}
	//_scene.draw(mat_rotation, mat_translation, mat_projection, Settings::_scale);
	_scene.draw(objectMatrix, worldMatrix, mat_projection, mat_view, Settings::_scale);

	// Unbind the shader program after drawing
	glUseProgram(0);

}

// move to bezier
void Renderer::updateAnimation()
{
	// todo - change acording to speed settings
	float deltaTime = 0.01;
	if (_animForward)
	{
		Settings::_t += Settings::_animationSpeed * deltaTime;
	}
	else {
		Settings::_t -= Settings::_animationSpeed * deltaTime;
	}
	if (Settings::_t > 1.0f)
	{
		Settings::_t = 1.0f;
		_animForward = false;
	}
	else if (Settings::_t < 0.0f)
	{
		Settings::_t = 0.0f;
		_animForward = true;
	}
}
