#version 330

const int maxPointLights = 3;

struct Light
{
    vec3 ambientColor;
    float ambientIntensity;
    vec3 diffuseColor;
    float diffuseIntensity;
};

struct DirectionalLight
{
    Light base;
    vec3 direction;
};

struct PointLights
{
    Light base;
    float constant, linear, exponent;
    vec3 pos, color;
};

struct Material
{
    float specularShininess;
    float specularIntensity;
    vec3 specularColor;
};

in vec4 vertexColor;
in vec2 vertexTextureCoord;
in vec3 vertexNormal;
in vec3 vertexPos;

uniform sampler2D textureSlot;
uniform DirectionalLight directionalLight;
uniform Material material;
uniform PointLights pointLights[maxPointLights];
uniform int pointLightsCount;
uniform vec3 cameraPos;

out vec4 color;

vec4 CalcLightFromDirection(Light light, vec3 diffuseDirection)
{
    vec4 ambientLight = vec4(light.ambientColor, 1.f) * light.ambientIntensity;
    float diffuseFactor = max(dot(normalize(vertexNormal), normalize(diffuseDirection)), 0.f);
    vec4 diffuseLight = vec4(light.diffuseColor * light.diffuseIntensity * diffuseFactor, 1.f);
    vec4 specularLight = vec4(0, 0, 0, 0);
    if (diffuseFactor > 0.f)
    {
        vec3 distance = normalize(cameraPos - vertexPos);
        vec3 reflection = normalize(reflect(diffuseDirection, normalize(vertexNormal)));
        float specularFactor = dot(distance, reflection);
        if (specularFactor > 0.f)
        {
            specularFactor = pow(specularFactor, material.specularShininess);
            specularLight = vec4(material.specularColor * material.specularIntensity * specularFactor, 1.f);
        }
    }
    return (ambientLight + diffuseLight + specularLight);
}

vec4 CalcDirectionalLight()
{
    return CalcLightFromDirection(directionalLight.base, directionalLight.direction);
}

vec4 CalcPointLights()
{
    vec4 totalColor = vec4(0, 0, 0, 0);
    for (int n = 0; n < pointLightsCount; n++)
    {
        vec3 direction = vertexPos - pointLights[n].pos;
        float distance = length(direction);
        direction = normalize(direction);
        vec4 color = CalcLightFromDirection(pointLights[n].base, direction);
        float attenuation = pointLights[n].exponent * distance * distance + pointLights[n].linear * distance + pointLights[n].constant;
        totalColor += (color / attenuation);
    }
    return totalColor;
}

void main()
{
    vec4 finalDirectionalLight = CalcDirectionalLight();
    vec4 finalPointLights = CalcPointLights();
    vec4 finalLights = finalDirectionalLight + finalPointLights;
    color = texture(textureSlot, vertexTextureCoord) * finalLights;
}
