#include "PointLight.h"

#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>

/**
 * Costruttore della classe PointLight.
 *
 * Crea una nuova istanza di PointLight con i seguenti parametri di default:
 * - Raggio: 1.0f
 *
 * La luce puntiforme emette luce in tutte le direzioni
 * da una posizione specifica con un effetto visibile fino a una distanza definita dal raggio.
 */
PointLight::PointLight()
    : Light{ "PointLight" }
{
    this->setRadius(1.0f);
}

///// Setter

/**
 * Imposta il raggio della luce pointLigth.
 *
 * Il raggio determina la distanza massima fino alla quale la luce ha effetto.
 * Maggiore il raggio, piu estesa sara l'area illuminata dalla luce.
 *
 * @param new_radius Il nuovo raggio della pointLigth.
 */
void LIB_API PointLight::setRadius(const float newRadius)
{
    this->_radius = newRadius;
}

// Render pointLight

/**
 * Renderizza la luce puntiforme.
 *
 * Questa funzione e chiamata automaticamente da MyEngine e non e necessario
 * chiamarla manualmente.
 *
 * @param viewMatrix La matrice di visualizzazione da utilizzare per renderizzare questo oggetto.
 */
void LIB_API PointLight::render(const glm::mat4 viewMatrix) const
{

    Node::render(viewMatrix);

    glEnable(GL_LIGHT0 + this->_lightId);

    // Definisce la posizione della luce come (0.0f, 0.0f, 0.0f) con una componente w di 1.0f,
    // che indica una pointLight.
    const glm::vec4 lightPosition(0.0f, 0.0f, 0.0f, 1.0f);

    const glm::vec4 ambient(this->_ambientColor, 1.0f);
    const glm::vec4 diffuse(this->_diffuseColor, 1.0f);
    const glm::vec4 specular(this->_specularColor, 1.0f);

    // Usato per dire a OpenGL che vogliamo una PointLight.
    float cutoff = 180.0f; // Valore speciale per una pointLight.

    // Calcola l'attenuazione costante della luce in base al suo raggio.
    // Questo valore determina quanto la luce diminuisce con la distanza dalla sorgente luminosa.
    const float constantAttenuation = 1.0f / this->_radius;

    const int currentLight = Light::getCurrentLight(this->_lightId);

    glLightfv(currentLight, GL_POSITION, glm::value_ptr(lightPosition));
    glLightfv(currentLight, GL_AMBIENT, glm::value_ptr(ambient));
    glLightfv(currentLight, GL_DIFFUSE, glm::value_ptr(diffuse));
    glLightfv(currentLight, GL_SPECULAR, glm::value_ptr(specular));
    glLightfv(currentLight, GL_SPOT_CUTOFF, &cutoff);
    glLightf(currentLight, GL_CONSTANT_ATTENUATION, constantAttenuation);
}
