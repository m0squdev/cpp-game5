#pragma once

#include "program.h"

class Material
{
public:
    static void Set(GLfloat shininess, GLfloat intensity = 1.f, GLfloat r = 1.f, GLfloat g = 1.f, GLfloat b = 1.f);

private:
    static GLfloat currentSpecularIntensity, currentSpecularShininess, currentSpecularR, currentSpecularG, currentSpecularB;
};