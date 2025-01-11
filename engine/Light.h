#pragma once

#include "Node.h"
#include "Common.h"

/**
 * @class Light
 * @brief Funge da base per l'implementazione delle luci nella scena.
 *
 * Questa classe serve come base per derivare altre classi che implementano diversi tipi di luci
 * nella scena.
 *
 * Gli attributi principali inclusi sono i colori ambientale, diffuso e speculare della luce.
 */
class LIB_API Light : public Node
{
public:

    Light(const std::string& type);
    virtual ~Light();

    // Getter
    int getCurrentLight(const int lightId) const;
    glm::vec3 getAmbientColor() const;   ///< Restituisce il colore ambientale.
    glm::vec3 getDiffuseColor() const;   ///< Restituisce il colore diffuso.
    glm::vec3 getSpecularColor() const;  ///< Restituisce il colore speculare.

    // Setter
    void setAmbientColor(const glm::vec3 newColor);
    void setDiffuseColor(const glm::vec3 newColor);
    void setSpecularColor(const glm::vec3 newColor);

    static void resetNextLightId();

protected:

    static int nextLightId;  ///< ID della prossima luce disponibile.

    glm::vec3 _ambientColor;   ///< Colore ambientale della luce.
    glm::vec3 _diffuseColor;   ///< Colore diffuso della luce.
    glm::vec3 _specularColor;  ///< Colore speculare della luce.

    int _lightId;              ///< ID della luce corrente.
};
