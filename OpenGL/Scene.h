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
//#include "Mathlib.h"
//#include "Light.h"

class Scene {
public:
	bool loadModel(const std::wstring& filename, Shader* shader);
	// Loading of the model from a file
	void draw(const glm::mat4& rotation, const glm::mat4& translation, const glm::mat4& projection);          // Render the scene with the given view-projection matrix
	void initSceneWithCube(Shader* shader);
	void toggleNormals(bool show);
	void toggleBBox(bool show);
	std::unique_ptr<TriangleMesh> getMesh() const { return std::make_unique<TriangleMesh>(*_mesh); } // Return a copy of the mesh

	// Setters
	//void setShowNormals(bool show) { _showNormals = show; }
	//void setShowBBox(bool show) { _showBBox = show; }
	// Getters
	MeshLoader getMeshLoader() const { return _meshLoader; }

private:
	std::unique_ptr<TriangleMesh> _mesh;
	//std::unique_ptr<LineSet> _normals;
	//std::unique_ptr<LineSet> _bbox;

	//std::shared_ptr<Shader> _lineShader;
	MeshLoader _meshLoader;
	bool _showNormals = false;
	bool _showBBox = false;
};

