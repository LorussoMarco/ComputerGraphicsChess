#include "Object.h"

Object::Object() : position(0.0f), rotationAxis(0.0f, 1.0f, 0.0f), rotationAngle(0.0f), scale(1.0f) {}

Object::~Object() {}

void Object::setPosition(float x, float y, float z) {
    position = glm::vec3(x, y, z);
}

void Object::setRotation(float angle, float x, float y, float z) {
    rotationAngle = angle;
    rotationAxis = glm::vec3(x, y, z);
}

void Object::setScale(float x, float y, float z) {
    scale = glm::vec3(x, y, z);
}

glm::mat4 Object::getModelMatrix() const {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis);
    model = glm::scale(model, scale);
    return model;
}
