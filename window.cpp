#include "window.h"

GLFWwindow* Window::currentWindow = NULL;
int Window::currentBufferWidth = NULL;
int Window::currentBufferHeight = NULL;
int Window::lastWindowedBufferWidth = NULL;
int Window::lastWindowedBufferHeight = NULL;
float Window::deltaTime = 0.f;
float Window::lastTime = 0.f;

void Window::Init(int vMajor, int vMinor, int profile, bool forwardCompatible, int fps)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, vMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, vMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, forwardCompatible);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    glfwWindowHint(GLFW_REFRESH_RATE, fps);
}

void Window::InitLib(int vMajor, int vMinor, int profile, bool forwardCompatible, int fps)
{
    Window::Init(vMajor, vMinor, profile, forwardCompatible, fps);
    Listener::Init();
    Texture::Init();
}

GLFWwindow* Window::Create(char* title, int width, int height, bool fullscreen)
{
    currentWindow = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (!currentWindow)
        err("Cannot create window with GLFW", nullptr);
    Window::Bind();
    Listener::Create(currentWindow);
    //glfwSetWindowUserPointer(currentWindow, this);
    return currentWindow;
        
}

void Window::Delete()
{
    if (currentWindow)
    {
        glfwSetWindowShouldClose(currentWindow, true);
        glfwDestroyWindow(currentWindow);
        glfwTerminate();
    }
    else
        ThrowErr::UndefinedWindow("Window::Delete");
}

void Window::Bind(GLFWwindow* window)
{
    currentWindow = window;
    Window::UpdateBufferSize();
    glfwMakeContextCurrent(currentWindow);
}

int Window::GetBufferWidth()
{
    if (currentBufferWidth)
        return currentBufferWidth;
    else
        ThrowErr::UndefinedWindow("Window::GetBufferWidth");
}

int Window::GetBufferHeight()
{
    if (currentBufferHeight)
        return currentBufferHeight;
    else
        ThrowErr::UndefinedWindow("Window::GetBufferHeight");
}

void Window::SetBufferWidth(int value)
{
    currentBufferWidth = value;
}

void Window::SetBufferHeight(int value)
{
    currentBufferHeight = value;
}

void Window::SetViewport(GLint xStart, GLint xLength, GLint yStart, GLint yLength)
{
    glViewport(xStart, yStart, xLength, yLength);
}

void Window::SetFullscreen(bool value)
{
    if (value)
    {
        lastWindowedBufferWidth = currentBufferWidth;
        lastWindowedBufferHeight = currentBufferHeight;
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        currentBufferWidth = mode->width;
        currentBufferHeight = mode->height;
    }
    else
    {
        currentBufferWidth = lastWindowedBufferWidth;
        currentBufferHeight = lastWindowedBufferHeight;
    }
    glfwSetWindowMonitor(currentWindow, value ? glfwGetPrimaryMonitor() : NULL, 0, 0, currentBufferWidth, currentBufferHeight, GLFW_DONT_CARE);
    Window::SetViewport();
}

void Window::SetCursor(bool value)
{
    glfwSetInputMode(currentWindow, GLFW_CURSOR, value ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void Window::RunLoop(void (*func)())
{
    while (!glfwWindowShouldClose(currentWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Camera::Update(deltaTime);
        func();
        Window::Update();
    }
}

void Window::ExitLoop()
{
    if (currentWindow)
        glfwSetWindowShouldClose(currentWindow, true);
    else
        ThrowErr::UndefinedWindow("Window::SetShouldClose");
}

void Window::SetBgColor(GLfloat r, GLfloat g, GLfloat b)
{
    glClearColor(r, g, b, 1.f);
}

void Window::Enable3D()
{
    glEnable(GL_DEPTH_TEST);
}

float Window::GetDeltaTime()
{
    return deltaTime;
}

void Window::UpdateBufferSize()
{
    glfwGetFramebufferSize(currentWindow, &currentBufferWidth, &currentBufferHeight);
}

void Window::Update()
{
    if (currentWindow)
    {
        glfwSwapBuffers(currentWindow);
        glfwPollEvents();
        float now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;
    }
    else
        ThrowErr::UndefinedWindow("Window::Update");
}