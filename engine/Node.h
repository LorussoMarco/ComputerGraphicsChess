#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>

class Node {
public:
    Node();
    virtual ~Node();

    // Trasformazioni
    void setPosition(float x, float y, float z);
    void setScale(float x, float y, float z);
    void addChild(std::shared_ptr<Node> child);
    void removeChild(std::shared_ptr<Node> child);

    // Disegno
    virtual void draw(const glm::mat4& parentTransform);

protected:
    glm::vec3 position;
    glm::vec3 scale;
    glm::mat4 modelMatrix;
    std::vector<std::shared_ptr<Node>> children;

    void updateModelMatrix();
};
