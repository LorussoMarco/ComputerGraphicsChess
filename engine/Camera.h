#pragma once

#include "Node.h"
#include "Common.h"

/**
 * @class Camera
 * @brief Funge da base da cui ereditare per implementare le camere nella scena.
 */
class LIB_API Camera : public Node
{

public:

    Camera(const std::string& type);

    // Getter
    glm::mat4 getInverseMatrix();

    // Setter 
    void setNearClipping(const float newNearClipping);
    void setFarClipping(const float newFarClipping);
    void setWindowSize(const int newWidth, const int newHeight);
    void setFov(const float newFov);
    void setActive(const bool newIsActive);

protected:

    float _fov;             ///< Campo visivo della camera
    float _nearClipping;    ///< Distanza del piano di clipping vicino
    float _farClipping;     ///< Distanza del piano di clipping lontano
    int _windowWidth;       ///< Larghezza della finestra della camera
    int _windowHeight;      ///< Altezza della finestra della camera
    bool _isActive;         ///< Indica se la camera e' attiva
};
