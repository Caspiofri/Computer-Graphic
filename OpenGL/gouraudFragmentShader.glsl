#version 460 //compatible with OpenGL version 4.6 (latest version)


in vec3 vColor;     // World-space position
out vec4 FragColor; 


void main()
{
    //FragColor = vec4(clamp(vColor, 0.0, 1.0), 1.0);
    FragColor = vec4(vColor * 0.5 + 0.5, 1.0);

}
