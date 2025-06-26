#pragma once
#include "common_glm_config.h"
#include <string>
#include <Glew/include/gl/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "MeshLoader.h"
#include "Scene.h"
#include "Utils/Utils.h"


bool Scene::loadModel(const std::wstring& filename , Shader* shader) {
	MeshLoader loader;
	std::cerr << "[loadModel] ======== before uploadFrom========= " << std::endl;

	bool result = loader.uploadFrom(filename); // loader holds vertices, indices, normals, and colors
	if (!result) {
        // Replace the problematic line with the following:
        std::wcout.imbue(std::locale("en_US.UTF-8"));
        std::wcout << L"Failed to load model from file: " << filename << std::endl;
		return false;
	}
	// Send to renderable(Trianglemesh) data from object  
	_mesh = std::make_unique<TriangleMesh>(loader.getVertices(), loader.getIndices(), shader);

	if (_showNormals) {
		std::cerr << "renderer of normals" << std::endl;

	/*	std::vector<glm::vec3> lines = generateNormalLines(vertexData);
		_normals = std::make_unique<LineSet>(lines, _lineShader);*/
	}

	if (_showBBox) {
		std::cerr << "renderer of BBox" << std::endl;

		//std::vector<glm::vec3> boxLines = generateBBoxLines(rawMesh);
		//_bbox = std::make_unique<LineSet>(boxLines, _lineShader);
	}
	return true;
}

void Scene::draw(const glm::mat4& rotation, const glm::mat4& translation, const glm::mat4& projection, float scale)
{

	if (!_mesh)
	{	// Check if the mesh is loaded
		std::cerr << "Mesh not loaded!" << std::endl;
		return;
	}
	std::cerr << "[Scene::draw] drawing mesh" << std::endl;
	_mesh->draw(rotation, translation, projection , scale);

	std::cerr << "[Scene::draw] done drawing meshy" << std::endl;

	if (_showBBox)
	{
		// Draw bounding box if available
	}
	if (_showNormals)
	{
		// Draw normals if available
	}

}

void Scene::initSceneWithCube(Shader* shader)
{
	std::cerr << "[initSceneWithCube] start init scene with cube" << std::endl;

	std::vector<glm::vec4> positions;
	std::vector<glm::vec4> colors;
	std::vector<glm::uvec3> triangles;

	std::cerr << "[initSceneWithCube] creating cube" << std::endl;
	createCube(positions, colors, triangles);

	for (size_t i = 0; i < positions.size(); ++i)
		std::cout << "[initSceneWithCube] pos[" << i << "] = " << glm::to_string(positions[i]) << std::endl;
	for (size_t i = 0; i < colors.size(); ++i)
		std::cout << "[initSceneWithCube] color[" << i << "] = " << glm::to_string(colors[i]) << std::endl;
	for (size_t i = 0; i < triangles.size(); ++i)
		std::cout << "[initSceneWithCube] tri[" << i << "] = " << glm::to_string(triangles[i]) << std::endl;

	std::vector<MeshLoader::Vertex> vertices;
	std::vector<unsigned int> indices;

	std::cerr << "[initSceneWithCube] creating vertexes" << std::endl;
	for (size_t i = 0; i < positions.size(); ++i) {
		MeshLoader::Vertex v;
		v.position = positions[i];
		v.color = colors[i];
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertices.push_back(v);
		std::cout << "[initSceneWithCube] vertex " << i << ": position = " << glm::to_string(v.position)
			<< ", color = " << glm::to_string(v.color)
			<< ", normal = " << glm::to_string(v.normal) << std::endl;
	}

	std::cerr << "[initSceneWithCube] creating indices" << std::endl;
	for (const glm::uvec3& tri : triangles) {
		indices.push_back(tri.x);
		indices.push_back(tri.y);
		indices.push_back(tri.z);
	}
	for (size_t i = 0; i < indices.size(); i += 3)
		std::cout << "[initSceneWithCube] triangle " << i / 3 << ": " << indices[i] << ", " << indices[i + 1] << ", " << indices[i + 2] << std::endl;

	std::cerr << "[initSceneWithCube] calling TriangleMesh " << std::endl;
	_mesh = std::make_unique<TriangleMesh>(vertices, indices, shader);
}