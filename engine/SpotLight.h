#pragma once

#include "Common.h"
#include "Light.h"

/**
 * @class SpotLight
 * @brief Rappresenta una spotLight.
 *
 * Una spotLight emette luce a forma di cono con un angolo e una distanza specifici.
 *
 * @details
 * La spotLight     una sorgente di luce che proietta un fascio di luce a forma di cono.
 *
 */
class LIB_API SpotLight : public Light
{
public:
    SpotLight();

    // Setter
    void setCutoff(const float newCutoff);
    void setRadius(const float newRadius);
    void setExponent(const float newExponent);
    void setDirection(const glm::vec3 newDirection);

    void render(const glm::mat4 viewMatrix) const override;

private:

    float _cutoff; ///<  Determina l'angolo del cono di luce. Maggiore     il valore, pi    ampio     il cono.
    float _radius; ///< Definisce la distanza alla quale la luce ha effetto. 

    // Un valore pi    alto rende il cono pi    stretto e concentrato.
    float _exponent; ///< Determina quanto il cono di luce     concentrato.
    glm::vec3 _direction; ///< Direzione della spotLight.
};
