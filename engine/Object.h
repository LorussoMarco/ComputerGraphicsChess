#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Object {
public:
    Object();
    virtual ~Object();

    void setPosition(float x, float y, float z);
    void setRotation(float angle, float x, float y, float z);
    void setScale(float x, float y, float z);

    glm::mat4 getModelMatrix() const;

protected:
    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotationAngle;
    glm::vec3 scale;
};
