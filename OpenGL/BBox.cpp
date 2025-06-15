//#include "BBox.h"
////#include "Utils.h"
//#include "common_glm_config.h"
//
//#include <cfloat>
//#include <glm/glm.hpp>
//#include <vector>
//#include <cmath>
//#include <freeglut/include/GL/freeglut.h>
//#include <iostream>
//#include <glm/mat4x4.hpp>
//#include <glm/vec4.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/string_cast.hpp>
//
//BBox::BBox() : _minCorner(glm::vec3(FLT_MAX)), _maxCorner(glm::vec3(-FLT_MAX)) {}
//
//void BBox::compute(const std::vector<glm::vec3>& vertices) {
//	_minCorner = glm::vec3(FLT_MAX);
//	_maxCorner = glm::vec3(-FLT_MAX);
//
//	for (const auto& vertex : vertices) {
//		_minCorner = glm::min(_minCorner, vertex);
//		_maxCorner = glm::max(_maxCorner, vertex);
//	}
//
//	if (std::abs(_maxCorner.z - _minCorner.z) < 1e-5f) {
//		_maxCorner.z += 0.1f;
//	}
//}
//
//std::vector<glm::vec3> BBox::getCorners() const {
//	return {
//		_minCorner,
//		{_minCorner.x, _minCorner.y, _maxCorner.z},
//		{_minCorner.x, _maxCorner.y, _minCorner.z},
//		{_minCorner.x, _maxCorner.y, _maxCorner.z},
//		{_maxCorner.x, _minCorner.y, _minCorner.z},
//		{_maxCorner.x, _minCorner.y, _maxCorner.z},
//		{_maxCorner.x, _maxCorner.y, _minCorner.z},
//		_maxCorner
//	};
//}
//
//void BBox::reset() {
//	_minCorner = glm::vec3(FLT_MAX);
//	_maxCorner = glm::vec3(-FLT_MAX);
//}