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
}