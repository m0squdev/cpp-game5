#include "material.h"

GLfloat Material::currentSpecularIntensity, Material::currentSpecularShininess, Material::currentSpecularR, Material::currentSpecularG, Material::currentSpecularB;

void Material::Set(GLfloat shininess, GLfloat intensity, GLfloat r, GLfloat g, GLfloat b)
{
    currentSpecularShininess = shininess;
    currentSpecularIntensity = intensity;
    currentSpecularR = r;
    currentSpecularG = g;
    currentSpecularB = b;
    Prog::SetUniform("material.specularShininess", currentSpecularShininess);
    Prog::SetUniform("material.specularIntensity", currentSpecularIntensity);
    Prog::SetUniform("material.specularColor", glm::vec3(currentSpecularR, currentSpecularG, currentSpecularB));
}