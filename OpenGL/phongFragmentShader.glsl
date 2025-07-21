#version 460 
in vec3 FragPos;
in vec3 worldNormal;

out vec4 FragColor;

// Camera
uniform vec3 viewPos;

// Material
uniform vec3 materialBaseColor;
uniform float materialAmbient;
uniform float materialDiffuse;
uniform float materialSpecular;
uniform float materialShininess;
uniform bool materialDoubleSided;

// Ambient
uniform vec3 ambientLight;

// Light 1
uniform bool light1Enabled;
uniform int light1Type; // 0 = directional, 1 = point
uniform vec3 light1Position;
uniform vec3 light1Direction;
uniform vec3 light1Intensity;

// Light 2
uniform bool light2Enabled;
uniform int light2Type;
uniform vec3 light2Position;
uniform vec3 light2Direction;
uniform vec3 light2Intensity;

vec3 computeLighting(vec3 P, vec3 N, vec3 V,
                     bool enabled, int type, vec3 pos, vec3 dir, vec3 intensity) {
    if (!enabled) return vec3(0.0);
 

    vec3 L;
    if (type == 0) { // DIRECTIONAL
        L = normalize(-dir);
    } else { // POINT
        L = normalize(pos - P);
    }
   
    float NdotL  = dot(N, L);
    
    if (!materialDoubleSided && NdotL <= 0.0)
        return vec3(0.0);
   if (materialDoubleSided)
        NdotL = abs(NdotL);

    // Diffuse
    vec3 diffuse = materialBaseColor * NdotL * materialDiffuse * intensity;

    // Specular
    vec3 R = reflect(-L, N);
    float RdotV = max(dot(R, V), 0.0);
    vec3 specular = pow(RdotV, materialShininess) * materialSpecular * intensity;
    return diffuse + specular;
}

void main()
{
    vec3 color = vec3(0.0);

    vec3 N = normalize(worldNormal);

    vec3 V = normalize(viewPos - FragPos);

    if (materialDoubleSided && dot(N, V) < 0.0)
        N = -N;


    // Ambient
    //color += ambientLight * materialBaseColor * materialAmbient;

    // Light 1
    color += computeLighting(FragPos, N, V, true, light1Type, light1Position, light1Direction, light1Intensity);
  
    // Light 2
    color += computeLighting(FragPos, N, V, light2Enabled, light2Type, light2Position, light2Direction, light2Intensity);
     
    
    FragColor = vec4(color, 1.0);
}
