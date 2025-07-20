#version 460 //compatible with OpenGL version 4.6 (latest version)

// data about each vertex
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vNormal;

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

// out to framebuffer 
out vec3 vColor;

vec3 computeLighting(vec3 P, vec3 N, vec3 V,
                     bool enabled, int type, vec3 pos, vec3 dir, vec3 intensity) {
    if (!enabled) return vec3(0.0);

    vec3 L;
    if (type == 0) { // DIRECTIONAL
        L = normalize(dir);
    } else { // POINT
        L = normalize(pos - P);
    }

    float NdotL = dot(N, L);

    if (!materialDoubleSided && NdotL <= 0.0)
        return vec3(0.0);

    if (materialDoubleSided)
        NdotL = abs(NdotL);

    // Diffuse
    vec3 diffuse = materialBaseColor * NdotL  *materialDiffuse * intensity ;

    // Specular
    vec3 R = reflect(-L, N);
    float RdotV = max(dot(R, V), 0.0);
    vec3 specular =  pow(RdotV, materialShininess) *materialSpecular * intensity ;

    return diffuse + specular;
}

void main()
{

    mat4 modelMatrix = objectMatrix * worldMatrix ;
    
    vec4 worldPos4 = vPosition * modelMatrix;
    vec3 worldPos = worldPos4.xyz / worldPos4.w;

    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    vec3 worldNormal = normalize(vNormal * normalMatrix);

     vec3 V = normalize(viewPos - worldPos);


     if (dot(worldNormal, V) < 0.0 && materialDoubleSided)
        worldNormal = -worldNormal;

    vec3 color = vec3(0.0);
    // Ambient
    color += ambientLight * materialBaseColor * materialAmbient;

    // Light 1
    color += computeLighting(worldPos, worldNormal, V,true,
                             light1Type, light1Position,
                             light1Direction, light1Intensity);

    // Light 2
    color += computeLighting(worldPos, worldNormal, V,
                           light2Enabled, light2Type, light2Position,
                            light2Direction, light2Intensity);

    vColor = color;
	
    gl_Position = vPosition;

	gl_Position.w = gl_Position.w / scale;
	
	gl_Position = gl_Position * objectMatrix * worldMatrix  *view * projection;

}
