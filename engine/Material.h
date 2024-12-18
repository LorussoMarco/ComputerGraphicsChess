#pragma once

#include <memory>

#include "Object.h"
#include "Texture.h"
#include "Common.h"

/**
 * @class Material
 * @brief Rappresenta un materiale che conferisce colore e texture alle mesh.
 *
 * La classe `Material` gestisce gli attributi visivi di un materiale, come il colore di emissione,
 * il colore ambientale, il colore diffuso e il colore speculare. Inoltre, supporta la definizione
 * della lucentezza, del valore alpha e dell'applicazione di una texture.
 *
 * Un materiale viene apllicato a una mesh per determinare come essa interagisce con la luce
 * e come viene visualizzata nella scena.
 */
class LIB_API Material : public Object
{
public:

    Material();

    // Getter
    glm::vec3 getEmissionColor() const;

    // Setter
    void setEmissionColor(const glm::vec3 newColor);
    void setAmbientColor(const glm::vec3 newColor);
    void setDiffuseColor(const glm::vec3 newColor);
    void setSpecularColor(const glm::vec3 newColor);
    void setShininess(const float newShininess);
    void setAlpha(const float newAlpha);
    void setTexture(const std::shared_ptr<Texture> newTexture);

    void render(const glm::mat4 viewMatrix) const override;

private:

    glm::vec3 _emissionColor; ///< Colore che il materiale emette come se fosse una luce propria.
    glm::vec3 _ambientColor; ///< Colore che il materiale riflette dalla luce ambientale.
    glm::vec3 _diffuseColor; ///< Colore visibile del materiale quando colpito dalla luce diretta.
    glm::vec3 _specularColor; ///< Colore dei riflessi lucidi e brillanti sulla superficie del materiale.
    float _shininess; ///< Misura di quanto il materiale e lucido;
    float _alpha; ///< Valore alpha del materiale (trasparenza)
    std::shared_ptr<Texture> _texture; ///< texture applicata sul materiale
};
