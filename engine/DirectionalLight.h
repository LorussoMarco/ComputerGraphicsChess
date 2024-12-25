#pragma once

#include "Light.h"
#include "Common.h"

/**
 * @class DirectionalLight
 * @brief Rappresenta una luce direzionale.
 *
 * Una luce direzionale proviene da una distanza infinita con una direzione.
 * Esempio: il sole. Questa luce emette raggi paralleli da una direzione specifica,
 * simile ai raggi solari sulla Terra.
 */
class LIB_API DirectionalLight : public Light
{

public:

    DirectionalLight();

    // Setter
    void setDirection(const glm::vec3 newDirection);

    void render(const glm::mat4 viewMatrix) const override;

private:

    glm::vec3 _direction; ///< Direzione della luce
};
