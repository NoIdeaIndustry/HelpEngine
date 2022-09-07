#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 texCoord;

struct Material
{
    bool useTexture;
    sampler2D albedoTexture;
    vec3 albedoColor;

    vec3 specularColor;

    float shininess;
};


#define MAX_LIGHT 7
struct Light
{
    int type;

    vec3 position;
    vec3 direction;
    bool usePosition;

    vec3 color;
    float intensity;

    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;

    float spotCutoff;
};
uniform vec4 ambientColor;


uniform Material material;
uniform Light lights[MAX_LIGHT];
uniform int lightCount;

uniform vec3 viewPos;


vec3 ComputeLight(Light currentLight)
{
    

    // diffuse 
    vec3 lightDir;
    if(currentLight.type == 0)
    {
        lightDir = normalize(-currentLight.direction);
    }
    

    if(currentLight.type > 0)
    {
        lightDir = normalize(currentLight.position - FragPos);

        float spotAttenuation = dot(lightDir, normalize(-currentLight.direction)) / currentLight.spotCutoff;
        if(currentLight.type == 2 && spotAttenuation < 1)
        {
            return vec3(0, 0, 0);
        }
    }

    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = currentLight.color * currentLight.intensity * diff;


    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    

    vec3 specular = material.specularColor * currentLight.intensity * spec;
    //total
    if(currentLight.type == 1)
    {
        float distance = length(currentLight.position - FragPos);
        float attenuation = 1 / 
        ((currentLight.quadraticAttenuation * distance * distance )
        + (currentLight.linearAttenuation * distance)
        + (currentLight.constantAttenuation));

        return vec3(diffuse + specular) * attenuation;
    }

    return vec3(diffuse + specular);
}


void main()
{
    //global lighting
    vec3 result;
    for(int i = 0; i < lightCount; i++)
    {
        result += ComputeLight(lights[i]);
    }

    //ambient
    result = result + vec3(ambientColor) * ambientColor.w;

    if(material.useTexture)
        result = result * vec3(texture(material.albedoTexture, texCoord)) * material.albedoColor;
    else
        result = result * material.albedoColor;

    FragColor = vec4(result, 1.0);
}


