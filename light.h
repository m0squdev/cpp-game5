#pragma once

#include "program.h"

class Light
{
    public:
        static void SetAmbient(GLfloat ambientIntensity = currentAmbientIntensity, GLfloat r = currentR, GLfloat g = currentG, GLfloat b = currentB);

    private:
        static GLfloat currentAmbientIntensity, currentR, currentG, currentB;
};