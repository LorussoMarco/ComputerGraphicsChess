#include "Node.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Node::Node() : position(0.0f), scale(1.0f), modelMatrix(1.0f) {}

Node::~Node() {}

void Node::setPosition(float x, float y, float z) {
    position = glm::vec3(x, y, z);
    updateModelMatrix();
}

void Node::setScale(float x, float y, float z) {
    scale = glm::vec3(x, y, z);
    updateModelMatrix();
}

void Node::addChild(std::shared_ptr<Node> child) {
    children.push_back(child);
}

void Node::removeChild(std::shared_ptr<Node> child) {
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

void Node::updateModelMatrix() {
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::scale(modelMatrix, scale);
}

void Node::draw(const glm::mat4& parentTransform) {
    glm::mat4 globalTransform = parentTransform * modelMatrix;

    for (const auto& child : children) {
        child->draw(globalTransform);
    }
}
