#pragma once

#include "program.h"

class Light
{
public:
    static void SetAmbient(GLfloat intensity = 1.f, GLfloat r = 1.f, GLfloat g = 1.f, GLfloat b = 1.f);
    
    static void SetDiffuse(GLfloat x = currentDiffuseX, GLfloat y = currentDiffuseY, GLfloat z = currentDiffuseZ, GLfloat intensity = 1.f, GLfloat r = 1.f, GLfloat g = 1.f, GLfloat b = 1.f);

private:
    static GLfloat currentAmbientIntensity, currentAmbientR, currentAmbientG, currentAmbientB;
    static GLfloat currentDiffuseIntensity, currentDiffuseR, currentDiffuseG, currentDiffuseB, currentDiffuseX, currentDiffuseY, currentDiffuseZ;
};