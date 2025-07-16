#pragma once
#include "MeshLoader.h"
#include "TriangleMesh.h"
#include "Settings.h"
#include "MathLib.h"
#include <glm/glm.hpp>
#include <set>
#include "LineSet.h"
#include "GouraudSet.h"

class Object {
private:
    std::string _name;

    // meshes and shaders
    MeshLoader _meshLoader;
    std::unique_ptr<TriangleMesh> _meshDrawer;
    std::unique_ptr<LineSet> _normalsDrawer;
    std::unique_ptr<LineSet> _bboxDrawer;
    std::unique_ptr<GouraudSet> _gouraudSet;
    //std::unique_ptr<PhongSet> _phongSet;

    // matrices for object transformations
    glm::mat4 _objectTranslationMatrix = glm::mat4(1.0f);
    glm::mat4 _objectRotationMatrix = glm::mat4(1.0f);
	glm::mat4 _objectScaleMatrix = glm::mat4(1.0f);
    glm::mat4 _objectMatrix = glm::mat4(1.0f);
    glm::mat4 _worldMatrix = glm::mat4(1.0f);
    glm::mat4 _worldTranslationMatrix = glm::mat4(1.0f);
    glm::mat4 _worldRotationMatrix = glm::mat4(1.0f);


public:
    Object();
    void ApplyTransformations();
    void ApplyWorldTransformations();
    void UpdateObjectLocalTransform();
    void UpdateWorldTransform();
	void clearObjTransformations() {
		_objectTranslationMatrix = glm::mat4(1.0f);
		_objectRotationMatrix = glm::mat4(1.0f);
		_objectScaleMatrix = glm::mat4(1.0f);
		_objectMatrix = glm::mat4(1.0f);
	}
    void clearWorldTransformations() {
        _worldTranslationMatrix = glm::mat4(1.0f);
        _worldRotationMatrix = glm::mat4(1.0f);
        _worldMatrix = glm::mat4(1.0f);
    }

    bool loadMesh(const std::wstring& filePath);
    void draw(const glm::mat4& objectMatrix, const glm::mat4& worldMatrix, const glm::mat4& view, const glm::mat4& projection, const float scale, const glm::vec3 cameraPos);
    void buildMeshDrawerFromLoader(Shader* shader);
    void clear();


    // Gettert:
    MeshLoader getMeshLoader() const { return _meshLoader; }
    //void rotate(float angle, glm::vec3 axis);
   
    void translateObj(glm::vec3 translation);
    void rotateObj();


    void translateWorld(glm::vec3 translation);
    void rotateWorld();

    void scale(glm::vec3 scaleFactor);
    void updateObjectMatrix();
    void setObjectMatrix(const glm::mat4& mat);
    const glm::mat4& getObjectMatrix() const;
    void setWorldMatrix(const glm::mat4& mat);
    const glm::mat4& getWorldMatrix() const;
    glm::mat4 getObjectTranslationMatrix() const {
        return _objectTranslationMatrix;
    }
    glm::mat4 getObjectRotationMatrix() const {
        return _objectRotationMatrix;
    }
    // Setter:
    MeshLoader setMeshLoader(const MeshLoader& mesh) { return _meshLoader = mesh; }

    const std::unique_ptr<TriangleMesh>& getMeshDrawer() const {
        return _meshDrawer;
    }
    const std::unique_ptr<LineSet>& getNormalDrawer() const {
        return _normalsDrawer;
    }
    const std::unique_ptr<LineSet>& getBboxDrawer() const {
        return _bboxDrawer;
    }
    const std::unique_ptr<GouraudSet>& getGouraudSet() const {
        return _gouraudSet;
    }
    
  
    void setMeshDrawer(std::unique_ptr<TriangleMesh> mesh) {
        _meshDrawer = std::move(mesh);
    }
    void setNormalDrawer(std::unique_ptr<LineSet> lineSet) {
        _normalsDrawer = std::move(lineSet);
    }
    void setBboxDrawer(std::unique_ptr<LineSet> lineSet) {
        _bboxDrawer = std::move(lineSet);
    }
	void setGouraudSet(std::unique_ptr<GouraudSet> gouraudSet) {
		_gouraudSet = std::move(gouraudSet);
	}
};