#version 460 //compatible with OpenGL version 4.6 (latest version)

// data about each vertex
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoords;

// MVP matrix - sent via renderable->draw
uniform mat4 objectMatrix;
uniform mat4 worldMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform float scale;

// scene properties 
uniform vec3 viewPos;          // Camera position
uniform vec3 ambientLight;     

// Material properties
uniform vec3 materialBaseColor;
uniform float materialAmbient;
uniform float materialDiffuse;
uniform float materialSpecular;
uniform float materialShininess;
uniform bool materialDoubleSided;

// Light 1
uniform int light1Type;         // 0 = directional, 1 = point
uniform vec3 light1Position;    
uniform vec3 light1Direction;   
uniform vec3 light1Intensity;

// Light 2 
uniform bool light2Enabled;
uniform int light2Type;
uniform vec3 light2Position;
uniform vec3 light2Direction;
uniform vec3 light2Intensity;

// Texture
uniform bool useTexture;
uniform sampler2D texMap;

//Deformation
uniform bool enableDeformation;
uniform float deformAmplitude; 
uniform float deformationTime;
uniform float deformationSpeed;
uniform float waveFrequency;
uniform float BboxSize;


// out to framebuffer 
out vec4 vColor;

vec3 computeLighting(vec3 P, vec3 N, vec3 V,
                     bool enabled, int type, vec3 pos, vec3 dir, vec3 intensity,  vec4 baseColor) {
    if (!enabled) return vec3(0.0);

    vec3 L;
    if (type == 0) { // DIRECTIONAL
        L = normalize(-dir);
    } else { // POINT
        L = normalize(pos - P);
    }

    float NdotL = dot(N, L);

    if (!materialDoubleSided && NdotL <= 0.0)
        return vec3(0.0);

    if (materialDoubleSided)
        NdotL = abs(NdotL);

    // Diffuse
    vec3 diffuse = baseColor.rgb  * NdotL * materialDiffuse * intensity ;

    // Specular
    vec3 R = reflect(-L, N);
    float RdotV = max(dot(R, V), 0.0);
    vec3 specular =  pow(RdotV, materialShininess) * materialSpecular * intensity ;

    return diffuse + specular;
}

void main()
{

    // Compute model matrix
    mat4 modelMatrix = objectMatrix * worldMatrix ;

    // transfer position to worlld space
     vec4 worldPos4 = vPosition * modelMatrix;
    vec3 worldPos = worldPos4.xyz;

    // transfer normal to world space
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    vec3 worldNormal = normalize(vNormal * normalMatrix);
    

    // Apply wave form deformation into world space
 
     if(enableDeformation){
        float wave = abs(cos(deformationTime * deformationSpeed + length(worldPos.xy) * waveFrequency));
        vec3 offset = worldNormal * wave * deformAmplitude * BboxSize*0.1; 
        worldPos += offset;

    }

    //handle double sided materials
    vec3 V = normalize(viewPos - worldPos);
    
    if (dot(worldNormal, V) < 0.0 && materialDoubleSided)
        worldNormal = -worldNormal;

    // calculate light
    vec3 color = vec3(0.0);
    vec4 baseColor = vec4(0.0);
    vec4 finalColor = vec4(0.0);

    if (useTexture) {
      baseColor = texture2D(texMap ,vTexCoords);

    }
    else {
        baseColor = vec4(materialBaseColor, 1.0);
    }

    // Ambient
    finalColor = vec4(ambientLight,1.0) * baseColor * materialAmbient;

    // Light 1
    color += computeLighting(worldPos, worldNormal, V,true,
                             light1Type, light1Position,
                             light1Direction, light1Intensity, baseColor);
    finalColor += vec4(color, 1.0);

    // Light 2
    color += computeLighting(worldPos, worldNormal, V,
                           light2Enabled, light2Type, light2Position,
                            light2Direction, light2Intensity, baseColor);
    finalColor += vec4(color, 1.0);

    vColor = finalColor;
	gl_Position =vec4(worldPos * scale , 1.0) * view * projection;
}
