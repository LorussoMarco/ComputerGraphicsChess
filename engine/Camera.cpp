#include "Camera.h"


// Costruttore
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

// Getter per il campo visivo
float Camera::getFov() const {
    return this->_fov;
}

// Getter per il piano di clipping vicino
float Camera::getNearClipping() const {
    return this->_nearClipping;
}

// Getter per il piano di clipping lontano
float Camera::getFarClipping() const {
    return this->_farClipping;
}

// Getter per la larghezza della finestra
int Camera::getWindowWidth() const {
    return this->_windowWidth;
}

// Getter per l'altezza della finestra
int Camera::getWindowHeight() const {
    return this->_windowHeight;
}

// Getter per lo stato attivo della camera
bool Camera::isActive() const {
    return this->_isActive;
}

// Calcola la matrice inversa della camera
glm::mat4 Camera::getInverseMatrix() {
    return glm::inverse(getLocalMatrix());
}

// Setter per il piano di clipping vicino
void Camera::setNearClipping(const float newNearClipping) {
    this->_nearClipping = newNearClipping;
}

// Setter per il piano di clipping lontano
void Camera::setFarClipping(const float newFarClipping) {
    this->_farClipping = newFarClipping;
}

// Setter per la dimensione della finestra
void Camera::setWindowSize(const int newWidth, const int newHeight) {
    this->_windowWidth = newWidth;
    this->_windowHeight = newHeight;
}

// Setter per il campo visivo
void Camera::setFov(const float newFov) {
    this->_fov = newFov;
}

// Setter per lo stato attivo
void Camera::setActive(const bool newIsActive) {
    this->_isActive = newIsActive;
}
