#include "camera.h"

glm::vec3 Camera::pos, Camera::front, Camera::right, Camera::up, Camera::worldUp;
GLfloat Camera::yaw, Camera::yawSin, Camera::yawCos, Camera::pitch, Camera::pitchSin, Camera::pitchCos, Camera::movementSpeed, Camera::turnSpeed, Camera::frontXMovement, Camera::frontZMovement;
GLfloat Camera::maxPitch = 89.f;
glm::vec3 Camera::rightMovement, Camera::upMovement;

void Camera::Create(GLfloat startMovementSpeed, GLfloat startTurnSpeed, glm::vec3 startPos, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch)
{
    pos = startPos;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;
    front = glm::vec3(0.f, 0.f, -1.f);
    movementSpeed = startMovementSpeed;
    turnSpeed = startTurnSpeed;
    //Camera::Update();
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

void Camera::GoRight()
{
    pos += rightMovement;
}

void Camera::GoLeft()
{
    pos -= rightMovement;
}

void Camera::GoDown()
{
    //pos -= worldUp * (movementSpeed * deltaTime);
    pos -= upMovement;
}

void Camera::GoUp()
{
    //pos += worldUp * (movementSpeed * deltaTime);
    pos += upMovement;
}

void Camera::GoBackward()
{
    //pos -= glm::vec3(front.x, 0.f, front.z) * (movementSpeed * deltaTime);
    pos.x -= frontXMovement;
    pos.z -= frontZMovement;
}

#include "log.h"

void Camera::GoForward()
{
    //pos += glm::vec3(front.x, 0.f, front.z) * (movementSpeed * deltaTime);
    pos.x += frontXMovement;
    pos.z += frontZMovement;

}

void Camera::Update(float deltaTime)
{
    if (pitch > maxPitch)
        pitch = maxPitch;
    else if (pitch < -maxPitch)
        pitch = -maxPitch;
    yawSin = sin(glm::radians(yaw));
    yawCos = cos(glm::radians(yaw));
    pitchSin = sin(glm::radians(pitch));
    pitchCos = cos(glm::radians(pitch));
    front.x = yawCos * pitchCos;
    front.y = pitchSin;
    front.z = yawSin * pitchCos;
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
    frontXMovement = yawCos * (movementSpeed * deltaTime);
    frontZMovement = yawSin * (movementSpeed * deltaTime);
    rightMovement = right * (movementSpeed * deltaTime);
    upMovement = worldUp * (movementSpeed * deltaTime);
}