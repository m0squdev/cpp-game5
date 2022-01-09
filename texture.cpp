#include "texture.h"

//#include "lib/stb_image/stb_image.h"

GLuint Texture::currentTexture;
int Texture::currentWidth, Texture::currentHeight, Texture::currentBitDepth;

void Texture::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

GLuint Texture::Create(char* path)
{
    unsigned char* image = SOIL_load_image(path, &currentWidth, &currentHeight, 0, SOIL_LOAD_RGBA);
    //unsigned char* image = stbi_load(path, &currentWidth, &currentHeight, &currentBitDepth, STBI_rgb_alpha);
    if (!image)
    {
        /*warn("Can't load texture number ", false);
        warn(currentTexture, false);
        warn(": ", false);
        warn(SOIL_last_result());*/
        warn("Cannot locate texture at ", false);
        warn(path);
    }
    glGenTextures(1, &currentTexture);
    Texture::Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, currentWidth, currentHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    Texture::Unbind();
    SOIL_free_image_data(image);
    //stbi_image_free(image);
    return currentTexture;
}

void Texture::Delete(GLuint texture)
{
    glDeleteTextures(1, &texture);
}

int Texture::GetWidth()
{
    return currentWidth;
}

int Texture::GetHeight()
{
    return currentHeight;
}

void Texture::Bind(GLuint texture)
{
    currentTexture = texture;
    glBindTexture(GL_TEXTURE_2D, currentTexture);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Set(GLuint texture)
{
    glActiveTexture(GL_TEXTURE0);
    Texture::Bind(texture);
    Prog::SetUniform("textureSlot", GL_TEXTURE0);
}