#pragma once
#include "Node.h"

class Object : public Node {
public:
    Object();
    ~Object();

    void draw(const glm::mat4& parentTransform) override;

private:
    void renderCube();
};
