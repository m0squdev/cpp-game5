#include "listener.h"

bool Listener::keys[], Listener::keyRetrieved[];
int Listener::lastPressedOnceKey;
bool Listener::mouseMoved = false;
float Listener::mouseX, Listener::mouseY, Listener::mouseXMovement, Listener::mouseYMovement;

void Listener::Init()
{
    for (int i = 0; i < KEY_LAST - KEY_SPACE; i++)
    {
        keys[i] = false;
        keyRetrieved[i] = false;
    }
}

void Listener::Create(GLFWwindow* window)
{
    glfwSetKeyCallback(window, Listener::KeyListener);
    glfwSetCursorPosCallback(window, Listener::MouseListener);
}

bool Listener::GetKeyPress(int key, bool pressedOnce)
{
    if (key >= KEY_SPACE && key <= KEY_MENU)
    {
        int _key = key - KEY_SPACE;
        if (pressedOnce)
        {
            if (keys[_key])
            {
                bool _keyRetrieved = keyRetrieved[_key];
                keyRetrieved[_key] = true;
                return !_keyRetrieved;
            }
            else
            {
                keyRetrieved[_key] = false;
                return keys[_key];
            }
        }
        else
        {
            return keys[_key];
        }
    }
    else
        ThrowErr::UnknownKey("Window::GetKeyPress");
}

void Listener::FirstPersonListener()
{
    if (Listener::GetKeyPress(KEY_A))
        Camera::GoLeft();
    if (Listener::GetKeyPress(KEY_D))
        Camera::GoRight();
    if (Listener::GetKeyPress(KEY_LEFT_SHIFT))
        Camera::GoDown();
    if (Listener::GetKeyPress(KEY_SPACE))
        Camera::GoUp();
    if (Listener::GetKeyPress(KEY_S))
        Camera::GoBackward();
    if (Listener::GetKeyPress(KEY_W))
        Camera::GoForward();
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