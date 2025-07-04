#pragma once
#include "MeshLoader.h"
#include "TriangleMesh.h"
#include <set>

class Object {
private:
    std::string _name;
    MeshLoader _meshLoader;
    std::unique_ptr<TriangleMesh> _meshDrawer;

public:
    Object();
    bool loadMesh(const std::wstring& filePath);
    void draw(const glm::mat4& rotation, const glm::mat4& translation, const glm::mat4& projection, const float scale);
    MeshLoader getMeshLoader() const { return _meshLoader; }
    MeshLoader setMeshLoader(const MeshLoader& mesh) { return _meshLoader = mesh; }
    void setMeshDrawer(std::unique_ptr<TriangleMesh> mesh) {
        _meshDrawer = std::move(mesh);
    }
	std::unique_ptr<TriangleMesh> getMeshDrawer() const {
		return std::make_unique<TriangleMesh>(*_meshDrawer);
	}

    void clear();
    void buildMeshDrawerFromLoader(Shader* shader);
};