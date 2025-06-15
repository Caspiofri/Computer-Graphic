#version 460 //compatible with OpenGL version 4.6 (latest version)

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

uniform mat4 rotation; 
uniform mat4 translation;
uniform mat4 projection;
uniform float scale;

//These colors will be interpolated by the rasterizer for each triangle after the vertex shader terminates.
//The interpolated colors will become the input of the fragment shader
out vec4 color;



void main()
{
	//gl_Position is a vec4 built-in GLSL output variable that holds the transformed vertex position
	gl_Position = vPosition;

	//uniform scaling - dividing the w coordinate is like multiplying the x, y, z coordinates
	gl_Position.w = gl_Position.w / scale;

	//first rotate, then translate in world coordinates, and finally project. We are assuming row vectors notations as the vector is on the left hand side of the matrix
	gl_Position = gl_Position * rotation * translation * projection;

	color = vColor; //pass throgh the color

	//You need to add your code for Gourard shading here instead of the pass through of the color above
	//There are many useful built-in functions in GLSL such as:
	//reflect,
	//dot,
	//cross,
	//length,
	//faceforward,
	//min,
	//max,
	//sin,
	//degrees,
	//radians
	//clamp,
	//ceil,
	//fract, etc.
	//Look for the "Built-In Functions" page in the OpenGL Reference Guide
}
