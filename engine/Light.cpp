#include "Light.h"

#include <GL/freeglut.h>

// Tiene traccia del prossimo ID da assegnare a una nuova luce.
int Light::nextLightId = 0;

// Ambient: Senza le aree non illuminate sarebbero sempre nere
// Diffuse: Una volta che colpisce una superficie si disperde uniformemente
// Specular: Lucentezza


 /**
  * Costruttore della classe Light.
  *
  * Crea una nuova istanza di luce con i segeuenti parametri di default:
  * id: autogenerato
  * Ambient color: 0.0f, 0.0f, 0.0f (Black)
  * Diffuse color: 1.0f, 1.0f, 1.0f (White)
  * Specular color: 1.0f, 1.0f, 1.0f (White)
  *
  * Nota: La luce viene attivata automaticamente quando viene inizializzata
  *
  * @param type Il tipo della luce, passato al costruttore della classe base `Node`.
  */
Light::Light(const std::string& type)
    : Node{ type }
{
    this->setPriority(1);

    int maxNumberOfLights;

    // Ottiene il numero massimo di luci supportate dalla GPU e memorizzate in maxNumberOfLights
    glGetIntegerv(GL_MAX_LIGHTS, &maxNumberOfLights);

    // Assegna un ID alla luce corrente 
    this->_lightId = Light::nextLightId;
    std::cout << "This light: " << this->_lightId << std::endl;

    // Se supero il numero massimo di luci
    if (this->_lightId > maxNumberOfLights)
    {
        WARNING("Maximum number of lights exceeded: (" << maxNumberOfLights << ").");
        return;
    }
    const int currentLight = getCurrentLight(this->_lightId);

    // nero // luce ambientale assente
    this->setAmbientColor(glm::vec3(0.0f, 0.0f, 0.0f));

    // bianco -> la luce diffusa si distribuisce uniformemente in tutte le direzioni.
    this->setDiffuseColor(glm::vec3(1.0f, 1.0f, 1.0f));

    // bianco // riflessi brillanti sulle superfici
    this->setSpecularColor(glm::vec3(1.0f, 1.0f, 1.0f));

    Light::nextLightId++;
}

// Getter 

/**
 * Restituisce il numero della luce in base all'ID della luce.
 *
 * Questa funzione calcola la costante di OpenGL per una determinata luce basata sul suo ID.
 * OpenGL utilizza una serie di costanti predefinite per le sorgenti luminose, partendo da `GL_LIGHT0`.
 * La costante `GL_LIGHT0` corrisponde alla prima sorgente di luce in OpenGL, e le sorgenti luminose successive
 * sono rappresentate incrementando questa costante.
 * 0x4000 valore di GL_LIGHT0
 *
 * @param lightId L'ID della luce, utilizzato per determinare quale costante di OpenGL restituire.
 * @return La costante di OpenGL corrispondente all'ID della luce. 0x4000 + id
 */
int LIB_API Light::getCurrentLight(const int lightId) const
{
    return GL_LIGHT0 + lightId;
}

// Setter

/**
 * Modifica il colore ambientale di questa luce.
 *
 * @param newColor Il nuovo colore ambientale della luce.
 */
void LIB_API Light::setAmbientColor(const glm::vec3 newColor)
{
    this->_ambientColor = newColor;
}

/**
 * Modifica il colore diffuso di questa luce.
 *
 * @param newColor Il nuovo colore diffuso della luce.
 */
void LIB_API Light::setDiffuseColor(const glm::vec3 newColor)
{
    this->_diffuseColor = newColor;
}

/**
 * Modifica il colore speculare di questa luce.
 *
 * @param newColor Il nuovo colore speculare della luce.
 */
void LIB_API Light::setSpecularColor(const glm::vec3 newColor)
{
    this->_specularColor = newColor;
}


///// Other

/**
 * Resetta l'ID della prossima luce a 0.
 *
 * Questo metodo statico viene utilizzato per ripristinare l'ID
 * della prossima luce a 0.
 */
void LIB_API Light::resetNextLightId() {
    Light::nextLightId = 0;
}
