#pragma once

#include "Common.h"
#include "Camera.h"

/**
 * @class PerspectiveCamera
 * @brief Rappresenta una camera con proiezione prospettica.
 *
 * Questa classe estende `Camera` e implementa una camera che renderizza la scena con un effetto di
 * prospettiva. A differenza della camera ortografica, la camera prospettica simula la
 * percezione visiva degli oggetti in base alla loro distanza dalla camera, creando un effetto
 * di profondit   . Gli oggetti lontani appaiono pi    piccoli rispetto a quelli vicini.
 */
class LIB_API PerspectiveCamera : public Camera
{
public:

    PerspectiveCamera();

    void render(const glm::mat4 viewMatrix) const override;
};
