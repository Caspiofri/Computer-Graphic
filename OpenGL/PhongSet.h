#pragma once
#include "Renderable.h"
#include "Vertex.h"
#include "Shader.h"
#include <vector>
#include "MeshLoader.h"
#include <glm/glm.hpp>


class PhongSet : public Renderable {
public:
	PhongSet(const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices,
		Shader* shade);
	void setCameraPos(const glm::vec3& cameraPos) { _cameraPos = cameraPos; }
	void setTextureID(GLuint id) {
		_textureID = id;
		_hasTexture = true;
	}
	void setShaderUniforms();
	void setupBuffers() override;

private:
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
	glm::vec3 _cameraPos;
	GLuint _textureID = 0;
	bool _hasTexture = false;
};
