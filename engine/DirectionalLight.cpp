#include "DirectionalLight.h"

#include <GL/freeglut.h>

#include <glm/gtc/type_ptr.hpp>

/**
 * Costruttore della classe DirectionalLight.
 *
 * Crea una nuova istanza di DirectionalLight con i seguenti parametri di default:
 * Direzione: 0.0f, 1.0f, 0.0f (Verso l'alto), parallela alla direzione indicata.
 *
 * Nota: La direzione predefinita indica che la luce     orientata verso l'alto lungo l'asse Y,
 * il che simula l'effetto di una luce ambientale proveniente dall'alto, come il sole.
 */
DirectionalLight::DirectionalLight()
    : Light{ "DirectionalLight" }
{
    this->setDirection(glm::vec3(0.0f, 1.0f, 0.0f));
}

///// Setter

/**
 * Modifica la direzione verso cui la luce viene puntata.
 *
 * @param new_direction Il nuovo vettore di direzione per la luce.
 */
void LIB_API DirectionalLight::setDirection(const glm::vec3 newDirection)
{
    this->_direction = newDirection;
}

// Render DirectionalLight

/**
 * Renderizza la luce direzionale.
 *
 * Questa funzione viene chiamata automaticamente da MyEngine e non bisogna chiamarla manualmente.
 *
 * @param viewMatrix La matrice di vista da utilizzare per il rendering dell'oggetto.
 *
 * Dettagli:
 * - Chiama il metodo `render` della classe base `Node` per gestire le operazioni di rendering di base.
 * - Abilita la sorgente di luce specificata dall'ID della luce (`this->_lightId`).
 * - Imposta la posizione della luce come un vettore 4D (0.0f, 1.0f, 0.0f, 0.0f), dove il valore 0.0f nella componente w indica che la luce     direzionale.
 */
void LIB_API DirectionalLight::render(const glm::mat4 viewMatrix) const
{

    Node::render(viewMatrix);

    // Abilita la sorgente di luce specificata dall'ID this->light_id.
    glEnable(GL_LIGHT0 + this->_lightId);

    // Definisce la posizione della luce come un vettore a 4 componenti, dove il quarto valore     0.0f, 
    // indicando una luce direzionale
    // perch    /w da infinito -> distanza infinita
    const glm::vec4 lightPosition(0.0f, 1.0f, 0.0f, 0.0f);

    const glm::vec4 ambient(this->_ambientColor, 1.0f);
    const glm::vec4 diffuse(this->_diffuseColor, 1.0f);
    const glm::vec4 specular(this->_specularColor, 1.0f);

    const int currentLight = Light::getCurrentLight(this->_lightId);

    glLightfv(currentLight, GL_POSITION, glm::value_ptr(lightPosition));
    glLightfv(currentLight, GL_AMBIENT, glm::value_ptr(ambient));
    glLightfv(currentLight, GL_DIFFUSE, glm::value_ptr(diffuse));
    glLightfv(currentLight, GL_SPECULAR, glm::value_ptr(specular));

}
