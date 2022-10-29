#pragma once

#include "program.h"

#define MAX_POINT_LIGHTS 3

class Light
{
public:
    static void SetAmbient(GLfloat intensity = 1.f, GLfloat r = 1.f, GLfloat g = 1.f, GLfloat b = 1.f);
    static void SetDiffuse(GLfloat x = currentDiffuseX, GLfloat y = currentDiffuseY, GLfloat z = currentDiffuseZ, GLfloat intensity = 1.f, GLfloat r = 1.f, GLfloat g = 1.f, GLfloat b = 1.f);
    static int CreatePoint(GLfloat constant, GLfloat linear, GLfloat exponent, GLfloat x = currentPointX, GLfloat y = currentPointY, GLfloat z = currentPointZ, GLfloat r = 1.f, GLfloat g = 1.f, GLfloat b = 1.f);
    static void SetPoints();

private:
    static GLfloat currentAmbientIntensity, currentAmbientR, currentAmbientG, currentAmbientB;
    static GLfloat currentDiffuseIntensity, currentDiffuseR, currentDiffuseG, currentDiffuseB, currentDiffuseX, currentDiffuseY, currentDiffuseZ;
    static GLfloat currentPointR, currentPointG, currentPointB, currentPointX, currentPointY, currentPointZ, currentPointConstant, currentPointLinear, currentPointExponent;
    static int pointLightsCount;
};