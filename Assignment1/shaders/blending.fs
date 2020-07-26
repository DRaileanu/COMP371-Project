#version 330 core
out vec4 FragColor;
  
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

#define MAX_LIGHTS 3
uniform PointLight pointLights[MAX_LIGHTS];
uniform Material material;

uniform vec3 viewPos;

uniform sampler2D texture1;

uniform samplerCube depthCubeMap;
uniform float far_plane;
uniform bool shadows;

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;
in vec2 TexCoord;


vec3 CalcPointLight(PointLight light, vec3 norm, vec3 fragPos, vec3 viewDir);
float ShadowCalculation(vec3 FragPos);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    for(int i = 0; i<MAX_LIGHTS; ++i){
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
	}

    FragColor = vec4(result * vec3(texture(texture1, TexCoord)) , 1.0);
}

vec3 CalcPointLight(PointLight light, vec3 norm, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(norm, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    //float distance = length(light.position - fragPos);
    //float attenuation = 1.0 / (1 + 0.01 * distance + 0.0025 * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient;
    vec3 diffuse = light.diffuse * diff ;
    vec3 specular = light.specular * spec;
   // ambient *= attenuation;
    //diffuse *= attenuation;
    //specular *= attenuation;

     // calculate shadow
    float shadow = shadows ? ShadowCalculation(FragPos) : 0.0;                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)); 

    return lighting;

}

float ShadowCalculation(vec3 FragPos)
{
    // get vector between fragment position and light position
    vec3 fragToLight = FragPos - pointLights[0].position;
    // ise the fragment to light vector to sample from the depth map    
    float closestDepth = texture(depthCubeMap, fragToLight).r;
    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
    closestDepth *= far_plane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // test for shadows
    float bias = 0.5; // we use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;        
    // display closestDepth as debug (to visualize depth cubemap)
    // FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
        
    return shadow;
}