#pragma once
#include "common_glm_config.h"
#include "Settings.h"
#include <string>
#include <Glew/include/gl/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "MeshLoader.h"
#include "Scene.h"
#include "Utils/Utils.h"
#include "Object.h"
#include "Vertex.h"


std::vector<Vertex> convertNormalsToLines(const std::vector<Vertex>& vertices) {
	std::vector<Vertex> lineVertices;
	int index = 0;
	for (const auto& v : vertices) {
		index++;
		glm::vec4 start = v.position;
		glm::vec4 end = v.position;
		end.x += v.normal.x * Settings::_normalScale;
		end.y += v.normal.y * Settings::_normalScale;
		end.z += v.normal.z * Settings::_normalScale;

		Vertex startVertex;
		startVertex.position = start;
		startVertex.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

		Vertex endVertex;
		endVertex.position = end;
		endVertex.color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); // Green for end
		lineVertices.push_back(startVertex);
		lineVertices.push_back(endVertex);
	}

	return lineVertices;
}

bool Scene::loadModel(const std::wstring& filename, Shader* meshShader , Shader* lineShader , Shader* gouraudShader) {
	std::cerr << "[loadModel] ======== before uploadFrom========= " << std::endl;

	if (!(_object.loadMesh(filename))) {
		std::wcout.imbue(std::locale("en_US.UTF-8"));
		std::wcout << L"Failed to load model from file: " << filename << std::endl;
		return false;
	}
	// attach renderable objects to the object
	_object.setMeshDrawer(std::make_unique<TriangleMesh>(_object.getMeshLoader().getVertices(), _object.getMeshLoader().getIndices(), meshShader));
	_object.setGouraudSet(std::make_unique<GouraudSet>(_object.getMeshLoader().getVertices(), _object.getMeshLoader().getIndices(), gouraudShader));


	auto normalLines = convertNormalsToLines(_object.getMeshLoader().getVertices());
	_object.setNormalDrawer(std::make_unique<LineSet>(normalLines, lineShader));

	std::vector<Vertex> bboxVertices;
	glm::vec4 color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

	std::vector<glm::vec3> corners = _object.getMeshLoader().getBoundingBox().getCorners();
	int boxEdges[24] = {
	0,1, 1,5, 5,4, 4,0,  
	2,3, 3,7, 7,6, 6,2,  
	0,2, 1,3, 4,6, 5,7  
	};

	for (int i = 0; i < 24; i += 2)
	{
		Vertex v1, v2;
		v1.position = glm::vec4(corners[boxEdges[i]], 1.0f);
		v2.position = glm::vec4(corners[boxEdges[i + 1]], 1.0f);
		v1.normal = glm::vec3(0.0f);
		v2.normal = glm::vec3(0.0f);
		v1.color = color;
		v2.color = color;
		bboxVertices.push_back(v1);
		bboxVertices.push_back(v2);
	}
	_object.setBboxDrawer(std::make_unique<LineSet>(bboxVertices , lineShader));
	
	if(_object.getMeshLoader().getVertices().empty())
	{
		std::cerr << "Mesh not loaded!" << std::endl;
		return false;
	}
	_isCube = false;
	return true;
}

void Scene::draw(const glm::mat4& objectMatrix, const glm::mat4& worldMatrix, const glm::mat4& projection, const glm::mat4& view, float scale)
{

	_object.draw(objectMatrix, worldMatrix , view ,  projection, scale , _camera.getPosition());

	if (!_isCube && Settings::_BBoxBtn)
	{
		_object.getBboxDrawer()->draw(objectMatrix, worldMatrix, view, projection, scale);
	}

	if (!_isCube && Settings::_vertexNormalsBtn)
	{
		_object.getNormalDrawer()->draw(objectMatrix, worldMatrix, view, projection, scale);
	}

}
// ===== Initialize Camera in Scene =====
void Scene::initializeScene() {

	/*_light1 = Light();
	_light2 = Light();
	_light2.setEnabled(false);

	_ambientLight = glm::vec3(0.2f);*/ // a low ambient intensity default (or 1.0f for full white)

	_camera = Camera();

	updateCameraMatrices();
}

void Scene::initSceneWithCube(Shader* shader)
{
	std::cerr << "[initSceneWithCube] start init scene with cube" << std::endl;

	std::vector<glm::vec4> positions;
	std::vector<glm::vec4> colors;
	std::vector<glm::uvec3> triangles;

	createCube(positions, colors, triangles);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < positions.size(); ++i) {
		Vertex v;
		v.position = positions[i];
		v.color = colors[i];
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertices.push_back(v);

	}

	for (const glm::uvec3& tri : triangles) {
		indices.push_back(tri.x);
		indices.push_back(tri.y);
		indices.push_back(tri.z);
	}
	for (size_t i = 0; i < indices.size(); i += 3)

	_object.setMeshDrawer(std::make_unique<TriangleMesh>(vertices, indices, shader));
	_isCube = true;
}


void Scene::updateCameraMatrices() {
	_camera.updateFromUI();
	_camera.updateViewMatrix();
	_camera.setPerspective();
}

void Scene::updateMaterial() {
	Material& mat = _object.getMaterial();
	mat.setAmbient(Settings::_ambient);
	mat.setDiffuse(Settings::_diffuse);
	mat.setSpecular(Settings::_specular);
	mat.setShininess(Settings::_shininess);
	mat.setBaseColor(glm::vec3(Settings::_baseColor));
	mat.setDoubleSided(Settings::_doubleSided);
}


void Scene::updateLight() {
	// === Light Sync ===
	_light1.setEnabled(true);
	_light1.setPosition(Settings::_light1Pos);
	_light1.setIntensity(Settings::_light1Intensity);
	_light1.setDirection(Settings::_light1Direction);
	_light1.setType(Settings::_light1Type);
	_light2.setEnabled(Settings::_light2Enabled);
	_light2.setPosition(Settings::_light2Pos);
	_light2.setIntensity(Settings::_light2Intensity);
	_light2.setDirection(Settings::_light2Direction);
	_light2.setType(Settings::_light2Type);

	// === Ambient Light Sync ===
	_ambientLight = glm::vec3(Settings::_ambientLight);

}