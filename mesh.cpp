#include "mesh.h"

GLuint Mesh::currentVao, Mesh::currentVbo, Mesh::currentIbo;

GLuint Mesh::Create(GLuint* indices, int indicesSize, GLfloat* vertices, int verticesSize, GLuint vbo, GLuint ibo)
{
    glGenVertexArrays(1, &currentVao);
    if (vbo)
        currentVbo = vbo;
    else
        glGenBuffers(1, &currentVbo);
    if (ibo)
        currentIbo = ibo;
    else
        glGenBuffers(1, &currentIbo);
    Mesh::Bind(currentVao, NULL);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    Mesh::Bind(NULL, currentVbo, NULL);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(sizeof(vertices[0]) * 3));
    glEnableVertexAttribArray(1);
    return currentVao;
}

GLuint Mesh::CreateWithProg(GLuint* indices, int indicesSize, GLfloat* vertices, int verticesSize, const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource, GLuint vbo, GLuint ibo, bool delShaders, bool showErr)
{
    Prog::CreateWithShaders(vertexShaderSource, fragmentShaderSource, delShaders, showErr);
    GLuint vao = Mesh::Create(indices, indicesSize, vertices, verticesSize, vbo, ibo);
    Mesh::BindWithProg();
    return vao;
}

GLuint Mesh::CreateWithProgFromShaderFiles(GLuint* indices, int indicesSize, GLfloat* vertices, int verticesSize, char* vertexShaderPath, char* fragmentShaderPath, GLuint vbo, GLuint ibo, bool delShaders, bool showErr)
{
    Prog::CreateWithShadersFromFiles(vertexShaderPath, fragmentShaderPath, delShaders, showErr);
    GLuint vao = Mesh::Create(indices, indicesSize, vertices, verticesSize, vbo, ibo);
    Mesh::BindWithProg();
    return vao;
}

void Mesh::Delete(GLuint vao, GLuint vbo, GLuint ibo)
{
    if (vao)
        glDeleteVertexArrays(1, &vao);
    if (vbo)
        glDeleteBuffers(1, &vao);
    if (ibo)
        glDeleteBuffers(1, &ibo);
}

void Mesh::DeleteWithProg(GLuint vao, GLuint vbo, GLuint ibo, GLuint prog)
{
    Mesh::Delete(vao, vbo, ibo);
    Prog::Delete(prog);
}

void Mesh::Bind(GLuint vao, GLuint vbo, GLuint ibo)
{
    if (vao)
    {
        currentVao = vao;
        glBindVertexArray(currentVao);
    }
    if (vbo)
    {
        currentVbo = vbo;
        glBindBuffer(GL_ARRAY_BUFFER, currentVbo);
    }
    if (ibo)
    {
        currentIbo = ibo;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentIbo);
    }
}

void Mesh::BindWithProg(GLuint vao, GLuint vbo, GLuint ibo, GLuint prog)
{
    Prog::Bind(prog);
    Mesh::Bind(vao, vbo, ibo);
}

void Mesh::Unbind(bool unbindVbo, bool unbindIbo)
{
    glBindVertexArray(0);
    if (unbindVbo)
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    if (unbindIbo)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::UnbindWithProg(bool unbindVbo, bool unbindIbo)
{
    Prog::Unbind();
    Mesh::Unbind(unbindVbo, unbindIbo);
}

GLuint Mesh::GetCurrentVao()
{
    return currentVao;
}

GLuint Mesh::GetCurrentVbo()
{
    return currentVbo;
}

GLuint Mesh::GetCurrentIbo()
{
    return currentIbo;
}

void Mesh::Render(GLint size, GLint offset)
{
    glDrawElements(GL_TRIANGLES, size / sizeof(GLuint), GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint) * 3));
}