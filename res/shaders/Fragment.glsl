#version 330

struct DirectionalLight
{
    float ambientIntensity;
    vec3 ambientColor;
    vec3 diffuseDirection;
    float diffuseIntensity;
    vec3 diffuseColor;
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
uniform vec3 cameraPos;

out vec4 color;

void main()
{
    vec4 ambientLight = vec4(directionalLight.ambientColor, 1.f) * vec4(vec3(directionalLight.ambientIntensity), 1.f);
    float diffuseFactor = max(dot(normalize(vertexNormal), normalize(directionalLight.diffuseDirection)), 0.f);
    vec4 diffuseLight = vec4(directionalLight.diffuseColor, 1.f) * directionalLight.diffuseIntensity * diffuseFactor;
    vec4 specularLight = vec4(0, 0, 0, 0);
    if (diffuseFactor > 0.f)
    {
        vec3 distance = normalize(cameraPos - vertexPos);
        vec3 reflection = normalize(reflect(directionalLight.diffuseDirection, normalize(vertexNormal)));
        float specularFactor = dot(distance, reflection);
        if (specularFactor > 0.f)
        {
            specularFactor = pow(specularFactor, material.specularShininess);
            specularLight = vec4(material.specularColor * material.specularIntensity * specularFactor, 1.f);
        }
    }
    color = texture(textureSlot, vertexTextureCoord) * (ambientLight + diffuseLight + specularLight);
}