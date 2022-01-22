#pragma once

#include "lib/glm/gtc/type_ptr.hpp"
#include "camera.h"
#include "shader.h"

class Prog
{
public:
    static GLuint Create(GLuint vertexShader, GLuint fragmentShader, bool delShaders = true, bool showErr = true);
    static GLuint CreateWithShaders(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource, bool delShaders = true, bool showErr = true);
    static GLuint CreateWithShadersFromFiles(char* vertexShaderPath, char* fragmentShaderPath, bool delShaders = true, bool showErr = true);
    static void Delete(GLuint prog = currentProg);

    static void Bind(GLuint prog = currentProg);
    static void Unbind();

    static GLuint GetCurrentProg();
    static GLint GetErrCode(GLuint prog, GLint status, bool printWarn = false);
    static GLchar* GetErrLog(GLuint prog, bool printWarn = false);

    static GLint BindUniform(GLchar* name);
    static void SetUniform(GLchar* name, GLint value);
    static void SetUniform(GLchar* name, GLfloat value);
    static void SetUniform(GLchar* name, glm::vec3 value);
    static void SetUniform(GLchar* name, glm::mat4 value);

    static void UpdateModel();
    static glm::mat4 TranslateModel(float x, float y, float z);
    static glm::mat4 RotateModel(float x, float y, float z, float angle);
    static glm::mat4 ScaleModel(float x, float y, float z);

    static void SetProjection(int width, int height, float near, float far, float fov = 45.f);

    static void UpdateView();

    static void UpdatePos();

private:
    static GLuint currentProg;
    static GLchar* currentUniformName;
    static GLint currentUniformLocation;
    static glm::mat4 modelMat, projectionMat;
};