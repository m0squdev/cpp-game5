#version 330

in vec4 vertexColor;
in vec2 vertexTextureCoord;

uniform sampler2D textureSlot;

out vec4 color;

void main()
{
    color = texture(textureSlot, vertexTextureCoord);
}