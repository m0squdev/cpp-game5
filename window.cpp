#include "window.h"

GameWindow Window::currentWindow = NULL;
int Window::currentBufferWidth = NULL;
int Window::currentBufferHeight = NULL;
bool Window::keys[KEY_LAST - KEY_SPACE];
bool Window::mouseMoved = false;
float Window::mouseX = 0.f;
float Window::mouseY = 0.f;
float Window::mouseXMovement = 0.f;
float Window::mouseYMovement = 0.f;
float Window::deltaTime = 0.f;
float Window::lastTime = 0.f;

void Window::Init(int vMajor, int vMinor, int profile, bool forwardCompatible)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, vMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, vMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, forwardCompatible);
    for (int i = KEY_SPACE; i < KEY_LAST; i++)
    {
        keys[i] = false;
    }
}

void Window::InitLib(int vMajor, int vMinor, int profile, bool forwardCompatible)
{
    Window::Init(vMajor, vMinor, profile, forwardCompatible);
    Texture::Init();
}

GameWindow Window::Create(char* title, int width, int height, bool fullscreen)
{
    currentWindow = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (!currentWindow)
        err("Cannot create window with GLFW", nullptr);
    Window::Bind();
    glfwSetKeyCallback(currentWindow, Window::KeyListener);
    glfwSetCursorPosCallback(currentWindow, Window::MouseListener);
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
        ThrowErr::UndefinedWindow("Window::Update");
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

void Window::Bind(GameWindow window)
{
    currentWindow = window;
    glfwGetFramebufferSize(currentWindow, &currentBufferWidth, &currentBufferHeight);
    glfwMakeContextCurrent(currentWindow);
}

void Window::SetViewport(GLint xStart, GLint xLength, GLint yStart, GLint yLength)
{
    glViewport(xStart, yStart, xLength, yLength);
}

void Window::SetFullscreen(bool fullscreen)
{
    glfwSetWindowMonitor(currentWindow, fullscreen ? glfwGetPrimaryMonitor() : NULL, 0, 0, currentBufferWidth, currentBufferHeight, GLFW_DONT_CARE);
}

void Window::SetLoop(void (*func)())
{
    while (!glfwWindowShouldClose(currentWindow))
    {
        func();
    }
}

void Window::ExitLoop()
{
    if (currentWindow)
        glfwSetWindowShouldClose(currentWindow, true);
    else
        ThrowErr::UndefinedWindow("Window::SetShouldClose");
}

void Window::SetBgColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    glClearColor(r, g, b, a);
}

void Window::Enable3D()
{
    glEnable(GL_DEPTH_TEST);
}

void Window::EnableCursor()
{
    glfwSetInputMode(currentWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::DisableCursor()
{
    glfwSetInputMode(currentWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool Window::GetKeyPress(int key)
{
    if (key >= KEY_SPACE && key <= KEY_MENU)
        return keys[key - KEY_SPACE];
    else
        ThrowErr::UnknownKey("Window::GetKeyPress");
}

void Window::FirstPersonListener()
{
    if (Window::GetKeyPress(KEY_A))
        Camera::GoLeft(deltaTime);
    if (Window::GetKeyPress(KEY_D))
        Camera::GoRight(deltaTime);
    if (Window::GetKeyPress(KEY_LEFT_SHIFT))
        Camera::GoDown(deltaTime);
    if (Window::GetKeyPress(KEY_SPACE))
        Camera::GoUp(deltaTime);
    if (Window::GetKeyPress(KEY_S))
        Camera::GoBackward(deltaTime);
    if (Window::GetKeyPress(KEY_W))
        Camera::GoForward(deltaTime);
    float mouseXMovement = Window::GetMouseXMovement();
    float mouseYMovement = Window::GetMouseYMovement();
    mouseXMovement *= Camera::GetTurnSpeed();
    mouseYMovement *= Camera::GetTurnSpeed();
    Camera::SetYaw(Camera::GetYaw() + mouseXMovement);
    Camera::SetPitch(Camera::GetPitch() + mouseYMovement);
}

GLfloat Window::GetMouseX()
{
    return mouseX;
}

GLfloat Window::GetMouseY()
{
    return mouseY;
}

GLfloat Window::GetMouseXMovement()
{
    float returnMouseXMovement = mouseXMovement;
    mouseXMovement = 0.f;
    return returnMouseXMovement;
}

GLfloat Window::GetMouseYMovement()
{
    float returnMouseYMovement = mouseYMovement;
    mouseYMovement = 0.f;
    return returnMouseYMovement;
}

void Window::ResetBuffers()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

float Window::GetDeltaTime()
{
    return deltaTime;
}

void Window::KeyListener(GameWindow window, int key, int code, int action, int mode)
{
    /*if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }*/
    if (key >= KEY_SPACE && key <= KEY_MENU)
    {
        if (action == GLFW_PRESS)
            keys[key - KEY_SPACE] = true;
        else if (action == GLFW_RELEASE)
            keys[key - KEY_SPACE] = false;
    }
    else
        ThrowErr::UnknownKey("Window::KeyListener");
}

void Window::MouseListener(GameWindow window, double xPos, double yPos)
{
    if (!mouseMoved)
    {
        mouseX = xPos;
        mouseY = yPos;
        mouseMoved = true;
    }
    mouseXMovement = xPos - mouseX;
    mouseYMovement = mouseY - yPos;
    mouseX = xPos;
    mouseY = yPos;
}