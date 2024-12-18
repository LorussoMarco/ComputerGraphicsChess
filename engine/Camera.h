#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include "Node.h"
#include "Common.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_inverse.hpp>

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
    float getFov() const;
    float getNearClipping() const;
    float getFarClipping() const;
    int getWindowWidth() const;
    int getWindowHeight() const;
    bool isActive() const;

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
    bool _isActive;         ///< Indica se la camera è attiva
};
