#include "Settings.h"
#include <iostream>
#include <glm/ext/vector_float3.hpp>

namespace Settings {
	bool _BBoxBtn = false; // Show Bounding Box button
	bool _vertexNormalsBtn = false; // Show Vertex Normals button
	double _normalScale = 1.0; // Scale for vertex normals
	bool _isMeshLoaded = false; // Flag to check if mesh is loaded


	// object transformation settings:
	float _scale = 1.0; // Scale factor for the model
	float _quaternion[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //[x,y,z,w] - w is the real part

	// object Transformations
	double _objTransX = 0.0, _objTransY = 0.0, _objTransZ = -5.0;
	double _objRotX = 0.0, _objRotY = 0.0, _objRotZ = 0.0;
}