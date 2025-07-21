#version 460 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

uniform mat4 objectMatrix;
uniform mat4 worldMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform float scale;

//These colors will be interpolated by the rasterizer for each triangle after the vertex shader terminates.
//The interpolated colors will become the input of the fragment shader
out vec4 color;


void main()
{
   		
    gl_Position = vPosition;

	gl_Position.w = gl_Position.w / scale;
	
	gl_Position = gl_Position * objectMatrix * worldMatrix  *view * projection;
	color = vColor; //pass throgh the color
}