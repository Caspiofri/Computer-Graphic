//#pragma once
//#include <glm/glm.hpp>
//#include <vector>
//
//class BBox {
//private:
//	glm::vec3 _minCorner;
//	glm::vec3 _maxCorner;
//	GLuint _vao, _vbo, _ebo;
//	Shader* _shader = nullptr;
//
//public:
//	BBox();
//	void compute(const std::vector<glm::vec3>& vertices);
//	void reset();
//
//
//	void setShader(Shader* shader) { _shader = shader; }
//	void initGLResources();
//	void draw(const glm::mat4& MVP);
//
//	const glm::vec3& getMinCorner() const { return _minCorner; }
//	const glm::vec3& getMaxCorner() const { return _maxCorner; }
//	std::vector<glm::vec3> getCorners() const;
//
//};
