#pragma once

#include "program.h"

class Mesh
{
    public:
        static GLuint Create(GLuint* indices, int indicesSize, GLfloat* vertices, int verticesSize, GLuint vbo = NULL, GLuint ibo = NULL);
        static GLuint CreateWithProg(GLuint* indices, int indicesSize, GLfloat* vertices, int verticesSize, const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource, GLuint vbo = NULL, GLuint ibo = NULL, bool delShaders = true, bool showErr = true);
        static GLuint CreateWithProgFromShaderFiles(GLuint* indices, int indicesSize, GLfloat* vertices, int verticesSize, char* vertexShaderPath, char* fragmentShaderPath, GLuint vbo = NULL, GLuint ibo = NULL, bool delShaders = true, bool showErr = true);
        static void Delete(GLuint vao = currentVao, GLuint vbo = currentVbo, GLuint ibo = currentIbo);
        static void DeleteWithProg(GLuint vao = currentVao, GLuint vbo = currentVbo, GLuint ibo = currentIbo, GLuint prog = Prog::GetCurrentProg());

        static void Bind(GLuint vao = currentVao, GLuint vbo = currentVbo, GLuint ibo = currentIbo);
        static void BindWithProg(GLuint vao = currentVao, GLuint vbo = currentVbo, GLuint ibo = currentIbo, GLuint prog = Prog::GetCurrentProg());
        static void Unbind(bool unbindVbo = true, bool unbindIbo = true);
        static void UnbindWithProg(bool unbindVbo = true, bool unbindIbo = true);

        static GLuint GetCurrentVao();
        static GLuint GetCurrentVbo();
        static GLuint GetCurrentIbo();

        static void Render(GLint size, GLint offset = 0);

    private:
        static GLuint currentVao, currentVbo, currentIbo;
};