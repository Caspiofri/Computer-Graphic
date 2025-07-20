#pragma once
#include "MeshLoader.h"
#include "TriangleMesh.h"
#include "Settings.h"
#include "MathLib.h"
#include <glm/glm.hpp>
#include <set>
#include "LineSet.h"
#include "GouraudSet.h"
#include "PhongSet.h"
#include "Material.h"

class Object {
private:
    std::string _name;

    // meshes and shaders
    MeshLoader _meshLoader;
    Material _material;

    std::unique_ptr<TriangleMesh> _meshDrawer;
    std::unique_ptr<LineSet> _normalsDrawer;
    std::unique_ptr<LineSet> _bboxDrawer;
    std::unique_ptr<GouraudSet> _gouraudSet;
    std::unique_ptr<PhongSet> _phongSet;

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

    // mesh and drawing functions
    bool loadMesh(const std::wstring& filePath);
    void draw(const glm::mat4& objectMatrix, const glm::mat4& worldMatrix, const glm::mat4& view, const glm::mat4& projection, const float scale, const glm::vec3 cameraPos);
    void buildMeshDrawerFromLoader(Shader* shader);
    void clear();
    MeshLoader getMeshLoader() const { return _meshLoader; }


    // == transformation functions == 
  
    void scale(glm::vec3 scaleFactor);

    void translateObj(glm::vec3 translation);
    glm::mat4 getObjectTranslationMatrix() const {
        return _objectTranslationMatrix;
    }

    void rotateObj();
    glm::mat4 getObjectRotationMatrix() const {
        return _objectRotationMatrix;
    }

    void updateObjectMatrix();
    void UpdateObjectLocalTransform();

    void setObjectMatrix(const glm::mat4& mat);
    const glm::mat4& getObjectMatrix() const;

    void ApplyTransformations();


    void translateWorld(glm::vec3 translation);
    void rotateWorld();
    
    void ApplyWorldTransformations();

    void UpdateWorldTransform();
    void setWorldMatrix(const glm::mat4& mat);
    const glm::mat4& getWorldMatrix() const;
 
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
   

    // shaders renderables:
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
	const std::unique_ptr<PhongSet>& getPhongSet() const {
		return _phongSet;
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
	void setPhongSet(std::unique_ptr<PhongSet> phongSet) {
		_phongSet = std::move(phongSet);
	}
    

	//Material properties
    bool setMaterial(const Material& m);
    Material& getMaterial() { return _material; }
    const Material& getMaterial() const { return _material; }
};