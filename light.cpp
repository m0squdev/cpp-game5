#include "light.h"

GLfloat Light::currentAmbientIntensity = 1.f;
GLfloat Light::currentAmbientR, Light::currentAmbientG, Light::currentAmbientB;
GLfloat Light::currentDiffuseIntensity = 1.f;
GLfloat Light::currentDiffuseR, Light::currentDiffuseG, Light::currentDiffuseB, Light::currentDiffuseX, Light::currentDiffuseY, Light::currentDiffuseZ;

void Light::SetAmbient(GLfloat intensity, GLfloat r, GLfloat g, GLfloat b)
{
    currentAmbientIntensity = intensity;
    currentAmbientR = r;
    currentAmbientG = g;
    currentAmbientB = b;
    Prog::SetUniform("directionalLight.ambientIntensity", currentAmbientIntensity);
    Prog::SetUniform("directionalLight.ambientColor", glm::vec3(currentAmbientR, currentAmbientG, currentAmbientB));
}

void Light::SetDiffuse(GLfloat x, GLfloat y, GLfloat z, GLfloat intensity, GLfloat r, GLfloat g, GLfloat b)
{
    currentDiffuseX = x;
    currentDiffuseY = y;
    currentDiffuseZ = z;
    currentDiffuseIntensity = intensity;
    currentDiffuseR = r;
    currentDiffuseG = g;
    currentDiffuseB = b;
    Prog::SetUniform("directionalLight.diffuseDirection", glm::vec3(currentDiffuseX, currentDiffuseY, currentDiffuseZ));
    Prog::SetUniform("directionalLight.diffuseIntensity", currentDiffuseIntensity);
    Prog::SetUniform("directionalLight.diffuseColor", glm::vec3(currentAmbientR, currentAmbientG, currentAmbientB));
}