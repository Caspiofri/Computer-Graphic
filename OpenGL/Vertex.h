#pragma once
#include <iostream>
#include <Glew/include/gl/glew.h>
#include <freeglut/include/GL/freeglut.h>

#include "Utils/Utils.h"
#include "Utils/wavefront_obj.h"

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Vertex
{
	glm::vec4 position;
	glm::vec3 normal;
	//glm::vec3 texcoord;
	glm::vec4 color;
};