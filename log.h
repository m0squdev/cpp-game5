#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

std::string getCurrentTime();

void print(const char* type, const char* text, bool endl = true);
void print(const char* type, const float n, bool endl = true);

void info(const char* text, bool endl = true, bool intro = true);
void info(const float n, bool endl = true, bool intro = true);

void warn(const char* text, bool endl = true, bool intro = true);
void warn(const float n, bool endl = true, bool intro = true);

void err(const char* text, void (*func)(), bool endl = true, bool intro = true);
void err(const float n, void (*func)(), bool endl = true, bool intro = true);

class ThrowErr
{
    private:
        static void Thrower(const char* type, const char* func, const char* text);
    public:
        // shader.cpp
        static void UnknownShaderType(const char* func);
        static void UnknownShaderStatus(const char* func);
        // program.cpp
        static void UnknownProgStatus(const char* func);
        static void NullMatAxes(const char* func);
        // texture.cpp
        static void UnknownTextureSlot(const char* func);
        // window.cpp
        static void UnknownKey(const char* func);
        static void UndefinedWindow(const char* func);
};