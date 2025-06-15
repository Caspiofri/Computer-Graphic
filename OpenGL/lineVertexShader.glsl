#version 460 core

layout(location = 0) in vec3 vPosition;

uniform mat4 rotation;
uniform mat4 translation;
uniform mat4 projection;
uniform float scale;

void main()
{
    vec4 pos = vec4(vPosition * scale, 1.0);
    gl_Position = projection * translation * rotation * pos;
}