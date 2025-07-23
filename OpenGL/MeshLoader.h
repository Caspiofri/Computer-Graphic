#pragma once
#include <iostream>
#include <Glew/include/gl/glew.h>
#include <freeglut/include/GL/freeglut.h>

#include "Utils/Utils.h"
#include "Utils/wavefront_obj.h"

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "BBox.h"
#include "Vertex.h"

class MeshLoader
{
public:
	MeshLoader();
	~MeshLoader();

	bool uploadFrom(const std::wstring& filePath);

	void computeNormals();
	//void updateBoundingBox(); // Recompute the bounding box

	void draw() const;
	void reset();

	//getters
	std::vector<Vertex> getVertices() const { return _vertices; }
	std::vector<glm::vec3> getNormals() const { return _normals; }
	//std::vector<glm::vec2> getTexcoords() const { return _texcoords; }
	bool isUsingTexture() const { return _usingTexture; }
	std::vector<unsigned int> getIndices() const { return _indices; }
	const BBox& getBoundingBox() const;

private:
	std::vector<Vertex> _vertices;
	std::vector<glm::vec3> _normals;
	std::vector<glm::vec2> _texcoords;
	std::vector<unsigned int> _indices;
	BBox _boundingBox;
	bool _usingTexture = false;

	void normalizeModel();

	void updateBoundingBox();

};