#pragma once

#include <GL/glew.h>
#include <fstream>

#include "log.h"

class Shader
{
    public:
        static GLuint Create(GLint shaderType, const GLchar* shaderSource, bool showErr = true);
        static GLuint CreateVertex(const GLchar* shaderSource, bool showErr = true);
        static GLuint CreateFragment(const GLchar* shaderSource, bool showErr = true);
        static GLuint CreateVertexFromFile(char* path, bool showErr = true);
        static GLuint CreateFragmentFromFile(char* path, bool showErr = true);
        static void Delete(GLuint shader);

        static GLint GetErrCode(GLuint shader, unsigned int type, GLint status, bool printWarn = false);
        static GLchar* GetErrLog(GLuint shader, unsigned int type, bool printWarn = false);
        
        static std::string GetFileContent(char* path);
};