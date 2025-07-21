#version 460 //compatible with OpenGL version 4.6 (latest version)

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vNormal;

// MVP matrix - sent via renderable->draw
uniform mat4 objectMatrix;
uniform mat4 worldMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform float scale;

out vec3 FragPos;
out vec3 worldNormal;

void main()
{
   mat4 modelMatrix = objectMatrix * worldMatrix ;
    
    vec4 worldPos4 = vPosition * modelMatrix;
    FragPos = worldPos4.xyz / worldPos4.w;

    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    worldNormal = normalize(vNormal * normalMatrix);

    gl_Position = vPosition;

	gl_Position.w = gl_Position.w / scale;
	
	gl_Position = gl_Position * objectMatrix * worldMatrix  *view * projection;
}
