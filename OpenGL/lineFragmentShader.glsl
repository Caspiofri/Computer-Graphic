#version 460 core

in vec4 color;
out vec4 outFragColor;

void main()
{
    outFragColor = color; // normal fragment shader outputs white color
}
