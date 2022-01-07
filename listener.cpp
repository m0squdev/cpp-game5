#include "listener.h"

bool Listener::keys[];
bool Listener::mouseMoved = false;
float Listener::mouseX, Listener::mouseY, Listener::mouseXMovement, Listener::mouseYMovement, Listener::deltaTime;

void Listener::Init()
{
    for (int i = KEY_SPACE; i < KEY_LAST; i++)
    {
        keys[i] = false;
    }
}

void Listener::Create(GLFWwindow* window)
{
    glfwSetKeyCallback(window, Listener::KeyListener);
    glfwSetCursorPosCallback(window, Listener::MouseListener);
}

bool Listener::GetKeyPress(int key)
{
    if (key >= KEY_SPACE && key <= KEY_MENU)
        return keys[key - KEY_SPACE];
    else
        ThrowErr::UnknownKey("Window::GetKeyPress");
}

void Listener::SetDeltaTime(float value)
{
    deltaTime = value;
}

void Listener::FirstPersonListener()
{
    if (Listener::GetKeyPress(KEY_A))
        Camera::GoLeft(deltaTime);
    if (Listener::GetKeyPress(KEY_D))
        Camera::GoRight(deltaTime);
    if (Listener::GetKeyPress(KEY_LEFT_SHIFT))
        Camera::GoDown(deltaTime);
    if (Listener::GetKeyPress(KEY_SPACE))
        Camera::GoUp(deltaTime);
    if (Listener::GetKeyPress(KEY_S))
        Camera::GoBackward(deltaTime);
    if (Listener::GetKeyPress(KEY_W))
        Camera::GoForward(deltaTime);
    float mouseXMovement = Listener::GetMouseXMovement();
    float mouseYMovement = Listener::GetMouseYMovement();
    mouseXMovement *= Camera::GetTurnSpeed();
    mouseYMovement *= Camera::GetTurnSpeed();
    Camera::SetYaw(Camera::GetYaw() + mouseXMovement);
    Camera::SetPitch(Camera::GetPitch() + mouseYMovement);
}

GLfloat Listener::GetMouseX()
{
    return mouseX;
}

GLfloat Listener::GetMouseY()
{
    return mouseY;
}

GLfloat Listener::GetMouseXMovement()
{
    float returnMouseXMovement = mouseXMovement;
    mouseXMovement = 0.f;
    return returnMouseXMovement;
}

GLfloat Listener::GetMouseYMovement()
{
    float returnMouseYMovement = mouseYMovement;
    mouseYMovement = 0.f;
    return returnMouseYMovement;
}

void Listener::KeyListener(GLFWwindow* window, int key, int code, int action, int mode)
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

void Listener::MouseListener(GLFWwindow* window, double xPos, double yPos)
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