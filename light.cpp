#include "light.h"

GLfloat Light::currentAmbientIntensity, Light::currentAmbientR, Light::currentAmbientG, Light::currentAmbientB;
GLfloat Light::currentDiffuseIntensity, Light::currentDiffuseR, Light::currentDiffuseG, Light::currentDiffuseB, Light::currentDiffuseX, Light::currentDiffuseY, Light::currentDiffuseZ;
GLfloat Light::currentPointR, Light::currentPointG, Light::currentPointB, Light::currentPointX, Light::currentPointY, Light::currentPointZ, Light::currentPointConstant, Light::currentPointLinear, Light::currentPointExponent;
int Light::pointLightsCount;
struct
{
    GLfloat r, g, b, x, y, z, constant, linear, exponent;
} pointLights[MAX_POINT_LIGHTS];

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

int Light::CreatePoint(GLfloat constant, GLfloat linear, GLfloat exponent, GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b)
{
    currentPointConstant = constant;
    currentPointLinear = linear;
    currentPointExponent = exponent;
    currentPointX = x;
    currentPointY = y;
    currentPointZ = z;
    currentPointR = r;
    currentPointG = g;
    currentPointB = b;
    pointLightsCount++;
    pointLights[pointLightsCount].constant = constant;
    pointLights[pointLightsCount].linear = linear;
    pointLights[pointLightsCount].exponent = exponent;
    pointLights[pointLightsCount].x = x;
    pointLights[pointLightsCount].y = y;
    pointLights[pointLightsCount].z = z;
    pointLights[pointLightsCount].r = r;
    pointLights[pointLightsCount].g = g;
    pointLights[pointLightsCount].b = b;
    /*Prog::SetUniform("constant", currentPointConstant);
    Prog::SetUniform("linear", currentPointLinear);
    Prog::SetUniform("exponent", currentPointExponent);
    Prog::SetUniform("pos", glm::vec3(currentPointX, currentPointY, currentPointZ));
    Prog::SetUniform("color", glm::vec3(currentPointR, currentPointG, currentPointB));
    Prog::SetUniform("pointLightsCount", pointLightsCount);*/
}

void Light::SetPoints()
{
    for (int n = 0; n < pointLightsCount; n++)
    {
        char* prefix = strcat(strcat("pointLights[", (char*)n), "].");
        Prog::SetUniform(strcat(prefix, "constant"), pointLights[n].constant);
        Prog::SetUniform(strcat(prefix, "linear"), pointLights[n].linear);
        Prog::SetUniform(strcat(prefix, "exponent"), pointLights[n].exponent);
        Prog::SetUniform(strcat(prefix, "pos"), glm::vec3(pointLights[n].x, pointLights[n].y, pointLights[n].z));
        Prog::SetUniform(strcat(prefix, "color"), glm::vec3(pointLights[n].r, pointLights[n].g, pointLights[n].b));
        Prog::SetUniform("pointLightsCount", pointLightsCount);
    }
}