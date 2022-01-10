#pragma once

#include "mesh.h"
#include "texture.h"
#include "light.h"
#include "material.h"
#include "listener.h"

class Window
{
public:
    static void Init(int vMajor = 3, int vMinor = 3, int profile = GLFW_OPENGL_CORE_PROFILE, bool forwardCompatible = GLFW_TRUE, int fps = 60);
    static void InitLib(int vMajor = 3, int vMinor = 3, int profile = GLFW_OPENGL_CORE_PROFILE, bool forwardCompatible = GLFW_TRUE, int fps = 60);

    static GLFWwindow* Create(char* title, int width, int height, bool fullscreen = false);
    static void Delete();

    static void Bind(GLFWwindow* window = currentWindow);

    static int GetBufferWidth();
    static int GetBufferHeight();
    static void SetBufferWidth(int value);
    static void SetBufferHeight(int value);

    static void SetViewport(GLint xStart = 0, GLint xLength = currentBufferWidth, GLint yStart = 0, GLint yLength = currentBufferHeight);
    static void SetFullscreen(bool value);
    static void SetCursor(bool value);

    static void RunLoop(void (*func)());
    static void ExitLoop();

    static void SetBgColor(GLfloat r, GLfloat g, GLfloat b);
    static void Enable3D();

    static float GetDeltaTime();

private:
    static GLFWwindow* currentWindow;
    static int currentBufferWidth, currentBufferHeight, lastWindowedBufferWidth, lastWindowedBufferHeight;
    static float deltaTime, lastTime;

    static void UpdateBufferSize();

    static void Update();
};