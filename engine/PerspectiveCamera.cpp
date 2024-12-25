#include "PerspectiveCamera.h"

#include <GL/freeglut.h>

#include <glm/gtc/type_ptr.hpp>

/**
 * @brief Costruttore della telecamera prospettica.
 */
PerspectiveCamera::PerspectiveCamera()
    : Camera{ "PerspectiveCamera" }
{}

///// Render PerspectiveCamera

/**
 * Renderizza la scena utilizzando una proiezione prospettica.
 *
 * Questa funzione viene chiamata automaticamente da MyEngine e non bisogna chiamarla manualmente.
 *
 * @param viewMatrix La matrice di view da usare per il rendering di questo oggetto.
 */
void LIB_API PerspectiveCamera::render(const glm::mat4 viewMatrix) const
{
    // Verifica se la telecamera     attiva
    if (!this->_isActive)
        return;

    Node::render(viewMatrix);

    // (width / height) serve a mantenere le proporzioni corrette dell'immagine visualizzata dalla camera.
    const float aspectRatio = static_cast<float>(this->_windowWidth) / static_cast<float>(this->_windowHeight);

    const glm::mat4 perspective_matrix = glm::perspective(glm::radians(this->_fov), aspectRatio, this->_nearClipping, this->_farClipping);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(perspective_matrix));
}

