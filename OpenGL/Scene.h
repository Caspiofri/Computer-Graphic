#pragma once
#include <string>
#include <Glew/include/gl/glew.h>
#include <glm/glm.hpp>
#include <vector>
//#include "Utils.h"
//#include "../Obj Parser/wavefront_obj.h"
//#include "Camera.h"
//#include <glm/ext/matrix_float4x4.hpp>
#include "MeshLoader.h"
#include "TriangleMesh.h"
#include "Object.h"
//#include "Mathlib.h"
//#include "Light.h"

class Scene {
public:
	bool loadModel(const std::wstring& filename, Shader* shader);
	void draw(const glm::mat4& objectMatrix, const glm::mat4& projection, float scale);
	// Loading of the model from a file
	//void draw(const glm::mat4& rotation, const glm::mat4& translation, const glm::mat4& projection);          // Render the scene with the given view-projection matrix
	void initSceneWithCube(Shader* shader);
	void toggleNormals(bool show);
	void toggleBBox(bool show);
	
	//const Object& getObject() const { return _object; }
	Object& getObject() { return _object; }
	// Setters
	//void setShowNormals(bool show) { _showNormals = show; }
	//void setShowBBox(bool show) { _showBBox = show; }
	// Getters

private:
	//std::unique_ptr<LineSet> _normals;
	//std::unique_ptr<LineSet> _bbox;

	//std::shared_ptr<Shader> _lineShader;
	Object _object;
	bool _showNormals = false;
	bool _showBBox = false;
};

