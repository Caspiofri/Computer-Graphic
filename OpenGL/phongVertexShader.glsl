#version 460 //compatible with OpenGL version 4.6 (latest version)

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoords;

// MVP matrix - sent via renderable->draw
uniform mat4 objectMatrix;
uniform mat4 worldMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform float scale;

//Deformation
uniform bool enableDeformation;
uniform float deformAmplitude; 
uniform float deformationTime;
uniform float deformationSpeed;
uniform float waveFrequency;
uniform float BboxSize;

out vec3 FragPos;
out vec3 worldNormal;
out vec2 FragTexCoords;

void main()
{
    // Calculate world position
    mat4 modelMatrix = objectMatrix * worldMatrix ;
    vec4 worldPos4 = vPosition * modelMatrix;
    vec3 FragPos = worldPos4.xyz;

    // Calculate world normal
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    worldNormal = normalize(vNormal * normalMatrix);

    // Calculate texture
    FragTexCoords  = vTexCoords;

    if(enableDeformation){
        float wave = abs(cos(deformationTime * deformationSpeed + length(FragPos.xy) * waveFrequency));
        vec3 offset = worldNormal * wave * deformAmplitude * BboxSize*0.1; 
        FragPos += offset;

    }

	gl_Position =vec4(FragPos * scale , 1.0)  *view * projection;
}
