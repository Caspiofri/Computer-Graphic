#pragma once
#include <string>
#include <Glew/include/gl/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Camera.h"
#include "MeshLoader.h"
#include "TriangleMesh.h"
#include "Object.h"
#include "Light.h"
#include "bezierCurve.h"
#include "MathLib.h"


class Scene {
public:
	bool loadModel(const std::wstring& filename, Shader* meshShader, Shader* lineShader, Shader* grouaudShader , Shader* phongShader);
	void draw(glm::mat4& objectMatrix, const glm::mat4& worldMatrix, const glm::mat4& projection, const glm::mat4& view, float scale);
	void initializeScene(Shader* lineShader);
	// Loading of the model from a file
	//void draw(const glm::mat4& rotation, const glm::mat4& translation, const glm::mat4& projection);          // Render the scene with the given view-projection matrix
	void initSceneWithCube(Shader* shader);
	void toggleNormals(bool show);
	void toggleBBox(bool show);

	void updateCameraMatrices();

	void updateMaterial();

	void updateLight();

	void updateAnimation();

	std::vector<Vertex> buildVisualBezier();
	
	std::vector<Vertex> convertNormalsToLine(const std::vector<Vertex>& vertices);

	void setWorldAxisDrawer(std::unique_ptr<LineSet> lineSet) {
		_worldAxisDrawer = std::move(lineSet);
	}
	void setObjectAxisDrawer(std::unique_ptr<LineSet> lineSet) {
		_objectAxisDrawer = std::move(lineSet);
	}
	void setBezierDrawer(std::unique_ptr<LineSet> lineSet) {
		_bezierDrawer = std::move(lineSet);
	}


	void setWorldAxisDrawer(bool isCube) { _isCube = isCube; }

	Object& getObject() { return _object; }
	Camera& getCamera() { return _camera; }
	
	//  Light Managment
	const Light& getLight1() const { return _light1; }
	const Light& getLight2() const { return _light2; }
	const glm::vec3 getAmbientLight() const { return _ambientLight; }

	// animation
	glm::mat4 calcAnimation();

private:

	Object _object;
	Camera _camera;
	bool _isCube = true;
	bool _showNormals = false;
	bool _showBBox = false;
	std::unique_ptr<LineSet> _worldAxisDrawer;
	std::unique_ptr<LineSet> _objectAxisDrawer;
	std::unique_ptr<LineSet> _bezierDrawer;


	Light _light1, _light2;
	glm::vec3 _ambientLight;
	BezierCurve _bezierCurve;
	bool _animForward = true;
};


