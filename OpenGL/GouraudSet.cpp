#include "GouraudSet.h"
#include "MeshLoader.h"
#include "Settings.h"

GouraudSet::GouraudSet(const std::vector<Vertex>& vertices,
	const std::vector<unsigned int>& indices,
	Shader* shader)
	: Renderable(shader, GL_TRIANGLES),
	_vertices(vertices),
	_indices(indices) {
	_indexCount = static_cast<GLsizei>(_indices.size());
	_cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
	setupBuffers();
}
void GouraudSet::setShaderUniforms() {

	// settings light parameters
	_shader->setVec3("viewPos", _cameraPos);
	_shader->setVec3("ambientLight", Settings::_ambientLight);

	//Material properties
	_shader->setVec3("materialBaseColor", Settings::_baseColor);
	_shader->setFloat("materialAmbient", Settings::_ambient);
	_shader->setFloat("materialDiffuse", Settings::_diffuse);
	_shader->setFloat("materialSpecular", Settings::_specular);
	_shader->setFloat("materialShininess", Settings::_shininess);
	_shader->setBool("materialDoubleSided", Settings::_doubleSided);

	// Light 1
	_shader->setInt("light1Type", Settings::_light1Type);
	_shader->setVec3("light1Position", Settings::_light1Pos);
	_shader->setVec3("light1Direction", Settings::_light1Direction);
	_shader->setVec3("light1Intensity", Settings::_light1Intensity);

	// Light 2
	_shader->setBool("light2Enabled", Settings::_light2Enabled);
	_shader->setInt("light2Type", Settings::_light2Type);
	_shader->setVec3("light2Position", Settings::_light2Pos);
	_shader->setVec3("light2Direction", Settings::_light2Direction);
	_shader->setVec3("light2Intensity", Settings::_light2Intensity);

	//Texture 
	if (_hasTexture) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _textureID);
		_shader->setInt("texMap", 0);
		_shader->setBool("useTexture", true);
	}
	else {
		_shader->setBool("useTexture", false);
	}

}

void GouraudSet::setupBuffers() {
	std::cerr << "[GouraudSet] in setupBuffers" << std::endl;

	// Building buffers
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	std::cout << "[GouraudSet] _vao = " << _vao << std::endl;

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

	// Setting vertex attributes
	glEnableVertexAttribArray(0); // Position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1); // normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2); // Texture 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));

	glBindVertexArray(0); // Unbind VAO
}
