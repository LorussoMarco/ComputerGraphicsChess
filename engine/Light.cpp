#include "Light.h"

#include <GL/freeglut.h>
#include <iostream>

// Tiene traccia del prossimo ID da assegnare a una nuova luce.
int Light::nextLightId = 0;

Light::Light(const std::string& type)
    : Node{ type }
{
    this->setPriority(1);

    int maxNumberOfLights;
    glGetIntegerv(GL_MAX_LIGHTS, &maxNumberOfLights);

    this->_lightId = Light::nextLightId;
    std::cout << "This light: " << this->_lightId << std::endl;

    if (this->_lightId > maxNumberOfLights)
    {
        WARNING("Maximum number of lights exceeded: (" << maxNumberOfLights << ").");
        return;
    }

    this->setAmbientColor(glm::vec3(0.0f, 0.0f, 0.0f));
    this->setDiffuseColor(glm::vec3(1.0f, 1.0f, 1.0f));
    this->setSpecularColor(glm::vec3(1.0f, 1.0f, 1.0f));

    Light::nextLightId++;
}

// Getter per il numero della luce
int LIB_API Light::getCurrentLight(const int lightId) const
{
    return GL_LIGHT0 + lightId;
}

// Getter per il colore ambientale
glm::vec3 LIB_API Light::getAmbientColor() const
{
    return _ambientColor;
}

// Getter per il colore diffuso
glm::vec3 LIB_API Light::getDiffuseColor() const
{
    return _diffuseColor;
}

// Getter per il colore speculare
glm::vec3 LIB_API Light::getSpecularColor() const
{
    return _specularColor;
}

// Setter per i colori
void LIB_API Light::setAmbientColor(const glm::vec3 newColor)
{
    this->_ambientColor = newColor;
}

void LIB_API Light::setDiffuseColor(const glm::vec3 newColor)
{
    this->_diffuseColor = newColor;
}

void LIB_API Light::setSpecularColor(const glm::vec3 newColor)
{
    this->_specularColor = newColor;
}

// Resetta l'ID della prossima luce
void LIB_API Light::resetNextLightId() {
    Light::nextLightId = 0;
}
