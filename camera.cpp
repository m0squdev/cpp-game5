#include "camera.h"

glm::vec3 Camera::pos, Camera::front, Camera::right, Camera::up, Camera::worldUp;
GLfloat Camera::yaw, Camera::pitch, Camera::movementSpeed, Camera::turnSpeed;
GLfloat Camera::maxPitch = 89.f;

void Camera::Create(GLfloat startMovementSpeed, GLfloat startTurnSpeed, glm::vec3 startPos, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch)
{
    pos = startPos;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;
    front = glm::vec3(0.f, 0.f, -1.f);
    movementSpeed = startMovementSpeed;
    turnSpeed = startTurnSpeed;
    Camera::Update();
}

GLfloat Camera::GetYaw()
{
    return yaw;
}

void Camera::SetYaw(GLfloat value)
{
    yaw = value;
}

GLfloat Camera::GetPitch()
{
    return pitch;
}

void Camera::SetPitch(GLfloat value)
{
    pitch = value;
}

GLfloat Camera::GetTurnSpeed()
{
    return turnSpeed;
}

glm::mat4 Camera::GetView()
{
    return glm::lookAt(pos, pos + front, up);
}

void Camera::GoLeft(float deltaTime)
{
    pos -= right * (movementSpeed * deltaTime);
}

void Camera::GoRight(float deltaTime)
{
    pos += right * (movementSpeed * deltaTime);
}

void Camera::GoDown(float deltaTime)
{
    pos -= worldUp * (movementSpeed * deltaTime);
}

void Camera::GoUp(float deltaTime)
{
    pos += worldUp * (movementSpeed * deltaTime);
}

void Camera::GoBackward(float deltaTime)
{
    pos -= front * (movementSpeed * deltaTime);
}

void Camera::GoForward(float deltaTime)
{
    pos += front * (movementSpeed * deltaTime);
}

void Camera::Update()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
    if (pitch > maxPitch)
        pitch = maxPitch;
    else if (pitch < -maxPitch)
        pitch = -maxPitch;
}