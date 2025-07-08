#include "Settings.h"
#include <iostream>
#include <glm/ext/vector_float3.hpp>

namespace Settings {
	bool _BBoxBtn = false; // Show Bounding Box button
	bool _vertexNormalsBtn = false; // Show Vertex Normals button
	double _normalScale = 1.0; // Scale for vertex normals
	bool _isMeshLoaded = false; // Flag to check if mesh is loaded
	
	// camera settings :
	int _screenWidth = 600;
	int _screenHeight = 800;
	float _aspectRatio = 600 / 800;


	// object transformation settings:
	float _scale = 1.0; // Scale factor for the model

	// object Transformations
	float _objQuaternion[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //[x,y,z,w] - w is the real part
	double _objTransX = 0.0, _objTransY = 0.0, _objTransZ = 0.0;

	//world Transformations
	float _worldQuaternion[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //[x,y,z,w] - w is the real part
	double _worldTransX = 0.0, _worldTransY = 0.0, _worldTransZ = 0.0;

	 // Perspective
    double _nearPlane = 0.1, _farPlane = 1000.0, _fov = 45.0;

    // Camera Controls
    double _camTransX = 0.0, _camTransY = 0.0, _camTransZ = 5.0;
	double _camRotX = 0.0, _camRotY = 0.0, _camRotZ = 0.0;

	// screen propeties
	void setScreenSize(int width, int height) {
		_screenWidth = width;
		_screenHeight = height;
		_aspectRatio = static_cast<float>(_screenWidth) / _screenHeight;
	}

	int getAspectRatio() {
		return _aspectRatio;
	}

	int getScreenWidth() {
		return _screenWidth;
	}

	int getScreenHeight() {
		return _screenHeight;
	}
	

}