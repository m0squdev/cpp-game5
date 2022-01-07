#pragma once

#include <GL/glew.h>

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"

class Camera
{
    public:
        static void Create(GLfloat startMovementSpeed, GLfloat startTurnSpeed, glm::vec3 startPos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 startUp = glm::vec3(0.f, 1.f, 0.f), GLfloat startYaw = 90.f, GLfloat startPitch = 0.f);

        static GLfloat GetYaw();
        static void SetYaw(GLfloat value);

        static GLfloat GetPitch();
        static void SetPitch(GLfloat value);
        
        static GLfloat GetTurnSpeed();
        static glm::mat4 GetView();

        static void GoLeft(float deltaTime);
        static void GoRight(float deltaTime);
        static void GoDown(float deltaTime);
        static void GoUp(float deltaTime);
        static void GoBackward(float deltaTime);
        static void GoForward(float deltaTime);
        
        static void Update();

    private:
        static glm::vec3 pos, front, right, up, worldUp;
        static GLfloat yaw, pitch, maxPitch, movementSpeed, turnSpeed;
};