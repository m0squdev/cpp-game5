#include "light.h"

GLfloat Light::currentAmbientIntensity, Light::currentAmbientR, Light::currentAmbientG, Light::currentAmbientB;
GLfloat Light::currentDiffuseIntensity, Light::currentDiffuseR, Light::currentDiffuseG, Light::currentDiffuseB, Light::currentDiffuseX, Light::currentDiffuseY, Light::currentDiffuseZ;
GLfloat Light::currentPointR, Light::currentPointG, Light::currentPointB, Light::currentPointX, Light::currentPointY, Light::currentPointZ, Light::currentPointConstant, Light::currentPointLinear, Light::currentPointExponent;
int Light::pointLightsCount = 0;
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
    Prog::SetUniform("directionalLight.base.ambientIntensity", currentAmbientIntensity);
    Prog::SetUniform("directionalLight.base.ambientColor", glm::vec3(currentAmbientR, currentAmbientG, currentAmbientB));
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
    Prog::SetUniform("directionalLight.direction", glm::vec3(currentDiffuseX, currentDiffuseY, currentDiffuseZ));
    Prog::SetUniform("directionalLight.base.diffuseIntensity", currentDiffuseIntensity);
    Prog::SetUniform("directionalLight.base.diffuseColor", glm::vec3(currentAmbientR, currentAmbientG, currentAmbientB));
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
    pointLights[pointLightsCount].constant = constant;
    pointLights[pointLightsCount].linear = linear;
    pointLights[pointLightsCount].exponent = exponent;
    pointLights[pointLightsCount].x = x;
    pointLights[pointLightsCount].y = y;
    pointLights[pointLightsCount].z = z;
    pointLights[pointLightsCount].r = r;
    pointLights[pointLightsCount].g = g;
    pointLights[pointLightsCount].b = b;
    /*char char_n[2];
    info("1");
    std::sprintf(char_n, "%d", 0);
    info(char_n);
    char* prefix = (char*)calloc(sizeof(char),128);
    strcat(prefix, "pointLights[");
    strcat(prefix, char_n);
    strcat(prefix, "].");
    //char* prefix = catStr(catStr("pointLights[", char_n), "].");
    info("2");
    char* aux = (char*)calloc(sizeof(char),128);
    catStr(aux, (const char*)prefix, "base.ambientIntensity");
    Prog::SetUniform(aux, currentAmbientIntensity);
    catStr(aux, (const char*)prefix, "base.ambientColor");
    Prog::SetUniform(aux, glm::vec3(currentAmbientR, currentAmbientG, currentAmbientB));
    catStr(aux, (const char*)prefix, "base.diffuseIntensity");
    Prog::SetUniform(aux, currentDiffuseIntensity);
    catStr(aux, (const char*)prefix, "base.diffuseColor");
    Prog::SetUniform(aux, glm::vec3(currentAmbientR, currentAmbientG, currentAmbientB));
    catStr(aux,(const char*)prefix, "constant");
    Prog::SetUniform(aux, pointLights[0].constant);
    catStr(aux,(const char*)prefix, "linear");
    Prog::SetUniform(aux, pointLights[0].linear);
    catStr(aux,(const char*)prefix, "exponent");
    Prog::SetUniform(aux, pointLights[0].exponent);
    catStr(aux,(const char*)prefix, "pos");
    Prog::SetUniform(aux, glm::vec3(pointLights[0].x, pointLights[0].y, pointLights[0].z));
    catStr(aux,(const char*)prefix, "color");
    Prog::SetUniform(aux, glm::vec3(pointLights[0].r, pointLights[0].g, pointLights[0].b));
    Prog::SetUniform("pointLightsCount", pointLightsCount);
    free(aux);
    free(prefix);*/
    pointLightsCount++;
    /*Prog::SetUniform("constant", currentPointConstant);
    Prog::SetUniform("linear", currentPointLinear);
    Prog::SetUniform("exponent", currentPointExponent);
    Prog::SetUniform("pos", glm::vec3(currentPointX, currentPointY, currentPointZ));
    Prog::SetUniform("color", glm::vec3(currentPointR, currentPointG, currentPointB));
    Prog::SetUniform("pointLightsCount", pointLightsCount);*/
}

void Light::SetPoints()
{
    if (pointLightsCount)
    {
        for (int n = 0; n < pointLightsCount; n++)
        {
            char char_n[2];
            std::sprintf(char_n, "%d", n);
            info(char_n);
            char* prefix = (char*)calloc(sizeof(char),128);
            strcat(prefix, "pointLights[");
            strcat(prefix, char_n);
            strcat(prefix, "].");
            //char* prefix = catStr(catStr("pointLights[", char_n), "].");
            char* aux = (char*)calloc(sizeof(char),128);
            catStr(aux, (const char*)prefix, "base.ambientIntensity");
            Prog::SetUniform(aux, currentAmbientIntensity);
            catStr(aux, (const char*)prefix, "base.ambientColor");
            Prog::SetUniform(aux, glm::vec3(currentAmbientR, currentAmbientG, currentAmbientB));
            catStr(aux, (const char*)prefix, "base.diffuseIntensity");
            Prog::SetUniform(aux, currentDiffuseIntensity);
            catStr(aux, (const char*)prefix, "base.diffuseColor");
            Prog::SetUniform(aux, glm::vec3(currentAmbientR, currentAmbientG, currentAmbientB));
            catStr(aux,(const char*)prefix, "constant");
            Prog::SetUniform(aux, pointLights[n].constant);
            catStr(aux,(const char*)prefix, "linear");
            Prog::SetUniform(aux, pointLights[n].linear);
            catStr(aux,(const char*)prefix, "exponent");
            Prog::SetUniform(aux, pointLights[n].exponent);
            catStr(aux,(const char*)prefix, "pos");
            Prog::SetUniform(aux, glm::vec3(pointLights[n].x, pointLights[n].y, pointLights[n].z));
            catStr(aux,(const char*)prefix, "color");
            Prog::SetUniform(aux, glm::vec3(pointLights[n].r, pointLights[n].g, pointLights[n].b));
            Prog::SetUniform("pointLightsCount", pointLightsCount);
            free(aux);
            free(prefix);
        }
    }
    else
        warn("No point light had been created. Create one with Light::CreatePoint");
}