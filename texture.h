#pragma once

#include "lib/soil/SOIL2.h"
#include "program.h"

class Texture
{
    public:
        static void Init();

        static GLuint Create(char* path);
        static void Delete(GLuint texture = currentTexture);

        static int GetWidth();
        static int GetHeight();

        static void Bind(GLuint texture = currentTexture);
        static void Unbind();

        static void SetUniform(GLuint texture = currentTexture);
    
    private:
        static GLuint currentTexture;
        static int currentWidth, currentHeight, currentBitDepth;
};