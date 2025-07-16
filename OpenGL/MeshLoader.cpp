#include "MeshLoader.h"
#include "common_glm_config.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

MeshLoader::MeshLoader()
{
}
MeshLoader ::~MeshLoader()
{
	reset();
}

bool MeshLoader::uploadFrom(const std::wstring& filePath) {
	std::cerr << "[uploadFrom] inside uploadFrom" << std::endl;

	Wavefront_obj wf;
	if (!wf.load_file(filePath)) {  // Now passing std::wstring
		std::cerr << "Failed to load OBJ file: " << std::endl;
		return false;
	}

	// Clear previous data
	_vertices.clear();
	_indices.clear();
	_normals.clear();

	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	for (const auto& v : wf.m_points) {
		int index = _vertices.size();
		Vertex vert;
		vert.position = glm::vec4(v[0], v[1], v[2], 1.0f);
		vert.normal = glm::vec3(0.0f); 
		
		// to do - change to texture 
		//vert.texcoord = glm::vec3(0.0f); // Assuming no texture coordinates for now

		switch (index % 3) {
			case 0: color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); break; // red
			case 1: color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); break; // green
			case 2: color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); break; // blue
		}

		vert.color = color;

		std::cout << "[uploadFrom] Vertex " << index << ":\n"
			<< "  Position = " << glm::to_string(vert.position) << "\n"
			<< "  Normal   = " << glm::to_string(vert.normal) << "\n"
			<< "  Color    = " << glm::to_string(vert.color) << "\n";

		_vertices.push_back(vert);
	}

	for (const auto& f : wf.m_faces) {
		_indices.push_back(f.v[0]);
		_indices.push_back(f.v[1]);
		_indices.push_back(f.v[2]);
	}
	std::cout << "[uploadFrom] Indices:\n";
	for (size_t i = 0; i < _indices.size(); i += 3) {
		std::cout << "  Triangle " << (i / 3) << ": "
			<< _indices[i] << ", "
			<< _indices[i + 1] << ", "
			<< _indices[i + 2] << "\n";
	}

	size_t F = _indices.size() / 3;
	std::vector<glm::vec3> faceNormals(F);

	// for each vertex,create a list of near face indices
	std::vector<std::vector<int>> pointToFaces(_vertices.size());
	for (size_t fi = 0; fi < F; ++fi) {
		int i0 = _indices[3 * fi + 0];
		int i1 = _indices[3 * fi + 1];
		int i2 = _indices[3 * fi + 2];
		const auto& v0 = glm::vec3(_vertices[i0].position);
		const auto& v1 = glm::vec3(_vertices[i1].position);
		const auto& v2 = glm::vec3(_vertices[i2].position);

		// compute this face's normal using its vertices
		glm::vec3 fn = glm::normalize(glm::cross(v2 - v0, v1 - v0));
		faceNormals[fi] = fn;

		// associate the face with each of its vertices
		pointToFaces[i0].push_back(fi);
		pointToFaces[i1].push_back(fi);
		pointToFaces[i2].push_back(fi);
	}

	normalizeModel();

	_normals.resize(_vertices.size());
	for (size_t vi = 0; vi < _vertices.size(); ++vi) {
		glm::vec3 sum(0.0f);
		for (int fi : pointToFaces[vi])
			sum += faceNormals.at(fi);
		_vertices[vi].normal = glm::normalize(sum);
		std::cout << "[_normals.resize] vertex.position = " << glm::to_string(_vertices[vi].normal) << std::endl;

	}
	for (size_t vi = 0; vi < _vertices.size(); ++vi) {
		std::cout << "[uploadFrom] Vertex " << vi << ":\n"
			<< "  Position = " << glm::to_string(_vertices[vi].position) << "\n"
			<< "  Normal   = " << glm::to_string(_vertices[vi].normal) << "\n"
			<< "  Color    = " << glm::to_string(_vertices[vi].color) << "\n";
	}
	updateBoundingBox();

	return true;
}

void MeshLoader::normalizeModel()
{
	glm::vec3 minPoint(FLT_MAX), maxPoint(-FLT_MAX);
	for (const auto& vertex : _vertices) {
		glm::vec3 pos3D = glm::vec3(vertex.position); // Extract 3D position from vec4
		minPoint = glm::min(minPoint, pos3D);
		maxPoint = glm::max(maxPoint, pos3D);
	}
	glm::vec3 center = (minPoint + maxPoint) / 2.0f;
	float maxLength = glm::length(maxPoint - minPoint);
	for (auto& vertex : _vertices) {
		glm::vec3 pos3D(vertex.position);
		pos3D = (pos3D - center) / maxLength;
		vertex.position = glm::vec4(pos3D, 1.0f);
		std::cout << "[normalizeModel()] vertex.position = " << glm::to_string(vertex.position) << std::endl;

	}
}

void MeshLoader::updateBoundingBox()
{
	_boundingBox.compute( _vertices);
}

const BBox& MeshLoader::getBoundingBox() const {
	return _boundingBox;
}

void MeshLoader::reset() {
	_vertices.clear();
	_indices.clear();
	_normals.clear();
	//_boundingBox.reset();
}
