#include "light.h"

GLfloat Light::currentAmbientIntensity, Light::currentR, Light::currentG, Light::currentB;

void Light::SetAmbient(GLfloat ambientIntensity, GLfloat r, GLfloat g, GLfloat b)
{
    currentAmbientIntensity = ambientIntensity;
    currentR = r;
    currentG = g;
    currentB = b;
    Prog::SetUniform("directionalLight.color", glm::vec3(currentR, currentG, currentB));
    Prog::SetUniform("directionalLight.ambientIntensity", currentAmbientIntensity);
}