#version 460 //compatible with OpenGL version 4.6 (latest version)


in vec4 vColor;     // World-space position
out vec4 FragColor; 


void main()
{
    FragColor = vColor;
}
