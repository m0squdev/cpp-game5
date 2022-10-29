#include "log.h"

bool previousEndl = true;

void catStr(char* result, const char* str1, const char* str2)
{
//    char result[128] = "";
    result[0] = '\0';
    info(str1);
    strcat(result, (const char*)str1);
    info(str2);
    strcat(result, (const char*)str2);

    //return result;
}

std::string getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%F %X");
    return ss.str();   
}

void print(const char* type, const char* text, bool endl)
{
    if (previousEndl && type != nullptr)
        std::cout << "[" << getCurrentTime() << "] " << type << " ";
    std::cout << text;
    if (endl)
        std::cout << std::endl;
    previousEndl = endl;
}

void print(const char* type, const float n, bool endl)
{
    if (previousEndl && type != nullptr)
        std::cout << "[" << getCurrentTime() << "] " << type << " ";
    std::cout << n;
    if (endl)
        std::cout << std::endl;
    previousEndl = endl;
}

void info(const char* text, bool endl, bool intro)
{
    if (intro)
        print("*", text, endl);
    else
        print(nullptr, text, endl);
}

void info(const float n, bool endl, bool intro)
{
    if (intro)
        print("*", n, endl);
    else
        print(nullptr, n, endl);
}

void warn(const char* text, bool endl, bool intro)
{
    if (intro)
        print("Warning:", text, endl);
    else
        print(nullptr, text, endl);
}

void warn(const float n, bool endl, bool intro)
{
    if (intro)
        print("Warning:", n, endl);
    else
        print(nullptr, n, endl);
}

void err(const char* text, void (*func)(), bool endl, bool intro)
{
    if (intro)
        print("Error:", text, endl);
    else
        print(nullptr, text, endl);
    if (endl)
    {
        if (func != nullptr)
            func();
        exit(EXIT_FAILURE);
    }
}

void err(const float n, void (*func)(), bool endl, bool intro)
{
    if (intro)
        print("Error:", n, endl);
    else
        print(nullptr, n, endl);
    if (endl)
    {
        if (func != nullptr)
            func();
        exit(EXIT_FAILURE);
    }
}

void ThrowErr::Thrower(const char* type, const char* func, const char* text)
{
    err(type, nullptr, false);
    err(": ", nullptr, false);
    err(func, nullptr, false);
    err(" ", nullptr, false);
    err(text, nullptr);
}

void ThrowErr::UnknownShaderType(const char* func)
{
    ThrowErr::Thrower("UnknownShaderType", func, "got specified an unknown shader type (availables are GL_VERTEX_SHADER and GL_FRAGMENT_SHADER)");
}

void ThrowErr::UnknownShaderStatus(const char* func)
{
    ThrowErr::Thrower("UnknownShaderStatus", func, "got specified an unknown shader status (availables are GL_COMPILE_STATUS)");
}

void ThrowErr::UnknownProgStatus(const char* func)
{
    ThrowErr::Thrower("UnknownProgStatus", func, "got specified an unknown shader status (availables are GL_LINK_STATUS)");
}

void ThrowErr::NullMatAxes(const char* func)
{
    ThrowErr::Thrower("NullMatAxes", func, "got specified 0.0f for all the axes (set almost one of them to another number)");
}

void ThrowErr::UnknownTextureSlot(const char* func)
{
    ThrowErr::Thrower("UnknownTextureSlot", func, "got specified an unknown texture slot (availables are from GL_TEXTURE0 to GL_TEXTURE31)");
}

void ThrowErr::UnknownKey(const char* func)
{
    ThrowErr::Thrower("UnknownKey", func, "got specified an unexisting key");
}

void ThrowErr::UndefinedWindow(const char* func)
{
    ThrowErr::Thrower("UndefinedWindow", func, "got called but currentWindow was null (create a window by calling Window::Create or bind one with Window::Bind)");
}