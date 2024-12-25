#pragma once

#include "Common.h"
#include "Light.h"

/**
*  @class PointLight
 * @brief Rappresenta una sorgente di luce che emette luce in tutte le direzioni da una posizione specifica.
 *
 * Una pointLight emette luce in tutte le direzioni da una posizione specifica e ha un raggio limitato.
 * Questa luce si comporta come una sorgente di luce che irradia verso l'esterno in tutte le direzioni
 * da un punto di origine, simile a una candela.
 *
 * La luce puntiforme ha un effetto visibile fino a una certa distanza, chiamata raggio. Oltre questo raggio,
 * la luce si attenua e non influenza l'ambiente circostante.
 *
 */
class LIB_API PointLight : public Light
{
public:

    PointLight();

    // Setter
    void setRadius(const float newRadius);

    void render(const glm::mat4 viewMatrix) const override;


private:

    float _radius; ///< Distanza massima alla quale la luce ha un effetto visibile.
};

