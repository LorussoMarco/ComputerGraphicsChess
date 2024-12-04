#include "Camera.h"


/**
 * @brief Costruttore della classe Camera.
 *
 * Questo costruttore inizializza una nuova istanza di `Camera` con i valori di default per
 * il campo visivo, i piani di clipping e la dimensione della finestra. Il costruttore
 * inizializza anche lo stato attivo della telecamera su `false`.
 *
 * - Campo visivo (fov): 90.0 gradi.
 * - Near clipping: 0.01.
 * - Far clipping: 1000.0.
 * - Dimensione della finestra: 0 x 0.
 * - Stato attivo: false.
 *
 * @param type Il tipo di questo nodo, passato al costruttore della classe base `Node`.
 */
Camera::Camera(const std::string& type)
    : Node{ type }
{
    this->setFov(90.0f);
    this->setNearClipping(0.01f);
    this->setFarClipping(1000.0f);
    this->_isActive = false;
    this->setWindowSize(0, 0);
    this->setPriority(2);
}

///// Getter

/**
 * @brief Calcola la matrice inversa della camera.
 *
 * @return `glm::mat4` La matrice inversa della matrice della camera.
 */
glm::mat4 LIB_API Camera::getInverseMatrix()
{
    glm::mat4 inverse = glm::inverse(getLocalMatrix());
    return inverse;
}

///// Setter

/**
 * @brief Imposta la dimensione del frame della telecamera.
 *
 * @param newWidth La larghezza del frame in pixel.
 * @param newHeight L'altezza del frame in pixel.
 */
void LIB_API Camera::setWindowSize(const int newWidth, const int newHeight)
{
    this->_windowWidth = newWidth;
    this->_windowHeight = newHeight;
}

/**
 * @brief Imposta il Campo Visivo (FOV) della camera.
 *
 * @param newFov Il nuovo valore del FOV in gradi.
 */
void LIB_API Camera::setFov(const float newFov)
{
    this->_fov = newFov;
}

/**
 * @brief Imposta il valore near clipping della camera.
 *
 * @param newNearClipping Il nuovo valore di clipping vicino.
 */
void LIB_API Camera::setNearClipping(const float newNearClipping) {
    this->_nearClipping = newNearClipping;
}

/**
 * @brief Imposta il valore di far clipping della camera.
 *
 * @param newFarClipping Il nuovo valore di clipping lontano.
 */
void LIB_API Camera::setFarClipping(const float newFarClipping) {
    this->_farClipping = newFarClipping;
}

/**
 * @brief Imposta lo stato attivo della camera.
 *
 * @param newIsActive Il nuovo stato della camera. `true` per attivare, `false` per disattivare.
 */
void LIB_API Camera::setActive(const bool newIsActive)
{
    this->_isActive = newIsActive;
}

