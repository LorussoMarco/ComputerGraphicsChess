#include "SpotLight.h"

#include <GL/freeglut.h>

#include "glm/ext.hpp"


/**
 * Costruttore della classe `SpotLight`.
 *
 * Crea una nuova istanza di `SpotLight` con i seguenti parametri di default:
 *
 * - Direzione: (0.0f, 1.0f, 0.0f) (Verso l'alto)
 * - Angolo di cutoff: 45.0f gradi definisce la larghezza del cono. (angolo tra 0 e 90   )
 * - Esponente: 8.0f -> 0.0f (senza attenuazione) - 128.0f (attenuazione massima)
 * - Raggio: 1.0f -> determina la distanza alla quale la luce ha effetto.
 *
 */
SpotLight::SpotLight()
    : Light{ "SpotLight" }
{
    this->setDirection(glm::vec3(0.0f, 1.0f, 0.0f));
    this->setCutoff(45.0f);
    this->setExponent(8.0f);
    this->setRadius(1.0f);
}

///// Setter

/**
 * Imposta l'angolo di cutoff per questa spotLight.
 *
 * @param newCutoff Il nuovo valore di cutoff per questa luce spot.
 */
void LIB_API SpotLight::setCutoff(const float newCutoff)
{
    this->_cutoff = newCutoff;
}

/**
 * Imposta il raggio della spotLight. Questo valore definisce la distanza alla quale la luce ha effetto.
 *
 * @param newRadius Il nuovo raggio per questa luce spot.
 */
void LIB_API SpotLight::setRadius(const float newRadius)
{
    this->_radius = newRadius;
}

/**
 * Imposta l'esponente della spotLight.
 *
 * @param newExponent Il nuovo esponente per questa spotLight.
 */
void LIB_API SpotLight::setExponent(const float newExponent)
{
    this->_exponent = newExponent;
}

/**
 * Cambia la direzione verso cui la luce viene puntata.
 *
 * @param newDirection La nuova direzione della luce.
 */
void LIB_API SpotLight::setDirection(const glm::vec3 newDirection)
{
    this->_direction = newDirection;
}

///// Render spotLight

/**
 * Renderizza la luce spot.
 *
 * Questa funzione viene chiamata automaticamente da MyEngine e non bisogna chiamarla manualmente.
 *
 * @param viewMatrix La matrice di vista da utilizzare per il rendering di questo oggetto.
 */
void LIB_API SpotLight::render(const glm::mat4 viewMatrix) const
{

    Node::render(viewMatrix);

    // Abilita la sorgente di luce specificata dall'ID corrente.
    glEnable(GL_LIGHT0 + this->_lightId);


    // Rappresenta il punto dal quale la luce proviene.
    const glm::vec4 lightPosition(this->_direction, 1.0f);

    // Imposta la direzione del cono di luce. La direzione del cono viene inclinata leggermente verso il basso.
    const glm::vec3 lightDirection(0.0f, -0.1f, 0.0f);

    const glm::vec4 ambient(this->_ambientColor, 1.0f);
    const glm::vec4 diffuse(this->_diffuseColor, 1.0f);
    const glm::vec4 specular(this->_specularColor, 1.0f);

    // Calcola l'attenuazione costante della luce in base al raggio.
    // Se e _radius     piccolo, la luce si attenua pi    rapidamente con la distanza.
    const float constantAttenuation = 1.0f / (this->_radius/100);

    const int currentLight = Light::getCurrentLight(this->_lightId);

    glLightfv(currentLight, GL_POSITION, glm::value_ptr(lightPosition));
    glLightfv(currentLight, GL_SPOT_DIRECTION, glm::value_ptr(lightDirection));
    glLightfv(currentLight, GL_AMBIENT, glm::value_ptr(ambient));
    glLightfv(currentLight, GL_DIFFUSE, glm::value_ptr(diffuse));
    glLightfv(currentLight, GL_SPECULAR, glm::value_ptr(specular));
    glLightfv(currentLight, GL_SPOT_CUTOFF, &this->_cutoff);
    glLightf(currentLight, GL_CONSTANT_ATTENUATION, constantAttenuation);
    glLightf(currentLight, GL_SPOT_EXPONENT, this->_exponent);
}
