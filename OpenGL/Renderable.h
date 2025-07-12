
#pragma once
#include <vector>
#include <Glew/include/gl/glew.h>
#include <glm/glm.hpp>
#include "Shader.h"

class Renderable {
public:
	Renderable(Shader* shader, GLenum drawMode);
	virtual ~Renderable();

	void draw(const glm::mat4& objectMatrix, const glm::mat4& worldMatrix , const glm::mat4& view,  const glm::mat4& projection,  float scale);

	virtual void setupBuffers() = 0; // Abstract method to be implemented by derived classes

protected:
	GLuint _vao, _vbo, _ebo;
	Shader* _shader;
	GLenum _drawMode;
	int _indexCount;
	bool _usesEBO = true;
};