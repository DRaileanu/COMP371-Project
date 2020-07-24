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
    //vec3 colour;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

#define MAX_LIGHTS 5
uniform PointLight pointLights[MAX_LIGHTS];
uniform Material material;

uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;

vec3 CalcPointLight(PointLight light, vec3 norm, vec3 FragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    for(int i = 0; i<MAX_LIGHTS; i++){
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
	}

    FragColor = vec4(result * Color, 0.4f);
}

vec3 CalcPointLight(PointLight light, vec3 norm, vec3 FragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - FragPos);
    // diffuse shading
    float diff = max(dot(norm, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    //float distance = length(light.position - FragPos);
    //float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    //ambient *= attenuation;
    //diffuse *= attenuation;
    //specular *= attenuation;
    return (ambient + diffuse + specular );

}