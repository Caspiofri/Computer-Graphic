#pragma once
#include <string>
#include <glm/glm.hpp>
#include <Glew/include/gl/glew.h>
#include "Utils/Utils.h"

class VertexBufferBuilder {
public:
	struct Attribute {
		GLuint location;
		GLint size;
		GLenum type;
		size_t offset;
	};

	template <typename VertexType>
	static void setupVAO(GLuint& vao, GLuint& vbo, const std::vector<VertexType>& vertices, const std::vector<Attribute>& attributes) {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		std::cout << "[setupVAO] vao = " << vao << ", vbo = " << vbo << std::endl;
		std::cout << "[setupVAO] uploaded " << vertices.size() << " vertices of size " << sizeof(VertexType) << std::endl;
		
	
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexType), vertices.data(), GL_STATIC_DRAW);

		for (const auto& attr : attributes) {
			glEnableVertexAttribArray(attr.location);
			glVertexAttribPointer(attr.location, attr.size, attr.type, GL_FALSE, sizeof(VertexType), (void*)attr.offset);
		}

		glBindVertexArray(0);
	}

	template <typename IndexType>
	static void setupEBO(GLuint& ebo, const std::vector<IndexType>& indices) {
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(IndexType), indices.data(), GL_STATIC_DRAW);
	}
};