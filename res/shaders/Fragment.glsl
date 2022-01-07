#version 330

struct DirectionalLight
{
    vec3 color;
    float ambientIntensity;
};

in vec4 vertexColor;
in vec2 vertexTextureCoord;

uniform sampler2D textureSlot;
uniform DirectionalLight directionalLight;

out vec4 color;

void main()
{
    vec4 ambientColor = vec4(directionalLight.color, 1.f) * directionalLight.ambientIntensity;
    color = texture(textureSlot, vertexTextureCoord) * ambientColor;
}