#pragma once
#include <iostream>
#include <Glew/include/gl/glew.h>
#include <freeglut/include/GL/freeglut.h>

#include "Utils/Utils.h"
#include "Utils/wavefront_obj.h"
#include "OpenGL/GLMesh.h"

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "BBox.h"

class GLMesh
{
private:
	struct Vertex
	{
		glm::vec4 position;
		glm::vec3 normal;
		//glm::vec3 texcoord;
		glm::vec4 color;
	};
	BBox _boundingBox; // Bounding box member
	std::vector<Vertex> _vertices;
	std::vector<glm::vec3> _normals;
	std::vector<unsigned int> _indices;

	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
	GLuint _normalVBO = 0;
	GLuint _normalVAO = 0;
	size_t _indexCount;

	void normalizeModel();

public:
	GLMesh();
	~GLMesh();

	void uploadFrom(const Wavefront_obj& obj);
	void computeNormals();
	void updateBoundingBox(); // Recompute the bounding box

	void draw() const;
	void reset();

};