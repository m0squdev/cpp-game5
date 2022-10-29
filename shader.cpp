#include "shader.h"

GLuint Shader::Create(GLint shaderType, const GLchar* shaderSource, bool showErr)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    if (showErr)
    {
        GLint success = Shader::GetErrCode(shader, shaderType, GL_COMPILE_STATUS, true);
        if (!success)
            Shader::GetErrLog(shader, shaderType, true);
    }
    return shader;
}

GLuint Shader::CreateVertex(const GLchar* shaderSource, bool showErr)
{
    GLuint shader = Shader::Create(GL_VERTEX_SHADER, shaderSource, showErr);
    return shader;
}

GLuint Shader::CreateFragment(const GLchar* shaderSource, bool showErr)
{
    GLuint shader = Shader::Create(GL_FRAGMENT_SHADER, shaderSource, showErr);
    return shader;
}

GLuint Shader::CreateVertexFromFile(char* path, bool showErr)
{
    GLuint shader = Shader::CreateVertex((char*)Shader::GetFileContent(path).c_str(), showErr);
    return shader;
}

GLuint Shader::CreateFragmentFromFile(char* path, bool showErr)
{
    GLuint shader = Shader::CreateFragment((char*)Shader::GetFileContent(path).c_str(), showErr);
    return shader;
}

void Shader::Delete(GLuint shader)
{
    glDeleteShader(shader);
}

GLint Shader::GetErrCode(GLuint shader, unsigned int type, GLint status, bool printWarn)
{
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, status, &success);
    if (!success && printWarn)
    {
        warn("Cannot ", false);
        if (status == GL_COMPILE_STATUS)
            warn("compile", false);
        else
            ThrowErr::UnknownShaderStatus("Shader::GetErrCode");
        warn(" ", false);
        if (type == GL_VERTEX_SHADER)
            warn("vertex", false);
        else if (type == GL_FRAGMENT_SHADER)
            warn("fragment", false);
        else
            ThrowErr::UnknownShaderType("Shader::GetErrCode");
        warn(" shader number ", false);
        warn(shader, false);
        warn(" (error code ", false);
        warn(success, false);
        warn(")");
    }
    return success;
}

GLchar* Shader::GetErrLog(GLuint shader, unsigned int type, bool printWarn)
{
    GLchar infoLog[512];
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    if (printWarn)
    {
        warn("Cannot compile ", false);
        if (type == GL_VERTEX_SHADER)
            warn("vertex", false);
        else if (type == GL_FRAGMENT_SHADER)
            warn("fragment", false);
        else
            ThrowErr::UnknownShaderType("Shader::GetErrLog");
        warn(" shader number ", false);
        warn(shader, false);
        warn(". The error log is the following:");
        warn(infoLog, true, false);
    }
    return infoLog;
}

std::string Shader::GetFileContent(char* path)
{
    std::string stringPath = path;
    std::ifstream stream(stringPath);
    std::string line;
    std::stringstream ss;
    while (getline(stream, line))
    {
        ss << line << std::endl;
    }
    return ss.str();
}