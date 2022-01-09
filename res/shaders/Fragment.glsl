#version 330

struct DirectionalLight
{
    float ambientIntensity;
    vec3 ambientColor;
    vec3 diffuseDirection;
    float diffuseIntensity;
    vec3 diffuseColor;
};

in vec4 vertexColor;
in vec2 vertexTextureCoord;
in vec3 vertexNormal;

uniform sampler2D textureSlot;
uniform DirectionalLight directionalLight;

out vec4 color;

void main()
{
    vec4 ambientLight = vec4(directionalLight.ambientColor, 1.f) * directionalLight.ambientIntensity;
    float diffuseFactor = max(dot(normalize(vertexNormal), normalize(directionalLight.diffuseDirection)), 0.f);
    vec4 diffuseLight = vec4(directionalLight.diffuseColor, 1.f) * directionalLight.diffuseIntensity * diffuseFactor;
    color = texture(textureSlot, vertexTextureCoord) * (ambientLight + diffuseLight);
}