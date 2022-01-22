#include "program.h"

GLuint Prog::currentProg;
GLchar* Prog::currentUniformName;
GLint Prog::currentUniformLocation;
glm::mat4 Prog::modelMat(1.f), Prog::projectionMat(1.f);

GLuint Prog::Create(GLuint vertexShader, GLuint fragmentShader, bool delShaders, bool showErr)
{
    currentProg = glCreateProgram();
    Prog::Bind();
    glAttachShader(currentProg, vertexShader);
    glAttachShader(currentProg, fragmentShader);
    glLinkProgram(currentProg);
    if (showErr)
    {
        GLint success = Prog::GetErrCode(currentProg, GL_LINK_STATUS, true);
        if (!success)
            Prog::GetErrLog(currentProg, true);
    }
    if (delShaders)
    {
        Shader::Delete(vertexShader);
        Shader::Delete(fragmentShader);
    }
    return currentProg;
}

GLuint Prog::CreateWithShaders(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource, bool delShaders, bool showErr)
{
    GLuint vertexShader = Shader::CreateVertex(vertexShaderSource, showErr);
    GLuint fragmentShader = Shader::CreateFragment(fragmentShaderSource, showErr);
    GLuint prog = Prog::Create(vertexShader, fragmentShader, delShaders, showErr);
    return prog;
}

GLuint Prog::CreateWithShadersFromFiles(char* vertexShaderPath, char* fragmentShaderPath, bool delShaders, bool showErr)
{
    GLuint vertexShader = Shader::CreateVertexFromFile(vertexShaderPath, showErr);
    GLuint fragmentShader = Shader::CreateFragmentFromFile(fragmentShaderPath, showErr);
    GLuint prog = Prog::Create(vertexShader, fragmentShader, delShaders, showErr);
    return prog;
}

void Prog::Delete(GLuint prog)
{
    glDeleteProgram(prog);
}

void Prog::Bind(GLuint prog)
{
    currentProg = prog;
    glUseProgram(currentProg);
}

void Prog::Unbind()
{
    glUseProgram(0);
}

GLuint Prog::GetCurrentProg()
{
    return currentProg;
}

GLint Prog::GetErrCode(GLuint prog, GLint status, bool printWarn)
{
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(prog, status, &success);
    if (!success && printWarn)
    {
        warn("Cannot ", false);
        if (status == GL_LINK_STATUS)
            warn("compile", false);
        else
            ThrowErr::UnknownProgStatus("Prog::GetErrCode");
        warn(" program number ", false);
        warn(prog, false);
        warn(" (error code ", false);
        warn(success, false);
        warn(")");
    }
    return success;
}

GLchar* Prog::GetErrLog(GLuint prog, bool printWarn)
{
    GLchar infoLog[512];
    glGetProgramInfoLog(prog, 512, NULL, infoLog);
    if (printWarn)
    {
        warn("Log for program number ", false);
        warn(prog, false);
        warn(":");
        warn(infoLog, true, false);
    }
    return infoLog;
}

GLint Prog::BindUniform(GLchar* name)
{
    if (name != currentUniformName);
    {
        currentUniformName = name;
        currentUniformLocation = glGetUniformLocation(currentProg, currentUniformName);
        if (currentUniformLocation == -1)
        {
            warn("Cannot locate uniform ", false);
            warn(currentUniformName);
        }
    }
    return currentUniformLocation;
}

void Prog::SetUniform(GLchar* name, GLint value)
{
    Prog::BindUniform(name);
    if (currentUniformLocation != -1)
        glUniform1i(currentUniformLocation, value);
}

void Prog::SetUniform(GLchar* name, GLfloat value)
{
    Prog::BindUniform(name);
    if (currentUniformLocation != -1)
        glUniform1f(currentUniformLocation, value);
}

void Prog::SetUniform(GLchar* name, glm::vec3 value)
{
    Prog::BindUniform(name);
    if (currentUniformLocation != -1)
        glUniform3f(currentUniformLocation, value.x, value.y, value.z);
}

void Prog::SetUniform(GLchar* name, glm::mat4 value)
{
    Prog::BindUniform(name);
    if (currentUniformLocation != -1)
        glUniformMatrix4fv(currentUniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Prog::UpdateModel()
{
    Prog::SetUniform("modelMat", modelMat);
    modelMat = glm::mat4(1.f);
}

glm::mat4 Prog::TranslateModel(float x, float y, float z)
{
    modelMat = glm::translate(modelMat, glm::vec3(x, y, z));
    return modelMat;
}

glm::mat4 Prog::RotateModel(float x, float y, float z, float angle = 0.f)
{
    if (!x && !y && !z)
        ThrowErr::NullMatAxes("Prog::SetModelMat");
    else
        modelMat = glm::rotate(modelMat, glm::radians(angle), glm::vec3(x, y, z));
        return modelMat;
}
glm::mat4 Prog::ScaleModel(float x, float y, float z)
{
    modelMat = glm::scale(modelMat, glm::vec3(x, y, z));
    return modelMat;
}

void Prog::SetProjection(int width, int height, float near, float far, float fov)
{
    projectionMat = glm::perspective(fov, (float)width / (float)height, near, far);
    Prog::SetUniform("projectionMat", projectionMat);
    projectionMat = glm::mat4(1.f);
}

void Prog::UpdateView()
{
    Prog::SetUniform("viewMat", Camera::GetView());
}

void Prog::UpdatePos()
{
    Prog::SetUniform("cameraPos", Camera::GetPos());
}