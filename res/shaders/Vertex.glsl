#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 normal;

uniform mat4 modelMat;
uniform mat4 projectionMat;
uniform mat4 viewMat;

out vec4 vertexColor;
out vec2 vertexTextureCoord;
out vec3 vertexNormal;
out vec3 vertexPos;

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(position, 1.);
    vertexColor = vec4(clamp(position, 0.f, 1.f), 1.f);
    vertexTextureCoord = textureCoord;
    vertexNormal = mat3(transpose(inverse(modelMat))) * normal;
    vertexPos = (modelMat * vec4(position, 1.)).xyz;
}