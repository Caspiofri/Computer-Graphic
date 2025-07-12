#pragma once

#include <iostream>

#include "common_glm_config.h"
#include <string>
#include <Glew/include/gl/glew.h>
#include <freeglut/include/GL/freeglut.h>
#include "Utils/Utils.h"
#include "Utils/wavefront_obj.h"
#include "Scene.h"
#include "Shader.h"
#include "Renderer.h"
#include "TriangleMesh.h"
#include "Settings.h"
#include <string>

class Renderer
{
public:
	
	Renderer() = default;
	~Renderer() = default;


	bool _isMeshLoaded = true;
	void initScene();
	bool loadModelToScene(const std::wstring& filename);
	void drawScene();
	void loadOBJModel(void* data);
	void initGraphics(int argc, char* argv[]);

	Shader* _triangleShader = nullptr;
	Shader* _lineShader = nullptr;
	Scene _scene;

	// Getters
	Shader* getTriangleShader() { return _triangleShader ; }
	//const Scene& getScene() const { return _scene; }
	Scene& getScene() { return _scene; }

	// Setters
	void setTriangleShader(Shader* shader) { _triangleShader = shader; }
	void setLineShader(Shader* shader) { _lineShader = shader; }

private:
	//std::vector<Pixel> _pixels;
	//std::vector<uint32_t> _colorBuffer; //32-bit ARGB
	//std::vector<float> _depthBuffer; // z-values of pixels
	//void ConvertQuaternionToMatrix(const float quaternion[4], glm::mat4x4& matrix);
	//void createTranslationMatrix(float x, float y, float z, glm::mat4x4& matrix);
	//void antTeakBar_UIscale();
	//void antTweakBarSettings();
	//void Terminate();

};

