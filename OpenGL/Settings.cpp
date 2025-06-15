#include "Settings.h"
#include <iostream>
#include <glm/ext/vector_float3.hpp>

namespace Settings {
	bool _BBoxBtn = false; // Show Bounding Box button
	bool _vertexNormalsBtn = false; // Show Vertex Normals button
	double _normalScale = 1.0; // Scale for vertex normals
	bool _isMeshLoaded = false; // Flag to check if mesh is loaded
}